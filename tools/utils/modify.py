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


def question_list(path: str, id: int):
    with open(path, "r+") as f:
        rows = list(csv.reader(f))
        for row in rows:
            if row[0] == str(id):
                row[-1] = 1
                f.seek(0);
                writer = csv.writer(f)
                writer.writerows(rows)
                f.truncate()
                print("[+] modify question #{} in question list".format(id))
                break

# def readme(path: str, ques: leetcode.Question):
#     with open(path, "r+") as f:
#         contents = f.readlines()
#         for line in contents:
#             find = re.search("(/d{4})")