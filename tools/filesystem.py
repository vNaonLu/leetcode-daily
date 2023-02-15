#!/usr/bin/env python3
import sys
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *


class SolutionFile:
    def __init__(self, id: int) -> None:
        self._id = id
        self._subdir = getSubdirectoryName(id)
        self._src_name = 'q{}.cc'.format(str(id).zfill(4))

    def subdirectory(self):
        return self._subdir
    
    def sourceName(self):
        return self._src_name
    
    def path(self, base: Path = Path(".")):
        return base.joinpath(self._subdir).joinpath(self._src_name).resolve()
    
    def id(self):
        return self._id


if __name__ == "__main__":
    qf = SolutionFile(123)
    print("id          : ", qf.id())
    print("source name : ", qf.sourceName())
    print("subdirectory: ", qf.subdirectory())
    print("path        : ", qf.path(SRC_ABSOLUTE))