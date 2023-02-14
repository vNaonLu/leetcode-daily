from threading import Thread, Lock
from typing import Callable
from functools import partial
import sys
import time
# prevent generating __pycache__
sys.dont_write_bytecode = True


class _PrintTool:
    __CMD_YPOS = 0

    BLACK = 30
    DARK_RED = 31
    DARK_GREEN = 32
    DARK_YELLOW = 33
    DARK_BLUE = 34
    DARK_MAGENTA = 35
    DARK_CYAN = 36
    DARK_WHITE = 37
    BRIGHT_BLACK = 90
    BRIGHT_RED = 91
    BRIGHT_GREEN = 92
    BRIGHT_YELLOW = 93
    BRIGHT_BLUE = 94
    BRIGHT_MAGENTA = 95
    BRIGHT_CYAN = 96
    WHITE = 97

    BOLD = 1 << 8
    VERBOSE = BRIGHT_BLACK
    HIGHTLIGHT = DARK_WHITE
    IMPORTANT = DARK_YELLOW | BOLD

    def reset(self):
        pass

    def __init__(self, *args):
        self.reset()
        self.__lock = Lock()
        self.__show_cursor = False

    def format(self, s: str, *args, flag: int = 0):
        modified = False
        s = f'{s}'.format(*args)
        if flag & (self.BOLD - 1):
            modified = True
            s = f'\033[{flag & (~self.BOLD)}m{s}'
        if flag & self.BOLD:
            modified = True
            s = f'\033[1m{s}'
        if modified:
            s += '\033[0m'
        return s

    def _getYPos(self):
        return self.__CMD_YPOS

    def _incYPos(self, inc: int):
        assert inc >= 0
        if self.__show_cursor and inc != 0:
            print(f'[{self.__CMD_YPOS}] ', end="")
        _PrintTool.__CMD_YPOS += inc

    def clear(self):
        with self.__lock:
            print("\033[F\033[E\033[K", end="")

    def print(self, *args):
        with self.__lock:
            self._incYPos(sum((x.count('\n') if isinstance(
                x, str) else 0 for x in args)))
            print(*args, end="")

    def oneline(self, *args):
        with self.__lock:
            self._incYPos(sum((x.count('\n') if isinstance(
                x, str) else 0 for x in args)) + 1)
            print(*args, end="\n")

    def _printAt(self, pmt: str, y: int):
        with self.__lock:
            up = int(self._getYPos() - y)
            assert up >= 0
            print('\033[s', end='')
            if up > 0:
                print(f'\033[{up}A', end='')
            print(f"\r\033[K{pmt}\033[u", end="")

    def formatPrint(self, s: str, *args, flag: int = 0):
        self.print(self.format(s, *args, flag=flag))

    def formatOneline(self, s: str, *args, flag: int = 0):
        self.oneline(self.format(s, *args, flag=flag))

    def printWithSymbol(self, symbol: str, s: str, *args, flag: int = 0, symbol_flag: int = 0):
        self.formatPrint(f'{symbol} ', flag=symbol_flag)
        self.formatPrint(s, *args, flag=flag)

    def formatWithSymbol(self, symbol: str, s: str, *args, flag: int = 0, symbol_flag: int = 0):
        res = self.format(f'{symbol} ', flag=symbol_flag)
        res += self.format(s, *args, flag=flag)
        return res

    def _input(self, pmt: str):
        with self.__lock:
            res = input(pmt)
            self._incYPos(1)
            return res

class _PromptImpl(_PrintTool):
    __DEFAULT_DISPATCHER = {
        'y': lambda: True,
        'n': lambda: False
    }

    CASESENSITIVE = 1 << 9

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def ask(self, s: str, *args, dispatcher: dict[str, Callable] = __DEFAULT_DISPATCHER, flag: int = 0):
        opts = [k[0] for k in dispatcher.items()]
        opts_prompt = self.format("[{}]", ", ".join(opts), flag=self.VERBOSE)
        question = self.format(s, *args, flag=flag)
        while True:
          pmt = self.formatWithSymbol("[?]", f'{question} {opts_prompt} ',
                                      symbol_flag=self.DARK_YELLOW)
          ans = self._input(pmt)

          for kw, action in dispatcher.items():
              if kw == ans or (not (flag & self.CASESENSITIVE) and kw.lower() == ans.lower()):
                  return action()


class _LogImpl(_PrintTool):
    _DYNAMIC_DOT = [" ⠇ ", " ⠏ ", " ⠋ ", " ⠛ ", " ⠙ ", " ⠹ ", " ⠸ ", " ⠼ ", " ⠴ ", " ⠶ ", " ⠦ ", " ⠧ "]

    class ThreadArgs:
        def __init__(self) -> None:
            self.ypos = 0
            self.is_running = True
            self.begin = 0.0
            self.elapsed = 0.0
            self.msg = ""
            self.lock = Lock()

    def __init__(self, *args, verbose = False, **kwargs):
        super().__init__(*args, **kwargs)
        self.__verbose = verbose
        self._working_thread: dict[str, Thread] = {}
        self._threading_args: dict[str, _LogImpl.ThreadArgs] = {}

    def verbose(self, s: str, *args):
        if self.__verbose:
            self.printWithSymbol('   ', f'{s}\n', *args, flag=self.VERBOSE,
                                 symbol_flag=self.VERBOSE)

    def __successForm(self, s: str, *args, flag: int = 0):
        return self.formatWithSymbol('[+]', f'{s}', *args, flag=flag,
                                     symbol_flag=self.DARK_GREEN)

    def __failureForm(self, s: str, *args, flag: int = 0):
        return self.formatWithSymbol('[x]', f'{s}', *args, flag=flag,
                                     symbol_flag=self.DARK_RED)

    def success(self, s: str, *args, flag: int = 0):
        self.oneline(self.__successForm(s, *args, flag=flag))

    def failure(self, s: str, *args, flag: int = 0):
        self.oneline(self.__failureForm(s, *args, flag=flag))

    def __taskLogging(self, task_name: str, arg):
        it = 0
        if not isinstance(arg, _LogImpl.ThreadArgs):
            return

        # placeholder
        self.oneline()
        while arg.is_running:
            with arg.lock:
                msg = arg.msg
            arg.elapsed = time.time() - arg.begin
            cur_dot = self._DYNAMIC_DOT[it % len(self._DYNAMIC_DOT)]
            it += 1
            msg = ""
            timing = self.format(f'({arg.elapsed:.1f} s)', flag=self.VERBOSE)
            pmt = self.__taskMsgForm(task_name, msg)
            pmt = self.formatWithSymbol(cur_dot, f'{pmt} {timing}', symbol_flag=self.BRIGHT_BLUE)
            self._printAt(pmt, y=arg.ypos)
            time.sleep(1/30)

    def __taskMsgForm(self, task_name: str, msg: str, *args):
        return self.format(f'{task_name}: {msg}', *args)

    def beginTask(self, task_name: str):
        assert task_name not in self._working_thread
        assert task_name not in self._threading_args
        thread_args = _LogImpl.ThreadArgs()
        thread_args.ypos = self._getYPos()
        thread_args.begin = time.time()
        self._threading_args[task_name] = thread_args
        self._working_thread[task_name] = Thread(
            target=partial(self.__taskLogging, task_name, thread_args))
        self._working_thread[task_name].start()
        # sleep for not update prompt too fast
        time.sleep(0.1)

    def endTask(self, task_name: str, receive_msg: str, *args, is_success: bool):
        assert task_name in self._working_thread
        assert task_name in self._threading_args
        thread_args = self._threading_args[task_name]
        thread = self._working_thread[task_name]
        thread_args.is_running = False
        thread.join()
        timing = self.format('({:.1f} s)', thread_args.elapsed, flag=self.VERBOSE)
        pmt = self.__taskMsgForm(task_name, receive_msg, *args)

        if is_success:
            self._printAt(self.__successForm(f'{pmt} {timing}'), y=thread_args.ypos)
        else:
            self._printAt(self.__failureForm(f'{pmt} {timing}'), y=thread_args.ypos)



class Log:
    __impl: _LogImpl = None

    @staticmethod
    def getInstance(*args, verbose = False, **kwargs):
        if Log.__impl is None:
            Log.__impl = _LogImpl(*args, verbose=verbose, **kwargs)
        return Log.__impl


class Prompt:
    __impl: _PromptImpl = None

    @staticmethod
    def getInstance(*args, **kwargs):
        if Prompt.__impl is None:
            Prompt.__impl = _PromptImpl(*args, **kwargs)
        return Prompt.__impl


if __name__ == "__main__":
    LOG = Log.getInstance(verbose=True)
    PMT = Prompt.getInstance()
    LOG.print("this is \n")
    LOG.formatOneline("{}", "hightlight", flag=LOG.HIGHTLIGHT)

    LOG.print("this is ")
    LOG.formatOneline("{}", "red", flag=LOG.DARK_RED)
    LOG.verbose("this is verbose1")
    LOG.verbose("this is verbose2")
    LOG.verbose("this is verbose3")

    LOG.print("this should not appear")
    LOG.clear()
    LOG.success("Success Message!")
    LOG.failure("Failure Message!")
    LOG.failure("Failure With {} Message!", LOG.format(
        "Important", flag=LOG.IMPORTANT))
    
    task1 = "Test Task1"
    task2 = "Test Task2"
    LOG.beginTask(task1)
    LOG.beginTask(task2)
    
    while not PMT.ask("Stop task1?"):
        LOG.verbose("keep task1")
        pass
    
    LOG.endTask(task1, "end of {}", task1, is_success=True)

    while not PMT.ask("Stop task2?"):
        LOG.verbose("keep task2")
        pass
    LOG.endTask(task2, "end of {}", task2, is_success=False)
