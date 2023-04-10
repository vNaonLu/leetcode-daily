#!/usr/bin/env python3
import sys
import regex
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from impl import *
import dcli


def getCommand(parent=None):
    @dcli.command(
        "detail",
        dcli.arg("id", metavar="id", default=-1,
                 type=int, help="question identifiers to add."),
        dcli.arg("-C", dest="src_path", default=str(SRC_ABSOLUTE), action="store",
                 metavar="[Source_Root]", help="specify the source root."),
        dcli.arg("--list", dest="questions_list_file", default=str(QUESTIONS_LIST_ABSOLUTE), action="store",
                 nargs=1, metavar="[Ques_List]", help="specify the questions list in CSV format."),
        dcli.arg("--resolve", dest="questions_log_file", default=str(QUESTIONS_LOG_ABSOLUTE), action="store",
                 nargs=1, metavar="[Solve_Log]", help="specify the resolve log in CSV format."),
        dcli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
                 help="enable verbose logging."),
        parent=parent,
        formatter_class=RawTextHelpFormatter,
        help=fixedWidth(
            "Get the information for specific problem with its id.",
            width=60
        ),
        description=fixedWidth(
            f'A script to get the information for specific problem with its id.'
        )
    )
    def ldtDetail(args):
        LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
        ARG_ID = getattr(args, "id")
        ARG_SRC_PATH = Path(getattr(args, "src_path")).resolve()
        ARG_QUESTIONS_LIST = Path(getattr(args, "questions_list_file")).resolve()
        ARG_RESOLVE_LOGS = Path(getattr(args, "questions_log_file")).resolve()

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

        if ARG_ID not in questions_list:
            LOG.failure("no information for problem #{}.",
                        LOG.format(ARG_ID, flag=LOG.HIGHTLIGHT))
            return 1

        detail = questions_list[ARG_ID]
        LOG.success("get information for problem #{}",
                    LOG.format(ARG_ID, flag=LOG.HIGHTLIGHT))

        LOG.log("     title: {}", detail.title)
        LOG.log("difficulty: {}", detail.levelString())
        LOG.log("       url: {}", LOG.format(
            "https://leetcode.com/problems/{}/", detail.slug, flag=LOG.HIGHTLIGHT))

        if ARG_ID in resolve_logs:
            solution_file = SolutionFile(ARG_ID, ARG_SRC_PATH)
            LOG.log("       src: {}", solution_file)

        return 0

    return ldtDetail


if __name__ == "__main__":
    sys.exit(safeRun(getCommand()))
