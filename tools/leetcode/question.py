import re
import regex
from . import request as LeetCodeRequest
from .argument import Argument
from .prettify import CodeSnippet, Description


class SolutionAbstract:
    def __init__(self, id: int, content: str):
        self._type: Argument = None
        self._id: int = id
        self._name: str = ""
        self._args: dict[str, Argument] = {}
        self._includes: set[str] = set()
        self._anyorder: bool = re.search("any order",
                                         content,
                                         re.IGNORECASE) != None
        self._includes.add("iostream")
        self._solnobj: str = "solution"

    def is_valid(self):
        return False

    def class_name(self):
        return "Solution"

    def solution_object(self):
        return self._solnobj

    def name(self):
        return self._name

    def type(self):
        return self._type.type()

    def isanyorder(self):
        return self._anyorder

    def args(self):
        return list(self._args.items())

    def includes(self):
        return self._includes

    def unittest_desc(self, content: str):
        return None

    def _add_include(self, arg: Argument):
        for include in arg.get_includes():
            self._includes.add(include)

    def function(self):
        return "{}({})".format(self.name(),
                               ", ".join([name for name, _ in self.args()]))


class SolutionFunction(SolutionAbstract):
    def __init__(self, id: int, code_snippet: list[str], content: str = ""):
        SolutionAbstract.__init__(self, id, content)
        self.__valid             : bool      = True
        self.__listnode_variables: list[str] = []
        self.__treenode_variables: list[str] = []
        self.__parse_codesnippets(code_snippet)

    def is_valid(self):
        return self.__valid

    def __parse_codesnippets(self, code_snippet: list[str]):
        for line in code_snippet:
            match = \
                re.search("(?P<return_type>\w+|\w+<[\w\W]+>|\w+? *\*) *(?P<function_name>\w+) *\((?P<args>.*)\) *{",
                          line)
            if match:
                self._name = match.group("function_name")
                self._type = Argument.generate(match.group("return_type"))
                self._add_include(self._type)
                for arg in match.group("args").split(","):
                    m_arg = \
                        re.search("(?P<type>[\w*&<> ]+[&*]{0,1}) +(?P<name>[\w]+)",
                                  arg)
                    if m_arg:
                        arg_name = m_arg.group("name")
                        arg = Argument.generate(m_arg.group("type"))
                        self._args[arg_name] = arg
                        self._add_include(arg)
                        self.__valid &= arg.is_valid()
                        if arg.type() == "ListNode*":
                            self.__listnode_variables.append(arg_name)
                        elif arg.type() == "TreeNode*":
                            self.__treenode_variables.append(arg_name)
                if self.type() == "ListNode*":
                    self.__listnode_variables.append("exp");
                    self.__listnode_variables.append("act");
                elif self.type() == "TreeNode*":
                    self.__treenode_variables.append("exp");
                    self.__treenode_variables.append("act");
                break

    def __parse_input(self, input: str):
        inputs: list[str] = []
        matches = regex.findall("(?P<name>\w+) *= *(?P<value>[.\d+-]+|\"[\w\W]*?\"|\'[\w\W]*?\'|\[(?:[^\[\]]|(?&value))*\])",
                                input)
        for i in range(0, len(matches)):
            if i < len(self.args()):
                # in order based on function arguments
                arg_name, argument = self.args()[i]
                value = matches[i][1]
                if argument == None:  # ???
                    continue
                inputs.append(argument.get_statement(arg_name, value))
            else:
                inputs.append("//{} = {}".format(matches[i][0], matches[i][1]))
        return inputs

    def __parse_output(self, output: str):
        outputs: list[str] = []
        if self.type() == "void":
            # assume adjust the first argument
            _, argument = self.args()[0]
            outputs.append(argument.get_statement("exp", output))
            outputs.append("{}->{};".format(self.solution_object(), self.function()))
        else:
            outputs.append(self._type.get_statement("exp", output))
        return outputs

    def __expect_equation(self):
        exp: list[str] = []
        eq_type = self.type()

        if eq_type == "void":
            name, type = self.args()[0]
            exp.append("// Assume the first argument is answer.")
            exp.append(type.expect_compare(name, "exp"))
        elif self._anyorder and re.search("vector", eq_type):
            eq_arg = "{}->{}".format(self._solnobj, self.function())
            exp.append("// Try EXPECT_EQ_ANY_ORDER_RECURSIVE")
            exp.append("// if the element is also matched in any order.")
            exp.append("EXPECT_EQ_ANY_ORDER({}, exp);".format(eq_arg))
        else:
            eq_arg = "{}->{}".format(self.solution_object(), self.function())
            exp.append("{} act = {};".format(eq_type, eq_arg))
            exp.append(self._type.expect_compare("act", "exp"))
        return exp

    def __generate_object(self):
        return ["{} = new {}();".format(self.solution_object(),
                                        self.class_name())]
    
    def __delete(self):
        _del: list[str] = []
        if len(self.__listnode_variables) > 0:
            _del.append("ListNode::release({});".format(", ".join(self.__listnode_variables)))
        if len(self.__treenode_variables) > 0:
            _del.append("TreeNode::release({});".format(", ".join(self.__treenode_variables)))
        _del.append("delete {};".format(self.solution_object()))
        return _del

    def unittest_desc(self, content: str):
        res: list[list[str]] = []
        cases = re.findall("(?P<case>Input[\w\W]+?)([^\n]+Example|$)", content)
        print(self._type)

        if self._type.is_valid():
            for case, _ in cases:
                m_cas = \
                    re.search("Input[\w\W]+? (?P<in>[\w\W]+)[^\w]+Output[^\[\"\'\w]* +(?P<out>[\d.+-]+|\[[\w\W]*\]|\"[^\n]*?\"|\'[^\n]*?\'|True|False|true|false)",
                              case)
                if m_cas:
                    res.append(self.__generate_object() +
                               self.__parse_input(m_cas.group("in").strip()) +
                               self.__parse_output(m_cas.group("out").strip()) +
                               self.__expect_equation() +
                               self.__delete())
        return res


class SolutionClass(SolutionAbstract):
    def __init__(self, id: int, class_name: str, code_snippet: list[str], content: str = ""):
        SolutionAbstract.__init__(self, id, content)
        self.__methods: dict[str, SolutionAbstract] = {}
        self.__name = class_name
        self.__valid = True
        self._solnobj = "_".join(
            [e.lower() for e in list(filter(lambda e: e != "",
                                            re.split("([A-Z][a-z]+)", self.__name)))])
        self.__parse_codesnippets(code_snippet)

    def is_valid(self):
        return self.__valid

    def class_name(self):
        return self.__name

    def __parse_codesnippets(self, code_snippet: list[str]):
        for line in code_snippet:
            if re.search(" *(?P<func>{} *\([\w\W]*\))".format(self.class_name()), line):
                func = SolutionFunction(self._id, ["void " + line])
                self.__methods[func.name()] = func
                self.__valid &= func.is_valid()
            elif re.match(" *\w+ +\w+ *\([\w\W]*\) *{", line):
                func = SolutionFunction(self._id, [line])
                self.__methods[func.name()] = func
                self.__valid &= func.is_valid()

    def __expect_equation(self, input: str, answer: list[str]):
        out: list[str] = []
        split = regex.findall("\[((?:[^\[\]]|(?R))*)\]", input)
        functions = re.findall("(\w+)", split[0])
        args_statement = regex.findall("\[((?:[^\[\]]|(?R))*)\]", split[1])
        if len(functions) != len(answer) or \
                len(functions) != len(args_statement):
            return out
        for i in range(0, len(functions)):
            if functions[i] not in self.__methods:
                continue
            method = self.__methods[functions[i]]
            arg_input = regex.findall("(\"[\w\W]*?\"|\'[\w\W]*?\'|[.\d+-]+|\[(?:[^\[\]]|(?R))*\])",
                                      args_statement[i])
            if len(method.args()) != len(arg_input):
                continue

            args = []

            if functions[i] == self.class_name():
                for j in range(0, len(arg_input)):
                    f, t = method.args()[j]
                    out.append("{} {} = {};".format(t.type(), f,
                                                    t.parse_value(arg_input[j])))
                    args.append(f)
                out.append("{} = new {}({});".format(self.solution_object(),
                                                     self.class_name(),
                                                     ", ".join(args)))
            else:
                for j in range(0, len(arg_input)):
                    _, t = method.args()[j]
                    args.append(t.parse_value(arg_input[j]))
                actual = "{}->{}({})".format(self.solution_object(),
                                             method.name(),
                                             ", ".join(args))
                if method.type() == "void":
                    out.append("{};".format(actual))
                else:
                    out.append(method._type.expect_compare(actual,
                                                           method._type.parse_value(answer[i])))
        out.append("delete {};".format(self.solution_object()))
        return out

    def __parse_output(self, output: str):
        outputs: list[str] = []
        match = re.search("\[(?P<out>.*?)\]", output)
        if not match:
            return outputs
        outputs = re.findall("(null|\"[\w\W]*?\"|\'[\w\W]*?\'|[.\d+-]+|\[[\w\W]*\]|true|false|True|False)",
                             match.group("out"))
        return outputs

    def unittest_desc(self, content: str):
        res: list[list[str]] = []
        cases = re.findall("(?P<case>Input[\w\W]+?)([^\n]+Example|$)", content)
        for case, _ in cases:
            m_cas = \
                re.search("Input[\w\W]+? (?P<in>[\w\W]+)[^\w]+Output[^\[\"\'\w]*(?P<out>\[[\w\W]*\])",
                          case)
            if m_cas:
                ans = self.__parse_output(m_cas.group("out").strip())
                res.append(self.__expect_equation(m_cas.group("in").strip(),
                                                  ans))
        return res


class Solution:
    @staticmethod
    def generate_template(id: int, code_snippet: str, content: str):
        multi_lines = code_snippet.splitlines()

        for i in range(len(multi_lines)-1, -1, -1):
            match = re.search("class (?P<class_name>\w+) *{", multi_lines[i])
            if match and match.group("class_name") == "Solution":
                return SolutionFunction(id, multi_lines[i:], content)
            elif match:
                return SolutionClass(id, match.group("class_name"),
                                     multi_lines[i:], content)
        return SolutionFunction(id, "", "")


class LeetCodeQuestion:

    def __init__(self, title_slug: str, testcase: bool, _snippet: str = None):
        self.__res_obj = LeetCodeRequest.question_details(title_slug)
        if self.__res_obj != None:
            self.__id: int = int(self.__res_obj['questionFrontendId'])
            self.__title: str = self.__res_obj['questionTitle']
            self.__slug: str = self.__res_obj['titleSlug']
            self.__level: str = self.__res_obj['difficulty']
            self.__snippet: str = ""
            self.__solntmp: SolutionAbstract = SolutionAbstract(-1, "")
            self.__desc: list[str] = None
            self.__cons: list[str] = None
            self.__testcase: list[list[str]] = []
            self.__parse_code_snippet(self.__res_obj['codeSnippets'],
                                      self.__res_obj['content'],
                                      _snippet)
            self.__parse_content(self.__res_obj['content'], testcase)

    def is_valid(self):
        return self.__res_obj != None

    def __parse_code_snippet(self, code_snippets: list[object], content: str, _snippet: str):
        if code_snippets != None:
            for snippet in code_snippets:
                if snippet['langSlug'] == "cpp":
                    self.__snippet = CodeSnippet.prettify(snippet['code'])
                    self.__solntmp = Solution.generate_template(self.id(),
                                                                self.__snippet,
                                                                content)
                    # indent
                    self.__snippet = "  " + "\n  ".join(self.__snippet.splitlines())
                    break

        if _snippet != None:
            self.__snippet = CodeSnippet.prettify(_snippet)
            # indent
            self.__snippet = "  " + "\n  ".join(self.__snippet.splitlines())

    def __parse_content(self, content: str, testcase: bool):
        if content != None:
            content = Description.prettify(content)
            match = \
                re.search("(?P<desc>[\w\W]+?)\n[^\n]+(?P<exam>Example[\w\W]+?)\n([^\n]+Constraints[^\n]+\s+(?P<cons>[\w\W]+)|$)",
                          content)
            if match:
                self.__desc = match.group("desc")
                self.__cons = match.group("cons").splitlines()
                if testcase and self.__solntmp.is_valid():
                    self.__testcase = \
                        self.__solntmp.unittest_desc(match.group("exam"))
                else:
                    self.__testcase = None

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

    def constraints(self):
        return self.__cons

    def includes(self):
        return self.__solntmp.includes()

    def __source(self, desc: str):
        _includes = list(self.includes())
        _includes.append("gtest/gtest.h")
        if self.__solntmp.isanyorder():
            _includes.append("leetcode/anyorder.hpp")
        return "\n".join([
            "#include <{}>".format(icd) for icd in sorted(_includes)] + [
            "",
            "using namespace std;",
            "",
            desc,
            "",
            "struct q{} : public ::testing::Test {{".format(self.id()),
            "  // Leetcode answer here",
            self.code_snippet(),
            "",
            "  class {} *{};".format(self.__solntmp.class_name(), self.__solntmp.solution_object()),
            "};",
            self.__unittest_cases()])

    def __unittest_cases(self):
        if self.__testcase == None:
            return "\n".join([
                "",
                "TEST_F(q{}, NOT_IMPLEMENT) {{".format(self.id()),
                "   EXPECT_TRUE(\"NOT IMPLEMENT\");",
                "}"
            ])
        res: list[str] = []
        for i in range(0, len(self.__testcase)):
            res.append("\n".join([
                "",
                "TEST_F(q{}, sample_input{}) {{".format(self.id(), str(i+1).zfill(2))] + [
                "  {}".format(line) for line in self.__testcase[i]] + [
                "}"]))
        return "\n".join(res)

    def __constraints(self):
        cons = self.constraints()
        res: list[str] = []
        for line in cons:
            match = re.search("- +(?P<list>[^\n]+)", line)
            if match:
                res.append(match.group("list").strip())
        return res

    def template(self, prompt: str, limit: int = 0):
        separate_line = "–" * int((limit - 12) / 2)
        desc_lines = Description.bound(self.__desc,
                                       limit if limit > 30 else None)
        desc = "\n".join([
            "/**",
            " * {}".format(prompt),
            " *",
            " * {}.".format(self.id()),
            " *  {} {}".format(" " * len(str(self.id())), self.title()),
            " *",
            " * "])
        if desc_lines == None:
            desc += "\n".join([
                "To unlock the question need a premium account.",
                " *",
                " */"])
        else:
            desc += "\n".join([
                separate_line + " Description " + separate_line,
                " *",
                " *   " +
                "\n *   ".join(desc_lines),
                " *",
                " * "])
            cons_lines = self.__constraints()
            if len(cons_lines) > 0:
                desc += "\n".join([
                    separate_line + " Constraints " + separate_line,
                    " *",
                    " *   • " +
                    "\n *   • ".join(cons_lines),
                    " *", ])
            desc += "\n".join([
                "",
                " */"])

        return self.__source(desc)
