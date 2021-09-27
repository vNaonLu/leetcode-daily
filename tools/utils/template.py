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
