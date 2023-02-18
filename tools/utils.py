#!/usr/bin/env python3
import textwrap
import math
import regex
import prompt
import time
import subprocess
from pathlib import Path
from typing import Callable

SCRIPT_NAME = "LeetCodeDailyTools"
CAT_SCRIPT_NAME = f"{SCRIPT_NAME}_Cat"
ADD_SCRIPT_NAME = f"{SCRIPT_NAME}_Add"
GEN_SCRIPT_NAME = f"{SCRIPT_NAME}_Gen"
RUN_SCRIPT_NAME = f"{SCRIPT_NAME}_Run"
BUILD_SCRIPT_NAME = f"{SCRIPT_NAME}_Build"
REMOVE_SCRIPT_NAME = f"{SCRIPT_NAME}_Remove"
UPDATE_SCRIPT_NAME = f"{SCRIPT_NAME}_Update"
UPDATE_ALL_SCRIPT_NAME = f"{UPDATE_SCRIPT_NAME}_All"
UPDATE_README_SCRIPT_NAME = f"{UPDATE_SCRIPT_NAME}_Readme"
UPDATE_QUESTIONS_LIST_SCRIPT_NAME = f"{UPDATE_SCRIPT_NAME}_QuestionsList"
UPDATE_RESOLVE_DIAGRAMS_SCRIPT_NAME = f"{UPDATE_SCRIPT_NAME}_ResolveStatus"
PROJECT_ROOT = Path(__file__).parent.parent.resolve()
SRC_RELATIVE = Path('./src')
DOCS_RELATIVE = Path('./docs')
ASSETS_RELATIVE = Path('./assets')
BUILD_RELATIVE = Path('./build')
SRC_ABSOLUTE = PROJECT_ROOT.joinpath(SRC_RELATIVE).resolve()
DOCS_ABSOLUTE = PROJECT_ROOT.joinpath(DOCS_RELATIVE).resolve()
ASSETS_ABSOLUTE = PROJECT_ROOT.joinpath(ASSETS_RELATIVE).resolve()
BUILD_ABSOLUTE = PROJECT_ROOT.joinpath(BUILD_RELATIVE).resolve()
QUESTIONS_LOG_ABSOLUTE = SRC_ABSOLUTE.joinpath("logs.csv")
QUESTIONS_LIST_ABSOLUTE = SRC_ABSOLUTE.joinpath("questions_list.csv")


def concat(*args, delimiter: str = '\n'):
    if len(args) == 0:
        return ""
    elif len(args) == 1 and isinstance(*args, str):
        return str(*args)
    return delimiter.join(*args)


def fixedWidth(*args, width: int = 80):
    if len(args) == 0:
        return ""
    elif len(args) == 1 and isinstance(*args, str):
        return concat(textwrap.wrap(*args, width, break_long_words=False))

    res = []
    for s in args:
        res.append(concat(textwrap.wrap(s, width, break_long_words=False)))
    return concat(res)


__ID_INTERVAL = 50


def __calcQuestionInterval(id: int):
    intv_idx = math.floor((id - 1) / 50)
    return int(intv_idx * __ID_INTERVAL + 1), int(intv_idx + 1) * __ID_INTERVAL


def getSubdirectoryName(id: int):
    lo, hi = __calcQuestionInterval(id)
    return f"q_{lo}_{hi}"


def getSolutionFileName(id: int):
    return f'q{str(id).zfill(4)}.cc'


__REGULAR_SOLUTION_FORMAT = regex.compile(
    "(?P<solution>class Solution *({(?:(?:[^{}]|(?2))*)});)")

__STRUCTURED_SOLUTION_FORMAT = regex.compile(
    "(?P<solution>class \w+ *({(?:(?:[^{}]|(?2))*)});)")


def parseSolution(src: str):
    LOG = prompt.Log.getInstance()
    LOG.funcVerbose("trying to search with regular type.")
    regular = __REGULAR_SOLUTION_FORMAT.search(src)
    if regular:
        LOG.funcVerbose("the regular solution format found.")
        return regular.group("solution")
    LOG.funcVerbose("failed to search with the regular solution format.")

    LOG.funcVerbose("trying to parse with structured type.")
    structured = __STRUCTURED_SOLUTION_FORMAT.search(src)
    if structured:
        LOG.funcVerbose("the structured solution format found.")
        return structured.group("solution")
    LOG.funcVerbose("failed to search with the structured solution format.")

    LOG.funcVerbose("failed to search all possible solution format.")
    return None


def FindExecutable(name: str):
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
    clang_format = FindExecutable("clang-format")
    if not clang_format:
        return src
    with tempfile.NamedTemporaryFile(suffix=".tmp") as tmp:
        LOG.funcVerbose("opened a temporary file and writing source in: {}", tmp.name)
        tmp.write(src.encode('utf-8'))
        tmp.flush()

        CMD = [clang_format, tmp.name]
        LOG.funcVerbose("run a command: {}", CMD)

        res = subprocess.run(CMD, stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE)
        if res.returncode != 0:
            LOG.funcVerbose("command ran failed: {}", res)
            return src
        LOG.funcVerbose("command ran successfully.")
        after = res.stdout.decode('utf-8')
        return after


def readlineFromPipe(proc: subprocess.Popen[str]):
    out = proc.stdout.readline()
    return out.replace('\n', '')


def parseCMakeGenarateLog(oneline: str):
    res = oneline.replace('\n', '')[3:]
    return res[0].lower() + res[1:]


def parseBuildLog(oneline: str):
    # [  0%] Built target gtest
    res = oneline.replace('\n', '')
    percent = int(res[1:4].strip())
    res = res[7:]
    return percent, res[0].lower() + res[1:]


__TEST_FAILED = regex.compile("^\[  FAILED  \] (?P<solution>[\w.]+)$", regex.MULTILINE)


def parseFailedTests(text: str):
    find = __TEST_FAILED.findall(text)

    if find:
        return set(find)
    return set([])


def parseTestBlock(text: str, target: str):
    LOG = prompt.Log.getInstance()
    target = target.replace('.', r'\.')
    r = regex.compile(f"(?P<block>\[ RUN      \] {target}[\w\W]+\[  FAILED  \] {target} \(\d+ ms\))")
    LOG.funcVerbose("trying to search with regex: {}", r)
    m = r.search(text)
    if m:
        return m.group("block")
    LOG.funcVerbose("no target found.")
    return None


def launchSubprocess(cmd: list[str]):
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
        LOG.log("change directory to: {}", self._path)
        self._origin = os.getcwd()
        os.chdir(self._path)

    def __exit__(self, type, value, traceback):
        import os
        LOG = prompt.Log.getInstance()
        LOG.log("change directory back to: {}", self._origin)
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


if __name__ == "__main__":

    import sys, time

    with subprocess.Popen(["cmake", "--build", "build.test"],
                          stdin=subprocess.PIPE,
                          stdout=subprocess.PIPE,
                          stderr=subprocess.PIPE) as proc:
        while not proc.poll():
            print(proc.stdout.readline())
            time.sleep(1)
        print("out")


    sys.exit()
    print("PROJECT_ROOT", str(PROJECT_ROOT))
    print("SRC_ABSOLUTE", str(SRC_ABSOLUTE))
    print("DOCS_ABSOLUTE", str(DOCS_ABSOLUTE))
    print("ASSETS_ABSOLUTE", str(ASSETS_ABSOLUTE))
    print()
    a = fixedWidth(
        'This page shares my best articles to read on topics like health'
        ', happiness, creativity, productivity and more. The central question'
        ' that drives my work is, “How can we live better?” To answer that'
        ' question, I like to write about science-based ways to solve'
        ' practical problems.'
    )
    print(a)

    with chDir("..") as p:
        print("i am in ", p)