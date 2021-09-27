import csv
from . import prompt as pmt


def __generate_prompt(file: str):
    pmt.show(pmt.succ("The file has been created: {}".format(file)))


def file(path: str, content: str):
    with open(path, "w") as f:
        f.write(content)
        __generate_prompt(path)


def question_list(path: str, ques: list[object]):
    ques.sort(key=lambda q: q['stat']['frontend_question_id'])
    with open(path, "w") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=["id", "title", "level", "slug", "done"],
            delimiter=',')
        writer.writeheader()
        writer.writerows([{
            "id": q['stat']['frontend_question_id'],
            "title": q['stat']['question__title'],
            "level": q['difficulty']['level'],
            "slug": q['stat']['question__title_slug'],
            "done": 0} for q in ques])
