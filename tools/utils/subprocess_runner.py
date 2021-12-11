import asyncio
from .worker import pending_pmt_worker
from . import prompt as pmt
from .cursor import cursor

class subprocess_runner(pending_pmt_worker):
  def __init__(self, task_name: str):
    pending_pmt_worker.__init__(self, task_name)
    self._stdout:list[str] = []
    self._stderr:list[str] = []

  async def _read_stdout_stream(self, stream):
    while True:
        line = await stream.readline()
        if line:
          self._stdout.append(line)
        else:
            break

  async def _read_stderr_stream(self, stream):
    while True:
        line = await stream.readline()
        if line:
          self._stderr.append(line)
        else:
            break

  async def _stream_subprocess(self, cmd):
      process = await asyncio.create_subprocess_exec(*cmd,
                                                      stdout=asyncio.subprocess.PIPE,
                                                      stderr=asyncio.subprocess.PIPE)
      await asyncio.wait([
          self._read_stdout_stream(process.stdout),
          self._read_stderr_stream(process.stderr)
      ])
      return await process.wait()
    
  def stdout(self):
    return self._stdout
    
  def stderr(self):
    return self._stderr

  def invoke(self, cmd: list[str], succ: str, fail: str):
    cursor.hide()
    self.start()
    loop = asyncio.get_event_loop()
    result = loop.run_until_complete(self._stream_subprocess(cmd,)) == 0
    loop.close()
    self.stop(pmt.succ(pmt.hi(succ)) if result 
                                     else pmt.fail(pmt.hi(fail), 'x'))
    cursor.show()
    return result
