#!/usr/bin/env python3
import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from filesystem import *
from questions import *
import net
import cli


__CACHED_QUESTIONS_LIST: QuestionsList =  None
__CACHED_SOLUTIONS_LIST: list[SolutionFile] = None
__QUESITONS_LIST_PATH: Path = None
__SOLUTIONS_LIST_PATH: Path = None


def __getSolutionsList(path: Path):
    global __CACHED_SOLUTIONS_LIST, __SOLUTIONS_LIST_PATH
    LOG = prompt.Log.getInstance()
    if __SOLUTIONS_LIST_PATH == None or path != __SOLUTIONS_LIST_PATH:
        __CACHED_SOLUTIONS_LIST = None
        __SOLUTIONS_LIST_PATH = path
        LOG.funcVerbose("the path to get solutions list changed, deleted the cache.")
        LOG.funcVerbose("changed solutions list path to: {}", __SOLUTIONS_LIST_PATH)

    if __CACHED_SOLUTIONS_LIST:
        LOG.funcVerbose("cached solutions list found. skipped searching.")
        return __CACHED_SOLUTIONS_LIST

    SEARCH_TASK = LOG.createTaskLog("Search Solutions")
    SEARCH_TASK.begin("searching the solutions in: {}", __SOLUTIONS_LIST_PATH)
    __CACHED_SOLUTIONS_LIST = getSolutionsList(path)
    SEARCH_TASK.done("{} solutions found.", len(
        __CACHED_SOLUTIONS_LIST), is_success=True)

    return __CACHED_SOLUTIONS_LIST


def __getQuestionsList(path: Path):
    global __CACHED_QUESTIONS_LIST, __QUESITONS_LIST_PATH
    assert __QUESITONS_LIST_PATH == None or path == __QUESITONS_LIST_PATH
    LOG = prompt.Log.getInstance()
    if __QUESITONS_LIST_PATH == None or path != __QUESITONS_LIST_PATH:
        __CACHED_QUESTIONS_LIST = None
        __QUESITONS_LIST_PATH = path
        LOG.funcVerbose("the path to get questions list has changed, deleted the cache.")
        LOG.funcVerbose("changed questions list path to: {}", __QUESITONS_LIST_PATH)

    if __CACHED_QUESTIONS_LIST:
        LOG.funcVerbose("cached questions list found. skipped parsing.")
        return __CACHED_QUESTIONS_LIST

    LIST_PARSE_TASK = LOG.createTaskLog("Parse Questions List")
    LIST_PARSE_TASK.begin("parsing the questions list.")
    __CACHED_QUESTIONS_LIST = QuestionsList(__QUESITONS_LIST_PATH)

    if __CACHED_QUESTIONS_LIST.isGood():
        LIST_PARSE_TASK.done("finished the parse.", is_success=True)
    else:
        LIST_PARSE_TASK.done("error occurred while parsing.", is_success=False)
        return None

    LOG.funcVerbose("cached the questions list.")

    return __CACHED_QUESTIONS_LIST


def __UpdateQuestionsListImpl(list_path: Path, src_path: Path):
    import json
    LOG = prompt.Log.getInstance()
    questions_list: QuestionsList = None

    if not src_path.exists():
        LOG.failure("the source directory not found: {}", src_path)
        return 1

    solutions = __getSolutionsList(src_path)
    LOG.log("{} solutions found in: {}", len(solutions),
            LOG.format(src_path, flag=LOG.HIGHTLIGHT))

    if not list_path.exists():
        LOG.log("the questions list not found: {}", list_path)
        LOG.log("new questions list file will be created.")
        questions_list = QuestionsList()
    else:
        questions_list = __getQuestionsList(list_path)
        if not questions_list:
            return 1
        LOG.log("loaded questions list from: {}", LOG.format(list_path, flag=LOG.HIGHTLIGHT))

    raw_list: list[object] = None
    try_cnt = 0
    while True:
        LOG.verbose("trying to get the questions list from LeetCode.")
        state, resp = net.requestQuestionsList()

        if state == net.REQUEST_OK and \
                isinstance(resp, net.requests.Response) and resp.status_code == 200:

            LOG.verbose("trying to parse the response content.")
            raw_list = json.loads(resp.content.decode('utf-8'))
            raw_list = raw_list["stat_status_pairs"]

            LOG.verbose("got and parsed the questions list from LeetCode.")
            break
        else:
            PMT = prompt.Prompt.getInstance()
            if not PMT.ask("failed to get questions list, try again{}?", "" if try_cnt == 0 else f"{try_cnt}"):
                LOG.log("skipped getting questions list.")
                break
        try_cnt += 1

    if raw_list == None or len(questions_list) == len(raw_list):
        LOG.log("no new question found, skipped updating question list.")
    else:
        raw_list.sort(key=lambda q: q['stat']['frontend_question_id'])
        LOG.log("{} new questions found, update to the questions list.",
                len(raw_list) - len(questions_list))

        for info in raw_list:
            ID = info['stat']['frontend_question_id']
            if ID not in questions_list:
                detail = QuestionDetails()
                detail.id = ID
                detail.title = info['stat']['question__title']
                detail.level = info['difficulty']['level']
                detail.slug = info['stat']['question__title_slug']
                detail.paid = info['paid_only']
                questions_list[ID] = detail

    if not questions_list.isGood():
        LOG.failure("refused to update due to invalid questions list.")
        return 1

    LOG.log("try to update solved information.")
    for solution in solutions:
        detail = questions_list[solution.id()]
        if not detail.done:
            detail.done = True
            LOG.log("updated question id: {}", solution.id())

    LOG.verbose("saving the questions list to: ", list_path)
    if not questions_list.save(list_path):
        LOG.failure("failed to save the question list.")
        return 1
    LOG.success("saved the question list: {}", LOG.format(list_path, flag=LOG.HIGHTLIGHT))
    return 0


@cli.command(
    formatter_class=RawTextHelpFormatter,
    name="update", prog=UPDATE_SCRIPT_NAME,
    help=fixedWidth(
        f"update the project documents and diagrams.",
        width=60
    ),
    description=fixedWidth(
        f'A nested script to request and update the questions list and update the readme and '
        f'resolve diagrams including activities and progress SVG.'
    )
)
def ldtUpdate(args: object):
    pass


@cli.command(
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    cli.arg("--src", dest="src_path", default=str(SRC_ABSOLUTE), action="store",
            metavar="[Source_Root]", help="specify the source root."),
    cli.arg("--list", dest="questions_list_file", default=str(QUESTIONS_LIST_ABSOLUTE), action="store",
            nargs=1, metavar="[Ques_List]", help="specify the questions list in CSV format."),
    cli.arg("--resolve", dest="questions_log_file", default=str(QUESTIONS_LOG_ABSOLUTE), action="store",
            nargs=1, metavar="[Solve_Log]", help="specify the resolve log in CSV format."),
    cli.arg("--assets", dest="assets_path", default=str(ASSETS_ABSOLUTE), action="store",
            nargs=1, metavar="[Assets_path]", help="specify the directory to save created assets."),
    cli.arg("--docs", dest="docs_path", default=str(DOCS_ABSOLUTE), action="store",
            nargs=1, metavar="[Docs_path]", help="specify the directory to save created documents."),
    formatter_class=RawTextHelpFormatter,
    parent=ldtUpdate, name="all", prog=UPDATE_ALL_SCRIPT_NAME,
    help=fixedWidth(
        f"update all things which the project has changed.",
        width=60
    ),
    description=fixedWidth(
        f'A simple script to combine the features |{UPDATE_README_SCRIPT_NAME}|, '
        f'|{UPDATE_QUESTIONS_LIST_SCRIPT_NAME}| and |{UPDATE_RESOLVE_DIAGRAMS_SCRIPT_NAME}|.'
    )
)
def UpdateAll(args: object):
    pass


@cli.command(
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    cli.arg("--list", dest="questions_list_file", default=str(QUESTIONS_LIST_ABSOLUTE), action="store",
            nargs=1, metavar="[Ques_List]", help="specify the questions list in CSV format."),
    cli.arg("--resolve", dest="questions_log_file", default=str(QUESTIONS_LOG_ABSOLUTE), action="store",
            nargs=1, metavar="[Solve_Log]", help="specify the resolve log in CSV format."),
    cli.arg("--assets", dest="assets_path", default=str(ASSETS_ABSOLUTE), action="store",
            nargs=1, metavar="[Assets_path]", help="specify the directory to load resolve status."),
    cli.arg("--docs", dest="docs_path", default=str(DOCS_ABSOLUTE), action="store",
            nargs=1, metavar="[Docs_path]", help="specify the directory to load documents."),
    cli.arg("readme_path", metavar="Target", nargs=1, type=str, help="target file to update."),
    formatter_class=RawTextHelpFormatter,
    parent=ldtUpdate, name="readme", prog=UPDATE_README_SCRIPT_NAME,
    help=fixedWidth("update the readme document.", width=60),
    description=fixedWidth('Update the readme document.')
)
def UpdateReadme(args: object):
    pass


@cli.command(
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    cli.arg("--src", dest="src_path", default=str(SRC_ABSOLUTE), action="store",
            metavar="[Source_Root]", help="specify the source root."),
    cli.arg("questions_list", metavar="Target", nargs="?", default=[str(QUESTIONS_LIST_ABSOLUTE)],
            type=str, help="target file to update."),
    formatter_class=RawTextHelpFormatter,
    parent=ldtUpdate, name="list", prog=UPDATE_QUESTIONS_LIST_SCRIPT_NAME,
    help=fixedWidth("request and update the questions list.", width=60 ),
    description=fixedWidth(
        'Request and update the questions list. '
        'Generate the questions list if the specified destination not found or is invalid.'
    )
)
def UpdateQuestionsList(args: object):
    prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    ARG_SRC_PATH = Path(getattr(args, "src_path")).resolve()
    ARG_QUESTIONS_LIST = Path(getattr(args, "questions_list")[0]).resolve()
    return __UpdateQuestionsListImpl(ARG_QUESTIONS_LIST, ARG_SRC_PATH)


@cli.command(
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    cli.arg("--assets", dest="assets_path", default=str(ASSETS_ABSOLUTE), action="store",
            nargs=1, metavar="[Assets_path]", help="specify the directory to save created assets."),
    cli.arg("--docs", dest="docs_path", default=str(DOCS_ABSOLUTE), action="store",
            nargs=1, metavar="[Docs_path]", help="specify the directory to save created documents."),
    formatter_class=RawTextHelpFormatter,
    parent=ldtUpdate, name="diagrams", prog=UPDATE_RESOLVE_DIAGRAMS_SCRIPT_NAME,
    help=fixedWidth("update the resolve diagrams and documents.", width=60 ),
    description=fixedWidth('Update the resolve diagrams and documents.')
)
def UpdateResolveDiagrams(args: object):
    pass


if __name__ == "__main__":
    sys.exit(safeRun(ldtUpdate))
