from time import time, sleep
from threading import Thread
from . import prompt as pmt

class pending_pmt_worker:
  def __init__(self, pmt: str):
    self._pmt   : str    = pmt
    self._timer : float  = 0.
    self._thread: Thread = None
    self._active: bool   = False

  def prompt(self, step: int = 0):
    _step = step
    _dot = ["⠇", "⠏", "⠋", "⠛", "⠙", "⠹", "⠸", "⠼", "⠴", "⠶", "⠦", "⠧"]
    return "\033[1;34m {} \033[0;37m{}{}\033[0m ({:.1f} s)".format(
        _dot[_step % len(_dot)], self._pmt,
        ("." * (int(_step / 3) % 3 + 1)).ljust(3, " "), self._timer)

  def __invoke(self):
    self._timer = 0.
    start_t = time()
    _step = 0
    pmt.show(self.prompt())
    while self._active:
      _step += 1
      self._timer = time() - start_t
      pmt.show(pmt.front() + self.prompt(_step))
      sleep(0.075)

  def start(self):
    if self._active:
      raise Exception("Already Running!")
    self._active = True
    self._thread = Thread(target=self.__invoke)
    self._thread.start()

  def stop(self, stop_pmt: str):
    if not self._active:
      raise Exception("Nothing working")
    self._active = False
    self._thread.join()
    pmt.show(pmt.front() + 
             stop_pmt +
             " ({:.1f}s)".format(self._timer))
