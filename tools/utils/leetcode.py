import requests
import json
import re
import math

__remove = ["</?p>", "</?ul>", "</?ol>", "</li>", "<img.*/>"]
__replace = [["&nbsp;", ""], ["&quot;", '"'], ["&lt;", "<"], ["&gt;", ">"],
             ["&le;", "≤"], ["&ge;", "≥"],
             ["<sup>", "^("], ["</sup>", ")"], ["&#39", "'"],
             ["<sub>", "⎽("], ["</sub>", ")"],
             ["<b>", " “"], ["</b>", "” "],
             ["&times;", "x"], ["&ldquo;", "“"], ["&rdquo;", "”"],
             [" *<strong> *", " “"], [" *</strong> *", "“ "],
             [" *<code> *", " "], [" *</code> *", " "], ["<pre>", ""],
             ["</pre>", ""], ["<em> *</em>", ""], [" *<em> *", " "],
             [" *</em> *", " "], ["</?div.*?>", ""], ["	*</?li>", "- "], ["\n\n", "\n"]]


def __repl(content: str):
    for label in __remove:
        content = re.sub(label, "", content)
    for patt, repl in __replace:
        content = re.sub(patt, repl, content)
    return content


def __limit_word(multi_lines=list[str], limit: int = 50):
    new_lines: list[str] = []
    for line in multi_lines:
        char_cnt = 0
        last = -1
        last_space = -1
        for i in range(0, len(line)):
            char_cnt += 1
            if line[i] == ' ':
                last_space = i
            if last == -1 and line[i] != ' ':
                last = i
            if char_cnt >= limit:
                if line[i] == ' ':
                    new_lines.append(line[last:i])
                    last = -1
                else:
                    new_lines.append(line[last:last_space])
                    last = last_space + 1
                char_cnt = 0
            if i == len(line) - 1 and last != -1:
                new_lines.append(line[last:])

    return new_lines


__example_id = " “Example"
__constraints_id = " “Constraints"


def __find_description(multi_lines: list[str]):
    for i in range(0, len(multi_lines)):
        if __example_id == multi_lines[i][:len(__example_id)] or \
                __constraints_id == multi_lines[i][:len(__constraints_id)]:
            return multi_lines[:i]
    return multi_lines


def __find_example(multi_lines: list[str], beg: int = 0):
    example_beg = beg
    for i in range(beg, len(multi_lines)):
        if __example_id == multi_lines[i][:len(__example_id)]:
            example_beg = i
            break

    for i in range(example_beg, len(multi_lines)):
        if __constraints_id == multi_lines[i][:len(__constraints_id)]:
            return multi_lines[example_beg:i]
    return []


def __prettify_constraints(multi_lines: list[str]):
    new_lines: list[str] = []

    for line in multi_lines:
        if len(line) > 0 and __constraints_id != line[:len(__constraints_id)]:
            new_lines.append(line)
    return new_lines


def __parse(block: str):
    multi_lines = __repl(block).splitlines()

    res = {}
    description = __find_description(multi_lines)
    example = __find_example(multi_lines, len(description))
    constraints = multi_lines[len(description)+len(example):]
    res['Description'] = __limit_word(description)
    res['Constraints'] = __prettify_constraints(constraints)

    return res


session = requests.Session()
user_agent = r'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/44.0.2403.157 Safari/537.36'


def __get_problem_content(slug: str):
    url = "https://leetcode.com/graphql"
    params = {
        'operationName': "getQuestionDetail",
        'variables': {'titleSlug': slug},
        'query': '''query getQuestionDetail($titleSlug: String!) {
            question(titleSlug: $titleSlug) {
                questionId
                questionTitle
                content
                difficulty
            }
        }'''
    }

    json_data = json.dumps(params).encode('utf8')

    headers = {'User-Agent': user_agent, 'Connection':
               'keep-alive', 'Content-Type': 'application/json',
               'Referer': 'https://leetcode.com/problems/' + slug}
    resp = session.post(url, data=json_data,
                        headers=headers, timeout=10).json()
    return resp['data']['question']


def __get_problem(number: int):
    res: list[Question] = []
    url = "https://leetcode.com/api/problems/all/"

    headers = {'User-Agent': user_agent, 'Connection': 'keep-alive'}
    resp = session.get(url, headers=headers, timeout=10)

    question_list = json.loads(resp.content.decode('utf-8'))

    for question in question_list['stat_status_pairs']:
        if number == question['stat']['frontend_question_id']:
            return __get_problem_content(question['stat']['question__title_slug'])
    return None


class Question:
    def __init__(self, id: int, name: str, level: int):
        self.id: int = id
        self.title: str = name
        self.level: str = 'Easy'
        if level == 2:
            self.level = 'Medium'
        elif level == 3:
            self.level = 'Hard'


def get_questions():
    res: list[Question] = []
    url = "https://leetcode.com/api/problems/all/"

    headers = {'User-Agent': user_agent, 'Connection': 'keep-alive'}
    resp = session.get(url, headers=headers, timeout=10)

    question_list = json.loads(resp.content.decode('utf-8'))

    for question in question_list['stat_status_pairs']:
        q = Question(question['stat']['frontend_question_id'],
                     question['stat']['question__title'],
                     question['difficulty']['level'])
        res.append(q)
    return res


def get_description(number: int, prompt: str):
    problem = __get_problem(int(number))
    if problem['content'] != None:
        title = problem['questionTitle']
        content = __parse(problem['content'])

        res: list[str] = []
        res.append("/**\n")
        res.append("  * {}\n".format(prompt))
        res.append("  *\n")
        res.append("  * {}. {}\n".format(number, title))
        res.append("  *\n")
        for statement in content['Description']:
            res.append("  * {}\n".format(statement))
        res.append("  *\n")
        res.append("  * Constraints:\n")
        for statement in content['Constraints']:
            res.append("  * {}\n".format(statement))
        res.append("  *\n")
        res.append("*/\n")
        return res
    else:
        return None


def get_question_id_path(id: int):
    interval_idx = math.floor(id / 50)
    path = "q_{}_{}".format(interval_idx * 50 + 1, (interval_idx+1) * 50)
    return path
