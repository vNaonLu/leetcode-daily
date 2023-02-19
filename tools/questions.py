#!/usr/bin/env python3
import sys
import csv
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *


class QuestionDetails:

    COL_NAMES = ["id", "title", "level", "slug", "paid", "done", "tc", "sc"]

    @staticmethod
    def __parse(csv_row: dict[str, str], name: str, default):
        return default if name not in csv_row else csv_row[name]

    def __init__(self, csv_row: dict[str, str] = {}) -> None:
        self.id = int(self.__parse(csv_row, "id", -1))
        self.title = self.__parse(csv_row, "title", "")
        self.level = int(self.__parse(csv_row, "level", -1))
        self.slug = self.__parse(csv_row, "slug", "")
        self.paid = self.__parse(csv_row, "paid", "0") == "1"
        self.done = self.__parse(csv_row, "done", "0") == "1"
        self.tc = self.__parse(csv_row, "tc", "")
        self.sc = self.__parse(csv_row, "sc", "")

    def dump(self):
        return {
            "id": self.id,
            "title": self.title,
            "level": self.level,
            "slug": self.slug,
            "paid": 1 if self.paid else 0,
            "done": 1 if self.done else 0,
            "tc": self.tc,
            "sc": self.sc
        }

    def isGood(self):
        return self.id > 0 and self.level > 0 and self.level < 4 and self.title != "" and self.slug != 0

    def levelString(self):
        return "Hard" if self.level == 3 else ("Medium" if self.level == 2 else "Easy")


class QuestionsList:

    def __init__(self, list_path: Path = None) -> None:
        LOG = prompt.Log.getInstance()
        self._path = None
        self._id_to_question: dict[int, QuestionDetails] = {}
        if list_path != None:
            self._path = Path(list_path)
            if not self._path.exists():
                LOG.funcVerbose("file not found: {}", self._path)
                return

            if not self._path.is_file():
                LOG.funcVerbose("the target is a directory: {}", self._path)
                return

            with self._path.open("r") as f:
                LOG.funcVerbose("parsing questions list: {}", self._path)
                for row in csv.DictReader(f, delimiter=','):
                    detail = QuestionDetails(row)
                    self._id_to_question[detail.id] = detail

    def __getitem__(self, id: int):
        if id not in self._id_to_question:
            raise IndexError
        return self._id_to_question[id]

    def __iter__(self):
        return iter(self._id_to_question.values())

    def __len__(self):
        return len(self._id_to_question)

    def __contains__(self, id: int):
        return id in self._id_to_question

    def __setitem__(self, id: int, detail: QuestionDetails):
        LOG = prompt.Log.getInstance()
        if not isinstance(detail, QuestionDetails) or not detail.isGood():
            LOG.funcVerbose("refused to set question details.")
            return
        self._id_to_question[id] = detail

    def isGood(self):
        LOG = prompt.Log.getInstance()
        if len(self._id_to_question) == 0:
            LOG.log("empty questions list is invalid.")
            return False

        mx = max(self._id_to_question.keys())
        for id in range(1, mx + 1):
            if id not in self._id_to_question:
                LOG.log("missing id in questions list: {}", id)
                return False
            elif not self._id_to_question[id].isGood():
                LOG.log("invalid id in questions list: {}", id)
                return False
        return True

    def save(self, dest: Path = None):
        LOG = prompt.Log.getInstance()

        LOG.funcVerbose("check whether questions list is valid.")

        if not self.isGood():

            LOG.funcVerbose("refused to save the questions list.")
            return False

        store_path = self._path if dest is None else dest

        if store_path is None:
            LOG.funcVerbose(
                "refused to save the questions list due to no destination supplied."
            )
            return False

        keys = sorted(self._id_to_question.keys())

        LOG.funcVerbose("start to save {} questions to: {}", len(keys),
                        store_path)

        with Path(store_path).resolve().open("w") as f:
            writer = csv.DictWriter(f,
                                    fieldnames=QuestionDetails.COL_NAMES,
                                    delimiter=',')
            writer.writeheader()
            details = [self._id_to_question[id] for id in keys]
            for d in details:
                writer.writerow(d.dump())
            return True
