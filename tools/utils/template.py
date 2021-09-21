def generate_source(path: str, num: int, desc: str):
    with open(path, "w") as f:
        f.write("\n".join([
            "",
            "#ifndef LEETCODE_Q{}_H__".format(num),
            "#define LEETCODE_Q{}_H__".format(num),
            "#include <iostream>",
            "",
            "namespace l{} {{".format(num),
            "using namespace std;",
            "",
            desc,
            "",
            "// Put your code here",
            "}}  // namespace l{}".format(num),
            "#endif",
        ]))
        print("[+] create file: {}".format(path))


def generate_unittest(path:str, num: int, desc: str):
    with open(path, "w") as f:
        f.write("\n".join([
            "",
            "#ifndef Q{}_UNITTEST_H__".format(num),
            "#define Q{}_UNITTEST_H__".format(num),
            "#include <gtest/gtest.h>",
            "",
            "#include \"q{}.hpp\"".format(str(num).rjust(4, '0')),
            "using namespace std;",
            "",
            desc,
            "",
            "TEST(q{}, sample_input01) {{".format(num),
            "}",
            "",
            "#endif",
        ]))
        print("[+] create file: {}".format(path))


def generate_intv_unittest(path: str, intv: str):
    with open(path, "w") as f:
        f.write("\n".join([
            "",
            "#ifndef {}_UNITTEST\n".format(intv.upper()),
            "#define {}_UNITTEST\n".format(intv.upper()),
            "#endif",
        ]))
        print("[+] create file: {}".format(path))
