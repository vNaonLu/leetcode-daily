import re
import csv
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
                id_map.items(), key=lambda pair: int(pair[0]))])
            f.truncate()


def readme_queslist(path: str, list: str):
    ids: dict[int, dict[str, any]] = {}
    with open(list, "r") as f:
        rows = csv.DictReader(f, delimiter=',')
        for row in rows:
            if row["done"] == "1":
                ids[int(row["id"])] = row
    
    if len(ids.keys()) == 0:
        return

    with open(path, "r+") as f:
        contents = f.readlines()
        for i in range(0, len(contents)):
            find = re.search("(/d{4})", contents[i])
            ques = None
            if find:
                ques = ids.get(int(find.group(1)))
                if ques:
                    contents[i] = "- [x] {} [{}]({})\n".format(
                        ques["id"].zfill(4),
                        ques["title"],
                        "src/{}/q{}.hpp".format(
                            leetcode.get_question_id_path(int(ques["id"])),
                            ques["id"].zfill(4)))
        
        f.seek(0)
        f.writelines(contents)
        f.truncate()
