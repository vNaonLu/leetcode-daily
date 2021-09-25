#!/usr/bin/python3
import optparse
import pathlib
import subprocess
import os


def __parser():
    parser = optparse.OptionParser(usage="%prog [options] id1 id2 ...")
    proj_group = optparse.OptionGroup(parser, "Project")
    proj_group.add_option("-a", "--add",
                          dest="add_identifier",
                          action="store_true",
                          default=False,
                          help="feature to add question and modify README and src automatically with args id.")
    proj_group.add_option("-d", "--del",
                          dest="del_identifier",
                          action="store_true",
                          default=False,
                          help="feature to delete question and modify README and src automatically with args id.")
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
                           help="run the unittest with args id.")
    build_group.add_option("--build-dest",
                           dest="build_dest",
                           action="store",
                           default="./build",
                           help="the destination to build.")
    build_group.add_option("--debug",
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

    if options.add_identifier and options.del_identifier:
        parser.error("options --add and --del are mutually exclusive.")

    file_path = pathlib.Path(__file__).parent
    if options.add_identifier:
        if len(args) == 0:
            print("Usage: {} -a id1 id2 ...".format(os.path.basename(__file__)))
            return
        subprocess.run(["python3", file_path.joinpath("./tools/leetcode_add.py").resolve(),
                        "--out", file_path.joinpath("./src/").resolve(),
                        "--question-list", file_path.joinpath(
                            "./src/questions_list.csv").resolve(),
                        "--question-log", file_path.joinpath("./src/logs.csv").resolve()] + args)

    if options.del_identifier:
        if len(args) == 0:
            print("Usage: {} -d id1 id2 ...".format(os.path.basename(__file__)))
            return
        subprocess.run(["python3", file_path.joinpath("./tools/leetcode_del.py").resolve(),
                        "--out", file_path.joinpath("./src/").resolve(),
                        "--question-list", file_path.joinpath(
                            "./src/questions_list.csv").resolve(),
                        "--question-log", file_path.joinpath("./src/logs.csv").resolve()] + args)

    if options.rdm_identifier:
        subprocess.run(["python3", file_path.joinpath("./tools/leetcode_rdm.py").resolve(),
                        "--out", file_path.joinpath("./README.md").resolve(),
                        "--question-list", file_path.joinpath(
                            "./src/questions_list.csv").resolve(),
                        "--question-log", file_path.joinpath("./src/logs.csv").resolve()] + args)

    if options.bud_identifier or options.cln_identifier or options.run_identifier:
        dest = file_path.joinpath(options.build_dest)
        if not pathlib.Path.exists(dest):
            pathlib.Path.mkdir(dest, parents=True, exist_ok=True)
            print("[+] create a directory: {}".format(dest))

        if options.cln_identifier:
            subprocess.run(
                ["cmake", "--build", dest.resolve(), "--target", "clean"])

        if options.bud_identifier:
            if options.debug_identifier:
                subprocess.run(
                    ["cmake", "-S", file_path.resolve(), "-B", dest.resolve(), "-D", "CMAKE_BUILD_TYPE=Debug"])
            else:
                subprocess.run(
                    ["cmake", "-S", file_path.resolve(), "-B", dest.resolve()])
            subprocess.run(
                ["cmake", "--build", dest.resolve()])

        if options.run_identifier:
            excute_file = dest.joinpath("unittest")
            if excute_file.exists():
                if len(args) == 0:
                    subprocess.run([excute_file.resolve()])
                else:
                    filter_arg: list[str] = []
                    for id in [int(n) for n in args]:
                        filter_arg.append("q{}.*".format(id))
                    subprocess.run(
                        [excute_file.resolve(), "--gtest_filter={}".format(":".join(filter_arg))])
            else:
                print("[x] you need to build project first.")


if __name__ == "__main__":
    __main()
