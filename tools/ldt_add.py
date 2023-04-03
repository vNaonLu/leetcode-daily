#!/usr/bin/env python3
from impl import *
import sys
import json
import regex
import dcli
from argparse import RawTextHelpFormatter
from enum import Enum
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from cpp_solution import *
from questions import *
from filesystem import *
from config import *
import net
import session


def _getComplexityInformation(id: int, snippets: str):
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


def _getCPPSolution(*, questions_details: QuestionDetails, solution_file: SolutionFile):
    LOG = prompt.Log.getInstance()
    ID = questions_details.id

    raw_content: object = None
    slug = questions_details.slug
    try_cnt = 0
    while True:
        LOG.verbose(
            "trying to get the information about question #{} from LeetCode.", ID)
        state, resp = net.requestQuestionInformation(slug)

        if state == net.REQUEST_OK and \
                isinstance(resp, net.requests.Response) and resp.status_code == 200:

            LOG.verbose("trying to parse the response content.")
            raw_content = json.loads(
                resp.content.decode('utf-8'))['data']['question']
            LOG.verbose("got and parsed the questions list from LeetCode.")
            break
        else:
            PMT = prompt.Prompt.getInstance()
            if not PMT.ask("failed to get questions list, try again{}?",
                           "" if try_cnt == 0 else f" ({try_cnt})"):
                LOG.log("skipped getting questions list.")
                break
        try_cnt += 1

    LOG.verbose("generate the code template")
    try:
        cpp_solution = CPPSolution(raw_content)
    except Exception as _:
        LOG.failure("caught exception when generating the C++ template.")
        return None

    if not solution_file.parent.exists():
        solution_file.parent.mkdir(exist_ok=True)
        LOG.log("generated the directory: {}", LOG.format(
            solution_file.parent, LOG.HIGHTLIGHT))

    if not solution_file.exists():
        gen_task = LOG.createTaskLog(f"Generate Template for Solution #{ID}")
        gen_task.begin("generating the solution template: {}",
                       LOG.format(slug, flag=LOG.HIGHTLIGHT))
        content = cpp_solution.solutionTemplate()
        gen_task.done("generated the solution template: {}",
                      LOG.format(slug, flag=LOG.HIGHTLIGHT), is_success=True)

        solution_file.write_text(clangFormat(content))
        LOG.success("saved the solution file for question #{}: {}",
                    LOG.format(ID, flag=LOG.HIGHTLIGHT),
                    LOG.format(solution_file, flag=LOG.HIGHTLIGHT))

    return cpp_solution


def _addResolveLogs(*, solution_file: SolutionFile, resolve_logs: ResolveLogsFile,
                    id: int, timestamp: int):
    LOG = prompt.Log.getInstance()

    tc, sc, notes = _getComplexityInformation(
        id, clangFormat(parseSolution(solution_file.read_text())))

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


class _UploadResult(Enum):
    Passed = 0
    Failed = 1
    UnsolvdProblem = 2


def _uploadToLeetCode(*, solution_file: SolutionFile,
                      leetcode_session: session.LeetCodeSession,
                      detail: QuestionDetails,
                      cpp_solution: CPPSolution,
                      answer: str) -> _UploadResult:
    result = _UploadResult.Failed
    LOG = prompt.Log.getInstance()
    PMT = prompt.Prompt.getInstance()
    TASK = LOG.createTaskLog("Submit to LeetCode")
    TASK.begin("connecting to LeetCode...")
    submission = leetcode_session.submitSolution(backend_id=detail.backend_id,
                                                 slug=detail.slug,
                                                 content=answer,
                                                 TASK=TASK)

    if not submission:
        Result = session.Submission.Result
        result = _UploadResult.Failed

        if submission.result == Result.WRONG_ANSWER:
            TASK.done("testcase not accepted due to Wrong Answer: {}", LOG.format(
                repr(submission.last_input), flag=LOG.HIGHTLIGHT), is_success=False)
        elif submission.result == Result.RUNTIME_ERROR:
            TASK.done("testcase not accepted due to Runtime Error: {}", LOG.format(
                submission.error_msg, flag=LOG.HIGHTLIGHT), is_success=False)
        elif submission.result == Result.TLE_ERROR:
            TASK.done("testcase not accepted due to Time Limit Exceed: {}", LOG.format(
                submission.error_msg, flag=LOG.HIGHTLIGHT), is_success=False)
            cpp_solution.setUnittestTimeout(submission.elapse_time)
        else:
            TASK.done("error: {}", LOG.format(
                submission.result, flag=LOG.HIGHTLIGHT), is_success=False)
            result = _UploadResult.UnsolvdProblem
            return result

        if submission.last_input != "" and submission.expect_output != "":
            gen_task = LOG.createTaskLog("Generate Unittest")
            gen_task.begin("generating testcase...")
            extra_input_idx = getCurrentUnittestExtraIndex(solution_file.read_text()) + 1
            unittest, suite_name = cpp_solution.getUnitTestFromSubmissionResult(
                name=f'Extra Testcase #{extra_input_idx}',
                suite_name=getExtraUnittestSuite(extra_input_idx),
                input=submission.last_input,
                output=submission.expect_output)
            gen_task.log("writing to solution file...")
            content = solution_file.read_text() + f'\n{unittest}'
            solution_file.write_text(clangFormat(content))
            gen_task.done("added an extra testcase for solution: {}",
                            LOG.format(suite_name, flag=LOG.HIGHTLIGHT), is_success=True)

    else:
        TASK.done("accepted by LeetCode", is_success=True)
        LOG.log("the solution was accepted by LeetCode which beats {} in runtime and {} in memory usage.",
                LOG.format("{:3.2f}%", submission.runtime_percent, flag=LOG.HIGHTLIGHT),
                LOG.format("{:3.2f}%", submission.memory_percent, flag=LOG.HIGHTLIGHT))

        result = _UploadResult.Passed

    return result


def _buildAndTest(*, build_path: Path, solution_file: SolutionFile, id: int,
                  detail: QuestionDetails, cpp_solution: CPPSolution,
                  leetcode_session: session.LeetCodeSession) -> bool:
    PMT = prompt.Prompt.getInstance()
    LOG = prompt.Log.getInstance()

    ldtGenImpl(src_path=PROJECT_ROOT,
               build_path=build_path,
               build_flag="Debug",
               compile_commands_flag="ON",
               leetcode_test_flag="ON",
               infra_test_flag="ON")

    test_passed = False
    while not test_passed:
        test_passed = ldtBuildImpl(build_path=build_path, build_args="-j8") == 0 and \
            ldtRunImpl(build_path=build_path, infra_test=False, ids=[id]) == 0

        if test_passed:
            answer = clangFormat(parseSolution(solution_file.read_text()))
            session_mode = leetcode_session is not None

            if session_mode:
                if not PMT.ask("passed all local test cases, submit the answer to LeetCode?"):
                    test_passed = False
                else:
                    result = _uploadToLeetCode(solution_file=solution_file,
                                               leetcode_session=leetcode_session,
                                               detail=detail,
                                               cpp_solution=cpp_solution,
                                               answer=answer)
                    if result == _UploadResult.UnsolvdProblem and \
                            PMT.ask("there are some unsolved problem in LeetCode session, switch to non-session mode?"):
                        session_mode = False
                        leetcode_session = None
                        test_passed = False
                        LOG.log("switched to non-session mode.")

                    elif result == _UploadResult.Passed:
                        if not PMT.ask("mark the question #{} as done?", LOG.format(detail.id, flag=LOG.HIGHTLIGHT)):
                           test_passed = False

            if test_passed and not session_mode:
                LOG.log("while passed all local test cases, "
                        "please try submitting to LeetCode to see whether the solution is correct:")
                LOG.print(answer, flag=LOG.DARK_GREEN)
                if not PMT.ask("was the solution accepted by LeetCode?"):
                    test_passed = False

                    if PMT.ask("add an extra test case for unittest?"):
                        extra_input = inputByEditor(cpp_solution.genExtraInputPrompt(id=id,
                                                                                     title=detail.title))
                        input, expect = cpp_solution.parseExtraInput(extra_input)
                        if input and expect:
                            extra_input_idx = getCurrentUnittestExtraIndex(solution_file.read_text()) + 1
                            unittest, suite_name = cpp_solution.getUnitTest(
                                name=f'Extra Testcase #{extra_input_idx}',
                                suite_name=getExtraUnittestSuite(extra_input_idx),
                                input=input, output=expect)
                            content = solution_file.read_text() + f'\n{unittest}'
                            solution_file.write_text(clangFormat(content))
                            LOG.success("added an extra testcase for solution: {}",
                                        LOG.format(suite_name, flag=LOG.HIGHTLIGHT))

        if not test_passed:
            if not PMT.ask("continue to write the solution #{} ?", LOG.format(id, flag=LOG.HIGHTLIGHT)):
                break
            openEditor(solution_file, line=getSolutionLine(solution_file.read_text()))
            solution_file.write_text(clangFormat(solution_file.read_text()))

    return test_passed


def _addAndPassTestsIfNecessary(*, build_path: Path, questions_list: QuestionsList,
                                solution_file: SolutionFile, without_test: bool,
                                leetcode_session: session.LeetCodeSession) -> bool:
    LOG = prompt.Log.getInstance()
    ID = solution_file.id()

    LOG.verbose("check whether the detail for question #{} exists.", ID)
    if ID not in questions_list:
        LOG.failure("there exists no detail for question #{} in questions list. "
                    "please update the questions list first.",
                    LOG.format(ID, flag=LOG.HIGHTLIGHT))
        return False

    INFO = questions_list[ID]

    cpp_solution = _getCPPSolution(questions_details=INFO,
                                   solution_file=solution_file)

    if not cpp_solution:
        return False

    openEditor(solution_file, line=getSolutionLine(solution_file.read_text()))
    solution_file.write_text(clangFormat(solution_file.read_text()))

    if not without_test:
        return _buildAndTest(build_path=build_path, solution_file=solution_file, id=ID, detail=INFO,
                             cpp_solution=cpp_solution, leetcode_session=leetcode_session)

    return True


def getCommand(parent=None):
    @dcli.command(
        "add",
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
        dcli.arg("--without-test", dest="without_test", default=False, action="store_true",
                 help="disable run test after each problem solving."),
        dcli.arg("--without-update", dest="without_update", default=False, action="store_true",
                 help="disable update references after running tests."),
        dcli.arg("--no-commit", dest="without_commit", default=False, action="store_true",
                 help="disable automatic commit after references updating."),
        dcli.arg("--no-cache", dest="no_cache", default=False, action="store_true",
                 help="delete the LeetCode session cache."),
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
        ARG_QUESTIONS_LIST = Path(getattr(args, "questions_list_file")).resolve()
        ARG_RESOLVE_LOGS = Path(getattr(args, "questions_log_file")).resolve()
        ARG_ASSETS_PATH = Path(getattr(args, "assets_path")).resolve()
        ARG_DOCS_PATH = Path(getattr(args, "docs_path")).resolve()
        ARG_README = Path(getattr(args, "readme_path")).resolve()
        ARG_SESSION_NAME = getattr(args, "session_name")
        ARG_ENABLE_LEETCODE_SESSION = getattr(args, "leetcode_session")
        ARG_WITHOUT_TEST_FLAG = getattr(args, "without_test")
        ARG_WITHOUT_UPDATE_FLAG = getattr(args, "without_update")
        ARG_WITHOUT_COMMIT_FLAG = getattr(args, "without_commit")
        ARG_NO_CACHE = getattr(args, "no_cache")
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

                while not LEETCODE_SESSION.loginWithLeetCodeSession(use_session_name, use_cache=not ARG_NO_CACHE):
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

            LOG.verbose("check whether the solution with id {} exists in: {}", id, solution_file)
            if solution_file.exists():
                LOG.verbose("solution exists, check whether the solution is committed.")
                CMD = ["git", "-C", PROJECT_ROOT, "ls-files",
                       PROJECT_ROOT, "--exclude-standard", "--others"]
                out, _ = launchSubprocess(CMD).communicate()
                LOG.verbose("got stdout: {}", out)
                if not regex.search(solution_file.fileName(), out):
                    LOG.success("skip solving question #{} since the solution exists and has already committed.",
                                LOG.format(id, flag=LOG.HIGHTLIGHT))
                    continue
                elif not PMT.ask("continue to solve question #{}?",
                                 LOG.format(id, flag=LOG.HIGHTLIGHT)):
                    continue

            if not _addAndPassTestsIfNecessary(build_path=ARG_BUILD_PATH, questions_list=questions_list,
                                               solution_file=solution_file, without_test=ARG_WITHOUT_TEST_FLAG,
                                               leetcode_session=LEETCODE_SESSION):

                LOG.failure("abort adding the solution #{}.",
                            LOG.format(id, flag=LOG.HIGHTLIGHT))

                if solution_file.exists() and PMT.ask("remove the solution #{}?", LOG.format(id, flag=LOG.HIGHTLIGHT)):
                    solution_file.unlink()
                    LOG.log("remove the file: {}", LOG.format(
                        solution_file, LOG.HIGHTLIGHT))

            else:
                RESOLVE_LOG = _addResolveLogs(solution_file=solution_file, resolve_logs=resolve_logs,
                                              id=id, timestamp=ADD_TIME)
                ADD_CMD = ["git", "-C", PROJECT_ROOT,
                           "add", solution_file, resolve_logs]

                if not ARG_WITHOUT_UPDATE_FLAG:
                    updateResolveReferenceImpl(questions_list=questions_list, resolve_logs=resolve_logs,
                                               docs_path=ARG_DOCS_PATH, assets_path=ARG_ASSETS_PATH, src_path=ARG_SRC_PATH)
                    ADD_CMD += [ARG_DOCS_PATH, ARG_ASSETS_PATH]

                    updateReadmeDocument(resolve_logs=resolve_logs, assets_path=ARG_ASSETS_PATH,
                                         docs_path=ARG_DOCS_PATH, readme_path=ARG_README)
                    ADD_CMD += [ARG_README]

                if not ARG_WITHOUT_COMMIT_FLAG:
                    launchSubprocess(ADD_CMD).communicate()

                    commit_msg = f"adds q{id}"
                    if RESOLVE_LOG.tc != "-" and RESOLVE_LOG.sc != "-":
                        commit_msg += f" with TC O({RESOLVE_LOG.tc}) and SC O({RESOLVE_LOG.sc})"
                        if RESOLVE_LOG.notes != "":
                            commit_msg += f", where {RESOLVE_LOG.notes}"
                    commit_msg += "."

                    CMD = ["git", "-C", PROJECT_ROOT,
                           "commit", "-m", commit_msg]
                    launchSubprocess(CMD).communicate()

                    LOG.success("committed with message: {}",
                                LOG.format(commit_msg, flag=LOG.IMPORTANT))

                LOG.success("the solution #{} added successfully.",
                            LOG.format(id, flag=LOG.HIGHTLIGHT))
        return 0

    return ldtAdd


if __name__ == "__main__":
    sys.exit(safeRun(getCommand()))
