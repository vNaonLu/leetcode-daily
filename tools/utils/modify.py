import re


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
        print("[+] modifify file: {}".format(path))


def unittest(path: str, num: str, intv: str):
    with open(path, "r+") as f:
        text = f.readlines()
        index = 0
        for i in range(0, len(text)):
            index = i
            if re.search("#include", text[i]):
                cintv = re.search("Q_(\d*)_(\d*)", text[i])
                if cintv and int(cintv.group(1)) > int(num):
                    break
                elif cintv and int(cintv.group(1)) < int(num) and int(cintv.group(2)) > int(num):
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
        print("[+] modifify file: {}".format(path))
