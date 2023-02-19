#!/usr/bin/env python3
import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
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
    LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    ARG_BUILD_PATH = Path(getattr(args, "build_path")).resolve()
    ARG_INFRA_TEST = getattr(args, "infra_test")
    ARG_IDS = getattr(args, "ids")

    LOG.verbose("check whether the directory exists: {}", ARG_BUILD_PATH)

    if not ARG_BUILD_PATH.exists():
        LOG.failure("the directory not found: {}", ARG_BUILD_PATH)
        return 1

    with chDir(ARG_BUILD_PATH):

        executable = ARG_BUILD_PATH

        if ARG_INFRA_TEST:
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

        if len(ARG_IDS) > 0:
            if ARG_INFRA_TEST:
                LOG.warn("discard the ids specified due to |--infra| enabled: {}", ARG_IDS)
            else:
                solutions = [f'q{id}.*' for id in ARG_IDS]
                filter = "--gtest_filter={}".format(":".join(solutions))
                CMD.append(filter)

        TASK = LOG.createTaskLog("Run Tests")

        with launchSubprocess(CMD) as proc:
            TASK.begin("running the executable: {}", executable)
            result = proc.stdout.read()
            TASK.log("parsing the test logs.")
            LOG.verbose(result.replace('\n', '\n    '))
            passed = parsePassedIds(result)
            failed = parseFailedTests(result)

            missing_ids = []
            for id in ARG_IDS:
                if id not in passed and id not in failed:
                    missing_ids.append(id)

            if len(failed) == 0 and len(missing_ids) == 0:
                TASK.done("passed all tests for {} solutions.",
                          LOG.format(len(passed), flag=LOG.HIGHTLIGHT), is_success=True)
                return 0

            elif len(failed) == 0 and len(missing_ids) > 0:
                TASK.done("solutions without any tests: {}", list(missing_ids), is_success=False)
                return 1

            else:
                TASK.done("failed on test(s): {}", list(failed), is_success=False)

                for test in failed:
                    LOG.failure("{} failed to pass:", LOG.format(test, flag=LOG.HIGHTLIGHT))
                    block = parseTestBlock(result, test)
                    LOG.print(block, flag=LOG.VERBOSE)

                if len(missing_ids) > 1:
                    LOG.failure("there is no tests for the solution: {}", list(missing_ids))

                return 1

if __name__ == "__main__":
    sys.exit(safeRun(ldtRun))
