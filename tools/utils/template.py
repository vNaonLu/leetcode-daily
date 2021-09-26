import re


def source(id: int, includes: set[str], desc: str, snippet: str):
    return "\n".join([
        "",
        "#ifndef LEETCODE_Q{}_H__".format(id),
        "#define LEETCODE_Q{}_H__".format(id)] + [
        "#include <{}>".format(icd) for icd in sorted(includes)] + [
        "",
        "namespace l{} {{".format(id),
        "using namespace std;",
        "",
        desc,
        "",
        snippet,
        "}}  // namespace l{}".format(id),
        "",
        "#endif"])


def __unittest_case(id: int, case: list[list[str]]):
    if case == None or len(case) == 0:
        return "\n".join([
            "",
            "TEST(q{}, NOT_IMPLEMENT) {{".format(id),
            "   EXPECT_TRUE(\"NOT IMPLEMENT\")",
            "}"
        ])
    res: list[str] = []
    for i in range(0, len(case)):
        res.append("\n".join([
            "",
            "TEST(q{}, sample_input{}) {{".format(id, str(i+1).zfill(2)),
            "  l{}::Solution solver;".format(id)] + [
            "  {}".format(line) for line in case[i]] + [
            "}"]))
    return "\n".join(res)


def unittest(id: int, desc: str, case: list[list[str]]):
    return "\n".join([
        "",
        "#ifndef Q{}_UNITTEST_H__".format(id),
        "#define Q{}_UNITTEST_H__".format(id),
        "#include <gtest/gtest.h>",
        "",
        "#include \"q{}.hpp\"".format(str(id).zfill(4)),
        "using namespace std;",
        "",
        desc,
        __unittest_case(id, case),
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
    if desc == None:
        return "\n".join([
            "/**",
            "  * {}".format(prompt),
            "  *",
            "  * {}. {}".format(id, title),
            "  * To unlock the question need a premium account.",
            "  *",
            "*/"])
    else:
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
