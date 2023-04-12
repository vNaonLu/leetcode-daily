#!/usr/bin/env python3
import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

import dcli
from utils import *

import ldt_cat
import ldt_check
import ldt_build
import ldt_add
import ldt_remove
import ldt_update
import ldt_config
import ldt_solve
import ldt_list


@dcli.command(
    SCRIPT_NAME,
    formatter_class=RawTextHelpFormatter,
    description=fixedWidth(
        'A script to manage LeetCode Daily project, including automatically adding '
        'and generating the C++ solution template for the LeetCode question, update '
        'the project readme and documents, or parse and print the C++ solution from '
        'specific solved solution.'
    ),
    skippable=False
)
def ldtMain(args: object):
    LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    length = 0
    args_list: list[str] = []
    LOG.verbose("[arguments beg]")
    for arg in vars(args):
        length = max(length, len(arg))
        args_list.append(arg)
    for arg in args_list:
        LOG.verbose("{} : {}", arg.ljust(length), getattr(args, arg))
    LOG.verbose("[arguments end]")


ldt_cat.getCommand(ldtMain)
ldt_list.getCommand(ldtMain)
ldt_check.getCommand(ldtMain)
ldt_build.getCommand(ldtMain)
ldt_add.getCommand(ldtMain)
ldt_solve.getCommand(ldtMain)
ldt_remove.getCommand(ldtMain)
ldt_update.getCommand(ldtMain)
ldt_config.getCommand(ldtMain)

sys.exit(safeRun(ldtMain))
