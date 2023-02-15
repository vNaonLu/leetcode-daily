#!/usr/bin/env python3
import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from filesystem import *
import cli


@cli.command(
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    cli.arg("--src", dest="src_path", default=str(SRC_ABSOLUTE), action="store",
            metavar="[Source_Root]", help="specify the source root."),
    cli.arg("id", metavar="id", nargs=1, type=int, help="question identifier to cat."),
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
    LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    assert len(getattr(args, "id")) == 1
    ARG_ID = getattr(args, "id")[0]
    assert hasattr(args, "src_path")
    ARG_SRC_PATH = Path(getattr(args, "src_path")).resolve()

    LOG.log("collecting the details for the solution of question #{}.",
              LOG.format(ARG_ID, flag=LOG.HIGHTLIGHT))
    qf = SolutionFile(ARG_ID)
    qpath = qf.path(ARG_SRC_PATH)

    LOG.verbose("cat LeetCode solution...")
    LOG.verbose("[source detail beg]")
    LOG.verbose(" - id     : {}", qf.id())
    LOG.verbose(" - target : {}", qpath)
    LOG.verbose("[source detail end]")
    LOG.verbose("checking whether the solution exists...")

    if not qpath.exists():

        LOG.verbose("target not found: {}", qpath)

        LOG.failure("questions #{} is not resolved yet.",
                    LOG.format(ARG_ID, flag=LOG.HIGHTLIGHT))
        return 1

    LOG.verbose("target found and trying to get solution snippet.")
    LOG.verbose("opening the file: {}", qpath)

    with qpath.open('r') as f:

        LOG.verbose("solution file opened.")

        code_buf = f.read()
        snippet = parseSolution(code_buf)

        if not snippet:
            LOG.failure("failed to parse the solution from file: {}", qpath)
            return 1

        LOG.success("the solution for question #{} found:",
                    LOG.format(ARG_ID, flag=LOG.HIGHTLIGHT))
        LOG.print(clangFormat(snippet))

    return 0

if __name__ == "__main__":
    sys.exit(ldtCat())