#!/usr/bin/env python3
from impl import *
import sys
import json
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from cpp_solution import *
from questions import *
from filesystem import *
import net
import cli


def _addSolutionImpl(*, questions_list: QuestionsList, solution_file: SolutionFile, no_testcases: bool):
    LOG = prompt.Log.getInstance()
    id = solution_file.id()

    LOG.verbose("check whether the detail for question #{} exists.", id)
    if id not in questions_list:
        LOG.failure("there exists no detail for question #{} in questions list. "
                    "please update the questions list first.",
                    LOG.format(id, flag=LOG.HIGHTLIGHT))
        return False
        
    raw_content: object = None
    slug = questions_list[id].slug
    try_cnt = 0
    while True:
        LOG.verbose("trying to get the information about question #{} from LeetCode.", id)
        state, resp = net.requestQuestionInformation(slug)

        if state == net.REQUEST_OK and \
                isinstance(resp, net.requests.Response) and resp.status_code == 200:

            LOG.verbose("trying to parse the response content.")
            raw_content = json.loads(resp.content.decode('utf-8'))['data']['question']
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
        return False

    gen_task = LOG.createTaskLog(f"Generate Template for Solution #{id}")
    gen_task.begin("generating the solution template: {}",
                   LOG.format(slug, flag=LOG.HIGHTLIGHT))
    content = cpp_solution.solutionTemplate()
    gen_task.done("generated the solution template: {}",
                  LOG.format(slug, flag=LOG.HIGHTLIGHT),
                  is_success=True)

    if not solution_file.parent.exists():
        solution_file.parent.mkdir(exist_ok=True)
        LOG.log("generated the directory: {}", LOG.format(
            solution_file.parent, LOG.HIGHTLIGHT))

    solution_file.write_text(clangFormat(content))
    LOG.success("saved the solution file for question #{}: {}",
                LOG.format(id, flag=LOG.HIGHTLIGHT),
                LOG.format(solution_file, flag=LOG.HIGHTLIGHT))
    return True


def _addResolveLogs(*, solution_file: SolutionFile, resolve_logs: ResolveLogsFile, id: int, timestamp: int):
    LOG = prompt.Log.getInstance()

    tc, sc, notes = _getComplexityInformation(id,
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


def _addProcess(*,
                src_path: Path,
                build_path: Path,
                docs_path: Path,
                assets_path: Path,
                readme_path: Path,
                questions_list: QuestionsList,
                resolve_logs: ResolveLogsFile,
                solution_file: SolutionFile,
                without_testcase: bool,
                without_test: bool,
                without_update: bool,
                without_commit: bool):
    PMT = prompt.Prompt.getInstance()
    LOG = prompt.Log.getInstance()
    ADD_TIME = int(time.time())
    ID = solution_file.id()

    if not _addSolutionImpl(questions_list=questions_list,
                            solution_file=solution_file,
                            no_testcases=without_testcase):
        return False

    openEditor(solution_file)

    if without_test:
        LOG.log("skipped running testcase due to enabling flag: {}",
                LOG.format("--without-test", flag=LOG.HIGHTLIGHT))
        _addResolveLogs(solution_file=solution_file,
                        resolve_logs=resolve_logs,
                        id=ID, timestamp=ADD_TIME)
        return True

    ldtGenImpl(src_path=PROJECT_ROOT,
               build_path=build_path,
               build_flag="Debug",
               compile_commands_flag="OFF",
               leetcode_test_flag="ON",
               infra_test_flag="ON")

    test_passed = False
    while not test_passed:
        test_passed = ldtBuildImpl(build_path=build_path) == 0 and \
            ldtRunImpl(build_path=build_path, infra_test=False, ids=[ID]) == 0

        if test_passed:
            LOG.log("while passed all local test cases, "
                    "please try submitting to LeetCode to see whether the solution is correct:")
            LOG.print(clangFormat(parseSolution(solution_file.read_text())),
                      flag=LOG.DARK_GREEN)
            if not PMT.ask("was the solution accepted by LeetCode?"):
                test_passed = False
        else:
            if not PMT.ask("the solution #{} failed to pass the testcases, continue to solve?",
                       LOG.format(ID, flag=LOG.HIGHTLIGHT)):
                return False

        if not test_passed:
            openEditor(solution_file)

    resolve = _addResolveLogs(solution_file=solution_file,
                              resolve_logs=resolve_logs,
                              id=ID, timestamp=ADD_TIME)

    if without_update:
        LOG.log("skipped updating documents due to enabling flag: {}",
                LOG.format("--without-update", flag=LOG.HIGHTLIGHT))
        return True

    if not updateResolveReferenceImpl(questions_list=questions_list,
                                      resolve_logs=resolve_logs,
                                      docs_path=docs_path,
                                      assets_path=assets_path,
                                      src_path=src_path):
        LOG.failure("failed to update references.")
        return False

    if not updateReadmeDocument(resolve_logs=resolve_logs,
                                assets_path=assets_path,
                                docs_path=docs_path,
                                readme_path=readme_path):
        LOG.failure("failed to update readme.")
        return False

    if not without_commit:
        CMD = ["git", "-C", PROJECT_ROOT, "add",
               solution_file, readme_path, docs_path, assets_path, resolve_logs]
        launchSubprocess(CMD).communicate()

        commit_msg = f"adds q{ID}"
        if resolve.tc != "-" and resolve.sc != "-":
            commit_msg += f" with TC O({resolve.tc}) and SC O({resolve.sc})"
            if resolve.notes != "":
                commit_msg += f", {resolve.notes}"
        commit_msg += "."

        CMD = ["git", "-C", PROJECT_ROOT, "commit", "-m", commit_msg]
        launchSubprocess(CMD).communicate()
        LOG.success("committed with message: {}",
                    LOG.format(commit_msg, flag=LOG.IMPORTANT))

    return True


def _getComplexityInformation(id: int, snippets: str):
    init_msg = [
        f'# The Solution #{id} requires complexities information.',
        f'# Time complexity in the first line:',
        f'# O(',
        f'',
        f'# )',
        f'',
        f'# Space complexity in the second line:',
        f'# O(',
        f'',
        f'# )',
        f'',
        f'# Notes in third line if necessary:',
        f'',
        f'',
        f'# The solution is as follows',
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
    return "-", "-", ""


@cli.command(
    cli.arg("-C", dest="src_path", default=str(SRC_ABSOLUTE), action="store",
            metavar="[Source_Root]", help="specify the source root."),
    cli.arg("-B", dest="build_path", default=str(BUILD_ABSOLUTE), action="store",
            metavar="[Build_Path]", help="specify the directory to build. Default: './build'."),
    cli.arg("--list", dest="questions_list_file", default=str(QUESTIONS_LIST_ABSOLUTE), action="store",
            nargs=1, metavar="[Ques_List]", help="specify the questions list in CSV format."),
    cli.arg("--resolve", dest="questions_log_file", default=str(QUESTIONS_LOG_ABSOLUTE), action="store",
            nargs=1, metavar="[Solve_Log]", help="specify the resolve log in CSV format."),
    cli.arg("--assets", dest="assets_path", default=str(ASSETS_ABSOLUTE), action="store",
            nargs=1, metavar="[Assets_path]", help="specify the directory to save created assets."),
    cli.arg("--docs", dest="docs_path", default=str(DOCS_ABSOLUTE), action="store",
            metavar="[Docs_path]", help="specify the directory to save created documents."),
    cli.arg("--readme", dest="readme_path", default=str(README_ABSOLUTE), action="store",
            metavar="[Docs_path]", help="specify the file to save readme."),
    cli.arg("--without-testcase", dest="without_testcase", default=False, action="store_true",
            help="disable test cases generation."),
    cli.arg("--without-test", dest="without_test", default=False, action="store_true",
            help="disable run test after each problem solving."),
    cli.arg("--without-update", dest="without_update", default=False, action="store_true",
            help="disable update references after running tests."),
    cli.arg("--no-commit", dest="without_commit", default=False, action="store_true",
            help="disable automatic commit after references updating."),
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    cli.arg("ids", metavar="id", nargs="+", type=int, help="question identifiers to add."),
    formatter_class=RawTextHelpFormatter, usage="%(prog)s [options] id [id ...]",
    name="add", prog=ADD_SCRIPT_NAME,
    help=fixedWidth(
        "add questions by their LeetCode identifier and generate C++ solution template.",
        width=60
    ),
    description=fixedWidth(
        'A script to add multiple unsolve questions by their LeetCode question number, '
        'and generate a C++ solution template, which is based on the code snippet queied'
        'from LeetCode, with GoogleTest interface and several test cases based on'
        'examples on the LeetCode website. This script will do the process:',
        '  - Generate the C++ template, and open an editor to solve.',
        '  - Run the testcases.',
        '  - Updates all references such as documents and diagrams.',
        '  - Run `git commit` if all the previous stages passes.'
    )
)
def ldtAdd(args: object):
    LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    ARG_SRC_PATH = Path(getattr(args, "src_path")).resolve()
    ARG_BUILD_PATH = Path(getattr(args, "build_path")).resolve()
    ARG_QUESTIONS_LIST = Path(getattr(args, "questions_list_file")).resolve()
    ARG_RESOLVE_LOGS = Path(getattr(args, "questions_log_file")).resolve()
    ARG_ASSETS_PATH = Path(getattr(args, "assets_path")).resolve()
    ARG_DOCS_PATH = Path(getattr(args, "docs_path")).resolve()
    ARG_README = Path(getattr(args, "readme_path")).resolve()
    ARG_NOTESTCASE_FLAG = getattr(args, "without_testcase")
    ARG_WITHOUT_TEST_FLAG = getattr(args, "without_test")
    ARG_WITHOUT_UPDATE_FLAG = getattr(args, "without_update")
    ARG_WITHOUT_COMMIT_FLAG = getattr(args, "without_commit")
    ARG_IDS = getattr(args, "ids")

    if not checkFile(ARG_QUESTIONS_LIST) or not checkFile(ARG_RESOLVE_LOGS):
        return 1
    if not checkPath(ARG_ASSETS_PATH) or not checkPath(ARG_DOCS_PATH) or not checkPath(ARG_SRC_PATH):
        return 1
    
    LOGS_PARSE_TASK = LOG.createTaskLog("Parse Resolving Logs")
    LOGS_PARSE_TASK.begin("parsing the resolved logs: {}", ARG_RESOLVE_LOGS)
    resolve_logs = ResolveLogsFile(ARG_RESOLVE_LOGS)
    LOGS_PARSE_TASK.done("loaded {} resolved logs from: {}",
                         LOG.format(len(resolve_logs), flag=LOG.HIGHTLIGHT),
                         LOG.format(ARG_RESOLVE_LOGS, flag=LOG.HIGHTLIGHT),
                         is_success=True)

    QLIST_PARSE_TASK = LOG.createTaskLog("Parse Questions list")
    QLIST_PARSE_TASK.begin("parsing the questions list: {}", ARG_QUESTIONS_LIST)
    questions_list = QuestionsList(ARG_QUESTIONS_LIST)
    QLIST_PARSE_TASK.done("loaded {} questions details from: {}",
                          LOG.format(len(questions_list), flag=LOG.HIGHTLIGHT),
                          LOG.format(ARG_QUESTIONS_LIST, flag=LOG.HIGHTLIGHT),
                          is_success=True)

    for id in ARG_IDS:
        solution_file = SolutionFile(id, ARG_SRC_PATH)

        LOG.verbose("check whether the solution with id {} exists in: {}", id, solution_file)
        if solution_file.exists():
            LOG.warn("the solution for question #{} already exists. skipped.",
                     LOG.format(id, flag=LOG.HIGHTLIGHT))
            continue

        if not _addProcess(src_path=ARG_SRC_PATH,
                           build_path=ARG_BUILD_PATH,
                           docs_path=ARG_DOCS_PATH,
                           assets_path=ARG_ASSETS_PATH,
                           readme_path=ARG_README,
                           questions_list=questions_list,
                           resolve_logs=resolve_logs,
                           solution_file=solution_file,
                           without_testcase=ARG_NOTESTCASE_FLAG,
                           without_test=ARG_WITHOUT_TEST_FLAG,
                           without_update=ARG_WITHOUT_UPDATE_FLAG,
                           without_commit=ARG_WITHOUT_COMMIT_FLAG):
            LOG.failure("abort adding the solution #{}.", LOG.format(id, flag=LOG.HIGHTLIGHT))
            solution_file.unlink()
            LOG.log("remove the file: {}", LOG.format(solution_file, LOG.HIGHTLIGHT))
            continue
        LOG.success("the solution #{} added successfully.",
                    LOG.format(id, flag=LOG.HIGHTLIGHT))

if __name__ == "__main__":
    sys.exit(safeRun(ldtAdd))
