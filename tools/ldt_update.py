#!/usr/bin/env python3
import sys
from argparse import RawTextHelpFormatter
from datetime import datetime, timedelta
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from filesystem import *
from questions import *
from refs import *
import net
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


def __logListToCntList(logs: list[list[list[logs.ResolveLog]]]):
    return [[len(d) for d in m] for m in logs]


def __flatAnnualLogs(year_logs: logs._YearlyResolvedLogList):
    res = []
    for _, month_log in year_logs:
        month = []
        for _, day_log in month_log:
            month.append(day_log)
        res.append(month)
    return res


def __getLatestDayLogs(logs: logs.ResolveLogsList, days: int):
    res = []
    earliest = sys.maxsize
    for y, year_log in reversed(logs):
        for m, month_log in reversed(year_log):
            month = []
            for d, day_log in reversed(month_log):
                earliest = min([earliest] + [q.timestamp for q in day_log])
                month.append(day_log)
                days -= 1
                if days == 0:
                    break
            month.reverse()
            res.append(month)
            if days == 0:
                return earliest, res
    return earliest, res


def __updateQuestionsListImpl(*args, list_path: Path, src_path: Path):
    assert src_path.exists()
    assert src_path.is_dir()
    import json
    LOG = prompt.Log.getInstance()
    questions_list: QuestionsList = None

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
            return False
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
            if not PMT.ask("failed to get questions list, try again{}?", "" if try_cnt == 0 else f" ({try_cnt})"):
                LOG.log("skipped getting questions list.")
                break
        try_cnt += 1

    if raw_list == None or len(questions_list) == len(raw_list):
        # TODO: update new questions list from LeetCode since the details change is possible.
        LOG.log("no new question found, skipped updating question list.")
    else:
        raw_list.sort(key=lambda q: q['stat']['frontend_question_id'])
        LOG.log("{} new questions found, update to the questions list.",
                LOG.format(len(raw_list) - len(questions_list), flag=LOG.HIGHTLIGHT))

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
        return False

    LOG.verbose("saving the questions list to: ", list_path)
    if not questions_list.save(list_path):
        LOG.failure("failed to save the question list.")
        return False
    LOG.success("saved the question list: {}", LOG.format(list_path, flag=LOG.HIGHTLIGHT))
    return True


def __updateResolveReferenceImpl(*args, docs_path: Path, assets_path: Path, src_path: Path, list_path: Path, log_path: Path):
    assert docs_path.exists() and docs_path.is_dir()
    assert assets_path.exists() and assets_path.is_dir()
    assert src_path.exists() and src_path.is_dir()
    assert list_path.exists() and list_path.is_file()
    assert log_path.exists() and log_path.is_file()
    LOG = prompt.Log.getInstance()

    questions_list = __getQuestionsList(list_path)
    if not questions_list:
        return False
    LOG.log("loaded questions list from: {}",
            LOG.format(list_path, flag=LOG.HIGHTLIGHT))

    cnt_by_level = [0, 0, 0]
    cnt_solved_by_level = [0, 0, 0]
    unsolved_details: dict[int, QuestionDetails] = {}

    resolve_logs = __getResolvedLogsList(log_path)
    LOG.log("loaded {} resolved logs from: {}",
            LOG.format(len(resolve_logs), flag=LOG.HIGHTLIGHT),
            LOG.format(log_path, flag=LOG.HIGHTLIGHT))

    for detail in questions_list:
        unsolved_details[detail.id] = detail
        if not detail.paid:
            cnt_by_level[detail.level - 1] += 1

    for resolve_log in resolve_logs.data():
        detail = questions_list[resolve_log.id]
        cnt_solved_by_level[detail.level - 1] += 1
        del unsolved_details[detail.id]

    LOG.log("loaded {} free questions with {} easy, {} medium and {} hard.",
            LOG.format(sum(cnt_by_level), flag=LOG.HIGHTLIGHT),
            LOG.format(cnt_by_level[0], flag=LOG.HIGHTLIGHT),
            LOG.format(cnt_by_level[1], flag=LOG.HIGHTLIGHT),
            LOG.format(cnt_by_level[2], flag=LOG.HIGHTLIGHT))

    LOG.verbose("update annual resolved references.")
    for y, year_logs in resolve_logs:
        LOG.verbose("generate the {} annual reference.", y)
        doc_file = docs_path.joinpath(f"{y}.md")
        chart_file = assets_path.joinpath(f"{y}_activity.svg")

        annual_logs = __flatAnnualLogs(year_logs)
        chart = ActivityChart(light_title="Activity",
                              orange_title="",
                              begin_time=calendar.timegm(
                                  date(y, 1, 1).timetuple()),
                              solved_array=__logListToCntList(annual_logs))
        chart.save(chart_file)
        LOG.success("saved {} annual activity chart: {}",
                    LOG.format(y, flag=LOG.HIGHTLIGHT),
                    LOG.format(chart_file, flag=LOG.HIGHTLIGHT))

        # TODO: relative directory
        doc = AnnualResolveDocument(year=y, year_log=year_logs,
                                    questions_list=questions_list, src_path="../src")
        doc.save(doc_file)
        LOG.success("saved {} annual documents: {}",
                    LOG.format(y, flag=LOG.HIGHTLIGHT),
                    LOG.format(doc_file, flag=LOG.HIGHTLIGHT))

    LOG.verbose("update summary resolved references.")
    earliest, latest_logs = __getLatestDayLogs(resolve_logs, 365)

    latest_logs.reverse()
    recent_activity_chart_name = assets_path.joinpath("recent_activity.svg")
    recent_activity_chart = ActivityChart(light_title="Recent Activity within",
                                          orange_title="365 Days",
                                          begin_time=earliest,
                                          solved_array=__logListToCntList(latest_logs))

    recent_activity_chart.save(recent_activity_chart_name)
    LOG.success("saved the recent activity chart: {}",
                LOG.format(recent_activity_chart_name, flag=LOG.HIGHTLIGHT))

    problem_resolve_progress_name = assets_path.joinpath("progress.svg")
    solved_doc_name = docs_path.joinpath("solved_solutions.md")
    unsolved_doc_name = docs_path.joinpath("unsolved_solutions.md")
    problem_resolve_progress = ProblemResolveProgress(
        cnt_solved_by_level, cnt_by_level)
    solved_doc = SolvedDocument(
        questions_list=questions_list,
        resolve_logs=resolve_logs.data(),
        src_path="../src")
    unsolved_doc = UnsolvedDocument(unsolved_details=unsolved_details.values())

    problem_resolve_progress.save(problem_resolve_progress_name)
    LOG.success("saved the problems resolve progress: {}",
                LOG.format(problem_resolve_progress_name, flag=LOG.HIGHTLIGHT))
    solved_doc.save(solved_doc_name)
    LOG.success("saved the solved document: {}",
                LOG.format(solved_doc_name, flag=LOG.HIGHTLIGHT))
    unsolved_doc.save(unsolved_doc_name)
    LOG.success("saved the unsolved document: {}",
                LOG.format(unsolved_doc_name, flag=LOG.HIGHTLIGHT))
    return True


def __updateReadmeDocument(*, questions_list: Path, logs_path: Path, assets_path: Path, docs_path: Path, readme_path: Path):
    assert docs_path.exists() and docs_path.is_dir()
    assert assets_path.exists() and assets_path.is_dir()
    assert questions_list.exists() and questions_list.is_file()
    assert logs_path.exists() and logs_path.is_file()
    LOG = prompt.Log.getInstance()

    resolve_logs = __getResolvedLogsList(logs_path)
    LOG.log("loaded {} resolved logs from: {}",
            LOG.format(len(resolve_logs), flag=LOG.HIGHTLIGHT),
            LOG.format(logs_path, flag=LOG.HIGHTLIGHT))

    README = Readme(docs_path=docs_path, assets_path=assets_path,
                    resolve_logs=resolve_logs)
    README.save(readme_path)
    LOG.success("saved the readme: {}",
                LOG.format(readme_path, flag=LOG.HIGHTLIGHT))
    return True


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
    prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    ARG_SRC_PATH = Path(getattr(args, "src_path")).resolve()
    ARG_QUESTIONS_LIST = Path(getattr(args, "questions_list_file")).resolve()
    ARG_RESOLVE_LOGS = Path(getattr(args, "questions_log_file")).resolve()
    ARG_ASSETS_PATH = Path(getattr(args, "assets_path")).resolve()
    ARG_DOCS_PATH = Path(getattr(args, "docs_path")).resolve()
    ARG_README = Path(getattr(args, "readme_path")).resolve()
    if not __checkPath(ARG_ASSETS_PATH) or not __checkPath(ARG_DOCS_PATH) or not __checkPath(ARG_SRC_PATH):
        return 1
    if not __checkFile(ARG_RESOLVE_LOGS) or not __checkFile(ARG_README):
        return 1
    if not __updateQuestionsListImpl(list_path=ARG_QUESTIONS_LIST,
                                     src_path=ARG_SRC_PATH):
        return 1
    if not __updateResolveReferenceImpl(list_path=ARG_QUESTIONS_LIST,
                                        log_path=ARG_RESOLVE_LOGS,
                                        docs_path=ARG_DOCS_PATH,
                                        assets_path=ARG_ASSETS_PATH,
                                        src_path=ARG_SRC_PATH):
        return 1
    if not __updateReadmeDocument(questions_list=ARG_QUESTIONS_LIST,
                                  logs_path=ARG_RESOLVE_LOGS,
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
    prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    ARG_QUESTIONS_LIST = Path(getattr(args, "questions_list_file")).resolve()
    ARG_RESOLVE_LOGS = Path(getattr(args, "questions_log_file")).resolve()
    ARG_ASSETS_PATH = Path(getattr(args, "assets_path")).resolve()
    ARG_DOCS_PATH = Path(getattr(args, "docs_path")).resolve()
    ARG_README = Path(getattr(args, "readme_path")[0]).resolve()
    if not __checkPath(ARG_ASSETS_PATH) or not __checkPath(ARG_DOCS_PATH):
        return 1
    if not __checkFile(ARG_QUESTIONS_LIST) or not __checkFile(ARG_RESOLVE_LOGS):
        return 1
    return 0 if __updateReadmeDocument(questions_list=ARG_QUESTIONS_LIST,
                                       logs_path=ARG_RESOLVE_LOGS,
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
    prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    ARG_SRC_PATH = Path(getattr(args, "src_path")).resolve()
    ARG_QUESTIONS_LIST = Path(getattr(args, "questions_list")[0]).resolve()
    if not __checkPath(ARG_SRC_PATH):
        return 1
    return 0 if __updateQuestionsListImpl(list_path=ARG_QUESTIONS_LIST,
                                          src_path=ARG_SRC_PATH
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
    prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    ARG_SRC_PATH = Path(getattr(args, "src_path")).resolve()
    ARG_QUESTIONS_LIST_PATH = Path(getattr(args, "questions_list_file")).resolve()
    ARG_RESOLVE_LOGS_PATH = Path(getattr(args, "questions_log_file")).resolve()
    ARG_ASSETS_PATH = Path(getattr(args, "assets_path")).resolve()
    ARG_DOCS_PATH = Path(getattr(args, "docs_path")).resolve()
    if not __checkFile(ARG_QUESTIONS_LIST_PATH) or not __checkFile(ARG_RESOLVE_LOGS_PATH):
        return False
    if not __checkPath(ARG_DOCS_PATH) or not __checkPath(ARG_ASSETS_PATH) or not __checkPath(ARG_SRC_PATH):
        return False
    return 0 if __updateResolveReferenceImpl(list_path=ARG_QUESTIONS_LIST_PATH,
                                             log_path=ARG_RESOLVE_LOGS_PATH,
                                             docs_path=ARG_DOCS_PATH,
                                             assets_path=ARG_ASSETS_PATH,
                                             src_path=ARG_SRC_PATH
                                             ) else 1


if __name__ == "__main__":
    sys.exit(safeRun(ldtUpdate))
