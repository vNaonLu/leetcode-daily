#!/usr/bin/env python3
import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from impl import *
import cli


@cli.command(
    cli.arg("-C", dest="src_path", default=str(SRC_ABSOLUTE), action="store",
            metavar="[Source_Root]", help="specify the source root."),
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
    ARG_RESOLVE_LOGS = Path(getattr(args, "questions_log_file")).resolve()
    ARG_IDS = getattr(args, "ids")

    if not checkFile(ARG_RESOLVE_LOGS):
        return 1
    if not checkPath(ARG_SRC_PATH):
        return 1
    
    LOGS_PARSE_TASK = LOG.createTaskLog("Parse Resolving Logs")
    LOGS_PARSE_TASK.begin("parsing the resolved logs: {}", ARG_RESOLVE_LOGS)
    resolve_logs = ResolveLogsFile(ARG_RESOLVE_LOGS)
    LOGS_PARSE_TASK.done("loaded {} resolved logs from: {}",
                         LOG.format(len(resolve_logs), flag=LOG.HIGHTLIGHT),
                         LOG.format(ARG_RESOLVE_LOGS, flag=LOG.HIGHTLIGHT),
                         is_success=True)
    
    return ldtRemoveImpl(src_path=ARG_SRC_PATH,
                         resolve_logs=resolve_logs,
                         ids=ARG_IDS)


if __name__ == "__main__":
    sys.exit(safeRun(ldtRemove))