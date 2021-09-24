import re
from . import request as LeetCodeRequest


class LeetCodeQuestion:
    __example_id = " “Example"
    __constraints_id = " “Constraints"
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

    def __init__(self, title_slug: str):
        res_obj = LeetCodeRequest.question_details(title_slug)
        self.__id: int = int(res_obj['questionId'])
        self.__title: str = res_obj['questionTitle']
        self.__slug: str = res_obj['titleSlug']
        self.__level: str = res_obj['difficulty']
        self.__snippet: str = None

        for snippet in res_obj['codeSnippets']:
            if snippet['langSlug'] == "cpp":
                self.__snippet = snippet['code']
                break

        self.__desc: list[str] = None
        self.__cons: list[str] = None
        self.__parse_content(res_obj['content'])

    def __parse_desc(self, mul_lines: list[str]):
        for i in range(0, len(mul_lines)):
            if self.__example_id == mul_lines[i][:len(self.__example_id)] or \
                    self.__constraints_id == mul_lines[i][:len(self.__constraints_id)]:
                return mul_lines[:i]
        return mul_lines

    def __parse_exam(self, mul_lines: list[str], beg: int = 0):
        example_beg = beg
        for i in range(beg, len(mul_lines)):
            if self.__example_id == mul_lines[i][:len(self.__example_id)]:
                example_beg = i
                break

        for i in range(example_beg, len(mul_lines)):
            if self.__constraints_id == mul_lines[i][:len(self.__constraints_id)]:
                return mul_lines[example_beg:i]
        return []

    def __parse_cons(self, mul_lines: list[str]):
        cons: list[str] = []

        for line in mul_lines:
            if len(line) > 0 and self.__constraints_id != line[:len(self.__constraints_id)]:
                cons.append(line)
        return cons

    def __parse_content(self, content: str):
        if content != None:
          for label in self.__remove:
              content = re.sub(label, "", content)
          for patt, repl in self.__replace:
              content = re.sub(patt, repl, content)
          multi_lines = content.splitlines()

          description = self.__parse_desc(multi_lines)
          example = self.__parse_exam(multi_lines, len(description))
          constraints = self.__parse_cons(
              multi_lines[len(description)+len(example):])
          self.__desc = description
          self.__cons = constraints

    def id(self):
        return self.__id

    def title(self):
        return self.__title

    def slug(self):
        return self.__slug

    def difficulty(self):
        return self.__level

    def code_snippet(self):
        return self.__snippet

    def description(self, limit: int = None):
        if self.__desc == None:
            return None
        if not limit:
            return "\n".join(self.__desc)
        else:
            desc: list[str] = []
            for line in self.__desc:
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
                            desc.append(line[last:i])
                            last = -1
                        else:
                            desc.append(line[last:last_space])
                            last = last_space + 1
                        char_cnt = 0
                    if i == len(line) - 1 and last != -1:
                        desc.append(line[last:])
            return "\n".join(desc)

    def constraints(self):
        return self.__cons
