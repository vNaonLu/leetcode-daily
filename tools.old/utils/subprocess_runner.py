from .worker import pending_pmt_worker
from . import prompt as pmt
from .cursor import cursor
import subprocess

class subprocess_runner(pending_pmt_worker):
  def __init__(self, task_name: str = "", sync: bool = True):
    pending_pmt_worker.__init__(self, task_name)
    self._sync = sync

  def invoke(self, cmd: list[str], succ: str = "", fail: str = ""):
    if self._sync:
      cursor.hide()
      self.start()
      cp = subprocess.run(cmd, stdout=subprocess.PIPE,
                              stderr=subprocess.PIPE)
      self.stop(pmt.succ(pmt.hi(succ)) if cp.returncode == 0 
                                      else pmt.fail(pmt.hi(fail), 'x'))
      cursor.show()
    else:
      cp = subprocess.run(cmd)
    return cp
