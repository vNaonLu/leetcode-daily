#!/usr/bin/env python3
import textwrap
import math
import regex
import prompt
import subprocess
from pathlib import Path

SCRIPT_NAME = "LeetCodeDailyTools"
CAT_SCRIPT_NAME = f"{SCRIPT_NAME}_Cat"
ADD_SCRIPT_NAME = f"{SCRIPT_NAME}_Add"
GEN_SCRIPT_NAME = f"{SCRIPT_NAME}_Gen"
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


def clangFormat(src: str):
    from shutil import which
    import tempfile
    LOG = prompt.Log.getInstance()
    LOG.funcVerbose("trying to search |clang-format| executable.")
    clang_format = which("clang-format")

    if not clang_format:
        LOG.funcVerbose("there is no |clang-format| exists.")
        return src
    LOG.funcVerbose("|clang-format| found: {}", clang_format)

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


if __name__ == "__main__":
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