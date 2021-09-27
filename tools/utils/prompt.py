import time
import threading


def printSameLine(prompt: str):
    print("\033[F\033[K{}".format(prompt))

def show(pmt: str):
    print(pmt)


def succ(prompt: str):
    return "\033[32m[+]\033[0m {}".format(prompt)


def fail(prompt: str):
    return "\033[31m[x]\033[0m {}".format(prompt)


class _LoadingPmt:
    _instance = None
    _dot = ["⠇", "⠏", "⠋", "⠛", "⠙", "⠹", "⠸", "⠼", "⠴", "⠶", "⠦", "⠧"]

    @staticmethod
    def instance():
        if _LoadingPmt._instance == None:
            _LoadingPmt()
        return _LoadingPmt._instance

    @staticmethod
    def _loading_format(step: int, prompt: str):
        return "\033[32;1m{}\033[0m {}".format(_LoadingPmt._dot[step % len(_LoadingPmt._dot)],
                                               prompt)

    def _loading(self):
        i = 0
        print(_LoadingPmt._loading_format(i, self._prompt))
        while self._start:
            i += 1
            printSameLine(_LoadingPmt._loading_format(i, self._prompt))
            time.sleep(0.075)

    def __init__(self):
        if _LoadingPmt._instance != None:
            raise Exception('_LoadingPmt exist!')
        self._thread = None
        self._start: bool = False
        self._prompt: str = ""
        _LoadingPmt._instance = self

    def start(self, prompt: str):
        self._prompt = prompt
        self._start = True
        self._thread = threading.Thread(target=self._loading)
        self._thread.start()

    def stop(self, prompt: str):
        self._start = False
        self._thread.join()
        printSameLine(prompt)

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
