#!/usr/bin/env python3
import sys
import json
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from questions import *
from filesystem import *
from code_gen import *
import net
import cli

def __checkPath(path: Path):
    assert isinstance(path, Path)
    LOG = prompt.Log.getInstance()
    LOG.funcVerbose("check whether the destination is directory: {}", path)
    if not path.exists():
        LOG.failure("the directory not found: {}", path)
        return False
    elif not path.is_dir():
        LOG.failure("the path is not a directory: {}", path)
        return False
    return True


def __checkFile(path: Path):
    assert isinstance(path, Path)
    LOG = prompt.Log.getInstance()
    LOG.funcVerbose("check whether the destination is file: {}", path)
    if not path.exists():
        LOG.failure("the file not found: {}", path)
        return False
    elif not path.is_file():
        LOG.failure("the path is not a file: {}", path)
        return False
    return True


def _addSolutionImpl(*, questions_list: QuestionsList, solution_file: SolutionFile, no_testcases: bool):
    LOG = prompt.Log.getInstance()
    id = solution_file.id()

    LOG.verbose("check whether the solution with id {} exists in: {}", id, solution_file)
    if solution_file.exists():
        LOG.failure("the solution for question #{} already exists.",
                    LOG.format(id, flag=LOG.HIGHTLIGHT))
        return False

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
    code_template = LeetCodeSolutionTemplate(not no_testcases, code_obj=raw_content)

    gen_task = LOG.createTaskLog(f"Generate Template for Solution #{id}")
    gen_task.begin("generating the solution template: {}",
                   LOG.format(slug, flag=LOG.HIGHTLIGHT))
    content = code_template.template(f"The file is generated by {SCRIPT_NAME}", 70)
    gen_task.done("generated the solution template: {}",
                  LOG.format(slug, flag=LOG.HIGHTLIGHT),
                  is_success=True)
    
    with solution_file.open("w") as f:
        f.write(clangFormat(content))
        LOG.success("added the solution file for question #{}: {}",
                    LOG.format(id, flag=LOG.HIGHTLIGHT),
                    LOG.format(solution_file, flag=LOG.HIGHTLIGHT))

    return True


@cli.command(
    cli.arg("-C", dest="src_path", default=str(SRC_ABSOLUTE), action="store",
            metavar="[Source_Root]", help="specify the source root."),
    cli.arg("--no-case", dest="no_testcase", default=False, action="store_true",
            help="disable test cases generation."),
    cli.arg("--list", dest="questions_list_file", default=str(QUESTIONS_LIST_ABSOLUTE), action="store",
            nargs=1, metavar="[Ques_List]", help="specify the questions list in CSV format."),
    cli.arg("--resolve", dest="questions_log_file", default=str(QUESTIONS_LOG_ABSOLUTE), action="store",
            nargs=1, metavar="[Solve_Log]", help="specify the resolve log in CSV format."),
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
        'examples on the LeetCode website. This script will not update the questions lists.'
    )
)
def ldtAdd(args: object):
    LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    ARG_NOTESTCASE_FLAG = getattr(args, "no_testcase")
    ARG_SRC_PATH = Path(getattr(args, "src_path")).resolve()
    ARG_QUESTIONS_LIST = Path(getattr(args, "questions_list_file")).resolve()
    ARG_RESOLVE_LOGS = Path(getattr(args, "questions_log_file")).resolve()
    ARG_IDS = getattr(args, "ids")

    if not __checkFile(ARG_QUESTIONS_LIST) or not __checkFile(ARG_RESOLVE_LOGS):
        return 1
    if not __checkPath(ARG_SRC_PATH):
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

    add_cnt = 0
    for id in ARG_IDS:
        solution_file = SolutionFile(id, ARG_SRC_PATH)
        if not _addSolutionImpl(questions_list=questions_list,
                                solution_file=solution_file,
                                no_testcases=ARG_NOTESTCASE_FLAG):
            LOG.log("skipped adding solution for question #{}.",
                    LOG.format(id, flag=LOG.HIGHTLIGHT))
            continue

        log = ResolveLog([int(time.time()), id])
        resolve_logs.addLog(log)
        LOG.verbose("added new resolve log for solution #{}: {}", log.id, log.timestamp)
        add_cnt += 1

    if add_cnt > 0:
        resolve_logs.save(ARG_RESOLVE_LOGS)
        LOG.success("the resolve log has been saved: {}",
                    LOG.format(ARG_RESOLVE_LOGS, flag=LOG.HIGHTLIGHT))

if __name__ == "__main__":
    sys.exit(ldtAdd())
