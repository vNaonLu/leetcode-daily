#!/usr/bin/env python3
import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from filesystem import *
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


@cli.command(
    cli.arg("-C", dest="src_path", default=str(SRC_ABSOLUTE), action="store",
            metavar="[Source_Root]", help="specify the source root."),
    cli.arg("--list", dest="questions_list_file", default=str(QUESTIONS_LIST_ABSOLUTE), action="store",
            nargs=1, metavar="[Ques_List]", help="specify the questions list in CSV format."),
    cli.arg("--resolve", dest="questions_log_file", default=str(QUESTIONS_LOG_ABSOLUTE), action="store",
            nargs=1, metavar="[Solve_Log]", help="specify the resolve log in CSV format."),
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    cli.arg("ids", metavar="ids", nargs="+", type=int, help="question identifiers to remove."),
    formatter_class=RawTextHelpFormatter,
    usage="%(prog)s [options] id [id ...]",
    name="remove",
    prog=REMOVE_SCRIPT_NAME,
    help=fixedWidth(
        f"remove the solutions which have created by the script before.",
        width=60
    ),
    description=fixedWidth(
        'A script to remove multiple question solutions, which are created by the other script, '
        f'|{ADD_SCRIPT_NAME}|, and updates the relative log csv file. This script can restore '
        f'anything which |{ADD_SCRIPT_NAME}| has done. This script will not update the questions '
        f'list.'
    )
)
def ldtRemove(args: object):
    LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
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
    resolve_logs = ResolvedLogsFile(ARG_RESOLVE_LOGS)
    LOGS_PARSE_TASK.done("loaded {} resolved logs from: {}",
                         LOG.format(len(resolve_logs), flag=LOG.HIGHTLIGHT),
                         LOG.format(ARG_RESOLVE_LOGS, flag=LOG.HIGHTLIGHT),
                         is_success=True)

    logs_remove_cnt = 0
    for id in ARG_IDS:
        LOG.verbose("check whether the solution with id {} exists.", id)
        rm_file = LOG.createTaskLog(f"Remove Solution #{id}")
        rm_file.begin("searching in: {}", ARG_SRC_PATH)
        target_file = SolutionFile(id, ARG_SRC_PATH)
        if not target_file.exists():
            rm_file.done("the solution #{} not found: {}",
                         LOG.format(id, flag=LOG.HIGHTLIGHT),
                         LOG.format(target_file, flag=LOG.HIGHTLIGHT), is_success=False)
        else:
            target_file.unlink(missing_ok=True)
            rm_file.done("the solution #{} has been removed: {}",
                         LOG.format(id, flag=LOG.HIGHTLIGHT),
                         LOG.format(target_file, flag=LOG.HIGHTLIGHT), is_success=True)

        rm_logs = LOG.createTaskLog(f"Remove Resolve Logs #{id}")
        rm_logs.begin("searching in resolve logs: {}", ARG_RESOLVE_LOGS)
        if not resolve_logs.removeById(id):
            rm_logs.done("the resolve log for solution #{} not found.",
                         LOG.format(id, flag=LOG.HIGHTLIGHT), is_success=False)
        else:
            rm_logs.done("the resolve log for solution #{} has been removed.",
                         LOG.format(id, flag=LOG.HIGHTLIGHT), is_success=True)
            logs_remove_cnt += 1

    if logs_remove_cnt > 0:
        resolve_logs.save(ARG_RESOLVE_LOGS)
        LOG.success("the resolve log has been saved: {}",
                    LOG.format(ARG_RESOLVE_LOGS, flag=LOG.HIGHTLIGHT))
    return 0


if __name__ == "__main__":
    sys.exit(safeRun(ldtRemove))