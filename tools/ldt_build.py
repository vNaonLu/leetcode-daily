#!/usr/bin/env python3
import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from impl import *
import dcli


def getCommand(parent=None):
    @dcli.command(
        "build",
        dcli.arg("-S", dest="src_path", default=str(PROJECT_ROOT), action="store",
                 metavar="[Project_Root]", help="specify the source directory which contains CMakeLists.txt."),
        dcli.arg("-C", dest="build_path", default=str(BUILD_ABSOLUTE), action="store",
                 metavar="[Build_Path]", help="specify the directory to build. Default: './build'."),
        dcli.arg("--disable-ninja", dest="use_ninja", default=True, action="store_false",
                 help="comfigure cmake without Ninja."),
        dcli.arg("--release", dest="release_mode", default=False, action="store_true",
                 help="generate the build file with release flags."),
        dcli.arg("--compile-commands", dest="compile_command", default=False, action="store_true",
                 help="generate the compile_commands.json in the build directory."),
        dcli.arg("--disable-leetcode-test", dest="disable_leetcode_test", default=False, action="store_true",
                 help="disable generate the build files for the solutions tests."),
        dcli.arg("--disable-infra-test", dest="disable_infra_test", default=False, action="store_true",
                 help="disable generate the build files for the LeetCode structures tests."),
        dcli.arg("--args", dest="build_args", default="-j8", action="store",
                 metavar="[Build_Args]", type=str, help="specify arguments to build project. Default: '-j8'"),
        dcli.arg("--run", dest="run_ids", default=None, action="store", nargs="*",
                 metavar="[Ids]", type=int, help="run the tests with identifiers after build."),
        dcli.arg("--run-infra", dest="run_infra", default=False, action="store_true",
                 help="identifier to run infrastructure test. cannot not run with |--run| at the same time."),
        dcli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
                 help="enable verbose logging."),
        parent=parent,
        formatter_class=RawTextHelpFormatter,
        help=fixedWidth(
            "generate the build files and build the project.",
            width=60
        ),
        description=fixedWidth(
            f'A script to generate the CMake build files and build the project.'
        )
    )
    def ldtBuild(args):
        LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
        ARG_SRC_PATH = Path(getattr(args, "src_path")).resolve()
        ARG_BUILD_PATH = Path(getattr(args, "build_path")).resolve()
        ARG_BUILD_ARGS = str(getattr(args, "build_args"))
        ARG_BUILD_FLAG = "Release" if getattr(args, "release_mode") else "Debug"
        ARG_COMPILE_COMMAND_FLAG = "ON" if getattr(args, "compile_command") else "OFF"
        ARG_LEETCODE_TEST_FLAG = "OFF" if getattr(args, "disable_leetcode_test") else "ON"
        ARG_INFRA_TEST_FLAG = "OFF" if getattr(args, "disable_infra_test") else "ON"
        ARG_RUN_IDS = getattr(args, "run_ids")
        ARG_RUN_INFRA = getattr(args, "run_infra")
        ARG_NINJA = getattr(args, "use_ninja")

        if ARG_RUN_INFRA and ARG_RUN_IDS != None:
            LOG.failure("ldt build cannot run with |--run| and |--run-infra| enabled at the same time.")
            return 1

        if ARG_RUN_INFRA and ARG_INFRA_TEST_FLAG == "OFF":
            LOG.failure("when ldt build run with |--run-infra| enabled, |--disable-infra-test| must be disabled.")
            return 1

        if ARG_RUN_IDS != None and ARG_LEETCODE_TEST_FLAG == "OFF":
            LOG.failure("when ldt build run with |--run| enabled, |--disable-leetcode-test| must be disabled.")
            return 1

        if result := ldtGenImpl(src_path=ARG_SRC_PATH,
                                build_path=ARG_BUILD_PATH,
                                build_flag=ARG_BUILD_FLAG,
                                compile_commands_flag=ARG_COMPILE_COMMAND_FLAG,
                                leetcode_test_flag=ARG_LEETCODE_TEST_FLAG,
                                infra_test_flag=ARG_INFRA_TEST_FLAG,
                                use_ninja=ARG_NINJA) != 0:
            return result

        if result := ldtBuildImpl(build_path=ARG_BUILD_PATH,
                                  build_args=ARG_BUILD_ARGS) != 0:
            return result

        if ARG_RUN_IDS != None:
            return ldtRunImpl(build_path=ARG_BUILD_PATH,
                              infra_test=False,
                              ids=ARG_RUN_IDS)

        elif ARG_RUN_INFRA:
            return ldtRunImpl(build_path=ARG_BUILD_PATH,
                              infra_test=True)

        return 0

    return ldtBuild


if __name__ == "__main__":
    sys.exit(safeRun(getCommand()))
