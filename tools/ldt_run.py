#!/usr/bin/env python3
import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
import cli


@cli.command(
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    cli.arg("-C", dest="build_path", default=str(BUILD_ABSOLUTE), action="store",
            metavar="[Build_Path]",
            help="specify the directory to run executables. Default: './build'."),
    cli.arg("--infra", dest="infra_test", default=False, action="store_true",
            help="identifier to build infrastructures instead of solutions."),
    cli.arg("ids", metavar="id", nargs="*", type=int,
            help="question identifiers to run test. run all tests if not specified."),
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
    LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    BUILD_PATH = Path(getattr(args, "build_path"))
    INFRA_TEST = getattr(args, "infra_test")
    IDS = getattr(args, "ids")

    LOG.verbose("check whether the directory exists: {}", BUILD_PATH)

    if not BUILD_PATH.exists():
        LOG.failure("the directory not found: {}", BUILD_PATH)
        return 1

    with chDir(BUILD_PATH):

        executable = BUILD_PATH

        if INFRA_TEST:
            LOG.log("run the infrastructure unit tests.")
            executable = executable.joinpath("infra_test")
        else:
            LOG.log("run the LeetCode solution unit tests.")
            executable = executable.joinpath("leetcode_test")

        LOG.verbose("check whether the executable exists: {}", executable)

        if not executable.exists():
            LOG.failure("the target executable not found: {}", executable)
            LOG.print("please run |ldt build| first.")
            return 1

        CMD = [executable]

        if len(IDS) > 0:
            if INFRA_TEST:
                LOG.warn("discard the ids specified due to |--infra| enabled: {}", IDS)
            else:
                solutions = [f'q{id}.*' for id in IDS]
                filter = "--gtest_filter={}".format(":".join(solutions))
                CMD.append(filter)

        LOG.verbose("run a command: {}", CMD)
        LOG.log("run the executable: {}", executable)

        subprocess.run(CMD)


if __name__ == "__main__":
    sys.exit(ldtRun())
