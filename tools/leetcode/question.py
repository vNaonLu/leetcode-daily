import re
import regex
from . import request as LeetCodeRequest
from .argument import Argument, CustomArgument


class SolutionAbstract:
    def __init__(self, content: str):
        self._type: Argument = None
        self._name: str = ""
        self._args: dict[str, Argument] = {}
        self._includes: set[str] = set()
        self._anyorder: bool = re.search("any order",
                                         content,
                                         re.IGNORECASE) != None
        self._includes.add("iostream")

    def class_name(self):
        return "Solution"

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
    def __init__(self, code_snippet: list[str], content: str = ""):
        SolutionAbstract.__init__(self, content)
        self.__parse_codesnippets(code_snippet)

    def __parse_codesnippets(self, code_snippet: list[str]):
        for line in code_snippet:
            match = \
                re.search("(?P<return_type>\w+|\w+<[\w\W]+>|\w+? *\*) *(?P<function_name>\w+)\((?P<args>.*)\) {",
                          line)
            if match:
                self._name = match.group("function_name")
                self._type = Argument.generate(match.group("return_type"))
                self._add_include(self._type)
                for arg in match.group("args").split(","):
                    m_arg = \
                        re.search("(?P<type>[\w<> ]+[&*]{0,1}) +(?P<name>[\w]+)",
                                  arg)
                    if m_arg:
                        arg = Argument.generate(m_arg.group("type"))
                        self._args[m_arg.group("name")] = arg
                        self._add_include(arg)
                break

    def __parse_input(self, input: str):
        inputs: list[str] = []
        matches = regex.findall("(?P<name>\w+) *= *(?P<value>[.\d+-]+|\"[\w\W]*?\"|\[(?:[^\[\]]|(?&value))*\])",
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
            outputs.append("solver.{};".format(self.function()))
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
            eq_arg = "solver." + self.function()
            exp.append("// Try EXPECT_EQ_ANY_ORDER_RECURSIVE")
            exp.append("// if the element is also matched in any order.")
            exp.append("EXPECT_EQ_ANY_ORDER({}, exp);".format(eq_arg))
        else:
            eq_arg = "solver." + self.function()
            exp.append(self._type.expect_compare(eq_arg, "exp"))
        return exp

    def unittest_desc(self, content: str):
        res: list[list[str]] = []
        cases = re.findall("(?P<case>Input[\w\W]+?)([^\n]+Example|$)", content)

        if self._type.is_valid():
            for case, _ in cases:
                m_cas = \
                    re.search("Input[\w\W]+? (?P<in>[\w\W]+)[^\w]+Output[^\[\"\'\w]*(?P<out>[\d+-]+|\[[\w\W]*\]|\"[^\n]+?\"|True|False|true|false)",
                              case)
                if m_cas:
                    inp = self.__parse_input(m_cas.group("in").strip())
                    out = self.__parse_output(m_cas.group("out").strip())
                    eq = self.__expect_equation()
                    res.append(inp + out + eq)
        return res


class SolutionClass(SolutionAbstract):
    def __init__(self, class_name: str, code_snippet: list[str], content: str = ""):
        SolutionAbstract.__init__(self, content)
        self.__methods: dict[str, SolutionAbstract] = {}
        self.__name = class_name
        self.__parse_codesnippets(code_snippet)

    def class_name(self):
        return self.__name

    def __parse_codesnippets(self, code_snippet: list[str]):
        for line in code_snippet:
            if re.match(" *\w+ +\w+ *\([\w\W]*\) *{", line):
                func = SolutionFunction([line])
                self.__methods[func.name()] = func

    def __expect_equation(self, input: str, answer: list[str]):
        out: list[str] = []
        split = re.findall("\[([^\[\]]*|\[.*\])\]", input)
        functions = re.findall("\"(\w+)\"", split[0])
        args_statement = re.findall("\[(.*?)\]", split[1])

        if len(functions) != len(answer) or \
                len(functions) != len(args_statement):
            return out
        for i in range(0, len(functions)):
            if functions[i] not in self.__methods:
                continue
            method = self.__methods[functions[i]]
            arg_input = re.findall("(\"[\w\W]*\"|[.\d+-]+|\[[\w\W]*\])",
                                   args_statement[i])
            if len(method.args()) != len(arg_input):
                continue

            args = []
            for j in range(0, len(arg_input)):
                _, t = method.args()[j]
                args.append(t.parse_value(arg_input[j]))
            actual = "solver.{}({})".format(method.name(),
                                            ", ".join(args))
            if method.type() == "void":
                out.append("{};".format(actual))
            else:
                out.append(method._type.expect_compare(actual,
                                                       method._type.parse_value(answer[i])))
        return out

    def __parse_output(self, output: str):
        outputs: list[str] = []
        match = re.search("\[(?P<out>.*?)\]", output)
        if not match:
            return outputs

        outputs = re.findall("(null|\"[\w\W]*\"|[.\d+-]+|\[[\w\W]*\])",
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
    def generate_template(code_snippet: str, content: str):
        multi_lines = code_snippet.splitlines()

        for i in range(0, len(multi_lines)):
            match = re.search("class (?P<class_name>\w+) *{", multi_lines[i])
            if match and match.group("class_name") == "Solution":
                return SolutionFunction(multi_lines[i:], content)
            elif match:
                return SolutionClass(match.group("class_name"),
                                     multi_lines[i:], content)


class LeetCodeQuestion:

    def __sup(match: re.Match):
        content = "^({})".format(match.group("content"))
        replmap: dict[str, str] = {
            "0": "⁰", "1": "¹", "2": "²", "3": "³", "4": "⁴", "5": "⁵",
            "6": "⁶", "7": "⁷", "8": "⁸", "9": "⁹", "+": "⁺", "-": "⁻",
            "=": "⁼", "(": "⁽", ")": "⁾",
            "a": "ᵃ", "b": "ᵇ", "c": "ᶜ", "d": "ᵈ", "e": "ᵉ",
            "f": "ᶠ", "g": "ᵍ", "h": "ʰ", "i": "ⁱ", "j": "ʲ", "l": "ˡ",
            "k": "ᵏ", "m": "ᵐ", "n": "ⁿ", "o": "ᵒ", "p": "ᵖ", "r": "ʳ",
            "s": "ˢ", "t": "ᵗ", "u": "ᵘ", "v": "ᵛ", "w": "ʷ", "x": "ˣ",
            "y": "ʸ", "z": "ᶻ",
        }
        relp: str = ""
        for c in match.group("content"):
            if c in replmap:
                relp += replmap[c]
            else:
                relp = None
                break
        if relp != None:
            content = relp
        return content

    def __sub(match: re.Match):
        content = "⎽({})".format(match.group("content"))
        replmap: dict[str, str] = {
            "0": "₀", "1": "₁", "2": "₂", "3": "₃", "4": "₄", "5": "₅",
            "6": "₆", "7": "₇", "8": "₈", "9": "₉", "+": "₊", "-": "₋",
            "=": "₌", "(": "₍", ")": "₎",
            "a": "ₐ", "d": "ᵈ", "e": "ₑ", "f": "ᶠ", "h": "ₕ",
            "i": "ᵢ", "j": "ⱼ", "k": "ₖ", "l": "ₗ", "m": "ₘ", "n": "ₙ",
            "o": "ₒ", "p": "ₚ", "r": "ᵣ", "s": "ₛ", "t": "ₜ", "u": "ᵤ",
            "v": "ᵥ", "x": "ₓ"
        }
        relp: str = ""
        for c in match.group("content"):
            if c in replmap:
                relp += replmap[c]
            else:
                relp = None
                break
        if relp != None:
            content = relp
        return content

    def __math(match: re.Match):
        repl = [
            ("[*]", "&times;"),
            ("==", "="),
            ("!=", "≠")
        ]
        content = match.group("content")
        for p, r in repl:
            content = re.sub(p, r, content)
        return " ‘{}’ ".format(content)

    def __illist(match: re.Match):
        li = re.search(" *<li>(?P<content>[\w\W]*?)<\/li> *",
                       )

    __repl = [
        ("&quot;(?P<content>[\w\W]*?)&quot;",                       # " "
         lambda match: "\"{}\"".format(match.group("content"))),
        ("&#39;(?P<content>[\w\W]*?)&#39;",                         # ' '
         lambda match: "'{}'".format(match.group("content"))),
        (" *<li>(?P<content>[\w\W]*?)<\/li> *",                     # -
         lambda match: "- {}".format(match.group("content"))),

        (" *<b>(?P<content>[\w\W]*?)<\/b> *",                       # “ ”
         lambda match: " “{}” ".format(match.group("content"))),
        (" *<strong>(?P<content>[\w\W]*?)<\/strong> *",             # “ ”
         lambda match: " “{}” ".format(match.group("content"))),
        (" *<em>(?P<content>[\w\W]*?)<\/em> *",                     # “ ”
         lambda match: " “{}” ".format(match.group("content"))),

        ("<img(?P<content>[\w\W]*?)\/>", ""),
        ("</?div.*?>", ""),
        ("\n\n", "\n"),

        (" *<code>(?P<content>[\w\W]+?)<\/code> *", __math),        # code
        ("<sup>(?P<content>[\w\W]+?)<\/sup>", __sup),               # sup
        ("<sub>(?P<content>[\w\W]+?)<\/sub>", __sub),               # sub
        ("&nbsp;", ""),                                             # space
        ("&lt;(?!=)", "<"),                                         # <
        ("&gt;(?!=)", ">"),                                         # >
        ("&lt;=", "≤"),                                             # ≤
        ("&gt;=", "≥"),                                             # ≥
        ("&le;", "≤"),                                              # ≤
        ("&ge;", "≥"),                                              # ≥
        ("&times;", "×"),                                           # ×
        ("&ldquo;", "“"),                                           # “
        ("&rdquo;", "”"),                                           # ”

        (" *<p>(?P<content>[\w\W]*?)<\/p>",
         lambda match: match.group("content")),
        (" *<ul>(?P<content>[\w\W]*?)<\/ul>",
         lambda match: match.group("content")),
        (" *<ol>(?P<content>[\w\W]*?)<\/ol>",
         lambda match: match.group("content")),
        (" *<pre>(?P<content>[\w\W]*?)<\/pre>",
         lambda match: match.group("content"))
    ]

    def __init__(self, title_slug: str):
        res_obj = LeetCodeRequest.question_details(title_slug)
        self.__id: int = int(res_obj['questionFrontendId'])
        self.__title: str = res_obj['questionTitle']
        self.__slug: str = res_obj['titleSlug']
        self.__level: str = res_obj['difficulty']
        self.__snippet: str = ""
        self.__slttmp: SolutionAbstract = SolutionAbstract("")
        self.__desc: list[str] = None
        self.__cons: list[str] = None
        self.__testcase: list[list[str]] = []
        self.__parse_code_snippet(res_obj['codeSnippets'], res_obj['content'])
        self.__parse_content(res_obj['content'])

    def __parse_code_snippet(self, code_snippets: list[object], content: str):
        if code_snippets != None:
            for snippet in code_snippets:
                if snippet['langSlug'] == "cpp":
                    self.__snippet = re.sub("  ", " ", snippet['code'])
                    self.__snippet = re.sub(
                        " *public:", " public:", self.__snippet)
                    self.__snippet = re.sub(
                        " *private:", " private:", self.__snippet)
                    self.__snippet = re.sub(
                        " *protected:", " protected:", self.__snippet)
                    # to google style
                    self.__slttmp = Solution.generate_template(self.__snippet,
                                                               content)
                    break

    def __parse_content(self, content: str):
        if content != None:
            for patt, repl in self.__repl:
                content = re.sub(patt, repl, content)
            match = \
                re.search("(?P<desc>[\w\W]+?)\n[^\n]+(?P<exam>Example[\w\W]+?)\n([^\n]+Constraints[^\n]+\s+(?P<cons>[\w\W]+)|$)",
                          content)
            if match:
                self.__desc = match.group("desc").splitlines()
                self.__cons = match.group("cons").splitlines()
                self.__testcase = \
                    self.__slttmp.unittest_desc(match.group("exam"))

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
            return self.__desc
        else:
            desc: list[str] = []
            for seg in self.__desc:
                if len(seg) == 0:
                    continue
                seg_lim: list[str] = []
                for d in re.findall("([^\n]{{0,{}}})[ .]".format(limit), seg):
                    seg_lim.append(d.strip())
                seg_lim[-1] += "."
                desc += seg_lim
                desc.append("")
            del desc[-1]
            return desc

    def constraints(self):
        return self.__cons

    def includes(self):
        return self.__slttmp.includes()

    def __source(self, desc: str):
        return "\n".join([
            "",
            "#ifndef LEETCODE_Q{}_H__".format(self.id()),
            "#define LEETCODE_Q{}_H__".format(self.id())] + [
            "#include <{}>".format(icd) for icd in sorted(self.includes())] + [
            "",
            "namespace l{} {{".format(self.id()),
            "using namespace std;",
            "",
            desc,
            "",
            self.code_snippet(),
            "}}  // namespace l{}".format(self.id()),
            "",
            "#endif"])

    def __unittest_cases(self):
        if self.__testcase == None:
            return "\n".join([
                "",
                "TEST(q{}, NOT_IMPLEMENT) {{".format(self.id()),
                "   EXPECT_TRUE(\"NOT IMPLEMENT\");",
                "}"
            ])
        res: list[str] = []
        for i in range(0, len(self.__testcase)):
            res.append("\n".join([
                "",
                "TEST(q{}, sample_input{}) {{".format(self.id(),
                                                      str(i+1).zfill(2)),
                "  l{}::{} solver;".format(self.id(), self.__slttmp.class_name())] + [
                "  {}".format(line) for line in self.__testcase[i]] + [
                "}"]))
        return "\n".join(res)

    def __unittest(self, desc: str):
        addition_include: list[str] = [""]
        if self.__slttmp.isanyorder():
            addition_include.append("#include <leetcode/anyorder.hpp>")
            addition_include.append("")
        return "\n".join([
            "",
            "#ifndef Q{}_UNITTEST_H__".format(self.id()),
            "#define Q{}_UNITTEST_H__".format(self.id()),
            "#include <gtest/gtest.h>",
            "\n".join(addition_include),
            "#include \"q{}.hpp\"".format(str(self.id()).zfill(4)),
            "using namespace std;",
            "",
            desc,
            self.__unittest_cases(),
            "",
            "#endif"])

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
        desc_lines = self.description(limit if limit > 30 else None)
        desc = "\n".join([
            "/**",
            "  * {}".format(prompt),
            "  *",
            "  * {}.".format(self.id()),
            "  *  {} {}".format(" " * len(str(self.id())), self.title()),
            "  *",
            "  * "])
        if desc_lines == None:
            desc += "\n".join([
                "To unlock the question need a premium account.",
                "  *",
                "*/"])
        else:
            desc += "\n".join([
                separate_line + " Description " + separate_line,
                "  *",
                "  *   " +
                "\n  *   ".join(desc_lines),
                "  *",
                "  * "])
            cons_lines = self.__constraints()
            if len(cons_lines) > 0:
                desc += "\n".join([
                    separate_line + " Constraints " + separate_line,
                    "  *",
                    "  *   • " +
                    "\n  *   • ".join(cons_lines),
                    "  *", ])
            desc += "\n".join([
                "",
                "*/"])

        return self.__source(desc), self.__unittest(desc)
