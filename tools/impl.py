#!/usr/bin/env python3
import sys
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from logs import *
from filesystem import *
from questions import *


def ldtGenImpl(*, src_path: Path, build_path: Path, build_flag: str, compile_commands_flag: str, leetcode_test_flag: str, infra_test_flag: str):
    LOG = prompt.Log.getInstance()
    ARG_SRC_PATH = src_path
    ARG_BUILD_PATH = build_path
    ARG_BUILD_FLAG = build_flag
    ARG_COMPILE_COMMAND_FLAG = compile_commands_flag
    ARG_LEETCODE_TEST_FLAG = leetcode_test_flag
    ARG_INFRA_TEST_FLAG = infra_test_flag

    LOG.verbose("checking whether the CMakeLists.txt exists in the directory: {}", ARG_SRC_PATH)
    if not ARG_SRC_PATH.joinpath("CMakeLists.txt").exists():
        LOG.failure("there is no |CMakeLists.txt| exists in the directory: {}", ARG_SRC_PATH)
        return 1

    cmake = findExecutable("cmake")

    if not cmake:
        LOG.failure("cmake not found.")
        return 1

    CMD = [
        cmake, "-S", ARG_SRC_PATH, "-B", ARG_BUILD_PATH,
        f"-DCMAKE_EXPORT_COMPILE_COMMANDS={ARG_COMPILE_COMMAND_FLAG}",
        f"-DCMAKE_BUILD_TYPE={ARG_BUILD_FLAG}",
        f"-DENABLE_LEETCODE_TEST={ARG_LEETCODE_TEST_FLAG}",
        f"-DENABLE_INFRA_TEST={ARG_INFRA_TEST_FLAG}",
    ]

    LOG.log("generate CMake build files with flag: {}", LOG.format(
        f"-DCMAKE_BUILD_TYPE={ARG_BUILD_FLAG}", flag=LOG.HIGHTLIGHT))
    if ARG_COMPILE_COMMAND_FLAG == "ON":
        LOG.log("generate CMake build files with flag: {}", LOG.format(
            f"-DCMAKE_EXPORT_COMPILE_COMMANDS={ARG_COMPILE_COMMAND_FLAG}", flag=LOG.HIGHTLIGHT))

    if ARG_LEETCODE_TEST_FLAG == "ON":
        LOG.log("generate CMake build files with flag: {}", LOG.format(
            f"-DENABLE_LEETCODE_TEST={ARG_LEETCODE_TEST_FLAG}", flag=LOG.HIGHTLIGHT))

    if ARG_INFRA_TEST_FLAG == "ON":
        LOG.log("generate CMake build files with flag: {}", LOG.format(
            f"-DENABLE_INFRA_TEST={ARG_INFRA_TEST_FLAG}", flag=LOG.HIGHTLIGHT))

    TASK = LOG.createTaskLog("Generate Build Files")

    def stdoutCallback(out: str):
        TASK.log(parseCMakeGenarateLog(out))
        LOG.verbose(out)

    with launchSubprocess(CMD) as proc:
        TASK.begin()
        asyncStdout(proc, stdoutCallback)

        if proc.poll() != 0:
            TASK.done("failed to generate the build files.", is_success=False)
            proc.stderr.seek(0)
            LOG.print(proc.stderr.read(), flag=LOG.VERBOSE)
            return 1

        TASK.done(is_success=True)
    return 0


def ldtBuildImpl(*, build_path: Path, build_args: str):
    LOG = prompt.Log.getInstance()
    ARG_BUILD_PATH = build_path
    ARG_BUILD_ARGS = build_args

    LOG.verbose("check whether the directory exists: {}", ARG_BUILD_PATH)

    if not ARG_BUILD_PATH.exists():
        LOG.failure("the directory not found: {}", ARG_BUILD_PATH)
        return 1

    cmake = findExecutable("cmake")

    if not cmake:
        LOG.failure("cmake not found.")
        return 1

    CMD = [cmake, "--build", ARG_BUILD_PATH]
    build_args = ARG_BUILD_ARGS.split()

    if len(build_args) > 0:
        CMD += build_args

    TASK = LOG.createTaskLog("Build Project")

    def stdoutCallback(out: str):
        percent, msg = parseBuildLog(out)
        TASK.log(msg, percent=percent)
        LOG.verbose(out)

    with launchSubprocess(CMD) as proc:
        TASK.begin()
        asyncStdout(proc, stdoutCallback)

        if proc.poll() != 0:
            TASK.done("failed to build in {}.", ARG_BUILD_PATH, is_success=False)
            LOG.print(proc.stderr.read(), flag=LOG.VERBOSE)
            return 1

        TASK.done("successfully built in {}.", ARG_BUILD_PATH, is_success=True)

    return 0


def ldtRunImpl(*, build_path: Path, infra_test: bool, ids: list[int] = []):
    LOG = prompt.Log.getInstance()
    ARG_BUILD_PATH = build_path
    ARG_INFRA_TEST = infra_test
    ARG_IDS = ids

    LOG.verbose("check whether the directory exists: {}", ARG_BUILD_PATH)

    if not ARG_BUILD_PATH.exists():
        LOG.failure("the directory not found: {}", ARG_BUILD_PATH)
        return 1

    with chDir(ARG_BUILD_PATH):

        executable = ARG_BUILD_PATH

        if ARG_INFRA_TEST:
            LOG.verbose("run the infrastructure unit tests.")
            executable = executable.joinpath("infra_test")
        else:
            LOG.verbose("run the LeetCode solution unit tests.")
            executable = executable.joinpath("leetcode_test")

        LOG.verbose("check whether the executable exists: {}", executable)

        if not executable.exists():
            LOG.failure("the target executable not found: {}", executable)
            LOG.print("please run |ldt build| first.")
            return 1

        CMD = [executable]

        if len(ARG_IDS) > 0:
            if ARG_INFRA_TEST:
                LOG.warn("discard the specified ids due to |--infra| enabled: {}", ARG_IDS)
                ARG_IDS = []
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
                TASK.done("passed all tests.",
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


def ldtRemoveImpl(*, src_path: Path, resolve_logs: ResolveLogsFile, ids: list[int]):
    LOG = prompt.Log.getInstance()
    ARG_SRC_PATH = src_path
    ARG_IDS = ids

    logs_remove_cnt = 0
    for id in ARG_IDS:
        LOG.verbose("check whether the solution with id {} exists.", id)
        rm_file = LOG.createTaskLog(f"Remove Solution #{id}")
        rm_file.begin("searching in: {}", ARG_SRC_PATH)
        target_file = SolutionFile(id, ARG_SRC_PATH)
        if not target_file.exists():
            rm_file.done("the solution #{} not found: {}",
                         LOG.format(id, flag=LOG.HIGHTLIGHT),
                         LOG.format(target_file, flag=LOG.HIGHTLIGHT), is_success=False)
        else:
            target_file.unlink(missing_ok=True)
            rm_file.done("the solution #{} has been removed: {}",
                         LOG.format(id, flag=LOG.HIGHTLIGHT),
                         LOG.format(target_file, flag=LOG.HIGHTLIGHT), is_success=True)

        rm_logs = LOG.createTaskLog(f"Remove Resolve Logs #{id}")
        rm_logs.begin("searching in resolve logs: {}", resolve_logs)
        if not resolve_logs.removeById(id):
            rm_logs.done("the resolve log for solution #{} not found.",
                         LOG.format(id, flag=LOG.HIGHTLIGHT), is_success=False)
        else:
            rm_logs.done("the resolve log for solution #{} has been removed.",
                         LOG.format(id, flag=LOG.HIGHTLIGHT), is_success=True)
            logs_remove_cnt += 1

    if logs_remove_cnt > 0:
        resolve_logs.save()
        LOG.success("the resolve log has been saved: {}",
                    LOG.format(resolve_logs, flag=LOG.HIGHTLIGHT))
    return 0
