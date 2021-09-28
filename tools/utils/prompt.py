import time
import threading


def printSameLine(prompt: str):
    print("\033[F\033[K{}".format(prompt))


def show(pmt: str):
    print(pmt)


def succ(prompt: str, syb: str = "+", bold: bool = False):
    if bold:
        return "\033[0;32m[{}] \033[1;32m{}\033[0m".format(syb, prompt)
    else:
        return "\033[32m[{}] \033[0;37m{}\033[0m".format(syb, prompt)


def fail(prompt: str, syb: str, bold: bool = False):
    if bold:
        return "\033[0;31m[{}] \033[1;31m{}\033[0m".format(syb, prompt)
    else:
        return "\033[31m[{}] \033[0;31m{}\033[0m".format(syb, prompt)


def ask(pmt: str):
    while True:
        req = input("\033[33m[?] \033[0;37m{} (y/n)?\033[0m ".format(pmt))[0]
        if req == 'y':
            return True
        elif req == 'n':
            return False


class _LoadingPmt:
    _instance = None
    _dot = ["⠇", "⠏", "⠋", "⠛", "⠙", "⠹", "⠸", "⠼", "⠴", "⠶", "⠦", "⠧"]

    @staticmethod
    def instance():
        if _LoadingPmt._instance == None:
            _LoadingPmt()
        return _LoadingPmt._instance

    @staticmethod
    def _loading_format(step: int, prompt: str, time: float):
        return "\033[1;34m {} \033[0;37m{}{}\033[0m ({:.1f} s)".format(
            _LoadingPmt._dot[step % len(_LoadingPmt._dot)],
            prompt,
            ("." * (int(step / 3) % 3 + 1)).ljust(3, " "),
            time)

    def _loading(self):
        i = 0
        print(_LoadingPmt._loading_format(i, self._prompt, 0.0))
        beg = time.time()
        while self._start:
            i += 1
            self._timer = time.time() - beg
            printSameLine(_LoadingPmt._loading_format(i,
                                                      self._prompt,
                                                      self._timer))
            time.sleep(0.075)

    def __init__(self):
        if _LoadingPmt._instance != None:
            raise Exception('_LoadingPmt exist!')
        self._thread = None
        self._start: bool = False
        self._prompt: str = ""
        self._timer: float = 0.0
        _LoadingPmt._instance = self

    def start(self, prompt: str):
        self._prompt = prompt
        self._start = True
        self._thread = threading.Thread(target=self._loading)
        self._thread.start()

    def stop(self, prompt: str):
        self._start = False
        self._thread.join()
        printSameLine(prompt + "    ({:.1f} s)".format(self._timer))

    def busy(self):
        return self._start


def pending(pmt: str):
    L = _LoadingPmt.instance()
    if L.busy():
        raise Exception("Loading Prompt is busy!")
    L.start(pmt)


def recieve(pmt: str):
    L = _LoadingPmt.instance()
    L.stop(pmt)
