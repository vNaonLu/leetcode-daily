#!/usr/bin/python3
import optparse
import subprocess


def __parser():
    parser = optparse.OptionParser()
    parser.add_option("-a", "--add",
                      dest="add_identify",
                      action="store_true",
                      default=False,
                      help="feature to add question and modify README and src automatically.")
    # parser.add_option("-d", "--del",
    #                   dest="del_identify",
    #                   action="store_true",
    #                   default=False,
    #                   help="feature to delete question and modify README and src automatically.")
    return parser


def __main():
    parser = __parser()
    options, args = parser.parse_args()
    # if options.add_identify and options.del_identify:
    #     parser.error("options -a and -d are mutually exclusive.")
    if options.add_identify:
        subprocess.run(["python3", "./tools/leetcode_add.py",
                        "--out", "./src/",
                        "--readme", "./README.md",
                        "--question-list", "./src/questions_list.csv",
                        "--question-log", "./src/logs.csv"] + args)


if __name__ == "__main__":
    __main()
