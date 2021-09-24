import os
import re
import math
import pathlib


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
