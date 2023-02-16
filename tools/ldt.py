#!/usr/bin/env python3
import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

import cli
from utils import *


@cli.command(
    formatter_class=RawTextHelpFormatter, prog=SCRIPT_NAME,
    description=fixedWidth(
        'A script to manage LeetCode Daily project, including automatically adding '
        'and generating the C++ solution template for the LeetCode question, update '
        'the project readme and documents, or parse and print the C++ solution from '
        'specific solved solution.'
    )
)
def ldtMain(args: object):
    LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    length = 0
    args_list: list[str] = []
    LOG.verbose("[arguments beg]")
    for arg in vars(args):
        if arg != "__subfunc":
            length = max(length, len(arg))
            args_list.append(arg)
    for arg in args_list:
        LOG.verbose("{} : {}", arg.ljust(length), getattr(args, arg))
    LOG.verbose("[arguments end]")

from ldt_cat import *
from ldt_gen import *
from ldt_run import *
from ldt_build import *
from ldt_add import *
from ldt_remove import *
from ldt_update import *

ldtMain()
