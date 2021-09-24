import csv


def __generate_prompt(file: str):
    print("[+] ganerate a file: {}".format(file))


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
        for q in ques:
            writer.writerow({
                "id": q['stat']['frontend_question_id'],
                "title": q['stat']['question__title'],
                "level": q['difficulty']['level'],
                "slug": q['stat']['question__title_slug'],
                "done": 0})
