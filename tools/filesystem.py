#!/usr/bin/env python3
import sys
import os
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from logs import *


class _UnjoinablePath(Path):
    import pathlib
    _flavour = pathlib._windows_flavour if os.name == 'nt' else pathlib._posix_flavour

    def __init__(self, *args):
        super().__init__()

    def __new__(cls, *args):
        return super(_UnjoinablePath, cls).__new__(cls, *args)

    def joinpath(self, *other):
        assert False, f"{self.__class__} should not join path."


class ResolveLogsFile(_UnjoinablePath, ResolveLogsList):
    def __init__(self, *args):
        pass

    def __new__(cls, path: Path):
        obj = _UnjoinablePath.__new__(cls, path)
        ResolveLogsList.__init__(obj, path)
        return obj

    def save(self, dest: Path = None):
        LOG = prompt.Log.getInstance()

        store_path = self._path if dest is None else dest

        if store_path is None:
            LOG.funcVerbose("refused to save the questions list due to no destination supplied.")
            return False

        LOG.funcVerbose("start to save {} resolved logs to: {}", len(self),
                        store_path)
        with Path(store_path).resolve().open("w") as f:
            writer = csv.writer(f, delimiter=',')
            for year, year_logs in self:
                for month, month_logs in year_logs:
                    LOG.funcVerbose("saving {} resolved logs in month {}, {}.", len(
                        month_logs), month, year)
                    for _, day_logs in month_logs:
                        writer.writerows(day_logs)
            LOG.funcVerbose("saved the resolved logs to: {}", store_path)
            return True


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
    solutions: dict[int, SolutionFile] = {}
    LOG.funcVerbose("start searching the solution files in: {}", base)
    for _, _, files in os.walk(base):
        for f in files:
            find = _FILE_TEMPLATE.match(f)
            if find:
                LOG.funcVerbose("solution found: {}", f)
                solution = SolutionFile(int(find.group(1)), base)
                solutions[solution.id()] = solution
    LOG.funcVerbose("{} solutions found.", len(solutions))
    return solutions
