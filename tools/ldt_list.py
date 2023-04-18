#!/usr/bin/env python3
import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from impl import *
import dcli


def getLevelWithColor(lvl: str):
    LOG = prompt.Log.getInstance()
    if lvl == "Easy":
        return LOG.format(lvl, flag=LOG.DARK_GREEN)
    elif lvl == "Medium":
        return LOG.format(lvl, flag=LOG.DARK_YELLOW)
    elif lvl == "Hard":
        return LOG.format(lvl, flag=LOG.DARK_RED)
    else:
        return lvl


def getCommand(parent=None):
    @dcli.command(
        "list",
        dcli.arg("-a", "--all", dest="show_all", default=False, action="store_true",
                 help="identifier of whether show all unsolved/solved problems."),
        dcli.arg("-e", "--easy", dest="show_easy", default=False, action="store_true",
                 help="identifier of whether show only easy problems. invalid if |-H|, |-m| are enabled"),
        dcli.arg("-m", "--medium", dest="show_medium", default=False, action="store_true",
                 help="identifier of whether show medium problems. invalid if |-H|, |-e| are enabled"),
        dcli.arg("-H", "--hard", dest="show_hard", default=False, action="store_true",
                 help="identifier of whether show hard problems. invalid if |-e|, |-m| are enabled"),
        dcli.arg("--list", dest="questions_list_file", default=str(QUESTIONS_LIST_ABSOLUTE), action="store",
                 nargs=1, metavar="[Ques_List]", help="specify the questions list in CSV format."),
        dcli.arg("--resolve", dest="questions_log_file", default=str(QUESTIONS_LOG_ABSOLUTE), action="store",
                 nargs=1, metavar="[Solve_Log]", help="specify the resolve log in CSV format."),
        dcli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
                 help="enable verbose logging."),
        parent=parent,
        formatter_class=RawTextHelpFormatter,
        help=fixedWidth("list all problems in LeetCode."),
        description=fixedWidth('A script to show the problems list from LeetCode.')
    )
    def ldtList(args):
        LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
        ARG_QUESTIONS_LIST = Path(getattr(args, "questions_list_file")).resolve()
        ARG_RESOLVE_LOGS = Path(getattr(args, "questions_log_file")).resolve()
        ARG_SHOW_ALL = getattr(args, "show_all")
        ARG_SHOW_EASY = getattr(args, "show_easy")
        ARG_SHOW_MEDIUM = getattr(args, "show_medium")
        ARG_SHOW_HARD = getattr(args, "show_hard")

        show_one_level = False

        if ARG_SHOW_EASY:
            show_one_level = True
            if ARG_SHOW_MEDIUM or ARG_SHOW_HARD:
                LOG.failure("ldt build cannot run with |-e| and |-H| or |-m| enabled at the same time.")
                return 1

        if ARG_SHOW_MEDIUM:
            show_one_level = True
            if ARG_SHOW_EASY or ARG_SHOW_HARD:
                LOG.failure("ldt build cannot run with |-m| and |-H| or |-e| enabled at the same time.")
                return 1

        if ARG_SHOW_HARD:
            show_one_level = True
            if ARG_SHOW_EASY or ARG_SHOW_MEDIUM:
                LOG.failure("ldt build cannot run with |-H| and |-e| or |-m| enabled at the same time.")
                return 1

        LOGS_PARSE_TASK = LOG.createTaskLog("Parse Solution Logs")
        LOGS_PARSE_TASK.begin("parsing the resolved logs: {}",
                              ARG_RESOLVE_LOGS)
        resolve_logs = ResolveLogsFile(ARG_RESOLVE_LOGS)
        LOGS_PARSE_TASK.done("loaded {} resolved logs from: {}",
                             LOG.format(len(resolve_logs),
                                        flag=LOG.HIGHTLIGHT),
                             LOG.format(ARG_RESOLVE_LOGS, flag=LOG.HIGHTLIGHT),
                             is_success=True)

        QLIST_PARSE_TASK = LOG.createTaskLog("Parse Questions List")
        QLIST_PARSE_TASK.begin("parsing the questions list: {}", 
                               ARG_QUESTIONS_LIST)
        questions_list = QuestionsList(ARG_QUESTIONS_LIST)
        QLIST_PARSE_TASK.done("loaded {} questions details from: {}",
                              LOG.format(len(questions_list),
                                         flag=LOG.HIGHTLIGHT),
                              LOG.format(ARG_QUESTIONS_LIST,
                                         flag=LOG.HIGHTLIGHT),
                              is_success=True)

        show_list: list[QuestionDetails] = []

        for detail in questions_list:
            if detail.paid:
                continue

            if not ARG_SHOW_ALL and detail.id in resolve_logs:
                continue

            if not show_one_level:
                show_list.append(detail)
            else:
                if ARG_SHOW_EASY and detail.level == 1:
                    show_list.append(detail)
                elif ARG_SHOW_MEDIUM and detail.level == 2:
                    show_list.append(detail)
                elif ARG_SHOW_HARD and detail.level == 3:
                    show_list.append(detail)

        show_list.sort(key=lambda d: d.id)
        max_length = max([len(d.title) for d in show_list])

        problems_text = ""
        for detail in show_list:
            problems_text += LOG.format("{} {} {}\n",
                                        LOG.format(str(detail.id).rjust(5),
                                                   flag=LOG.HIGHTLIGHT),
                                        detail.title.ljust(max_length),
                                        getLevelWithColor(detail.levelString()))

        showWithLess(problems_text)

        return 0

    return ldtList


if __name__ == "__main__":
    sys.exit(safeRun(getCommand()))
