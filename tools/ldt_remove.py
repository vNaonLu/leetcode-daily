import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
import cli


@cli.command(
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    cli.arg("-C", dest="src_path", default=str(SRC_ABSOLUTE), action="store",
            metavar="[Source_Root]", help="specify the source root."),
    cli.arg("--list", dest="questions_list_file", default=str(QUESTIONS_LIST_ABSOLUTE), action="store",
            nargs=1, metavar="[Ques_List]", help="specify the questions list in CSV format."),
    cli.arg("--resolve", dest="questions_log_file", default=str(QUESTIONS_LOG_ABSOLUTE), action="store",
            nargs=1, metavar="[Solve_Log]", help="specify the resolve log in CSV format."),
    cli.arg("ids", metavar="id", nargs="+", type=int, help="question identifiers to remove."),
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
        f'anything which |{ADD_SCRIPT_NAME}| has done.' 
    )
)
def ldtRemove(args: object):
    pass

if __name__ == "__main__":
    sys.exit(ldtRemove())