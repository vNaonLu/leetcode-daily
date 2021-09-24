#!/usr/bin/python3
import optparse
import pathlib
import subprocess
import os


def __parser():
    parser = optparse.OptionParser()
    parser.add_option("-a", "--add",
                      dest="add_identify",
                      action="store_true",
                      default=False,
                      help="feature to add question and modify README and src automatically.")
    parser.add_option("-d", "--del",
                      dest="del_identify",
                      action="store_true",
                      default=False,
                      help="feature to delete question and modify README and src automatically.")
    return parser


def __main():
    parser = __parser()
    options, args = parser.parse_args()
    if options.add_identify and options.del_identify:
        parser.error("options -a and -d are mutually exclusive.")
    file_path = pathlib.Path(__file__).parent
    if options.add_identify:
        subprocess.run(["python3", file_path.joinpath("./tools/leetcode_add.py").resolve(),
                        "--out", file_path.joinpath("./src/").resolve(),
                        "--readme", file_path.joinpath("./README.md").resolve(),
                        "--question-list", file_path.joinpath("./src/questions_list.csv").resolve(),
                        "--question-log", file_path.joinpath("./src/logs.csv").resolve()] + args)
    if options.del_identify:
        subprocess.run(["python3", file_path.joinpath("./tools/leetcode_del.py").resolve(),
                        "--out", file_path.joinpath("./src/").resolve(),
                        "--readme", file_path.joinpath("./README.md").resolve(),
                        "--question-list", file_path.joinpath("./src/questions_list.csv").resolve(),
                        "--question-log", file_path.joinpath("./src/logs.csv").resolve()] + args)


if __name__ == "__main__":
    __main()
