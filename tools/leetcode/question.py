import re
from . import request as LeetCodeRequest


class SolutionAbstract:
    _func_pattern: str = "(?P<return_type>[\w<>*]+) +(?P<functionName>\w*)\((?P<args>.*)\) {"
    _args_pattern: str = "(?P<type>[\w<>*]+)&{0,1} +(?P<name>[\w]+)"
    _type_pattern: list[str, str] = [("ListNode", "leetcode/listnode.hpp"), ("TreeNode", "leetcode/treenode.hpp"),
                                     ("vector", "vector"), ("map", "map"),
                                     ("unordered_map", "unordered_map"), ("string", "string")]
    _input_identifier: str = "Input:"
    _output_identifier: str = "Output:"
    _outputend_identifier: str = "“"

    def __init__(self):
        self._type: str = ""
        self._name: str = ""
        self._args: dict[str, str] = {}
        self._includes: set[str] = set()
        self._includes.add("iostream")

    def name(self):
        return self._name

    def type(self):
        return self._type

    def args(self):
        return self._args.items()

    def includes(self):
        return self._includes

    def unittest_desc(self, desc: list[str]):
        return []

    def _parse_type(self, type: str):
        for pttn, include in self._type_pattern:
            if re.search(pttn, type):
                self._includes.add(include)


class SolutionFunction(SolutionAbstract):
    _inpt_pattern = "(?P<name>\w+) = (?P<value>\d+|\[.*\]|\".*\")"
    _otpt_pattern = "“Output:” (?P<value>.+)"

    def __init__(self, code_snippet: list[str]):
        SolutionAbstract.__init__(self)
        self.__parse_codesnippets(code_snippet)

    def __parse_codesnippets(self, code_snippet: list[str]):
        for line in code_snippet:
            match = re.search(self._func_pattern, line)
            if match:
                self._name = match.group("functionName")
                self._type = match.group("return_type")
                self._parse_type(self._type)
                args = match.group("args").split(",")
                for arg in args:
                    arg_match = re.search(self._args_pattern, arg)
                    self._parse_type(arg_match.group("type"))
                    self._args[arg_match.group(
                        "name")] = arg_match.group("type")

    def __parse_input(self, input: str):
        inputs: list[str] = []
        matches = re.findall(self._inpt_pattern, input)
        for m in matches:
            name = m[0]
            value = m[1]
            arg_type = self._args[name]
            if arg_type == None:
                continue
            if re.search("vector", arg_type):
                value = re.sub(" ", "", value)
                value = re.sub(",", ", ", value)
                value = re.sub("\[", "{", value)
                value = re.sub("\]", "}", value)

            if re.search("ListNode", arg_type):
                value = re.sub(" ", "", value)
                value = re.sub(",", ", ", value)
                value = re.sub("\[", "{", value)
                value = re.sub("\]", "}", value)
                value = "ListNode::generate({})".format(value)

            if re.search("TreeNode", arg_type):
                value = re.sub(" ", "", value)
                value = re.sub(",", ", ", value)
                value = re.sub("null", "NULL_TREENODE", value)
                value = re.sub("\[", "{", value)
                value = re.sub("\]", "}", value)
                value = "TreeNode::generate({})".format(value)

            inputs.append("{} {} = {};".format(arg_type, name, value))
        return inputs

    def __parse_output(self, output: str):
        match = re.search(self._otpt_pattern, output)
        if match:
            value = match.group("value")
            if re.search("vector", self._type):
                value = re.sub(" ", "", value)
                value = re.sub(",", ", ", value)
                value = re.sub("\[", "{", value)
                value = re.sub("\]", "}", value)

            if re.search("ListNode", self._type):
                value = re.sub(" ", "", value)
                value = re.sub(",", ", ", value)
                value = re.sub("\[", "{", value)
                value = re.sub("\]", "}", value)
                value = "ListNode::generate({})".format(value)

            if re.search("TreeNode", self._type):
                value = re.sub(" ", "", value)
                value = re.sub(",", ", ", value)
                value = re.sub("null", "NULL_TREENODE", value)
                value = re.sub("\[", "{", value)
                value = re.sub("\]", "}", value)
                value = "TreeNode::generate({})".format(value)

            return "{} exp = {};".format(self._type, value)

    def unittest_desc(self, desc: list[str]):
        case: list[list[str]] = []
        for i in range(0, len(desc)):
            if re.search(self._input_identifier, desc[i]):
                inputs = []
                outputs = []
                for j in range(0, len(desc)-i):
                    if(re.search(self._output_identifier, desc[i+j])):
                        inputs = desc[i:i+j]
                        i += j
                        break
                for j in range(1, len(desc)-i):
                    if(re.search(self._outputend_identifier, desc[i+j])):
                        outputs = desc[i:i+j]
                        i += j
                        break

                if len(inputs) == 0 or len(outputs) == 0:
                    continue

                inp = self.__parse_input("".join(inputs))
                out = self.__parse_output("".join(outputs))
                if inp and out:
                    case.append(inp + [out])
        return case


class SolutionStructure(SolutionAbstract):
    def __init__(self, code_snippet: list[str]):
        SolutionAbstract.__init__(self)
        self.__parse_codesnippets(code_snippet)

    def __parse_codesnippets(self, code_snippet: list[str]):
        print("not implement structure")


class Solution:
    __func_pattern = "class Solution {1,}{"

    @staticmethod
    def generate_template(code_snippet: str):
        multi_lines = code_snippet.splitlines()
        for i in range(0, len(multi_lines)):
            if re.match(Solution.__func_pattern, multi_lines[i]):
                return SolutionFunction(multi_lines[i:])
        return SolutionStructure(multi_lines)


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
                 [" *<strong> *", " “"], [" *</strong> *", "” "],
                 [" *<code> *", " "], [" *</code> *", " "], ["<pre>", ""],
                 ["</pre>", ""], ["<em> *</em>", ""], [" *<em> *", " "],
                 [" *</em> *", " "], ["</?div.*?>", ""], ["	*</?li>", "- "], ["\n\n", "\n"]]

    def __init__(self, title_slug: str):
        res_obj = LeetCodeRequest.question_details(title_slug)
        self.__id: int = int(res_obj['questionFrontendId'])
        self.__title: str = res_obj['questionTitle']
        self.__slug: str = res_obj['titleSlug']
        self.__level: str = res_obj['difficulty']
        self.__snippet: str = ""
        self.__slttmp: SolutionAbstract = SolutionAbstract()
        self.__parse_code_snippet(res_obj['codeSnippets'])
        self.__desc: list[str] = None
        self.__cons: list[str] = None
        self.__testcase: list[list[str]] = []
        self.__parse_content(res_obj['content'])

    def __parse_code_snippet(self, code_snippets: list[object]):
        if code_snippets != None:
            for snippet in code_snippets:
                if snippet['langSlug'] == "cpp":
                    self.__snippet = re.sub("  ", " ", snippet['code'])
                    self.__snippet = re.sub("public:", " public:", self.__snippet)
                    self.__snippet = re.sub("private:", " private:", self.__snippet)
                    self.__snippet = re.sub("protected:", " protected:", self.__snippet)
                    # to google style
                    self.__slttmp = Solution.generate_template(self.__snippet)
                    break

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
            self.__testcase = self.__slttmp.unittest_desc(example)

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
            return [self.__desc]
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
            return desc

    def constraints(self):
        return self.__cons

    def includes(self):
        return self.__slttmp.includes()

    def function(self):
        return "{}({})".format(
            self.__slttmp.name(),
            ", ".join([name for name , _ in self.__slttmp.args()]))

    def return_type(self):
        return self.__slttmp.type()

    def return_args(self):
        return self.__slttmp.args()

    def unittest_case(self):
        return self.__testcase
