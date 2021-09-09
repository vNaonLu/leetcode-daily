#!/usr/bin/python3
import sys
import os
import pathlib
import subprocess
from utils import leetcode

if((len(sys.argv) - 2) % 3):
    print("[Usage] <question number>")
else:
    gen = os.path.basename(__file__)
    quest_num = sys.argv[1]
    project_path = pathlib.Path(__file__).parent.parent.resolve()
    source_path = os.path.join(project_path, "src")
    test_path = os.path.join(project_path, "test")
    source_name = "q{}.hpp".format(quest_num.rjust(4, '0'))
    source = os.path.join(source_path, source_name)
    unittest_name = "q{}_unittest.hpp".format(quest_num.rjust(4, '0'))
    unittest = os.path.join(test_path, unittest_name)

    if os.path.exists(source):
        print("[-] file exist: {}".format(source))
    elif os.path.exists(unittest):
        print("[-] file exist: {}".format(unittest))
    else:
        description = leetcode.get_description(
            int(quest_num), "this file is generated by {}\n".format(gen))
        if description != None:
            with open(source, 'w') as f:
                f.write("\n")
                f.write("#ifndef LEETCODE_Q{}_H__\n".format(quest_num))
                f.write("#define LEETCODE_Q{}_H__\n".format(quest_num))
                f.write("#include <iostream>\n")
                f.write("\n")
                f.write("namespace l{} {{\n".format(quest_num))
                f.write("using namespace std;\n")
                f.write("\n")
                f.writelines(description)
                f.write("\n")
                f.write("   // Put your code here\n")
                f.write("}}  // namespace l{}\n".format(quest_num))
                f.write("#endif")

            print("[+] create file: {}".format(source))

            with open(unittest, 'w') as f:
                f.write("\n")
                f.write("#ifndef Q{}_UNITTEST_H__\n".format(quest_num))
                f.write("#define Q{}_UNITTEST_H__\n".format(quest_num))
                f.write("#include <gtest/gtest.h>\n")
                f.write("\n")
                f.write("#include \"../src/{}\"\n".format(source_name))
                f.write("using namespace std;\n")
                f.write("\n")
                f.writelines(description)
                f.write("\n")
                f.write("TEST(q{}, sample_input01) {{\n".format(quest_num))
                f.write("}\n")
                f.write("\n")
                f.write("#endif")

            print("[+] create file: {}".format(unittest))

            subprocess.run(["code", source])
            subprocess.run(["code", unittest])

        else:
            print(
                "[-] question #{} need plus account or does not exist.".format(quest_num))
            sys.exit()
