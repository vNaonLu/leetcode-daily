#!/usr/bin/python3
import optparse
import pathlib
import subprocess
import os
import shutil
from tools.utils import prompt as pmt
from tools.utils import local

_file_path = pathlib.Path(__file__).parent


def _run_process(argc: list[str], hide: bool = False):
    if hide:
        return subprocess.run(argc,
                              stdout=subprocess.PIPE,
                              stderr=subprocess.PIPE)
    return subprocess.run(argc)


def _build_option(options: optparse, args: list[str]):
    dest = _file_path.joinpath(options.build_dest)
    operation: subprocess.CompletedProcess = None
    if options.cln_identifier:
        operation = "clean"
        if pathlib.Path.exists(dest):
            shutil.rmtree(dest)
            pmt.show(
                pmt.succ("\033[37mThe directory has been removed:\033[0m {}".format(dest), "-"))
        else:
            pmt.show(
                pmt.fail("\033[37mThe directory not found: \033[0m{}".format(dest), "x"))

    if options.bud_identifier:
        if not pathlib.Path.exists(dest):
            pathlib.Path.mkdir(dest, parents=True, exist_ok=True)
            pmt.show(
                pmt.succ("\033[37mThe directory has been created: \033[0m{}".format(dest), "+"))

        pmt.pending("Configuring the CMakeLists.txt")
        if options.debug_identifier:
            operation = _run_process([
                "cmake",
                "-S", _file_path.resolve(),
                "-B", dest.resolve(),
                "-D", "CMAKE_BUILD_TYPE=Debug"], True)
        else:
            operation = _run_process([
                "cmake",
                "-S", _file_path.resolve(),
                "-B", dest.resolve()], True)

        if operation.returncode == 0:
            pmt.recieve(
                pmt.succ("\033[37mHas been Configured the CMakeLists.txt!\033[0m", "v"))
        else:
            pmt.recieve(
                pmt.fail("\033[37mFailed to Configure the CMakeLists.txt, the reason is below:\033[0m", "x"))
            pmt.show(operation.stderr.decode('unicode_escape'))

        pmt.pending("Building the project")
        operation = _run_process([
            "cmake",
            "--build", dest.resolve()], True)
        if operation.returncode == 0:
            pmt.recieve(
                pmt.succ("\033[37mBuild the project successfully!\033[0m", "v"))
        else:
            pmt.recieve(
                pmt.fail("\033[37mFailed to build the project, the reason is below:\033[0m", "x"))
            pmt.show(operation.stderr.decode('unicode_escape'))

    if options.run_identifier:
        if options.bud_identifier and operation.returncode != 0:
            if not pmt.ask("The project has failed to build, run the old version"):
                return operation

        excute_file = dest.joinpath("unittest")
        if not excute_file.exists():
            operation = "fail"
            pmt.show(
                pmt.fail("\033[37mThe project has not been built ever.\033[0m", "x"))
        else:
            if len(args) == 0:
                operation = _run_process([
                    excute_file.resolve()])
            else:
                filter_arg: list[str] = []
                for id in [int(n) for n in args]:
                    filter_arg.append("q{}.*".format(id))
                operation = _run_process([
                    excute_file.resolve(),
                    "--gtest_filter={}".format(":".join(filter_arg))])
    return operation


def __parser():
    parser = optparse.OptionParser(usage="%prog [options] id1 id2 ...")
    proj_group = optparse.OptionGroup(parser, "Project")
    proj_group.add_option("-a", "--add",
                          dest="add_identifier",
                          action="store_true",
                          default=False,
                          help="feature to add question and modify README and src automatically with arg ids.")
    proj_group.add_option("-d", "--del",
                          dest="del_identifier",
                          action="store_true",
                          default=False,
                          help="feature to delete question and modify README and src automatically with arg ids.")
    proj_group.add_option("-R", "--update-readme",
                          dest="rdm_identifier",
                          action="store_true",
                          default=False,
                          help="update README.md.")

    build_group = optparse.OptionGroup(parser, "Build & Unittest")
    build_group.add_option("-B", "--build",
                           dest="bud_identifier",
                           action="store_true",
                           default=False,
                           help="feature to build project.")
    build_group.add_option("-c", "--clean",
                           dest="cln_identifier",
                           action="store_true",
                           default=False,
                           help="clean the build folder.")
    build_group.add_option("-r", "--run",
                           dest="run_identifier",
                           action="store_true",
                           default=False,
                           help="run the unittest with arg ids.")
    build_group.add_option("--b-dest",
                           dest="build_dest",
                           action="store",
                           default="./build",
                           help="the destination to build.")
    build_group.add_option("-D", "--debug",
                           dest="debug_identifier",
                           action="store_true",
                           default=False,
                           help="build debug mode.")

    parser.add_option_group(proj_group)
    parser.add_option_group(build_group)
    return parser


def __main():
    parser = __parser()
    options, args = parser.parse_args()
    operation: subprocess.CompletedProcess = None

    # from tools.leetcode.question import LeetCodeQuestion
    # from tools.leetcode import request as Rq
    # slug = Rq.question_slug(int(args[0]))
    # if slug:
    #     q = LeetCodeQuestion(slug)
    #     s, u = q.template("prompt test", 70)
    #     print()
    #     print("=====================================================")
    #     print()
    #     print(s)
    #     print()
    #     print("=====================================================")
    #     print()
    #     print(u)
    # return

    if options.add_identifier and options.del_identifier:
        parser.error("options --add and --del are mutually exclusive.")

    if options.add_identifier:
        if len(args) == 0:
            pmt.show("Usage: {} -a id1 id2 ...".format(os.path.basename(__file__)))
            return
        operation = _run_process([
            "python3",
            _file_path.joinpath("./tools/leetcode_add.py").resolve(),
            "--out",
            _file_path.joinpath("./src/").resolve(),
            "--question-list",
            _file_path.joinpath("./src/questions_list.csv").resolve(),
            "--question-log",
            _file_path.joinpath("./src/logs.csv").resolve()] + args)

    if options.del_identifier:
        if len(args) == 0:
            pmt.show("Usage: {} -d id1 id2 ...".format(os.path.basename(__file__)))
            return
        operation = _run_process([
            "python3",
            _file_path.joinpath("./tools/leetcode_del.py").resolve(),
            "--out",
            _file_path.joinpath("./src/").resolve(),
            "--question-list",
            _file_path.joinpath("./src/questions_list.csv").resolve(),
            "--question-log",
            _file_path.joinpath("./src/logs.csv").resolve()] + args)

    if options.rdm_identifier:
        operation = _run_process([
            "python3",
            _file_path.joinpath("./tools/leetcode_rdm.py").resolve(),
            "--out",
            _file_path.joinpath("./README.md").resolve(),
            "--assets",
            _file_path.joinpath("./assets/").resolve(),
            "--question-list",
            _file_path.joinpath("./src/questions_list.csv").resolve(),
            "--question-log",
            _file_path.joinpath("./src/logs.csv").resolve(),
            "--source",
            _file_path.joinpath("./src/").resolve(), ] + args)

    if options.bud_identifier or options.cln_identifier or options.run_identifier:
        operation = _build_option(options, args)

    if operation == None:
        pmt.show("Usage: {} [options] id1 id2 ...".format(
            os.path.basename(__file__)))


if __name__ == "__main__":
    __main()
