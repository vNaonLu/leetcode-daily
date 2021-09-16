#!/usr/bin/python3

import os
import pathlib
import re
from utils import leetcode

qs = leetcode.get_questions()

project_path = pathlib.Path(__file__).parent.parent.resolve()
source_root_path = os.path.join(project_path, "src")

file_map: dict[int, str] = {}
for path, _, files in os.walk(source_root_path):
    for file in files:
        g = re.search("q(\d*).hpp", file)
        if g is not None:
            file_map[int(g.group(1))
                     ] = 'src/{}/{}'.format(pathlib.PurePath(path).name, file)


def id(q: leetcode.Question):
    return q.id


qs.sort(key=id)

for q in qs:
    if q.id in file_map:
        print("- [x] {} [{}]({})".format(str(q.id).rjust(4, '*'), q.title, file_map[q.id]))
    else:
        print("- [ ] {} {}".format(str(q.id).rjust(4, '*'), q.title))
