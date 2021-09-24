#!/usr/bin/python3
import os
import optparse
import pathlib
from utils import local, template, modify, generate
from leetcode import request as LeetCodeRequest

prompt = "This file is generated by {}".format(os.path.basename(__file__))
readme_path = ""
sour_path = ""
list_csv = ""
log_csv = ""


def __parser():
    parser = optparse.OptionParser(usage="%prog [options] id1 id2 ...")
    parser.add_option("-o", "--out",
                      dest="output",
                      action="store",
                      default=".",
                      metavar=" Source_Path",
                      help="The directory where files are generated")
    parser.add_option("-r", "--readme",
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
    global readme_path, sour_path, list_csv, log_csv
    parser = __parser()
    options, args = parser.parse_args()

    readme_path = pathlib.Path(options.readme).resolve()
    sour_path = pathlib.Path(options.output).resolve()
    list_csv = pathlib.Path(options.list).resolve()
    log_csv = pathlib.Path(options.log).resolve()

    modify_subunittest: set = set()
    modify_md = False

    for id in args:
        remove_success = False
        qfile = local.QuestionSource(int(id))
        remove_success |= modify.remove(os.path.join(qfile.src(sour_path)))
        remove_success |= modify.remove(
            os.path.join(qfile.unittest(sour_path)))
        modify_md |= remove_success

        if remove_success:
            modify.dellog(log_csv, id)
            modify_subunittest.add(qfile.interval())

    for subunittest in modify_subunittest:
        subsrc = os.path.join(sour_path, subunittest)
        ids = local.solved_question_ids(subsrc)
        generate.file(os.path.join(sour_path, subunittest, "unittest.hpp"),
                      template.subunittest(subunittest,
                                           ["q{}_unittest.hpp".format(str(id).zfill(4)) for id in ids]))

    if modify_md:
        if not os.path.exists(list_csv):
            question_list = LeetCodeRequest.questions()
            generate.question_list(list_csv, question_list)
        solved = local.solved_question_ids(sour_path)
        modify.done_question(list_csv, solved)
        modify.readme(readme_path, list_csv, log_csv)


if __name__ == "__main__":
    __main()
