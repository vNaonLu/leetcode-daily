#!/usr/bin/python3
import os
import optparse
import pathlib
import time
import datetime
from utils import modify, local, template, prompt as pmt
from utils import generate


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
    assets_path = pathlib.Path(options.assets).resolve()
    list_csv = pathlib.Path(options.list).resolve()
    log_csv = pathlib.Path(options.log).resolve()

    if not os.path.exists(list_csv):
        pmt.show(pmt.fail("The question list not found: {}".format(list_csv),
                          "x"))
    elif not os.path.exists(log_csv):
        pmt.show(pmt.fail("The log file not found: {}".format(log_csv),
                          "x"))
    else:
        total_submit = [0, 0, 0]
        log = local.SolvedLog(log_csv)
        questions = local.QuestionList(list_csv)
        sub_md: list[str, list[int]] = []
        solved_question: list[local.Log] = []
        for year in log.years():
            for month in log.months(year):
                timetuple = datetime.datetime(year, month, 1).timetuple()
                md_title = time.strftime("%B %Y", timetuple)
                file_name = time.strftime("%B_%Y", timetuple)
                logs = log.get_by_month(year, month)
                submissions = [0, 0, 0]
                solved_question += logs
                for l in logs:
                    submissions[questions.get(l.id()).level() - 1] += 1
                    total_submit[questions.get(l.id()).level() - 1] += 1
                generate.file(assets_path.joinpath(file_name + ".md").resolve(),
                              template.log_readme(md_title, logs,
                                                  questions))
                sub_md.append((file_name, submissions))
        sub_md.reverse()
        solved_question.sort(key=lambda log: log.timestamp(),
                             reverse=True)
        generate.file(assets_path.joinpath("submission.svg").resolve(),
                      template.accepted_svg(total_submit[0],
                                            total_submit[1],
                                            total_submit[2],
                                            len(questions.ids())))
        modify.readme(readme_path.resolve(), questions,
                      solved_question, sub_md)


if __name__ == "__main__":
    __main()
