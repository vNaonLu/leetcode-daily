import csv


def generate_source(path: str, num: int,
                    desc: str, snippet: str):
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
            snippet,
            "}}  // namespace l{}".format(num),
            "#endif",
        ]))
        print("[+] create file: {}".format(path))


def generate_unittest(path: str, num: int, desc: str):
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


def generate_question_list(path: str, ques: list[object]):
    ques.sort(key=lambda q: q['stat']['frontend_question_id'])
    with open(path, "w", newline="") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=["id", "title", "level", "slug", "done"],
            delimiter=',')
        writer.writeheader()
        for q in ques:
            writer.writerow({
                "id": q['stat']['frontend_question_id'],
                "title": q['stat']['question__title'],
                "level": q['difficulty']['level'],
                "slug": q['stat']['question__title_slug'],
                "done": 0,
            })
        print("[+] create file: {}".format(path))


def generate_question_description(prompt: str,
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
        "*/"
    ])
