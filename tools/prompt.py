#!/usr/bin/env python3
from threading import Thread, Lock
from typing import Callable
from functools import partial
import sys
import inspect
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
    HIGHTLIGHT = DARK_CYAN
    IMPORTANT = DARK_YELLOW | BOLD

    def reset(self):
        pass

    def __init__(self, *args):
        self.reset()
        self.__lock = Lock()
        self.__show_cursor = False

    def format(self, s: str, *args, flag: int = 0):
        modified = False
        if len(args) > 0:
            if len(args) > 0:
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

    def _clear(self):
        with self.__lock:
            print("\033[F\033[E\033[K", end="")

    def _print(self, *args):
        with self.__lock:
            self._incYPos(sum((x.count('\n') if isinstance(
                x, str) else 0 for x in args)))
            print(*args, end="")

    def _oneline(self, *args):
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

    def _formatPrint(self, s: str, *args, flag: int = 0):
        self._print(self.format(s, *args, flag=flag))

    def _formatOneline(self, s: str, *args, flag: int = 0):
        self._oneline(self.format(s, *args, flag=flag))

    def _printWithSymbol(self, symbol: str, s: str, *args, flag: int = 0, symbol_flag: int = 0):
        self._formatPrint(f'{symbol} ', flag=symbol_flag)
        self._formatPrint(s, *args, flag=flag)

    def _formatWithSymbol(self, symbol: str, s: str, *args, flag: int = 0, symbol_flag: int = 0):
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
          pmt = self._formatWithSymbol("[?]", f'{question} {opts_prompt} ',
                                       symbol_flag=self.DARK_YELLOW)
          ans = self._input(pmt)

          for kw, action in dispatcher.items():
              if kw == ans or (not (flag & self.CASESENSITIVE) and kw.lower() == ans.lower()):
                  return action()


class _LogImpl(_PrintTool):
    _DYNAMIC_DOT = [" ⠇ ", " ⠏ ", " ⠋ ", " ⠛ ", " ⠙ ",
                    " ⠹ ", " ⠸ ", " ⠼ ", " ⠴ ", " ⠶ ", " ⠦ ", " ⠧ "]

    class Task:
        def __init__(self, log, task_name: str) -> None:
            self.__log: _LogImpl = log
            self._ypos = 0
            self._is_running = False
            self._begin = 0.0
            self._elapsed = 0.0
            self._name = task_name
            self._msg = ""
            self._lock = Lock()
            self._thread = Thread(target=self.__taskLogging)

        def __taskLogging(self):
            it = 0
            LOG = self.__log
            while self._is_running:
                with self._lock:
                    msg = self._msg
                self._elapsed = time.time() - self._begin
                cur_dot = LOG._DYNAMIC_DOT[it % len(LOG._DYNAMIC_DOT)]
                it += 1
                timing = LOG.format(f'({self._elapsed:.1f} s)', flag=LOG.VERBOSE)
                pmt = LOG._taskMsgForm(self._name, msg)
                pmt = LOG._formatWithSymbol(cur_dot, f'{pmt} {timing}', symbol_flag=LOG.BRIGHT_BLUE)
                LOG._printAt(pmt, y=self._ypos)
                time.sleep(1/30)

        def log(self, msg: str, *arg):
            assert self._is_running
            with self._lock:
                self._msg = self.__log.format(msg, *arg)

        def begin(self, msg: str = "", *arg):
            assert not self._is_running
            with self._lock:
                self._msg = self.__log.format(msg, *arg)
            self._ypos = self.__log._getYPos()
            self._is_running = True
            self._begin = time.time()
            # placeholder
            self.__log._oneline()
            self._thread.start()
            # sleep for not update prompt too fast
            time.sleep(0.1)

        def end(self, msg: str = "", *arg, is_success: bool):
            assert self._is_running
            with self._lock:
                self._msg = self.__log.format(msg, *arg)
            self._is_running = False
            self._thread.join()
            self.__log._endTask(self._name, msg, *arg, is_success=is_success)

    def __init__(self, *args, verbose=False, **kwargs):
        super().__init__(*args, **kwargs)
        self.__verbose = verbose
        self._tasks_map: dict[str, _LogImpl.Task] = {}

    def verbose(self, s: str, *args):
        if self.__verbose:
            self._printWithSymbol('   ', f'{s}\n', *args, flag=self.VERBOSE,
                                  symbol_flag=self.VERBOSE)

    def funcVerbose(self, s: str, *args):
        self.verbose(f'[{inspect.stack()[1][3]}] {s}', *args)

    def __successForm(self, s: str, *args, flag: int = 0):
        return self._formatWithSymbol('[+]', f'{s}', *args, flag=flag,
                                      symbol_flag=self.DARK_GREEN)

    def __failureForm(self, s: str, *args, flag: int = 0):
        return self._formatWithSymbol('[x]', f'{s}', *args, flag=flag,
                                      symbol_flag=self.DARK_RED)

    def __warnForm(self, s: str, *args, flag: int = 0):
        return self._formatWithSymbol('[!]', f'{s}', *args, flag=flag,
                                      symbol_flag=self.DARK_YELLOW)

    def __logFrom(self, s: str, *args, flag: int = 0):
        return self._formatWithSymbol('[ ]', f'{s}', *args, flag=flag,
                                      symbol_flag=self.VERBOSE)

    def print(self, s: str, *args, flag: int = 0):
        self._formatOneline(s, *args, flag=flag)

    def log(self, s: str, *args, flag: int = 0):
        self._oneline(self.__logFrom(s, *args, flag=flag))

    def success(self, s: str, *args, flag: int = 0):
        self._oneline(self.__successForm(s, *args, flag=flag))

    def failure(self, s: str, *args, flag: int = 0):
        self._oneline(self.__failureForm(s, *args, flag=flag))

    def warn(self, s: str, *args, flag: int = 0):
        self._oneline(self.__warnForm(s, *args, flag=flag))

    def _taskMsgForm(self, task_name: str, msg: str, *args):
        msg = self.format(msg, *args)
        if msg == "":
            return task_name
        return self.format(f'{task_name}: {msg}')

    def createTaskLog(self, task_name: str):
        assert task_name not in self._tasks_map
        task = _LogImpl.Task(self, task_name)
        self._tasks_map[task_name] = task
        return task

    def _endTask(self, task_name: str, receive_msg: str, *args, is_success: bool):
        assert task_name in self._tasks_map
        thread_args = self._tasks_map[task_name]
        timing = self.format('({:.1f} s)', thread_args._elapsed, flag=self.VERBOSE)
        pmt = self._taskMsgForm(task_name, receive_msg, *args)
        if is_success:
            self._printAt(self.__successForm(
                f'{pmt} {timing}'), y=thread_args._ypos)
        else:
            self._printAt(self.__failureForm(
                f'{pmt} {timing}'), y=thread_args._ypos)
        del self._tasks_map[task_name]


class Log:
    __impl: _LogImpl = None

    @staticmethod
    def getInstance(*args, verbose=False, **kwargs):
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

    def IAmFunc1():
        LOG.funcVerbose("Hello")

    def IAmFunc2():
        LOG.funcVerbose("Hello")

    IAmFunc1()
    IAmFunc2()

    LOG.failure("this is {}", LOG.format("hightlight", flag=LOG.HIGHTLIGHT))
    LOG.failure("this is {}", LOG.format("dark red", flag=LOG.DARK_RED))
    LOG.failure("this is {}", LOG.format("verbose", flag=LOG.VERBOSE))
    LOG.failure("this is {}", LOG.format("important", flag=LOG.IMPORTANT))

    LOG.print("this is {}", LOG.format("hightlight", flag=LOG.HIGHTLIGHT))
    LOG.print("this is {}", LOG.format("black", flag=LOG.BLACK))
    LOG.print("this is {}", LOG.format("dark red", flag=LOG.DARK_RED))
    LOG.print("this is {}", LOG.format("dark green", flag=LOG.DARK_GREEN))
    LOG.print("this is {}", LOG.format("dark yello", flag=LOG.DARK_YELLOW))
    LOG.print("this is {}", LOG.format("dark blue", flag=LOG.DARK_BLUE))
    LOG.print("this is {}", LOG.format("dark magenta", flag=LOG.DARK_MAGENTA))
    LOG.print("this is {}", LOG.format("dark cyan", flag=LOG.DARK_CYAN))
    LOG.print("this is {}", LOG.format("dark white", flag=LOG.DARK_WHITE))
    LOG.print("this is {}", LOG.format("bright black", flag=LOG.BRIGHT_BLACK))
    LOG.print("this is {}", LOG.format("bright red", flag=LOG.BRIGHT_RED))
    LOG.print("this is {}", LOG.format("bright green", flag=LOG.BRIGHT_GREEN))
    LOG.print("this is {}", LOG.format("bright yello", flag=LOG.BRIGHT_YELLOW))
    LOG.print("this is {}", LOG.format("bright blue", flag=LOG.BRIGHT_BLUE))
    LOG.print("this is {}", LOG.format(
        "bright magenta", flag=LOG.BRIGHT_MAGENTA))
    LOG.print("this is {}", LOG.format("bright cyan", flag=LOG.BRIGHT_CYAN))
    LOG.print("this is {}", LOG.format("bright white", flag=LOG.WHITE))
    LOG.verbose("this is verbose1")
    LOG.verbose("this is verbose2")
    LOG.verbose("this is verbose3")

    LOG._print("this should not appear")
    LOG._clear()
    LOG.success("Success Message!")
    LOG.failure("Failure Message!")
    LOG.failure("Failure With {} Message!", LOG.format(
        "Important", flag=LOG.IMPORTANT))

    task1 = LOG.createTaskLog("Success Task")
    task2 = LOG.createTaskLog("Failure Task")

    cnt1 = 0
    cnt2 = 0
    task1.begin("Running... ({})", cnt1)
    task2.begin("Running... ({})", cnt2)
    while not PMT.ask("Stop task1?"):
        cnt1 += 1
        task1.log("Running... ({})", cnt1)
        LOG.verbose("keep task1")
    task1.end("Stopped", is_success=True)

    while not PMT.ask("Stop task2?"):
        cnt2 += 1
        task2.log("Running... ({})", cnt2)
        LOG.verbose("keep task2")
    task2.end("Stopped", is_success=False)
