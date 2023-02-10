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

def done_question(path: str, ids: list[int]):
    id_map: dict[int, dict[str, any]] = {}

    with open(path, "r+") as f:
        rows = csv.DictReader(f, delimiter=',')
        writer = csv.DictWriter(
            f,
            fieldnames=['id', 'title', 'level', 'slug', "paid", 'done', "tc", "sc"],
            delimiter=',')
        for row in rows:
            id_map[int(row["id"])] = row
            id_map[int(row["id"])]["done"] = '0'

        if len(ids) > 0:
            for id in ids:
                id_map[id]['done'] = '1'
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


def readme(path: str, question_list: local.QuestionList,
           solved: list[local.Log], sub_md: list[str]):
    with open(path, "w") as f:
        f.write("\n".join([
            "# Daily LeetCode in C++",
            "",
            "[![githubbuild](https://github.com/vNaonLu/Daily_LeetCode/actions/workflows/test.yml/badge.svg)](https://github.com/vNaonLu/Daily_LeetCode/actions)",
            "",
            "This repository collects some of my LeetCode solutions since 2021/09/06.",
            "Here is my [LeetCode account](https://leetcode.com/naon/) if you are interested.",
            "",
            "## Questions List",
            "",
            "![free questions progress](./assets/submission.svg)"
            "",
            ""
        ]))

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
            "|Time|#|</>|Question Title|Difficulty|",
            "|:--|--:|:-:|:--|:--|",
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
            "|Month|Submissions|Easy|Medium|Hard|",
            "|:--|:--|:--|:--|:--|",
            ""
        ]))

        for md in sub_md:
            row = ["[{}](./assets/{}.md)".format(md[0], md[0]),
                   str(md[1][0] + md[1][1] + md[1][2]),
                   str(md[1][0]), str(md[1][1]), str(md[1][2])]
            f.write("|{}|\n".format("|".join(row)))
        f.truncate()
        __modify_prompt(path)
