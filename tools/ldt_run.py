#!/usr/bin/env python3
import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from impl import *
import cli


@cli.command(
    cli.arg("-C", dest="build_path", default=str(BUILD_ABSOLUTE), action="store",
            metavar="[Build_Path]",
            help="specify the directory to run executables. Default: './build'."),
    cli.arg("--infra", dest="infra_test", default=False, action="store_true",
            help="identifier to build infrastructures instead of solutions."),
    cli.arg("ids", metavar="id", nargs="*", type=int,
            help="question identifiers to run test. run all tests if not specified."),
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    formatter_class=RawTextHelpFormatter,
    name="run", prog=RUN_SCRIPT_NAME,
    help=fixedWidth(
        "run solved question tests.",
        width=60
    ),
    description=fixedWidth(
        f'A script to easily execute the unit tests of solved questions with GoogleTest '
        'filter interface.'
    )
)
def ldtRun(args):
    prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    ARG_BUILD_PATH = Path(getattr(args, "build_path")).resolve()
    ARG_INFRA_TEST = getattr(args, "infra_test")
    ARG_IDS = getattr(args, "ids")

    return ldtRunImpl(build_path=ARG_BUILD_PATH,
                      infra_test=ARG_INFRA_TEST,
                      ids=ARG_IDS)

if __name__ == "__main__":
    sys.exit(safeRun(ldtRun))
