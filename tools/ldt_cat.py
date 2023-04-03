#!/usr/bin/env python3
import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from impl import *
import dcli


def getCommand(parent=None):
    @dcli.command(
        "cat",
        dcli.arg("--src", dest="src_path", default=str(SRC_ABSOLUTE), action="store",
                 metavar="[Source_Root]", help="specify the source root."),
        dcli.arg("id", metavar="id", nargs=1, type=int,
                 help="question identifier to cat."),
        dcli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
                 help="enable verbose logging."),
        parent=parent,
        formatter_class=RawTextHelpFormatter,
        help=fixedWidth(
            "concatenate and print the solution for specific question.",
            width=60
        ),
        description=fixedWidth(
            'A script to concatenate and print the solution for solved questions.'
        )
    )
    def ldtCat(args):
        prompt.Log.getInstance(verbose=getattr(args, "verbose"))
        assert len(getattr(args, "id")) == 1
        ARG_ID = getattr(args, "id")[0]
        assert hasattr(args, "src_path")
        ARG_SRC_PATH = Path(getattr(args, "src_path")).resolve()
        return 0 if ldtCatImpl(id=ARG_ID, src_path=ARG_SRC_PATH) == 0 else 1

    return ldtCat


if __name__ == "__main__":
    sys.exit(safeRun(getCommand()))
