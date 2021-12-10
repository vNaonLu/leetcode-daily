#!/usr/bin/python3
import os
import optparse
import pathlib
from utils import local, template, modify, generate, prompt as pmt
from leetcode import request as LeetCodeRequest

def __parser():
    parser = optparse.OptionParser(usage="%prog [options] id1 id2 ...")
    parser.add_option("-o", "--out",
                      dest="output",
                      action="store",
                      default=".",
                      metavar=" Source_Path",
                      help="The directory where files are generated")
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
    options, args = parser.parse_args()

    if len(args) == 0:
        pmt.show("Usage: {} [options] id1 id2 ...".format(os.path.basename(__file__)))
        return

    sour_path = pathlib.Path(options.output).resolve()
    list_csv = pathlib.Path(options.list).resolve()
    log_csv = pathlib.Path(options.log).resolve()

    question_deleted = False

    for id in [int(arg) for arg in args]:
        remove_success = False
        qfile = local.QuestionSource(int(id), sour_path)
        remove_success |= modify.remove(os.path.join(qfile.src()))

        if remove_success:
            question_deleted = True
            modify.dellog(log_csv, id)

    if question_deleted:
        if not os.path.exists(list_csv):
            question_list = LeetCodeRequest.questions()
            generate.question_list(list_csv, question_list)
        solved = local.solved_question_ids(sour_path)
        modify.done_question(list_csv, solved)


if __name__ == "__main__":
    __main()
