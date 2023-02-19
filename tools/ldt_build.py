#!/usr/bin/env python3
import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from impl import *
import cli


@cli.command(
    cli.arg("-S", dest="src_path", default=str(PROJECT_ROOT), action="store",
            metavar="[Project_Root]", help="specify the source directory which contains CMakeLists.txt."),
    cli.arg("-C", dest="build_path", default=str(BUILD_ABSOLUTE), action="store",
            metavar="[Build_Path]", help="specify the directory to build. Default: './build'."),
    cli.arg("--debug", dest="debug_mode", default=False, action="store_true",
            help="generate the build file with debug flags."),
    cli.arg("--compile-commands", dest="compile_command", default=False, action="store_true",
            help="generate the compile_commands.json in the build directory."),
    cli.arg("--disable-leetcode-test", dest="disable_leetcode_test", default=False, action="store_true",
            help="disable generate the build files for the solutions tests."),
    cli.arg("--disable-infra-test", dest="disable_infra_test", default=False, action="store_true",
            help="disable generate the build files for the LeetCode structures tests."),
    cli.arg("--args", dest="build_args", default="-j8", action="store",
            metavar="[Build_Args]", type=str, help="specify arguments to build project. Default: '-j8'"),
    cli.arg("--run", dest="run_ids", default=None, action="store", nargs="*",
            metavar="[Ids]", type=int, help="run the tests with identifiers after build."),
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    formatter_class=RawTextHelpFormatter,
    name="build", prog=BUILD_SCRIPT_NAME,
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
    ARG_BUILD_FLAG = "Debug" if getattr(args, "debug_mode") else "Release"
    ARG_COMPILE_COMMAND_FLAG = "ON" if getattr(args, "compile_command") else "OFF"
    ARG_LEETCODE_TEST_FLAG = "OFF" if getattr(args, "disable_leetcode_test") else "ON"
    ARG_INFRA_TEST_FLAG = "OFF" if getattr(args, "disable_infra_test") else "ON"
    ARG_RUN_IDS = getattr(args, "run_ids")

    result = ldtGenImpl(src_path=ARG_SRC_PATH,
                        build_path=ARG_BUILD_PATH,
                        build_flag=ARG_BUILD_FLAG,
                        compile_commands_flag=ARG_COMPILE_COMMAND_FLAG,
                        leetcode_test_flag=ARG_LEETCODE_TEST_FLAG,
                        infra_test_flag=ARG_INFRA_TEST_FLAG)

    if result != 0:
        LOG.failure("failed to generate build files, skipped the build.")
        return result

    result = ldtBuildImpl(build_path=ARG_BUILD_PATH,
                          build_args=ARG_BUILD_ARGS)

    if result != 0 or ARG_RUN_IDS is None:
        return result

    return ldtRunImpl(build_path=ARG_BUILD_PATH,
                      infra_test=False,
                      ids=ARG_RUN_IDS)



if __name__ == "__main__":
    sys.exit(safeRun(ldtBuild))