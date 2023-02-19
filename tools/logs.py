#!/usr/bin/env python3
import sys
import csv
import time
import calendar
# prevent generating __pycache__
sys.dont_write_bytecode = True


from utils import *


class ResolveLog:
    def __init__(self, csv_row: dict[str, str]) -> None:
        self.timestamp = int(csv_row[0])
        self.id = int(csv_row[1])
        self.year = int(time.strftime("%Y", time.localtime(self.timestamp)))
        self.month = int(time.strftime("%m", time.localtime(self.timestamp)))
        self.day = int(time.strftime("%d", time.localtime(self.timestamp)))

    def __iter__(self):
        return iter([self.timestamp, self.id])


class _MonthlyResolvedLogLists:
    def __init__(self, day_cnt: int) -> None:
        self._logs: dict[int, list[ResolveLog]] = {}
        for day in range(1, day_cnt + 1):
            self._logs[day] = []

    def addLog(self, resolve_log: ResolveLog):
        assert resolve_log.day in self._logs
        self._logs[resolve_log.day].append(resolve_log)

    def __getitem__(self, key: int):
        assert isinstance(key, int)

        if key not in self._logs:
            raise IndexError
        return self._logs[key]

    def days(self):
        return iter(self._logs.keys())
    
    def __reversed__(self):
        return reversed(self._logs.items())

    def __iter__(self):
        return iter(self._logs.items())

    def __len__(self):
        return sum(len(self._logs[day]) for day in self._logs)

    def removeById(self, id: int):
        assert isinstance(id, int)
        for lgs in self._logs.values():
            for i in range(len(lgs)):
                if lgs[i].id == id:
                    del lgs[i]
                    return True
        return False


class _YearlyResolvedLogList:
    def __init__(self, year: int) -> None:
        assert year <= TODAY.year, "refused to store the future log."
        LOG = prompt.Log.getInstance()
        self._logs: dict[int, _MonthlyResolvedLogLists] = {}

        max_month = 12 if year != TODAY.year else TODAY.month
        LOG.funcVerbose("initialized with months in {}: [1, {}]", year, max_month)
        for month in range(1, max_month + 1):
            assert year != TODAY.year or month <= TODAY.month, "refused to store the future log."
            max_days = calendar.monthrange(year, month)[1] if year != TODAY.year or (
                month != TODAY.month) else TODAY.day
            self._logs[month] = _MonthlyResolvedLogLists(max_days)

    def addLog(self, resolve_log: ResolveLog):
        assert resolve_log.month in self._logs
        self._logs[resolve_log.month].addLog(resolve_log)

    def months(self):
        return sorted(list(self._logs.keys()))
    
    def __reversed__(self):
        return reversed(self._logs.items())

    def __getitem__(self, key: int):
        assert isinstance(key, int)

        if key not in self._logs:
            raise IndexError
        return self._logs[key]

    def __iter__(self):
        return iter(self._logs.items())

    def __len__(self):
        return sum(len(self._logs[m]) for m in self._logs)

    def removeById(self, id: int):
        for lgs in self._logs.values():
            if lgs.removeById(id):
                return True
        return False


class ResolveLogsList:
    def __init__(self, path: Path) -> None:
        self._path = Path(path)
        self._logs: dict[int, _YearlyResolvedLogList] = {}
        assert self._path.exists() and self._path.is_file()

        LOG = prompt.Log.getInstance()
        LOG.funcVerbose("trying to parse log file: {}", self._path)
        with self._path.open("r") as f:
            for row in csv.reader(f, delimiter=','):
                log = ResolveLog(row)
                if  log.year not in self._logs:
                    LOG.funcVerbose("create yearly resolved logs for year {}", log.year)
                    self._logs[log.year] = _YearlyResolvedLogList(log.year)
                self._logs[log.year][log.month][log.day].append(log)

    def data(self):
        res: list[ResolveLog] = []
        for y, yl in self:
            for m, ml in yl:
                for d, dl in ml:
                    res += dl
        return res

    def addLog(self, resolve_log: ResolveLog):
        LOG = prompt.Log.getInstance()
        if resolve_log.year not in self._logs:
            LOG.funcVerbose("create yearly resolved logs for year {}", resolve_log.year)
            self._logs[resolve_log.year] = _YearlyResolvedLogList(resolve_log.year)
        self._logs[resolve_log.year].addLog(resolve_log)

    def removeById(self, id: int):
        for lgs in self._logs.values():
            if lgs.removeById(id):
                return True
        return False

    def __reversed__(self):
        return reversed(self._logs.items())

    def __getitem__(self, year: int):
        assert isinstance(year, int)

        if year not in self._logs:
            raise IndexError
        return self._logs[year]

    def __iter__(self):
        return iter(self._logs.items())

    def __len__(self):
        return sum(len(self._logs[y]) for y in self._logs)

if __name__ == "__main__":
    LOG = prompt.Log.getInstance(verbose=True)
    lg = ResolveLogsList("../src/logs.csv")
    d = {'a' : 213, 'b': 12313}
    for k, v in reversed(d.items()):
        print (k, v)

    for y, yl in reversed(lg):
        for m, ml in reversed(yl):
            for d, l in reversed(ml):
                print(y, m, d, l)
    print(len(lg))

