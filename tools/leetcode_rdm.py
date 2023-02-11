#!/usr/bin/python3
import os
import optparse
import pathlib
import time
import datetime
from utils import modify, local, template, prompt as pmt
from utils import generate
from leetcode import request as LeetCodeRequest


def __parser():
    parser = optparse.OptionParser(usage="%prog [options]")
    parser.add_option("-o", "--out",
                      dest="readme",
                      action="store",
                      default="./README.md",
                      metavar=" Readme_File")
    parser.add_option("-a", "--assets",
                      dest="assets",
                      action="store",
                      default=".",
                      metavar=" Assets_Destination")
    parser.add_option("-s", "--source",
                      dest="source_path",
                      action="store",
                      default=".",
                      metavar=" Source_Path")
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
    parser.add_option("-f", "--force",
                      dest="force",
                      action="store_true",
                      default=False)
    return parser


def __main():
    parser = __parser()
    options, _ = parser.parse_args()

    readme_path = pathlib.Path(options.readme).resolve()
    assets_path = pathlib.Path(options.assets).resolve()
    source_path = pathlib.Path(options.source_path).resolve()
    list_csv = pathlib.Path(options.list).resolve()
    log_csv = pathlib.Path(options.log).resolve()
    force_update = options.force

    pmt.pending(pmt.hi("Requesting the question list"))
    question_list = LeetCodeRequest.questions()
    pmt.recieve(
        pmt.succ(pmt.hi("Successfully received the question list."), "v"))

    if not os.path.exists(list_csv):
        pmt.show(pmt.fail("The question list not found: {}".format(list_csv),
                          "x"))
        if (pmt.ask("Create a question list")):
            generate.question_list(list_csv.resolve(), question_list)
            solved = local.solved_question_ids(source_path)
            modify.done_question(list_csv.resolve(), solved, source_path.resolve())

    if not os.path.exists(log_csv):
        pmt.show(pmt.fail("The log file not found: {}".format(log_csv),
                          "x"))

    total_submit = [0, 0, 0]
    free_questions = [0, 0, 0]
    log = local.SolvedLog(log_csv)
    questions = local.QuestionList(list_csv)
    if (len(questions.ids()) != len(question_list) and \
            pmt.ask("New questions found, do you want to update the question list")) or force_update:
        generate.question_list(list_csv.resolve(), question_list)
        solved = local.solved_question_ids(source_path)
        modify.done_question(list_csv.resolve(), solved, source_path.resolve())
        questions = local.QuestionList(list_csv)

    sub_md: list[str, list[int]] = []
    solved_question: list[local.Log] = []
    for id in questions.ids():
        if not questions.get(id).paid_only():
            free_questions[questions.get(id).level() - 1] += 1

    for year in log.years():
        md_title = "{}".format(year)
        file_name = "{}".format(year)
        year_subs = [0, 0, 0]
        year_log = []
        for month in log.months(year):
            logs = log.get_by_month(year, month)
            year_log += logs
            solved_question += logs
            for l in logs:
                year_subs[questions.get(l.id()).level() - 1] += 1
                total_submit[questions.get(l.id()).level() - 1] += 1
        generate.file(assets_path.joinpath(file_name + ".md").resolve(),
                        template.log_readme(md_title, year_log,
                                            questions))
        sub_md.append((file_name, year_subs))
    sub_md.reverse()
    solved_question.sort(key=lambda log: log.timestamp(),
                         reverse=True)

    generate.file(assets_path.joinpath("process.svg").resolve(),
                  template.problem_solves_process_svg(total_submit[0] + total_submit[1] + total_submit[2],
                                                      free_questions[0] + free_questions[1] + free_questions[2]))

    modify.readme(readme_path.resolve(), questions,
                  solved_question, sub_md, total_submit, free_questions)


if __name__ == "__main__":
    __main()
