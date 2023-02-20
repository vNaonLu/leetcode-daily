#!/usr/bin/env python3
import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from filesystem import *
from questions import *
from impl import *
import cli


__CACHED_QUESTIONS_LIST: QuestionsList =  None
__CACHED_SOLUTIONS_LIST: dict[SolutionFile] = None
__CACHED_RESOLVED_LOGS: ResolveLogsFile = None
__QUESITONS_LIST_PATH: Path = None
__SOLUTIONS_LIST_PATH: Path = None
__RESOLVED_LOGS_PATH: Path = None


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
    LIST_PARSE_TASK.begin("parsing the questions list: {}", __QUESITONS_LIST_PATH)
    __CACHED_QUESTIONS_LIST = QuestionsList(__QUESITONS_LIST_PATH)

    if __CACHED_QUESTIONS_LIST.isGood():
        LIST_PARSE_TASK.done("finished the parse: {}",
                             __QUESITONS_LIST_PATH, is_success=True)
    else:
        LIST_PARSE_TASK.done("error occurred while parsing.", is_success=False)
        return None

    LOG.funcVerbose("cached the questions list.")

    return __CACHED_QUESTIONS_LIST


def __getResolvedLogsList(path: Path):
    global __CACHED_RESOLVED_LOGS, __RESOLVED_LOGS_PATH
    assert __RESOLVED_LOGS_PATH == None or path == __RESOLVED_LOGS_PATH
    LOG = prompt.Log.getInstance()
    if __RESOLVED_LOGS_PATH == None or path != __RESOLVED_LOGS_PATH:
        __CACHED_RESOLVED_LOGS = None
        __RESOLVED_LOGS_PATH = path
        LOG.funcVerbose("the path to get resolved logs has changed, deleted the cache.")
        LOG.funcVerbose("changed resolved logs path to: {}", __RESOLVED_LOGS_PATH)

    if __CACHED_RESOLVED_LOGS:
        LOG.funcVerbose("cached resolved logs found. skipped parsing.")
        return __CACHED_RESOLVED_LOGS

    LOGS_PARSE_TASK = LOG.createTaskLog("Parse Resolving Logs")
    LOGS_PARSE_TASK.begin("parsing the resolved logs: {}", __RESOLVED_LOGS_PATH)
    __CACHED_RESOLVED_LOGS = ResolveLogsFile(__RESOLVED_LOGS_PATH)
    LOGS_PARSE_TASK.done("finished the parse: {}", __RESOLVED_LOGS_PATH, is_success=True)

    LOG.funcVerbose("cached the resolved logs.")

    return __CACHED_RESOLVED_LOGS


@cli.command(
    cli.arg("--src", dest="src_path", default=str(SRC_ABSOLUTE), action="store",
            metavar="[Source_Root]", help="specify the source root."),
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
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    formatter_class=RawTextHelpFormatter,
    required_subcmd=False,
    name="update", prog=UPDATE_SCRIPT_NAME,
    help=fixedWidth(
        f"update the project documents and diagrams.",
        width=60
    ),
    description=fixedWidth(
        f'A nested script to request and update the questions list and update the readme and '
        f'resolve diagrams including activities and progress SVG. Run without subcommand works '
        f'same as combination of the features |{UPDATE_QUESTIONS_LIST_SCRIPT_NAME}|, '
        f'|{UPDATE_RESOLVE_REFERENCE_SCRIPT_NAME}| and |{UPDATE_README_SCRIPT_NAME}|.'
    )
)
def ldtUpdate(args: object):
    if getattr(args, "__subfunc") != ldtUpdate:
        return 0
    LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    ARG_SRC_PATH = Path(getattr(args, "src_path")).resolve()
    ARG_QUESTIONS_LIST = Path(getattr(args, "questions_list_file")).resolve()
    ARG_RESOLVE_LOGS = Path(getattr(args, "questions_log_file")).resolve()
    ARG_ASSETS_PATH = Path(getattr(args, "assets_path")).resolve()
    ARG_DOCS_PATH = Path(getattr(args, "docs_path")).resolve()
    ARG_README = Path(getattr(args, "readme_path")).resolve()
    if not checkPath(ARG_ASSETS_PATH) or not checkPath(ARG_DOCS_PATH) or not checkPath(ARG_SRC_PATH):
        return 1
    if not checkFile(ARG_RESOLVE_LOGS) or not checkFile(ARG_README):
        return 1
    
    solutions = __getSolutionsList(ARG_SRC_PATH)
    LOG.log("{} solutions found in: {}", len(solutions),
            LOG.format(ARG_SRC_PATH, flag=LOG.HIGHTLIGHT))
    
    questions_list: QuestionsList = None

    if not ARG_QUESTIONS_LIST.exists():
        LOG.log("the questions list not found: {}", ARG_QUESTIONS_LIST)
        LOG.log("new questions list file will be created.")
        questions_list = QuestionsList()
    else:
        questions_list = __getQuestionsList(ARG_QUESTIONS_LIST)
        if not questions_list:
            return False
        LOG.log("loaded questions list from: {}", LOG.format(ARG_QUESTIONS_LIST, flag=LOG.HIGHTLIGHT))

    resolve_logs = __getResolvedLogsList(ARG_RESOLVE_LOGS)
    LOG.log("loaded {} resolved logs from: {}",
            LOG.format(len(resolve_logs), flag=LOG.HIGHTLIGHT),
            LOG.format(ARG_RESOLVE_LOGS, flag=LOG.HIGHTLIGHT))

    if not updateQuestionsListImpl(list_path=ARG_QUESTIONS_LIST,
                                   questions_list=questions_list):
        return 1

    if not updateResolveReferenceImpl(questions_list=questions_list,
                                      resolve_logs=resolve_logs,
                                      docs_path=ARG_DOCS_PATH,
                                      assets_path=ARG_ASSETS_PATH,
                                      src_path=ARG_SRC_PATH):
        return 1

    if not updateReadmeDocument(resolve_logs=resolve_logs,
                                assets_path=ARG_ASSETS_PATH,
                                docs_path=ARG_DOCS_PATH,
                                readme_path=ARG_README):
        return 1
    return 0


@cli.command(
    cli.arg("--list", dest="questions_list_file", default=str(QUESTIONS_LIST_ABSOLUTE), action="store",
            nargs=1, metavar="[Ques_List]", help="specify the questions list in CSV format."),
    cli.arg("--resolve", dest="questions_log_file", default=str(QUESTIONS_LOG_ABSOLUTE), action="store",
            nargs=1, metavar="[Solve_Log]", help="specify the resolve log in CSV format."),
    cli.arg("--assets", dest="assets_path", default=str(ASSETS_ABSOLUTE), action="store",
            nargs=1, metavar="[Assets_path]", help="specify the directory to load resolve status."),
    cli.arg("--docs", dest="docs_path", default=str(DOCS_ABSOLUTE), action="store",
            nargs=1, metavar="[Docs_path]", help="specify the directory to load documents."),
    cli.arg("readme_path", metavar="Target", nargs="?", default=[str(README_ABSOLUTE)],
            type=str, help="target file to update."),
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    formatter_class=RawTextHelpFormatter,
    parent=ldtUpdate, name="readme", prog=UPDATE_README_SCRIPT_NAME,
    help=fixedWidth("update the readme document.", width=60),
    description=fixedWidth('Update the readme document.')
)
def updateReadme(args: object):
    LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    ARG_QUESTIONS_LIST = Path(getattr(args, "questions_list_file")).resolve()
    ARG_RESOLVE_LOGS = Path(getattr(args, "questions_log_file")).resolve()
    ARG_ASSETS_PATH = Path(getattr(args, "assets_path")).resolve()
    ARG_DOCS_PATH = Path(getattr(args, "docs_path")).resolve()
    ARG_README = Path(getattr(args, "readme_path")[0]).resolve()
    if not checkPath(ARG_ASSETS_PATH) or not checkPath(ARG_DOCS_PATH):
        return 1
    if not checkFile(ARG_QUESTIONS_LIST) or not checkFile(ARG_RESOLVE_LOGS):
        return 1

    resolve_logs = __getResolvedLogsList(ARG_RESOLVE_LOGS)
    LOG.log("loaded {} resolved logs from: {}",
            LOG.format(len(resolve_logs), flag=LOG.HIGHTLIGHT),
            LOG.format(ARG_RESOLVE_LOGS, flag=LOG.HIGHTLIGHT))

    return 0 if updateReadmeDocument(resolve_logs=resolve_logs,
                                     assets_path=ARG_ASSETS_PATH,
                                     docs_path=ARG_DOCS_PATH,
                                     readme_path=ARG_README
                                     ) else 1


@cli.command(
    cli.arg("--src", dest="src_path", default=str(SRC_ABSOLUTE), action="store",
            metavar="[Source_Root]", help="specify the source root."),
    cli.arg("questions_list", metavar="Target", nargs="?", default=[str(QUESTIONS_LIST_ABSOLUTE)],
            type=str, help="target file to update."),
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    formatter_class=RawTextHelpFormatter,
    parent=ldtUpdate, name="list", prog=UPDATE_QUESTIONS_LIST_SCRIPT_NAME,
    help=fixedWidth("request and update the questions list.", width=60 ),
    description=fixedWidth(
        'Request and update the questions list. '
        'Generate the questions list if the specified destination not found or is invalid.'
    )
)
def updateQuestionsList(args: object):
    LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    ARG_SRC_PATH = Path(getattr(args, "src_path")).resolve()
    ARG_QUESTIONS_LIST = Path(getattr(args, "questions_list")[0]).resolve()
    if not checkPath(ARG_SRC_PATH):
        return 1
    
    questions_list: QuestionsList = None

    if not ARG_QUESTIONS_LIST.exists():
        LOG.log("the questions list not found: {}", ARG_QUESTIONS_LIST)
        LOG.log("new questions list file will be created.")
        questions_list = QuestionsList()
    else:
        questions_list = __getQuestionsList(ARG_QUESTIONS_LIST)
        if not questions_list:
            return False
        LOG.log("loaded questions list from: {}",
                LOG.format(ARG_QUESTIONS_LIST, flag=LOG.HIGHTLIGHT))

    return 0 if updateQuestionsListImpl(questions_list=questions_list,
                                        list_path=ARG_QUESTIONS_LIST,
                                        ) else 1


@cli.command(
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
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    formatter_class=RawTextHelpFormatter,
    parent=ldtUpdate, name="ref", prog=UPDATE_RESOLVE_REFERENCE_SCRIPT_NAME,
    help=fixedWidth("update the resolve diagrams and documents.", width=60 ),
    description=fixedWidth('Update the resolve diagrams and documents.')
)
def updateResolveReference(args: object):
    LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    ARG_SRC_PATH = Path(getattr(args, "src_path")).resolve()
    ARG_QUESTIONS_LIST_PATH = Path(getattr(args, "questions_list_file")).resolve()
    ARG_RESOLVE_LOGS_PATH = Path(getattr(args, "questions_log_file")).resolve()
    ARG_ASSETS_PATH = Path(getattr(args, "assets_path")).resolve()
    ARG_DOCS_PATH = Path(getattr(args, "docs_path")).resolve()
    if not checkFile(ARG_QUESTIONS_LIST_PATH) or not checkFile(ARG_RESOLVE_LOGS_PATH):
        return 1
    if not checkPath(ARG_DOCS_PATH) or not checkPath(ARG_ASSETS_PATH) or not checkPath(ARG_SRC_PATH):
        return 1
    
    questions_list = __getQuestionsList(ARG_QUESTIONS_LIST_PATH)
    if not questions_list:
        return False

    resolve_logs = __getResolvedLogsList(ARG_RESOLVE_LOGS_PATH)
    LOG.log("loaded {} resolved logs from: {}",
            LOG.format(len(resolve_logs), flag=LOG.HIGHTLIGHT),
            LOG.format(ARG_RESOLVE_LOGS_PATH, flag=LOG.HIGHTLIGHT))
    return 0 if updateResolveReferenceImpl(questions_list=questions_list,
                                           resolve_logs=resolve_logs,
                                           docs_path=ARG_DOCS_PATH,
                                           assets_path=ARG_ASSETS_PATH,
                                           src_path=ARG_SRC_PATH) else 1


if __name__ == "__main__":
    sys.exit(safeRun(ldtUpdate))
