from threading import Thread, Lock
from typing import Callable
import sys
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
        self.__show_cursor = True

    def format(self, s: str, *args, flag: int = 0):
        modified = False
        s = f'{s}'.format(*args)
        if flag != 0:
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
        if self.__show_cursor and inc > 0:
            print(f'[{self.__CMD_YPOS}] ', end="")
        _PrintTool.__CMD_YPOS += inc

    def clear(self):
        with self.__lock:
            print("\r\033[K", end="")

    def print(self, *args):
        with self.__lock:
            print(*args, end="")
            self._incYPos(sum((x.count('\n') if isinstance(
                x, str) else 0 for x in args)))

    def oneline(self, *args):
        with self.__lock:
            print(*args, end="\n")
            self._incYPos(sum((x.count('\n') if isinstance(
                x, str) else 0 for x in args)) + 1)

    def _printBefore(self, *args, cnt: int):
        with self.__lock:
            print(f'\033[{cnt}A', end="")
            print("\r\033[K", end="")
            print(*args, end="")
            down = sum((x.count('\n') if isinstance(
                x, str) else 0 for x in args))
            print(cnt, down, end='')
            if down < cnt:
                print(f'\r\033[{cnt-down}B', end="")


    def formatPrint(self, s: str, *args, flag: int = 0):
        self.print(self.format(s, *args, flag=flag))

    def formatOneline(self, s: str, *args, flag: int = 0):
        self.oneline(self.format(s, *args, flag=flag))

    def withSymbol(self, symbol: str, s: str, *args, flag: int = 0, symbol_flag: int = 0):
        self.formatPrint(f'{symbol} ', flag=symbol_flag)
        self.formatPrint(s, *args, flag=flag)

    def _input(self):
        with self.__lock:
            res = input()
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
          self.withSymbol("[?]", f'{question}? {opts_prompt} ',
                          symbol_flag=self.DARK_YELLOW)
          ans = self._input()

          for kw, action in dispatcher.items():
              if kw == ans or (not (flag & self.CASESENSITIVE) and kw.lower() == ans.lower()):
                  return action()


class _LogImpl(_PrintTool):
    _DYNAMIC_DOT = ["⠇", "⠏", "⠋", "⠛", "⠙", "⠹", "⠸", "⠼", "⠴", "⠶", "⠦", "⠧"]

    TASK_FAILED = 1 << 9

    def __init__(self, *args, verbose = False, **kwargs):
        super().__init__(*args, **kwargs)
        self.__verbose = verbose
        self._working_thread: dict[str, tuple[int, bool, Thread]] = None

    def verbose(self, s: str, *args):
        if self.__verbose:
            self.withSymbol('   ', f'{s}\n', *args, flag=self.VERBOSE,
                            symbol_flag=self.VERBOSE)

    def success(self, s: str, *args, flag: int = 0):
        self.withSymbol('[+]', f'{s}\n', *args, flag=flag,
                        symbol_flag=self.DARK_GREEN)

    def failure(self, s: str, *args, flag: int = 0):
        self.withSymbol('[-]', f'{s}\n', *args, flag=flag,
                        symbol_flag=self.DARK_RED)

    def __taskLogging(self, task_name: str, pending_msg: str, *args, thread_tuple:tuple[int, bool, Thread], flag: int = 0):
        pass

    def logTask(self, task_name: str, pending_msg: str, *args, flag: int = 0):
        assert task_name not in self._working_thread

    def endTask(self, task_name: str, receive_msg: str, *args, flag: int = 0):
        assert task_name in self._working_thread

    def TEST(self, s, cnt: int):
        self._printBefore(s, cnt=cnt)


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
    LOG = Log.getInstance(verbose=False)
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
    LOG.TEST("I rebase success message", 3)

    LOG.formatOneline(PMT.ask("Default Dispatcher"))
    LOG.formatOneline(PMT.ask("Default Dispatcher With Case Sensitive",
                              flag=PMT.CASESENSITIVE))

    def fun1():
      LOG.print("fun1")

    def fun2():
      LOG.print("fun2")

    def fun3():
      LOG.print("fun3")

    # PMT.ask('Which function you want to call', dispatcher={
    #         "fun1": fun1, "fun2": fun2, "fun3": fun3})
