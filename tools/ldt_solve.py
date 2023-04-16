#!/usr/bin/env python3
from impl import *
import sys
import regex
import dcli
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from questions import *
from filesystem import *
from config import *
import session


def _getComplexityInformation(id: int,
                              snippets: str,
                              tc: str = "",
                              sc: str = "",
                              note: str = ""):
    init_msg = [
        f'# time complexity in the first line:',
        f'# O(',
        f'{tc}',
        f'# )',
        f'',
        f'# space complexity in the second line:',
        f'# O(',
        f'{sc}',
        f'# )',
        f'',
        f'# notes in third line if necessary:',
        f'{note}',
        f'',
        f'# please enter the complexities information for the solution #{id}.',
        f'# lines starting with \'#\' will be ignored.',
        f'# the solution is as follows',
        '# {}'.format(snippets.replace('\n', '\n# '))
    ]
    user_input = inputByEditor('\n'.join(init_msg))
    input_lines = user_input.splitlines()
    if len(input_lines) > 2:
        complexities = []
        for line in input_lines:
            line = line.strip()
            if len(line) > 0 and line[0] != "#":
                complexities.append(line)
        if len(complexities) == 2:
            return complexities[0], complexities[1], ""
        if len(complexities) == 3:
            return complexities[0], complexities[1], complexities[2]
    return "-", "-", "not calculated"


def _modifyResolvedLog(*, solution_file: SolutionFile, resolve_logs: ResolveLogsFile,
                    id: int, timestamp: int):
    LOG = prompt.Log.getInstance()
    log: ResolveLog = None

    if id in resolve_logs:
        log = resolve_logs.getLogById(id)

        tc, sc, notes = _getComplexityInformation(
            id,
            clangFormat(parseSolution(solution_file.read_text())),
            log.tc,
            log.sc,
            log.notes)

        log.tc = tc
        log.sc = sc
        log.notes = notes

    else:
        tc, sc, notes = _getComplexityInformation(
            id,
            clangFormat(parseSolution(solution_file.read_text())))
        log = ResolveLog({"timestamp": timestamp,
                        "id": id,
                        "tc": tc,
                        "sc": sc,
                        "notes": notes})
        resolve_logs.addLog(log)
        LOG.verbose(f"added new resolve log for solution #{log.id} with TC "
                    f"O({log.tc}) and SC O({log.sc}): {log.timestamp}")

        resolve_logs.save()
        LOG.success("the resolve log has been saved: {}",
                    LOG.format(resolve_logs, flag=LOG.HIGHTLIGHT))
    return log


def getCommand(parent=None):
    @dcli.command(
        "solve",
        dcli.arg("-C", dest="src_path", default=str(SRC_ABSOLUTE), action="store",
                 metavar="[Source_Root]", help="specify the source root."),
        dcli.arg("-B", dest="build_path", default=str(BUILD_ABSOLUTE), action="store",
                 metavar="[Build_Path]", help="specify the directory to build. Default: './build'."),
        dcli.arg("--session", dest="session_name", default="", action="store",
                 help="explicitly use specific session cache."),
        dcli.arg("--guest", dest="leetcode_session", default=True, action="store_false",
                 help="identifier to skip the leetcode session establishment."),
        dcli.arg("--list", dest="questions_list_file", default=str(QUESTIONS_LIST_ABSOLUTE), action="store",
                 nargs=1, metavar="[Ques_List]", help="specify the questions list in CSV format."),
        dcli.arg("--resolve", dest="questions_log_file", default=str(QUESTIONS_LOG_ABSOLUTE), action="store",
                 nargs=1, metavar="[Solve_Log]", help="specify the resolve log in CSV format."),
        dcli.arg("--assets", dest="assets_path", default=str(ASSETS_ABSOLUTE), action="store",
                 nargs=1, metavar="[Assets_Path]", help="specify the directory to save created assets."),
        dcli.arg("--docs", dest="docs_path", default=str(DOCS_ABSOLUTE), action="store",
                 metavar="[Docs_Path]", help="specify the directory to save created documents."),
        dcli.arg("--readme", dest="readme_path", default=str(README_ABSOLUTE), action="store",
                 metavar="[Docs_Path]", help="specify the file to save readme."),
        dcli.arg("--no-update", dest="without_update", default=False, action="store_true",
                 help="disable update references after running tests."),
        dcli.arg("--no-commit", dest="without_commit", default=False, action="store_true",
                 help="disable automatic commit after references updating."),
        dcli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
                 help="enable verbose logging."),
        dcli.arg("ids", metavar="id", nargs="+", default=[],
                 type=int, help="question identifiers to add."),
        parent=parent,
        formatter_class=RawTextHelpFormatter, usage="%(prog)s [options] id [id ...]",
        help=fixedWidth(
            "solve problem by their LeetCode identifier.",
            width=60
        ),
        description=fixedWidth(
            'A script to solve multiple unsolve problems by their LeetCode question number. '
            'This script will do the process:',
            '  - Open an editor to solve.',
            '  - Run the testcases.',
            '  - Updates all references such as documents and diagrams.',
            '  - Run `git commit` if all the previous stages passes.'
        )
    )
    def ldtSolve(args: object):
        PMT = prompt.Prompt.getInstance()
        LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
        CONFIG = Configuration.getInstance()

        ARG_SRC_PATH = Path(getattr(args, "src_path")).resolve()
        ARG_BUILD_PATH = Path(getattr(args, "build_path")).resolve()
        ARG_QUESTIONS_LIST = Path(getattr(args, "questions_list_file")).resolve()
        ARG_RESOLVE_LOGS = Path(getattr(args, "questions_log_file")).resolve()
        ARG_ASSETS_PATH = Path(getattr(args, "assets_path")).resolve()
        ARG_DOCS_PATH = Path(getattr(args, "docs_path")).resolve()
        ARG_README = Path(getattr(args, "readme_path")).resolve()
        ARG_SESSION_NAME = getattr(args, "session_name")
        ARG_ENABLE_LEETCODE_SESSION = getattr(args, "leetcode_session")
        ARG_WITHOUT_UPDATE_FLAG = getattr(args, "without_update")
        ARG_WITHOUT_COMMIT_FLAG = getattr(args, "without_commit")
        ARG_IDS: list[int] = getattr(args, "ids")

        LEETCODE_SESSION: session.LeetCodeSession = None

        use_session_name = CONFIG.default_user

        if ARG_SESSION_NAME != "":
            if regex.search('\W', ARG_SESSION_NAME):
                LOG.failure("invalid session name: {}", LOG.format(
                    ARG_SESSION_NAME, flag=LOG.HIGHTLIGHT))
                return 1
            else:
                use_session_name = ARG_SESSION_NAME

        if ARG_ENABLE_LEETCODE_SESSION:

            if use_session_name != "":
                LEETCODE_SESSION = session.LeetCodeSession()

                while not LEETCODE_SESSION.loginWithLeetCodeSession(use_session_name):
                    if not PMT.ask("log in failed, try again?"):
                        LEETCODE_SESSION = None
                        break
            else:
                LOG.warn(
                    "default session name is not set, run |ldt config session| to set the default session.")

        if not checkFile(ARG_QUESTIONS_LIST) or not checkFile(ARG_RESOLVE_LOGS):
            return 1

        if not checkPath(ARG_ASSETS_PATH) or not checkPath(ARG_DOCS_PATH) or not checkPath(ARG_SRC_PATH):
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

        for id in ARG_IDS:
            TIME = int(time.time())
            solution_file = SolutionFile(id, ARG_SRC_PATH)

            LOG.verbose("check whether the solution with id {} exists in: {}", id, solution_file)
            if not solution_file.exists():
                LOG.failure("skip solving question #{} since the solution file not found.",
                            LOG.format(id, flag=LOG.HIGHTLIGHT))
                continue

            LOG.verbose("check whether the detail for question #{} exists.", id)
            if id not in questions_list:
                LOG.failure("there exists no detail for the problem #{} in questions list. "
                            "please update the questions list first.",
                            LOG.format(id, flag=LOG.HIGHTLIGHT))
                LOG.failure("skip solving question #{} due to no information for it.",
                            LOG.format(id, flag=LOG.HIGHTLIGHT))
                continue

            INFO = questions_list[id]

            cpp_solution = requestAndGetCPPSolution(questions_details=INFO,
                                                    solution_file=solution_file)

            original_solution = solution_file.read_text()

            if not solveProblem(build_path=ARG_BUILD_PATH,
                                solution_file=solution_file,
                                detail=INFO,
                                cpp_solution=cpp_solution,
                                leetcode_session=LEETCODE_SESSION):

                LOG.failure("abort solving the problem #{}.",
                            LOG.format(id, flag=LOG.HIGHTLIGHT))

                if PMT.ask("resume the solution #{}?", LOG.format(id, flag=LOG.HIGHTLIGHT)):
                    solution_file.write_text(original_solution)

            else:
                RESOLVE_LOG = _modifyResolvedLog(solution_file=solution_file,
                                                 resolve_logs=resolve_logs,
                                                 id=id,
                                                 timestamp=TIME)
                ADD_CMD = ["git", "-C", PROJECT_ROOT, "add", solution_file, resolve_logs]

                if not ARG_WITHOUT_UPDATE_FLAG:
                    updateResolveReferenceImpl(questions_list=questions_list, resolve_logs=resolve_logs,
                                               docs_path=ARG_DOCS_PATH, assets_path=ARG_ASSETS_PATH, src_path=ARG_SRC_PATH)
                    ADD_CMD += [ARG_DOCS_PATH, ARG_ASSETS_PATH]

                    updateReadmeDocument(resolve_logs=resolve_logs, assets_path=ARG_ASSETS_PATH,
                                         docs_path=ARG_DOCS_PATH, readme_path=ARG_README)
                    ADD_CMD += [ARG_README]

                if not ARG_WITHOUT_COMMIT_FLAG:
                    launchSubprocess(ADD_CMD).communicate()

                    msg = getCommitMessageFromResolveLog(RESOLVE_LOG, "modifies")

                    CMD = ["git", "-C", PROJECT_ROOT, "commit", "-m", msg]
                    launchSubprocess(CMD).communicate()

                    LOG.success("committed with message: {}",
                                LOG.format(msg, flag=LOG.IMPORTANT))

                LOG.success("the solution #{} solved successfully.",
                            LOG.format(id, flag=LOG.HIGHTLIGHT))
        return 0

    return ldtSolve


if __name__ == "__main__":
    sys.exit(safeRun(getCommand()))
