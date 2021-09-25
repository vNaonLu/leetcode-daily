def source(num: int, includes: set[str], desc: str, snippet: str):
    return "\n".join(["",
                      "#ifndef LEETCODE_Q{}_H__".format(num),
                      "#define LEETCODE_Q{}_H__".format(num)] + [
                      "#include <{}>".format(icd) for icd in includes] + [
                      "",
                      "namespace l{} {{".format(num),
                      "using namespace std;",
                      "",
                      desc,
                      snippet,
                      "}}  // namespace l{}".format(num),
                      "#endif"])


def unittest(num: int, desc: str):
    return "\n".join([
        "",
        "#ifndef Q{}_UNITTEST_H__".format(num),
        "#define Q{}_UNITTEST_H__".format(num),
        "#include <gtest/gtest.h>",
        "",
        "#include \"q{}.hpp\"".format(str(num).zfill(4)),
        "using namespace std;",
        "",
        desc,
        "",
        "TEST(q{}, sample_input01) {{".format(num),
        "}",
        "",
        "#endif"])


def subunittest(intv: str, files: list[str]):
    return "\n".join([
        "",
        "#ifndef {}_UNITTEST".format(intv.upper()),
        "#define {}_UNITTEST".format(intv.upper()),
        ""] + [
        "#include \"{}\"".format(file) for file in files] + [
        "",
        "#endif"])


def mainunittest(subunittest: list[str]):
    return "\n".join([
        "#include <gtest/gtest.h>"] + [
        "#include \"{}\"".format(utfile) for utfile in subunittest] + [
        "",
        "int main(int argc, char **argv) {",
        "  ::testing::InitGoogleTest(&argc, argv);",
        "  return ::RUN_ALL_TESTS();",
        "}"])


def question_description(prompt: str,
                         id: int,
                         title: str,
                         desc: list[str],
                         cons: list[str]):
    return "\n".join([
        "/**",
        "  * {}".format(prompt),
        "  *",
        "  * {}. {}".format(id, title),
        "  * " + "\n  * ".join(desc),
        "  *",
        "  * Constraints:",
        "  * " + "\n  * ".join(cons),
        "  *",
        "*/"])
