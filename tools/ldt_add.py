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
                              snippets: str):
    init_msg = [
        f'# time complexity in the first line:',
        f'# O(',
        f'',
        f'# )',
        f'',
        f'# space complexity in the second line:',
        f'# O(',
        f'',
        f'# )',
        f'',
        f'# notes in third line if necessary:',
        f'',
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


def _addResolveLogs(*, solution_file: SolutionFile,
                    resolve_logs: ResolveLogsFile,
                    id: int,
                    timestamp: int):
    LOG = prompt.Log.getInstance()

    tc, sc, notes = _getComplexityInformation(
        id, clangFormat(parseSolution(solution_file.read_text())))

    log = ResolveLog({"timestamp": timestamp,
                      "id": id,
                      "tc": tc,
                      "sc": sc,
                      "notes": notes})
    resolve_logs.addLog(log)
    LOG.funcVerbose(f"added new resolve log for solution #{log.id} with TC "
                    f"O({log.tc}) and SC O({log.sc}): {log.timestamp}")

    resolve_logs.save()
    LOG.success("the resolve log has been saved: {}",
                LOG.format(resolve_logs, flag=LOG.HIGHTLIGHT))
    return log


def getCommand(parent=None):
    @dcli.command(
        "add",
        dcli.arg("-C", dest="src_path", default=str(SRC_ABSOLUTE), action="store",
                 metavar="[Source_Root]", help="specify the source root."),
        dcli.arg("-B", dest="build_path", default=str(BUILD_ABSOLUTE), action="store",
                 metavar="[Build_Path]", help="specify the directory to build. Default: './build'."),
        dcli.arg("-s", "--solve", dest="solve_problem", default=False, action="store_true",
                 help="identifier of whether solving problem."),
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
                 help="disable update references after running tests. only effects with |-s|."),
        dcli.arg("--no-commit", dest="without_commit", default=False, action="store_true",
                 help="disable automatic commit after references updating. only effects with |-s|."),
        dcli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
                 help="enable verbose logging."),
        dcli.arg("ids", metavar="id", nargs="*", default=[],
                 type=int, help="question identifiers to add."),
        parent=parent,
        formatter_class=RawTextHelpFormatter, usage="%(prog)s [options] [id [id ...]]",
        help=fixedWidth(
            "add questions by their LeetCode identifier and generate C++ solution template.",
            width=60
        ),
        description=fixedWidth(
            'A script to add multiple unsolve questions by their LeetCode question number, '
            'and generate a C++ solution template, with GoogleTest interface and several test cases based on'
            'examples on the LeetCode website. This script will automatically grab the question of today if '
            '|ids| is empty and |--guest| is not specified. This script will do the process:',
            '  - Generate the C++ template, and open an editor to solve.',
            '  - Run the testcases.',
            '  - Updates all references such as documents and diagrams.',
            '  - Run `git commit` if all the previous stages passes.'
        )
    )
    def ldtAdd(args: object):
        PMT = prompt.Prompt.getInstance()
        LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
        CONFIG = Configuration.getInstance()

        ARG_SRC_PATH = Path(getattr(args, "src_path")).resolve()
        ARG_BUILD_PATH = Path(getattr(args, "build_path")).resolve()
        ARG_SOLVE_FLAG = getattr(args, "solve_problem")
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

        if len(ARG_IDS) == 0 and LEETCODE_SESSION:
            TASK = LOG.createTaskLog("Question of Today")
            question_of_today: session.LeetCodeSession.QuestionOfToday = None

            try_cnt = 0
            TASK.begin("request question of today...")
            while not question_of_today:
                try:
                    time.sleep(1)
                    TASK.log("request question of today...{}",
                             f'({try_cnt})' if try_cnt > 0 else "")
                    question_of_today = LEETCODE_SESSION.getQuestionOfToday()
                    try_cnt += 1
                except KeyboardInterrupt:
                    break

            if question_of_today:
                TASK.done("get {}", LOG.format('{}. {}', question_of_today.id,
                                               question_of_today.title, flag=LOG.HIGHTLIGHT), is_success=True)
                ARG_IDS.append(question_of_today.id)
            else:
                TASK.done("aborted", is_success=False)

        for id in ARG_IDS:
            ADD_TIME = int(time.time())
            solution_file = SolutionFile(id, ARG_SRC_PATH)

            LOG.funcVerbose("check whether the solution with id {} exists in resolve logs", id)
            if solution_file.id() in resolve_logs:
                LOG.success("skip solving question #{} since the solution exists in resolve logs.",
                            LOG.format(id, flag=LOG.HIGHTLIGHT))
                continue

            LOG.funcVerbose("check whether the solution with id {} exists in: {}", id, solution_file)
            if solution_file.exists():
                if not ARG_SOLVE_FLAG:
                    LOG.success("skip adding solution #{} since it already exists.",
                                LOG.format(id, flag=LOG.HIGHTLIGHT))
                    continue

                LOG.funcVerbose("solution exists, check whether the solution is committed.")
                CMD = ["git", "-C", PROJECT_ROOT, "ls-files", PROJECT_ROOT, "--exclude-standard", "--others"]
                out, _ = launchSubprocess(CMD).communicate()
                LOG.funcVerbose("got stdout: {}", out)
                if not regex.search(solution_file.fileName(), out):
                    LOG.success("skip solving question #{} since the solution exists and has already committed and not been modified.",
                                LOG.format(id, flag=LOG.HIGHTLIGHT))
                    continue

                if not PMT.ask("continue to solve question #{}?",
                               LOG.format(id, flag=LOG.HIGHTLIGHT)):
                    continue

            LOG.funcVerbose("check whether the detail for question #{} exists.", id)
            if id not in questions_list:
                LOG.failure("there does not exist detail for the problem #{} in questions list. "
                            "please update the questions list first.",
                            LOG.format(id, flag=LOG.HIGHTLIGHT))
                return False

            INFO = questions_list[id]


            cpp_solution = requestAndGetCPPSolution(questions_details=INFO,
                                                    solution_file=solution_file)

            LOG.success("the solution #{} added successfully.",
                        LOG.format(id, flag=LOG.HIGHTLIGHT))

            if not ARG_SOLVE_FLAG:
                continue

            if not solveProblem(build_path=ARG_BUILD_PATH,
                                solution_file=solution_file,
                                detail=INFO,
                                cpp_solution=cpp_solution,
                                leetcode_session=LEETCODE_SESSION):

                LOG.failure("abort adding the solution #{}.",
                            LOG.format(id, flag=LOG.HIGHTLIGHT))

                if solution_file.exists() and PMT.ask("remove the solution #{}?", LOG.format(id, flag=LOG.HIGHTLIGHT)):
                    solution_file.unlink()
                    LOG.log("remove the file: {}", LOG.format(
                        solution_file, LOG.HIGHTLIGHT))

            else:
                if not ARG_WITHOUT_COMMIT_FLAG:
                    RESOLVE_LOG = _addResolveLogs(solution_file=solution_file,
                                                resolve_logs=resolve_logs,
                                                id=id,
                                                timestamp=ADD_TIME)

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

                    msg = getCommitMessageFromResolveLog(RESOLVE_LOG, "adds")

                    CMD = ["git", "-C", PROJECT_ROOT, "commit", "-m", msg]
                    launchSubprocess(CMD).communicate()

                    LOG.success("committed with message: {}",
                                LOG.format(msg, flag=LOG.IMPORTANT))

                LOG.success("the solution #{} solved successfully.",
                            LOG.format(id, flag=LOG.HIGHTLIGHT))
        return 0

    return ldtAdd


if __name__ == "__main__":
    sys.exit(safeRun(getCommand()))
