#!/usr/bin/python3

import sys
from utils import leetcode


class Question(object):
    def __init__(self, num: str, name: str, diff: str):
        self.num = num
        self.name = name
        self.diff = diff


def number(q: Question):
    return int(q.num)


# minus filename and date
if((len(sys.argv) - 2) % 3):
    print("[Usage] <date> [<question number> \"<question name>\" <difficulty=e/m/d>]...")
else:
    date = sys.argv[1]
    arr = sys.argv[2:]
    ques = []

    for i in range(0, len(arr), 3):
        ques.append(Question(arr[i], arr[i+1], arr[i+2]))

    ques.sort(key=number)

    mdtable = "output: \n\n|{}".format(str(date))
    for i in range(0, len(ques)):
        mdtable += "<br>"

    mdtable += "|"
    for q in ques:
        sub = leetcode.get_question_id_path(int(q.num))
        mdtable += "[📄](src/{}/q{}.hpp)".format(
            sub.lower(), q.num.rjust(4, '0'))
        if q != ques[-1]:
            mdtable += "<br>"

    mdtable += "|"
    for q in ques:
        mdtable += str(q.num)
        if q != ques[-1]:
            mdtable += "<br>"

    mdtable += "|"
    for q in ques:
        mdtable += "[{}](https://leetcode.com/problems/{}/)".format(q.name,
                                                                    "-".join((q.name.lower().split(' '))))
        if q != ques[-1]:
            mdtable += "<br>"

    mdtable += "|"
    for q in ques:
        if q.diff == "e":
            mdtable += '<span style="color:green">Easy</span>'
        elif q.diff == "m":
            mdtable += '<span style="color:orange">Medium</span>'
        elif q.diff == "h":
            mdtable += '<span style="color:red">Hard</span>'

        if q != ques[-1]:
            mdtable += "<br>"

    mdtable += "|"

    print(mdtable)
