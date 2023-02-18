#!/usr/bin/env python3
import sys
import os
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *


class _UnjoinablePath(Path):
    import pathlib
    _flavour = pathlib._windows_flavour if os.name == 'nt' else pathlib._posix_flavour

    def __init__(self, *args):
        super().__init__()

    def __new__(cls, *args):
        return super(_UnjoinablePath, cls).__new__(cls, *args)

    def joinpath(self, *other):
        assert False, f"{self.__class__} should not join path."


class SolutionFile(_UnjoinablePath):
    _id: int
    _subdir: str
    _file_name: str
    _base: Path

    def __init__(self, *args):
        super().__init__()

    def __new__(cls, id: int, base: Path = Path('.')):
        subdir = getSubdirectoryName(id)
        file = getSolutionFileName(id)
        full = base.joinpath(subdir).joinpath(file)
        obj = super(SolutionFile, cls).__new__(cls, full)
        obj._id = id
        obj._subdir = subdir
        obj._file_name = file
        obj._base = base
        return obj

    def subdirectory(self):
        return self._subdir

    def fileName(self):
        return self._file_name

    def id(self):
        return self._id



_FILE_TEMPLATE = regex.compile("q(\d*).cc")
def getSolutionsList(base: Path):
    LOG = prompt.Log.getInstance()
    solutions: list[SolutionFile] = []
    LOG.funcVerbose("start searching the solution files in: {}", base)
    for _, _, files in os.walk(base):
        for f in files:
            find = _FILE_TEMPLATE.match(f)
            if find:
                LOG.funcVerbose("solution found: {}", f)
                solutions.append(SolutionFile(int(find.group(1)), base))
    LOG.funcVerbose("{} solutions found.", len(solutions))
    return solutions


if __name__ == "__main__":
    qf = SolutionFile(123, SRC_ABSOLUTE)
    print("id          : ", qf.id())
    print("source name : ", qf.fileName())
    print("subdirectory: ", qf.subdirectory())
    print("path        : ", qf)
    qf.joinpath()
