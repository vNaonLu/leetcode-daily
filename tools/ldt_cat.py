import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
import cli


@cli.command(
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    cli.arg("ids", metavar="id", nargs=1, type=int, help="question identifier to cat."),
    formatter_class=RawTextHelpFormatter,
    name="cat", prog=ADD_SCRIPT_NAME,
    help=fixedWidth(
        "concatenate and print the solution for specific question.",
        width=60
    ),
    description=fixedWidth(
        'A script to concatenate and print the solution for solved questions.'
    )
)
def ldtCat(args):
    pass

if __name__ == "__main__":
    sys.exit(ldtCat())