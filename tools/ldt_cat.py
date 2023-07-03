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
        return LOG.format(lvl, flag=LOG.BRIGHT_GREEN)
    elif lvl == "Medium":
        return LOG.format(lvl, flag=LOG.DARK_YELLOW)
    elif lvl == "Hard":
        return LOG.format(lvl, flag=LOG.DARK_RED)
    else:
        return lvl


def getCommand(parent=None):
    @dcli.command(
        "cat",
        dcli.arg("--src", dest="src_path", default=str(SRC_ABSOLUTE), action="store",
                 metavar="[Source_Root]", help="specify the source root."),
        dcli.arg("--list", dest="questions_list_file", default=str(QUESTIONS_LIST_ABSOLUTE), action="store",
                 nargs=1, metavar="[Ques_List]", help="specify the questions list in CSV format."),
        dcli.arg("--resolve", dest="questions_log_file", default=str(QUESTIONS_LOG_ABSOLUTE), action="store",
                 nargs=1, metavar="[Solve_Log]", help="specify the resolve log in CSV format."),
        dcli.arg("--no-snippet", dest="no_snippet", default=False, action="store_true", 
                 help="identifier of whether show solution snippet if solution exists."),
        dcli.arg("id", metavar="id", nargs=1, type=int,
                 help="question identifier to cat."),
        dcli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
                 help="enable verbose logging."),
        parent=parent,
        formatter_class=RawTextHelpFormatter,
        help=fixedWidth(
            "concatenate and print the solution for specific question.",
            width=60
        ),
        description=fixedWidth(
            'A script to concatenate and print the solution for solved questions.'
        )
    )
    def ldtCat(args):
        LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
        ARG_ID = getattr(args, "id")[0]
        ARG_SRC_PATH = Path(getattr(args, "src_path")).resolve()
        ARG_QUESTIONS_LIST = Path(getattr(args, "questions_list_file")).resolve()
        ARG_RESOLVE_LOGS = Path(getattr(args, "questions_log_file")).resolve()
        ARG_NO_SNIPPET = getattr(args, "no_snippet")

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

        less_msg = ""
        LOG.log("     title: {}", detail.title)
        less_msg += LOG.format("//      title: {}\n", detail.title)
        LOG.log("difficulty: {}", getLevelWithColor(detail.levelString()))
        less_msg += LOG.format("// difficulty: {}\n", getLevelWithColor(detail.levelString()))
        LOG.log("       url: {}", LOG.format(
            "https://leetcode.com/problems/{}/", detail.slug, flag=LOG.HIGHTLIGHT))
        less_msg += LOG.format("//        url: {}\n", LOG.format(
            "https://leetcode.com/problems/{}/", detail.slug, flag=LOG.HIGHTLIGHT))

        if ARG_ID in resolve_logs:
            solution_file = SolutionFile(ARG_ID, ARG_SRC_PATH)
            LOG.log("       src: {}", solution_file)

            if ARG_NO_SNIPPET:
                return 0

            LOG.verbose("target found and trying to get solution snippet.")
            with solution_file.open('r') as f:
                code_buf = f.read()
                snippet = parseSolution(code_buf)

                if not snippet:
                    LOG.failure("failed to parse the solution from file: {}", solution_file)
                    return 1

                solution = clangFormat(snippet).splitlines()
                less_msg += "//     answer:\n\n"
                less_msg += LOG.format("{}\n", "\n".join([LOG.format("{}", x, flag=LOG.DARK_GREEN) for x in solution]))
                showWithLess(less_msg);

        return 0

    return ldtCat


if __name__ == "__main__":
    sys.exit(safeRun(getCommand()))
