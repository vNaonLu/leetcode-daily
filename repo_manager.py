#!/usr/bin/env python3
import optparse
import pathlib
import subprocess
import os
import shutil
from tools.utils import prompt as pmt
from tools.utils.subprocess_runner import subprocess_runner

_file_path  = pathlib.Path(__file__).parent
_add_script = _file_path.joinpath("./tools/leetcode_add.py")
_del_script = _file_path.joinpath("./tools/leetcode_del.py")
_rdm_script = _file_path.joinpath("./tools/leetcode_rdm.py")

_readme_path = _file_path.joinpath("./README.md")
_assets_path = _file_path.joinpath("./assets/")
_source_path = _file_path.joinpath("./src")
_qlist_path  = _file_path.joinpath("./src/questions_list.csv")
_qlog_path   = _file_path.joinpath("./src/logs.csv")

def _build_option(options: optparse, args: list[str]):
    dest = _file_path.joinpath(options.build_dest)
    operation: subprocess.CompletedProcess = None
    if options.cln_identifier:
        operation = "clean"
        if pathlib.Path.exists(dest):
            shutil.rmtree(dest)
            pmt.show(pmt.succ(pmt.hi("The directory has been removed: ") + str(dest)), "-")
        else:
            pmt.show(pmt.fail(pmt.hi("The directory not found: ") + str(dest), "x"))

    if options.bud_identifier:
        if not pathlib.Path.exists(dest):
            pathlib.Path.mkdir(dest, parents=True, exist_ok=True)
            pmt.show(pmt.succ(pmt.hi("The directory has been created: ") + str(dest), "+"))

        _conf_command: list[str] = ["cmake", "-S", _file_path.resolve(),
                                             "-B", dest.resolve(),
                                             "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON",
                                             "-DENABLE_LEETCODE_TEST=ON",
                                             "-DENABLE_INFRA_TEST=ON"]
        if options.debug_identifier:
            _conf_command.append("-DCMAKE_BUILD_TYPE=Debug")
        operation = subprocess_runner("Configuring the CMakeLists.txt") \
                    .invoke(_conf_command,
                            "Has been Configured the CMakeLists.txt!",
                            "Failed to Configure the CMakeLists.txt, the reason is below:")
        if operation.returncode != 0:
            pmt.show(operation.stderr.decode("unicode_escape"))

        _build_cmd    = ["cmake", "--build", dest.resolve(), "-j8"]
        operation = subprocess_runner("Building the project")\
                    .invoke(_build_cmd,
                            "Build the project successfully!",
                            "Failed to build the project, the reason is below:")
        if operation.returncode != 0:
            pmt.show(operation.stderr.decode("unicode_escape"))

    if options.run_identifier:
        if options.bud_identifier and operation.returncode != 0:
            if not pmt.ask("The project has failed to build, run the old version"):
                return operation

        leetcode_test = dest.joinpath("leetcode_test")
        if not leetcode_test.exists():
            pmt.show(pmt.fail(pmt.hi("The project has not been built ever."), "x"))
        else:
            _test_cmd = [leetcode_test.resolve()]
            if len(args) > 0:
                filter_arg = ["q{}.*".format(id) for id in [int(n) for n in args]]
                _test_cmd.append("--gtest_filter={}".format(":".join(filter_arg)))
            operation = subprocess_runner("leetcode_test", False)\
                        .invoke(_test_cmd)
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
    proj_group.add_option("--no-testcase",
                          dest="no_testcase",
                          action="store_true",
                          default=False,
                          help="add questions without generating testcases.")

    build_group = optparse.OptionGroup(parser, "Build & Test")
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
                           help="run the googletest with arg ids.")
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

def __test_code(options, args):
    from tools.leetcode.question import LeetCodeQuestion
    from tools.leetcode import request as Rq
    slug = Rq.question_slug(int(args[0]))
    if slug:
        q = LeetCodeQuestion(slug, not options.no_testcase)
        s = q.template("prompt test", 70)
        print()
        print("=====================================================")
        print()
        print(s)

def __main():
    parser = __parser()
    options, args = parser.parse_args()
    operation: subprocess.CompletedProcess = None
    
    if options.add_identifier and options.del_identifier:
        parser.error("options --add and --del are mutually exclusive.")

    if options.add_identifier:
        if len(args) == 0:
            pmt.show("Usage: {} -a id1 id2 ...".format(os.path.basename(__file__)))
            return
        _add_question_cmd = ["python3",         _add_script.resolve(),
                             "--out",           _source_path.resolve(),
                             "--question-list", _qlist_path.resolve(),
                             "--question-log",  _qlog_path.resolve()]
        if options.no_testcase:
            _add_question_cmd.append("--no-testcase")
        operation = subprocess_runner("add questions", False)\
                    .invoke(_add_question_cmd + args)

    if options.del_identifier:
        if len(args) == 0:
            pmt.show("Usage: {} -d id1 id2 ...".format(os.path.basename(__file__)))
            return
        
        _del_cmd = ["python3",         _del_script.resolve(),
                    "--out",           _source_path.resolve(),
                    "--question-list", _qlist_path.resolve(),
                    "--question-log",  _qlog_path.resolve()]
        operation = subprocess_runner("del questions", False)\
                    .invoke(_del_cmd + args)

    if options.rdm_identifier:
        _rdm_cmd = ["python3",         _rdm_script.resolve(),
                    "--out",           _readme_path.resolve(),
                    "--source",        _source_path.resolve(),
                    "--assets",        _assets_path.resolve(),
                    "--question-list", _qlist_path.resolve(),
                    "--question-log",  _qlog_path.resolve()]
        operation = subprocess_runner("rdm modifies", False)\
                    .invoke(_rdm_cmd + args)

    if options.bud_identifier or options.cln_identifier or options.run_identifier:
        operation = _build_option(options, args)

    if operation == None:
        pmt.show("Usage: {} [options] id1 id2 ...".format(
            os.path.basename(__file__)))


if __name__ == "__main__":
    __main()
