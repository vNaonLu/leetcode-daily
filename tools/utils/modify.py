import datetime
import calendar
import time
import csv
import re
from . import leetcode


def subunittest(path: str, new_file: str):
    with open(path, "r+") as f:
        content = f.readlines()
        for i in range(0, len(content)):
            if content[i] == "#endif":
                content.insert(i, "#include \"{}\"\n".format(new_file))
                break
        f.seek(0)
        f.writelines(content)
        f.truncate()
        print("[+] modify file: {}".format(path))


def unittest(path: str, num: int, intv: str):
    with open(path, "r+") as f:
        text = f.readlines()
        index = 0
        for i in range(0, len(text)):
            index = i
            if re.search("#include", text[i]):
                cintv = re.search("Q_(\d*)_(\d*)", text[i])
                if cintv and int(cintv.group(1)) > num:
                    break
                elif cintv and int(cintv.group(1)) < num and int(cintv.group(2)) > num:
                    index = len(text) - 1
                    break
            else:
                break

        if index < len(text) - 1:
            text.insert(
                index, "#include \"{}/unittest.hpp\"\n".format(intv.lower()))
            f.seek(0)
            f.write("".join(text))
            f.truncate()
        print("[+] modify file: {}".format(path))


def question_list(path: str, ids: list[int]):
    id_map: dict[int, dict[str, any]] = {}

    with open(path, "r+") as f:
        rows = csv.DictReader(f, delimiter=',')
        writer = csv.DictWriter(
            f,
            fieldnames=['id', 'title', 'level', 'slug', 'done'],
            delimiter=',')
        for row in rows:
            id_map[int(row["id"])] = row

        if len(ids) > 0:
            for id in ids:
                id_map[id]['done'] = 1
                print("[+] modify question #{:4} in list".format(id))
            f.seek(0)
            writer.writeheader()
            writer.writerows([v for _, v in sorted(
                id_map.items(), key=lambda pair: pair[0])])
            f.truncate()


def log(log: str, id: int):
    with open(log, "a") as f:
        f.write("{},{}\n".format(
            calendar.timegm(time.strptime(
                datetime.date.today().strftime("%Y%m%d"), '%Y%m%d')),
            id))


def __table(line: list[str], obj: dict[str, any]):
    line[2] += ("[📄](src/{}/q{}.hpp)".format(
        leetcode.get_question_id_path(int(obj["id"])),
        obj["id"].zfill(4)
    ))
    line[3] += obj["id"]
    line[4] += "[{}](https://leetcode.com/problems/{}/)".format(
        obj["title"],
        obj["slug"]
    )
    line[5] += "{}".format("Hard" if obj["level"] == "3" else (
        "Medium" if obj["level"] == "2" else "Easy"))
    return line


def readme(readme: str, qlist: str, log: str):
    ids_map: dict[int, dict[str, any]] = {}
    quest_list: list[str] = []
    with open(qlist, "r") as f:
        rows = csv.DictReader(f, delimiter=',')
        for row in rows:
            ids_map[int(row["id"])] = row
            if row["done"] == "1":
                quest_list.append("- [x] {} [{}]({})".format(
                    row["id"].zfill(4),
                    row["title"],
                    "src/{}/q{}.hpp".format(
                        leetcode.get_question_id_path(int(row["id"])),
                        row["id"].zfill(4))))
            else:
                quest_list.append("- [ ] {} {}".format(
                    row["id"].zfill(4),
                    row["title"]))

    log_map: dict[int, list[int]] = {}
    with open(log, "r") as f:
        rows = csv.DictReader(f, delimiter=",")
        for row in rows:
            date = time.strftime("%Y%m%d", time.localtime(int(row["date"])))
            if not log_map.get(date):
                log_map[date] = []
            log_map[date].append(int(row["id"]))

    with open(readme, "w") as f:
        f.write("\n".join([
            "# Daily Leetcode in C++",
            "",
            "[![githubbuild](https://github.com/vNaonLu/Daily_LeetCode/actions/workflows/test.yml/badge.svg)](https://github.com/vNaonLu/Daily_LeetCode/actions)",
            "",
            "My daily challenge on leetcode since 2021/09/06.",
            "",
            "## Questions List",
            "",
            ""
        ]))

        for i in range(0, len(quest_list), 250):
            lines = ["<details>",
                     "  <summary>### {} ~ {}</summary>".format(i+1, i+250),
                     ""]
            lines += quest_list[i:min(i+250, len(quest_list))]
            lines.append("</details>")
            lines.append("")
            f.write("\n".join(lines))

        f.write("\n".join([
            "",
            "---"
            "",
            "## Questions List",
            "",
            "|Date|File|#|Question Title|Difficulty|",
            "|:-:|:-:|--:|:--|:--|",
            ""
        ]))

        for date, ids in sorted(log_map.items(), key=lambda pair: pair[0], reverse=True):
            line: list[str] = ["", str(date) + "<br>", "", "", "", "", "\n"]
            line = __table(line, ids_map[ids[0]])
            for i in range(1, len(ids)):
                for j in range(1, 6):
                    line[j] += "<br>"
                line = __table(line, ids_map[ids[i]])
            f.write("|".join(line))
        f.truncate()
        print("[+] modify file: {}".format(readme))
