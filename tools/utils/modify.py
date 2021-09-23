import re
import csv
import time

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


def readme(path: str, qlist: str, log: str):
    # ids_map: dict[int, dict[str, any]] = {}
    # with open(qlist, "r") as f:
    #     rows = csv.DictReader(f, delimiter=',')
    #     for row in rows:
    #         ids_map[int(row["id"])] = row

    log_map: dict[int, list[int]] = {}
    with open(log, "r") as f:
        rows = csv.DictReader(f, delimiter=",")
        for row in rows:
            date = time.strftime("%Y%m%d", time.localtime(int(row["date"])))
            if not log_map.get(date):
                log_map[date] = []
            log_map[date].append(int(row["id"]))
    print(log_map)