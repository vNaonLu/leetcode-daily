import csv
from pathlib import Path
import re
import os
import time
from . import local, template, prompt as pmt


def __modify_prompt(file: Path):
    pmt.show(pmt.succ(pmt.hi("The file has been modified: ") + str(file), "+"))


def __delete_prompt(file: Path):
    pmt.show(pmt.succ(pmt.hi("The file has been deleted : ") + str(file), "-"))


def remove(path: Path):
    try:
        os.remove(path)
    except OSError as e:
        pmt.show(pmt.fail(pmt.hi("{} : ".format(e.strerror)) + str(path), "x"))
        return False
    else:
        __delete_prompt(path)
        return True


def removesubunittest(path: str, id: int):
    new_contents: list[str] = []
    modify = False
    with open(path, "r") as f:
        content = f.readlines()
        for i in range(0, len(content)):
            find = re.search("#include \"q{}.hpp\"", content[i])
            if find and int(find.group(1)) == id:
                modify = True
                continue
            new_contents.append(content[i])

    if modify:
        with open(path, "w") as f:
            f.writelines(new_contents)
            __modify_prompt(path)


def subunittest(path: str, file_name: str):
    with open(path, "r+") as f:
        content = f.readlines()
        for i in range(0, len(content)):
            if content[i] == "#endif":
                content.insert(i, "#include \"{}\"\n".format(file_name))
                break
        f.seek(0)
        f.writelines(content)
        f.truncate()
        __modify_prompt(path)


def done_question(path: str, ids: list[int], src_path: str):
    id_map: dict[int, dict[str, any]] = {}

    with open(path, "r+") as f:
        rows = csv.DictReader(f, delimiter=',')
        writer = csv.DictWriter(
            f,
            fieldnames=['id', 'title', 'level',
                        'slug', "paid", 'done', "tc", "sc"],
            delimiter=',')
        for row in rows:
            id_map[int(row["id"])] = row
            id_map[int(row["id"])]["done"] = '0'

        if len(ids) > 0:
            for id in ids:
                id_map[id]['done'] = '1'

                if id_map[id]["tc"] == "" and id_map[id]["sc"] == "":
                    cp = local.get_commit_log(
                        local.QuestionSource(id, src_path))
                    if cp.returncode == 0:
                        com = local.get_complexity_infomation(
                            cp.stdout.decode("utf-8"))
                        if com:
                            id_map[id]["tc"] = com.time_complexity()
                            id_map[id]["sc"] = com.space_complexity()
                        else:
                            id_map[id]["tc"] = "-"
                            id_map[id]["sc"] = "-"

            f.seek(0)
            writer.writeheader()
            writer.writerows([v for _, v in sorted(
                id_map.items(), key=lambda pair: pair[0])])
            f.truncate()
            __modify_prompt(path)


def log(path: str, id: int, timestamp: int):
    with open(path, "a") as f:
        writer = csv.writer(f, delimiter=',')
        writer.writerow([timestamp, id])
        __modify_prompt(path)


def dellog(path: str, id: int):
    contents: list[list[str]] = []
    modify = False
    with open(path, "r") as f:
        rows = csv.reader(f, delimiter=',')
        for row in rows:
            if int(row[1]) == id:
                modify = True
            else:
                contents.append(row)

    if modify:
        with open(path, "w") as f:
            writer = csv.writer(f, delimiter=',')
            writer.writerows(contents)
            __modify_prompt(path)


def __introduce():
    return "\n".join([
        "# Daily LeetCode in C++",
        "",
        "[![githubbuild](https://github.com/vNaonLu/Daily_LeetCode/actions/workflows/test.yml/badge.svg)](https://github.com/vNaonLu/Daily_LeetCode/actions)",
        "",
        "This repository collects some of my LeetCode solutions for **free** questions since 2021/09/06."
        "The remain questions is still being solved so the current project may not contain the solutions you are looking for. "
        "Please check the chapter [Getting Started](#getting-started) for more details.",
        "",
        "Here is my [LeetCode account](https://leetcode.com/naon/) if you are interested.",
        "",
    ])


def __get_started():
    return "\n".join([
        "## Getting Started",
        "See [Activity](#activity) to check the recent solution resolution status, including the historical statistics and the recent submissions.",
        "All solutions are stored in `src` and more information can be found at [Find Solution](#finding-solution).",
        "See [Installation](#installation) if you are interested in how to build the project or want to add some testcases for some solutions.",
    ])


def __activity(solved_count: list[int], total_count: list[int], sub_activity: list[str]):
    docs = []
    for name in sub_activity:
        docs.append("- Submissions in {}: [docs/{}.md](./docs/{}.md)".format(name, name, name))
    return "\n".join([
        "## Activity",
        ""
        "![progress](./assets/progress.svg)"
        "",
        "More information about full activity can be found at:",
        "",
        "\n".join(docs)
    ])

def __finding_solution():
    return "\n".join([
        "## Finding Solution",
        "Solutions can be found in the directories in `./src` by its question identifier. "
        "For instance, the solution for [1. Two Sum](https://leetcode.com/problems/two-sum/) is stored in [`./src/q1_50/q0001.cc`](./src/q1_50/q0001.cc). "
        "The source usually contains a structure which is named by question identifier and inherits from the google test structure `testing::Test` and several testcases:",
        "```cpp",
        "#include <gtest/gtest.h>",
        "#include <iostream>",
        "",
        "// ...",
        "",
        "struct q1 : public ::testing::Test {",
        "  class Solution {",
        "  public:",
        "    vector<int> twoSum(vector<int> &nums, int target) {",
        "      // some solution...",
        "    }",
        "  };",
        "// ...",
        "};",
        "",
        "TEST_F(q1, sample_input01) {",
        "// some test input...",
        "}",
        "// ...",
        "```",
        "The approach is always appeared in the `struct` block."
        " Or you can simply use the script `repo_manager.py` to cat the exist solution via:",
        "```sh",
        "$ repo_manager.py -c <question id>",
        "```",
        "But the script probably won't work as it is very rough currently.",
    ])

def __installation():
    return "\n".join([
        "## Installation",
        "It is not necessary to build or install this project if you just want specific solutions, but you can still build and run this project. "
        "There has a python scripts named `repo_manager.py` in the root, which is a tool to automatically add/delete the solution in this project, generate the solution template or update the readme or log. "
        "However the script may too rough to use since I haven't tested it in other environment.",
        "Before running to build project, please check below dependencies exist in the build environment:",
        " - Compiler supports `C++17`.",
        " - CMake above `3.11`.",
        " - Unix-like OS.",
        "",
        "Then you can build the project easily by",
        "",
        "``` sh",
        "# Clone this project and change workspace to the project root.",
        "$ git clone https://github.com/vNaonLu/daily-leetcode",
        "$ cd daily-leetcode",
        "# Configure the cmake build files and build it.",
        "$ cmake -S . -B build -DENABLE_LEETCODE_TEST=ON",
        "$ cmake --build build",
        "# Run the leetcode test by GTest interface.",
        "$ ./build/leetcode_test",
        "```",
    ])


def readme(path: str, solved_count: list[int], total_count: list[int], sub_activity: list[str]):
    with open(path, "w") as f:
        f.write("\n".join([
            __introduce(),
            "",
            __get_started(),
            "",
            __activity(solved_count, total_count, sub_activity),
            "",
            __finding_solution(),
            "",
            __installation(),
            "",
        ]))
        f.truncate()
        __modify_prompt(path)
        return

        ids = question_list.ids()
        for i in range(0, len(ids), 250):
            lines = ["<details>",
                     "  <summary>### {} ~ {}</summary>".format(
                         i+1, min(i+250, len(ids))),
                     "",
                     "|</>|#|Solution Title|Difficulty|",
                     "|:-:|--:|:--|:--|"]
            lines += [template.question_detail(question_list.get(id))
                      for id in ids[i:min(i+250, len(ids))]]
            lines.append("</details>")
            lines.append("")
            f.write("\n".join(lines))

        f.write("\n".join([
            "",
            "---"
            "",
            "## Last 25 Submissions",
            "",
            "|Time|Question Title|Difficulty|Solution|",
            "|:--|:--|:-:|:--|",
            ""
        ]))
        for log in solved[0:25]:
            date = time.strftime("%Y-%m-%d %H:%M",
                                 time.localtime(log.timestamp()))
            row = template.table_row(date, [question_list.get(log.id())])
            f.write("{}\n".format(row))

        f.write("\n".join([
            "",
            "## Previous Logs",
            "",
            "|Year|Submissions|Easy|Medium|Hard|",
            "|:--|:--|:--|:--|:--|",
            ""
        ]))

