#!/usr/bin/env python3
import sys
import regex
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True


from utils import *
from config import *
from session import *
import dcli


def getCommand(parent=None):
    @dcli.command(
        "config",
        parent=parent,
        formatter_class=RawTextHelpFormatter,
        help=fixedWidth(
            f"edit the configuration for {SCRIPT_NAME}.", width=60),
        description=fixedWidth(
            f'A script to modify the configuration for {SCRIPT_NAME} usage, such as LeetCode Session.'
        )
    )
    def ldtConfig(args: object):
        pass

    @dcli.command(
        "session",
        dcli.arg("session_name", metavar="Session_Name", default="",
                 type=str, help="set |Session_Name| as default session user."),
        dcli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
                 help="enable verbose logging."),
        formatter_class=RawTextHelpFormatter,
        parent=ldtConfig,
        help=fixedWidth(f"add default session to {SCRIPT_NAME}.", width=60),
        description=fixedWidth(
            f'Add default session to {SCRIPT_NAME} which is used in LeetCode session.',
        )
    )
    def configSession(args: object):
        LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
        CONFIG = Configuration.getInstance()
        ARG_SESSION_NAME: str = getattr(args, "session_name")

        if not ARG_SESSION_NAME or regex.search('\W', ARG_SESSION_NAME):
            LOG.failure("invalid session name which contains non-word character(s): {}",
                        LOG.format(ARG_SESSION_NAME, flag=LOG.HIGHTLIGHT))
            return 1

        CONFIG.default_user = ARG_SESSION_NAME
        LOG.success("set default session name: {}", LOG.format(
            ARG_SESSION_NAME, flag=LOG.HIGHTLIGHT))
        CONFIG.save()

        return 0

    return ldtConfig


if __name__ == "__main__":
    sys.exit(safeRun(getCommand()))
