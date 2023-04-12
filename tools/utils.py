#!/usr/bin/env python3
import sys
import os
import textwrap
import math
import regex
import time
import subprocess
from pathlib import Path
from typing import Callable
from datetime import date, datetime
# prevent generating __pycache__
sys.dont_write_bytecode = True

import prompt
from utils_impl.prettify import *

SCRIPT_NAME = "LeetCodeDailyTools"
CAT_SCRIPT_NAME = f"{SCRIPT_NAME}_Cat"
ADD_SCRIPT_NAME = f"{SCRIPT_NAME}_Add"
GEN_SCRIPT_NAME = f"{SCRIPT_NAME}_Gen"
RUN_SCRIPT_NAME = f"{SCRIPT_NAME}_Run"
BUILD_SCRIPT_NAME = f"{SCRIPT_NAME}_Build"
CHECK_SCRIPT_NAME = f"{SCRIPT_NAME}_Check"
REMOVE_SCRIPT_NAME = f"{SCRIPT_NAME}_Remove"
UPDATE_SCRIPT_NAME = f"{SCRIPT_NAME}_Update"
CONFIG_SCRIPT_NAME = f"{SCRIPT_NAME}_Config"
UPDATE_ALL_SCRIPT_NAME = f"{UPDATE_SCRIPT_NAME}_All"
UPDATE_README_SCRIPT_NAME = f"{UPDATE_SCRIPT_NAME}_Readme"
UPDATE_QUESTIONS_LIST_SCRIPT_NAME = f"{UPDATE_SCRIPT_NAME}_QuestionsList"
UPDATE_RESOLVE_REFERENCE_SCRIPT_NAME = f"{UPDATE_SCRIPT_NAME}_ResolveReference"
CONFIG_SESSION_SCRIPT_NAME = f"{SCRIPT_NAME}_ConfigDefaultSession"
PROJECT_ROOT = Path(__file__).parent.parent.resolve()
SRC_RELATIVE = Path('./src')
DOCS_RELATIVE = Path('./docs')
ASSETS_RELATIVE = Path('./assets')
BUILD_RELATIVE = Path('./build')
SRC_ABSOLUTE = PROJECT_ROOT.joinpath(SRC_RELATIVE).resolve()
DOCS_ABSOLUTE = PROJECT_ROOT.joinpath(DOCS_RELATIVE).resolve()
ASSETS_ABSOLUTE = PROJECT_ROOT.joinpath(ASSETS_RELATIVE).resolve()
BUILD_ABSOLUTE = PROJECT_ROOT.joinpath(BUILD_RELATIVE).resolve()
QUESTIONS_LOG_ABSOLUTE = SRC_ABSOLUTE.joinpath("solution_logs.csv")
QUESTIONS_LIST_ABSOLUTE = SRC_ABSOLUTE.joinpath("questions_list.csv")
README_ABSOLUTE = PROJECT_ROOT.joinpath("README.md")

LDTCONFIG_EXTENSION = ".ldtconf"
LDTCONFIG_ABSOLUTE = PROJECT_ROOT.joinpath(LDTCONFIG_EXTENSION).resolve()

TODAY = datetime.now()
PROJECT_INITIAL_DATE = datetime(2021, 9, 6)

def concat(*args, delimiter: str = '\n'):
    if len(args) == 0:
        return ""
    elif len(args) == 1 and isinstance(*args, str):
        return str(*args)
    return delimiter.join([*args])


def fixedWidth(*args, width: int = 80):
    if len(args) == 0:
        return ""
    elif len(args) == 1 and isinstance(*args, str):
        return concat(*textwrap.wrap(*args, width, break_long_words=False))

    res = []
    for s in args:
        res.append(concat(*textwrap.wrap(s, width, break_long_words=False)))
    return concat(*res)


__ID_INTERVAL = 50


def __calcQuestionInterval(id: int):
    intv_idx = math.floor((id - 1) / 50)
    return int(intv_idx * __ID_INTERVAL + 1), int(intv_idx + 1) * __ID_INTERVAL


def getSubdirectoryName(id: int):
    lo, hi = __calcQuestionInterval(id)
    return f"q_{lo}_{hi}"


def getSolutionFileName(id: int):
    return f'q{str(id).zfill(4)}.cc'


__SOLUTION_FORMAT = regex.compile(
    "LEETCODE_BEGIN_RESOLVING\([ \n]*\d+,[ \n]*\w+,[ \n]*\w+\);([\w\W]+)LEETCODE_END_RESOLVING\([ \n]*\w+\);"
)

__BEGIN_SOLUTION_SPECIFIER = "LEETCODE_BEGIN_RESOLVING"


def parseSolution(src: str):
    LOG = prompt.Log.getInstance()
    LOG.funcVerbose("try to parse the source: \n{}", src)
    LOG.funcVerbose("with regex: {}", __SOLUTION_FORMAT)
    mat = __SOLUTION_FORMAT.search(src)
    if not mat:
        LOG.funcVerbose("solution segment not found.")
        return None
    return mat.group(1).strip()


def getSolutionLine(src: str) -> int:
    occu = src.find(__BEGIN_SOLUTION_SPECIFIER)
    if not occu:
        return 0
    return src[:occu].count('\n')


def findExecutable(name: str):
    from shutil import which
    LOG = prompt.Log.getInstance()
    LOG.funcVerbose(f"trying to find |{name}| executable.")
    res = which(name)

    if not res:
        LOG.funcVerbose(f"there is no |{name}| exists.")
        return None
    LOG.funcVerbose(f"|{name}| found: {res}")
    return res


def clangFormat(src: str):
    import tempfile
    LOG = prompt.Log.getInstance()
    LOG.funcVerbose("trying to search |clang-format| executable.")
    clang_format = findExecutable("clang-format")
    if not clang_format:
        return src
    with tempfile.NamedTemporaryFile(suffix=".tmp") as tmp:
        LOG.funcVerbose("opened a temporary file and writing source in: {}", tmp.name)
        tmp.write(src.encode('utf-8'))
        tmp.flush()

        CMD = [clang_format,
               f"--style=file:{PROJECT_ROOT.joinpath('.clang-format')}",
               tmp.name]
        LOG.funcVerbose("run a command: {}", CMD)

        res = subprocess.run(CMD, stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE)
        if res.returncode != 0:
            LOG.funcVerbose("command ran failed: {}", res)
            return src
        LOG.funcVerbose("command ran successfully.")
        after = res.stdout.decode('utf-8')
        return after


def showWithLess(src: str):
    import tempfile
    LOG = prompt.Log.getInstance()
    less = findExecutable("less")
    if not less:
        return

    with tempfile.NamedTemporaryFile(suffix=".tmp") as tmp:
        LOG.funcVerbose("opened a temporary file and writing source in: {}", tmp.name)
        tmp.write(src.encode('utf-8'))
        tmp.flush()

        CMD = [less, "-R", tmp.name]
        LOG.funcVerbose("run a command: {}", CMD)

        if result := subprocess.run(CMD).returncode != 0:
            LOG.failure("failed to open: {}", result)


def openEditor(file: Path, *, line: int = None):
    LOG = prompt.Log.getInstance()
    EDITOR = os.environ.get("EDITOR", findExecutable("vim"))
    CMD = [EDITOR, "+set backupcopy=yes"]
    if line != None and isinstance(line, int) and line >= 0:
        CMD.append(f"+{line}")
    CMD.append(file)
    LOG.funcVerbose("run a command: {}", CMD)
    subprocess.call(CMD)


def inputByEditor(init_msg: str):
    import tempfile
    LOG = prompt.Log.getInstance()

    with tempfile.NamedTemporaryFile(suffix=".tmp") as tmp:
        LOG.funcVerbose("opened a temporary file and writing source in: {}", tmp.name)
        tmp.write(init_msg.encode('utf-8'))
        tmp.flush()

        openEditor(tmp.name)

        tmp.seek(0)
        msg = tmp.read().decode('utf-8')
        LOG.funcVerbose("got message: {}", msg)
        return msg


def checkPath(path: Path):
    assert isinstance(path, Path)
    LOG = prompt.Log.getInstance()
    LOG.funcVerbose("check whether the destination is directory: {}", path)
    if not path.exists():
        LOG.failure("the directory not found: {}", path)
        return False
    elif not path.is_dir():
        LOG.failure("the path is not a directory: {}", path)
        return False
    return True


def checkFile(path: Path):
    assert isinstance(path, Path)
    LOG = prompt.Log.getInstance()
    LOG.funcVerbose("check whether the destination is file: {}", path)
    if not path.exists():
        LOG.failure("the file not found: {}", path)
        return False
    elif not path.is_file():
        LOG.failure("the path is not a file: {}", path)
        return False
    return True


def readlineFromPipe(proc: subprocess.Popen[str]):
    out = proc.stdout.readline()
    return out.replace('\n', '')


def parseCMakeGenarateLog(oneline: str):
    res = oneline.replace('\n', '')[3:]
    return res[0].lower() + res[1:]


def parseBuildLog(oneline: str):
    # [  0%] Built target gtest
    res = oneline.replace('\n', '')
    try:
        percent = int(res[1:4].strip())
        res = res[7:]
        return percent, res[0].lower() + res[1:]
    except:
        return None, None


def parseFailedBlock(result: str, target: str):
    LOG = prompt.Log.getInstance()
    target = target.replace('.', r'\.')
    r = regex.compile(f"(?P<block>\[ RUN      \] {target}[\w\W]+\[  FAILED  \] {target} \(\d+ ms\))")
    LOG.funcVerbose("trying to search with regex: {}", r)
    m = r.search(result)
    if m:
        return m.group("block")
    LOG.funcVerbose("no target found.")
    return None


def launchSubprocess(cmd: list[str], *, timeout: int=None):
    LOG = prompt.Log.getInstance()
    LOG.verbose("run a command: {}", cmd)
    return subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, encoding='utf-8')


def asyncStdout(proc: subprocess.Popen[str], callback: Callable):
    while proc.poll() is None:
        out = readlineFromPipe(proc)
        if out != "":
            callback(out)
        time.sleep(1/30)

    out = readlineFromPipe(proc)
    while out != "":
        callback(out)
        out = readlineFromPipe(proc)


def getCurrentUnittestExtraIndex(text: str):
    result = 0
    result = max([result] + [int(x)
                 for x in regex.findall("extra_testcase_(\d+)", text)])
    return result


def getExtraUnittestSuite(index: int):
    return f"extra_testcase_{index}"


class _ChDir:
    def __init__(self, path) -> None:
        self._path = Path(path).resolve()
        self._origin: Path = None

    def path(self):
        return self._path

    def __enter__(self):
        import os
        assert self._path.exists()
        LOG = prompt.Log.getInstance()
        LOG.funcVerbose("change directory to: {}", self._path)
        self._origin = os.getcwd()
        os.chdir(self._path)

    def __exit__(self, type, value, traceback):
        import os
        LOG = prompt.Log.getInstance()
        LOG.funcVerbose("change directory back to: {}", self._origin)
        os.chdir(self._origin)


def chDir(path: Path):
    return _ChDir(path)


def safeRun(func: Callable, *args, **kwargs):
    try:
        return func(*args, **kwargs)

    except KeyboardInterrupt:
        LOG = prompt.Log.getInstance()
        LOG._clear()
        LOG.failure("interrupted by user.")
        import sys
        import os
        try:
            sys.exit(130)
        except SystemExit:
            os._exit(130)
