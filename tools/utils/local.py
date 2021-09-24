import os
import re
import math
import pathlib


class QuestionSource:
    def __init__(self, id: int):
        self.__id: str = str(id).zfill(4)
        self.__intv: str = id_folder(id)
        self.__name: str = "q{}.hpp".format(self.__id)
        self.__ut_name: str = "q{}_unittest.hpp".format(self.__id)

    def interval(self):
        return self.__intv

    def id(self):
        return int(self.__id)

    def src(self, base: str):
        return os.path.join(self.path(base), self.__name)

    def unittest(self, base: str):
        return os.path.join(self.path(base), self.__ut_name)

    def path(self, base: str):
        return os.path.join(base, self.__intv)


def solved_question_ids(path: str):
    res: list[int] = []
    for _, _, files in os.walk(path):
        for file in files:
            g = re.search("q(\d*).hpp", file)
            if g is not None:
                res.append(int(g.group(1)))
    res.sort()
    return res


def question_folders(path: str):
    res: list[int] = []
    for base, paths, _ in os.walk(path):
        if pathlib.PurePath(base) != path:
            continue
        for path in paths:
            res.append(path)
    res.sort(key=lambda p: int(re.search("(\d{1,})", p).group(1)))
    return res


def id_interval(id: int):
    interval_idx = math.floor((id - 1) / 50)
    return [interval_idx * 50 + 1, (interval_idx+1) * 50]


def id_folder(id: int):
    intv = id_interval(id)
    return "q_{}_{}".format(intv[0], intv[1])
