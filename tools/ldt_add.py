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
    cli.arg("--no-case", dest="no_testcase", default=False, action="store_true",
            help="disable test cases generation."),
    cli.arg("--list", dest="questions_list_file", default=str(QUESTIONS_LIST_ABSOLUTE), action="store",
            nargs=1, metavar="[Ques_List]", help="specify the questions list in CSV format."),
    cli.arg("--resolve", dest="questions_log_file", default=str(QUESTIONS_LOG_ABSOLUTE), action="store",
            nargs=1, metavar="[Solve_Log]", help="specify the resolve log in CSV format."),
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
        'examples on the LeetCode website.'
    )
)
def ldtAdd(args: object):
    pass

if __name__ == "__main__":
    sys.exit(ldtAdd())
