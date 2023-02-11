import os
import re
import math
import pathlib
import csv
import time
import subprocess


class Complexity:
    def __init__(self, time: str, space: str):
        self.__tc = time
        self.__sc = space

    def time_complexity(self):
        return self.__tc

    def space_complexity(self):
        return self.__sc

class QuestionSource:
    def __init__(self, id: int, base: str):
        base_path = pathlib.Path(base)
        self.__id: str = str(id).zfill(4)
        self.__intv: str = id_folder(id)
        self.__dir: pathlib.Path = base_path.joinpath(self.__intv)
        self.__src: pathlib.Path = self.__dir.joinpath(
            "q{}.cc".format(self.__id))

    def interval(self):
        return self.__intv

    def id(self):
        return int(self.__id)

    def src(self):
        return self.__src

    def path(self):
        return self.__dir


class QuestionDetails:
    def __init__(self, csv_data: dict[str, str]):
        self._id = int(csv_data["id"])
        self._level = int(csv_data["level"])
        self._title = csv_data["title"]
        self._slug = csv_data["slug"]
        self._paid = csv_data["paid"] == "1"
        self._done = csv_data["done"] == "1"
        self._tc = csv_data["tc"]
        self._sc = csv_data["sc"]

    def id(self):
        return self._id

    def level(self):
        return self._level

    def title(self):
        return self._title

    def slug(self):
        return self._slug

    def paid_only(self):
        return self._paid

    def done(self):
        return self._done

    def tc(self):
        return self._tc

    def sc(self):
        return self._sc


class QuestionList:
    def __init__(self, path: str):
        self._question: dict[int, QuestionDetails] = {}
        self.__parse(path)

    def __parse(self, path: str):
        with open(path, "r") as f:
            rows = csv.DictReader(f, delimiter=',')
            for row in rows:
                details = QuestionDetails(row)
                self._question[details.id()] = details

    def get(self, id: int):
        if id in self._question:
            return self._question[id]
        return None

    def ids(self):
        return sorted([id for id in self._question])


class Log:
    def __init__(self, csv_data: list[str]):
        self._id = int(csv_data[1])
        self._timestamp = int(csv_data[0])

    def timestamp(self):
        return self._timestamp

    def id(self):
        return self._id


class SolvedLog:
    def __init__(self, path: str):
        self._log: dict[int, dict[int, dict[int, list[Log]]]] = {}
        self.__parse(path)

    def __parse(self, path: str):
        with open(path, "r") as f:
            rows = csv.reader(f, delimiter=",")
            for row in rows:
                log = Log(row)
                t = time.localtime(log.timestamp())
                year = int(time.strftime("%Y", t))
                month = int(time.strftime("%m", t))
                day = int(time.strftime("%d", t))
                if year not in self._log:
                    self._log[year] = {}
                if month not in self._log[year]:
                    self._log[year][month] = {}
                if day not in self._log[year][month]:
                    self._log[year][month][day] = []
                self._log[year][month][day].append(log)

    def get_by_day(self, year: int, month: int, day: int):
        if year in self._log and \
            month in self._log[year] and \
                day in self._log[year][month]:
            return self._log[year][month][day]
        return []

    def get_by_month(self, year: int, month: int):
        log: list[Log] = []
        for day in self.days(year, month):
            log += self.get_by_day(year,
                                   month, day)
        return log

    def get_by_year(self, year: int):
        log: list[Log] = []
        for month in self.months(year):
            for date in self.days(year, month):
                log += self.get_by_day(year,
                                       month, date)
        return log

    def years(self):
        return [y for y in self._log]

    def months(self, year: int):
        if year in self._log:
            return [m for m in self._log[year]]
        return []

    def days(self, year: int, month: int):
        if year in self._log and month in self._log[year]:
            return [d for d in self._log[year][month]]
        return []


def solved_question_ids(path: str):
    res: list[int] = []
    for _, _, files in os.walk(path):
        for file in files:
            g = re.search("q(\d*).cc", file)
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


def get_commit_log(file: QuestionSource):
    cmd = ["git", "log", "--oneline", file.src()]
    cp = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return cp if cp.returncode == 0 else None


def get_complexity_infomation(log_info: str):
    kLogRegex = re.compile(
        "(?:.*tc *O\((?P<tc>.+)\) +.*sc *O\((?P<sc>.+)\))|(?:(.*tc +and +sc O\((?P<tc_and_sc>.+)\)))", re.IGNORECASE)
    m = kLogRegex.match(log_info)
    if m is not None:
        if m.group("tc_and_sc"):
            return Complexity(m.group("tc_and_sc"), m.group("tc_and_sc"))
        elif m.group("tc") and m.group("sc"):
            return Complexity(m.group("tc"), m.group("sc"))
    return None