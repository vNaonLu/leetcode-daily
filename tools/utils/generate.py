import csv
from pathlib import Path
from . import prompt as pmt


def __generate_prompt(file: Path):
    pmt.show(pmt.succ(pmt.hi("The file has been created : ") + str(file), "+"))


def file(path: str, content: str):
    with open(path, "w") as f:
        f.write(content)
        __generate_prompt(path)


def question_list(path: str, ques: list[object]):
    ques.sort(key=lambda q: q['stat']['frontend_question_id'])
    with open(path, "w") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=["id", "title", "level", "slug", "paid", "done"],
            delimiter=',')
        writer.writeheader()
        writer.writerows([{
            "id": q['stat']['frontend_question_id'],
            "title": q['stat']['question__title'],
            "level": q['difficulty']['level'],
            "slug": q['stat']['question__title_slug'],
            "paid": 1 if q['paid_only'] == True else 0,
            "done": 0} for q in ques])
