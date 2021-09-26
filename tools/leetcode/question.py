import re
from . import request as LeetCodeRequest


class CodePrettifier:
    @staticmethod
    def argument(type: str, value: str):
        m_vec = re.search("vector<(?P<typ>.+)>", type)
        m_chr = re.search("char", type)
        m_lst = re.search("ListNode", type)
        m_trn = re.search("TreeNode", type)
        if m_vec:
            m_typ = m_vec.group("typ")
            m_val = re.search("\[(?P<val>.*)\]", value)
            m_val = m_val if m_val == None else m_val.group("val")
            if m_val:
                elm = re.findall("(\[[\w\"\',]*\]|[\w\"']+)", m_val)
                val_in_vec = [CodePrettifier.argument(m_typ, e) for e in elm]
                value = "{{{}}}".format(", ".join(val_in_vec))

        elif m_chr:
            value = re.sub("\"", "'", value)

        elif m_lst:
            m_val = re.search("\[(?P<val>[\w,]*)\]", value)
            m_val = m_val if m_val == None else m_val.group("val")
            if m_val:
                m_val = re.sub(",", ", ", m_val)
                value = "ListNode::generate({{{}}})".format(m_val)

        elif m_trn:
            m_val = re.search("\[(?P<val>[\w,]*)\]", value)
            m_val = m_val if m_val == None else m_val.group("val")
            if m_val:
                m_val = re.sub(",", ", ", m_val)
                m_val = re.sub("null", "NULL_TREENODE", m_val)
                value = "TreeNode::generate({{{}}})".format(m_val)

        return value


class SolutionAbstract:
    _func_pattern: str = "(?P<return_type>[\w<>*]+) +(?P<function_name>\w*)\((?P<args>.*)\) {"
    _args_pattern: str = "(?P<type>[\w<>*]+)&{0,1} +(?P<name>[\w]+)"
    _type_pattern: list[str, str] = [("ListNode", "leetcode/listnode.hpp"), ("TreeNode", "leetcode/treenode.hpp"),
                                     ("vector", "vector"), ("map", "map"),
                                     ("unordered_map", "unordered_map"), ("string", "string")]
    _input_identifier: str = "Input:"
    _output_identifier: str = "Output:"
    _outputend_identifier: str = "“"

    def __init__(self):
        self._type: str = None
        self._name: str = ""
        self._args: dict[str, str] = {}
        self._includes: set[str] = set()
        self._includes.add("iostream")

    def name(self):
        return self._name

    def type(self):
        return self._type

    def args(self):
        return list(self._args.items())

    def includes(self):
        return self._includes

    def unittest_desc(self, desc: list[str]):
        return []

    def _parse_type(self, type: str):
        for pttn, include in self._type_pattern:
            if re.search(pttn, type):
                self._includes.add(include)

    def function(self):
        return "{}({})".format(self.name(),
                               ", ".join([name for name, _ in self.args()]))

    @staticmethod
    def _is_known_type(type: str):
        primitive_pattern = "void|int|char|double|float"
        stllib_pattern = "vector|map|unoredered_map|set|unoredered_set|stack|queue|string"
        custom_pattern = "ListNode|TreeNode"
        single_container_pattern = "(?P<type>\w+)<(?P<val>\w+)>"
        double_container_pattern = "(?P<type>\w+)<(?P<val1>\w+),[ ]*(?P<val2>\w+)>"

        m_s = re.search(single_container_pattern, type)
        if m_s:
            return SolutionAbstract._is_known_type(m_s.group("type")) and \
                SolutionAbstract._is_known_type(m_s.group("val"))
        m_d = re.search(double_container_pattern, type)
        if m_d:
            return SolutionAbstract._is_known_type(m_d.group("type")) and \
                SolutionAbstract._is_known_type(m_d.group("val1")) and \
                SolutionAbstract._is_known_type(m_d.group("val2"))
        if re.match(primitive_pattern, type):
            return True
        elif re.match(stllib_pattern, type):
            return True
        elif re.match(custom_pattern, type):
            return True
        return False


class SolutionFunction(SolutionAbstract):
    def __init__(self, code_snippet: list[str]):
        SolutionAbstract.__init__(self)
        self.__parse_codesnippets(code_snippet)

    def __parse_codesnippets(self, code_snippet: list[str]):
        for line in code_snippet:
            match = re.search(self._func_pattern, line)
            if match:
                self._name = match.group("function_name")
                self._type = match.group("return_type")
                self._parse_type(self._type)
                args = match.group("args").split(",")
                for arg in args:
                    m_arg = re.search(self._args_pattern, arg)
                    self._parse_type(m_arg.group("type"))
                    self._args[m_arg.group("name")] = m_arg.group("type")

    def __parse_input(self, input: str):
        inputs: list[str] = []
        matches = re.findall("(?P<name>\w+) = (?P<value>\d+|\[[^=]+\]|\"[^=]+\")",
                             input)
        for i in range(0, len(matches)):
            # in order based on function arguments
            arg_name, arg_type = self.args()[i]
            value = matches[i][1]
            if arg_type == None:
                continue
            value = CodePrettifier.argument(arg_type, value)
            inputs.append("{} {} = {};".format(arg_type, arg_name, value))
        return inputs

    def __parse_output(self, output: str):
        outputs: list[str] = []
        if self._type == "void":
            # assume adjust the first argument
            _, type = self.args()[0]
            output = CodePrettifier.argument(type, output)
            outputs.append("{} exp = {};".format(type, output))
            outputs.append("solver.{};".format(self.function()))
        else:
            output = CodePrettifier.argument(self._type, output)
            outputs.append("{} exp = {};".format(self._type, output))
        return outputs

    def __expect_equation(self):
        expect: list[str] = []
        eq_arg1 = "solver." + self.function()
        eq_type = self._type

        if self._type == "void":
            # assume adjust the first argument
            name, type = self.args()[0]
            eq_type = type
            eq_arg1 = name

        if re.search("ListNode", eq_type):
            expect.append("EXPECT_LISTNODE_EQ({}, exp);".format(eq_arg1))
        elif re.search("TreeNode", eq_type):
            expect.append("EXPECT_TREENODE_EQ({}, exp);".format(eq_arg1))
        else:
            expect.append("EXPECT_EQ({}, exp);".format(eq_arg1))

        return expect

    def unittest_desc(self, desc: list[str]):
        res: list[list[str]] = []
        content = "".join(desc)
        cases = re.split("Example", content)

        if self._is_known_type(self.type()):
            for case in cases:
                m_cas = \
                    re.search("Input:[^\w]+(?P<in>[\w -=\[\],\"']+)[^\w]+Output:[^\w=-\[\],\"']+(?P<out>[\w -=\[\],\"']+)",
                              case)
                if m_cas:
                    inp = self.__parse_input(m_cas.group("in").strip())
                    out = self.__parse_output(m_cas.group("out").strip())
                    eq = self.__expect_equation()
                    res.append(inp + out + eq)
        return res


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
                 ["<sup>", "^("], ["</sup>", ")"], ["&#39;", "'"],
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
                    self.__snippet = re.sub(
                        "public:", " public:", self.__snippet)
                    self.__snippet = re.sub(
                        "private:", " private:", self.__snippet)
                    self.__snippet = re.sub(
                        "protected:", " protected:", self.__snippet)
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
        return self.__slttmp.function()

    def return_type(self):
        return self.__slttmp.type()

    def return_args(self):
        return self.__slttmp.args()

    def unittest_case(self):
        return self.__testcase
