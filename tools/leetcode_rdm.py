#!/usr/bin/python3
import os
import optparse
import pathlib
from utils import modify

readme_path = ""
list_csv = ""
log_csv = ""


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
    global readme_path, list_csv, log_csv
    parser = __parser()
    options, _ = parser.parse_args()

    readme_path = pathlib.Path(options.readme).resolve()
    list_csv = pathlib.Path(options.list).resolve()
    log_csv = pathlib.Path(options.log).resolve()
    

    if not os.path.exists(list_csv):
        print("[x] question list not found: {}".format(list_csv))
    elif not os.path.exists(log_csv):
        print("[x] log file not found: {}".format(log_csv))
    else:
        modify.readme(readme_path, list_csv, log_csv)


if __name__ == "__main__":
    __main()
