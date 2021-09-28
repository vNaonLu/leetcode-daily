#!/usr/bin/python3
import os
import optparse
import pathlib
import csv
import time
import calendar
from utils import modify, local, prompt as pmt


def __read_question_list(path: str):
    ids_map: dict[int, dict[str, any]] = {}
    quest_list: list[str] = []
    acc_cnt: list[int] = [0, 0, 0]
    lev_cnt: list[int] = [0, 0, 0]
    with open(path, "r") as f:
        rows = csv.DictReader(f, delimiter=',')
        for row in rows:
            ids_map[int(row["id"])] = row
            lev_cnt[int(row["level"])-1] += 1
            if row["done"] == "1":
                acc_cnt[int(row["level"])-1] += 1
                quest_list.append("- [x] {} [{}]({})".format(
                    row["id"].zfill(4),
                    row["title"],
                    "src/{}/q{}.hpp".format(
                        local.id_folder(int(row["id"])),
                        row["id"].zfill(4))))
            else:
                quest_list.append("- [ ] {} {}".format(
                    row["id"].zfill(4),
                    row["title"]))
    return ids_map, quest_list, [acc_cnt, lev_cnt]


def __read_log(path: str):
    log_map: dict[int, list[int]] = {}
    with open(path, "r") as f:
        rows = csv.reader(f, delimiter=",")
        for row in rows:
            date = time.strftime("%Y%m%d", time.localtime(int(row[0])))
            if not log_map.get(date):
                log_map[date] = []
            log_map[date].append(int(row[1]))
    return log_map


def __parser():
    parser = optparse.OptionParser(usage="%prog [options]")
    parser.add_option("-o", "--out",
                      dest="readme",
                      action="store",
                      default="./README.md",
                      metavar=" Readme_File")
    parser.add_option("-q", "--question-list",
                      dest="list",
                      action="store",
                      default="./questions_list.csv",
                      metavar=" Question_Lists_File")
    parser.add_option("-l", "--question-log",
                      dest="log",
                      action="store",
                      default="./logs.csv",
                      metavar=" Question_Logs_File")
    return parser


def __main():
    parser = __parser()
    options, _ = parser.parse_args()

    readme_path = pathlib.Path(options.readme).resolve()
    list_csv = pathlib.Path(options.list).resolve()
    log_csv = pathlib.Path(options.log).resolve()

    if not os.path.exists(list_csv):
        pmt.show(pmt.fail("The question list not found: {}".format(list_csv),
                          "x"))
    elif not os.path.exists(log_csv):
        pmt.show(pmt.fail("The log file not found: {}".format(log_csv),
                          "x"))
    else:
        idsmap, queslist, levelcnt = __read_question_list(list_csv)
        logmap = __read_log(log_csv)
        modify.readme(readme_path,
                      idsmap,
                      logmap,
                      queslist)


if __name__ == "__main__":
    __main()
