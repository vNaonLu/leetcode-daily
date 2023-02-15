import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

import cli
from utils import *


@cli.command(
    formatter_class=RawTextHelpFormatter, prog=SCRIPT_NAME,
    description=fixedWidth(
        'A script to manage LeetCode Daily project, including automatically adding'
        'the unsolved questions, generating the C++ solution template based on the'
        'code snippet queried from LeetCode.'
    )
)
def ldtMain(args: object):
    print("ldtMain")

from ldt_cat import *
from ldt_add import *
from ldt_remove import *
from ldt_update import *

ldtMain()
