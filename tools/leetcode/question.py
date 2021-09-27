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
            if m_val != None:

                elm = \
                    re.findall("(\[[\w\"\',]*\]|\"[^\n]+?\"|[\d.+-]+)",
                               m_val)
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
    _type_pattern: list[str, str] = [("ListNode", "leetcode/listnode.hpp"), ("TreeNode", "leetcode/treenode.hpp"),
                                     ("vector", "vector"), ("map", "map"),
                                     ("unordered_map", "unordered_map"), ("string", "string")]

    def __init__(self, content: str):
        self._type: str = None
        self._name: str = ""
        self._args: dict[str, str] = {}
        self._includes: set[str] = set()
        self._anyorder: bool = re.search("any order",
                                         content,
                                         re.IGNORECASE) != None
        self._includes.add("iostream")

    def name(self):
        return self._name

    def type(self):
        return self._type

    def isanyorder(self):
        return self._anyorder

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
        primitive_pattern = "void|int|char|double|float|bool"
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
    def __init__(self, code_snippet: list[str], content: str):
        SolutionAbstract.__init__(self, content)
        self.__parse_codesnippets(code_snippet)

    def __parse_codesnippets(self, code_snippet: list[str]):
        for line in code_snippet:
            match = \
                re.search("(?P<return_type>[\w<>*]+) +(?P<function_name>\w*)\((?P<args>.*)\) {",
                          line)
            if match:
                self._name = match.group("function_name")
                self._type = match.group("return_type")
                self._parse_type(self._type)
                args = match.group("args").split(",")
                for arg in args:
                    m_arg = \
                        re.search("(?P<type>[\w<>*]+)&{0,1} +(?P<name>[\w]+)",
                                  arg)
                    self._parse_type(m_arg.group("type"))
                    self._args[m_arg.group("name")] = m_arg.group("type")

    def __parse_input(self, input: str):
        inputs: list[str] = []
        matches = re.findall("(?P<name>\w+) = (?P<value>[\d+-]+|\[[^=]+\]|\"[^\n]+?\")",
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
            if self._anyorder and re.search("vector", self.type()):
                expect.append("// Try EXPECT_EQ_ANY_ORDER_RECURSIVE")
                expect.append(
                    "// if the element is also matched in any order.")
                expect.append("EXPECT_EQ_ANY_ORDER({}, exp);".format(eq_arg1))
            else:
                expect.append("EXPECT_EQ({}, exp);".format(eq_arg1))

        return expect

    def unittest_desc(self, content: list[str]):
        res: list[list[str]] = []
        cases = re.findall("(?P<case>Input[\w\W]+?)([^\n]+Example|$)", content)

        if self._is_known_type(self.type()):
            for case, _ in cases:
                m_cas = \
                    re.search("Input[\w\W]+? (?P<in>[\w\W]+)[^\w]+Output.* *(?P<out>[\d+-]+|\[[^=]+\]|\"[^\n]+?\")",
                              case)
                if m_cas:
                    inp = self.__parse_input(m_cas.group("in").strip())
                    out = self.__parse_output(m_cas.group("out").strip())
                    eq = self.__expect_equation()
                    res.append(inp + out + eq)
        return res


class SolutionStructure(SolutionAbstract):
    def __init__(self, code_snippet: list[str], content: str):
        SolutionAbstract.__init__(self, content)
        self.__parse_codesnippets(code_snippet)

    def __parse_codesnippets(self, code_snippet: list[str]):
        # does not implement structure
        pass


class Solution:
    @staticmethod
    def generate_template(code_snippet: str, content: str):
        multi_lines = code_snippet.splitlines()
        for i in range(0, len(multi_lines)):
            if re.match("class Solution {1,}{",
                        multi_lines[i]):
                return SolutionFunction(multi_lines[i:], content)
        return SolutionStructure(multi_lines, content)


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
            "a": "ₐ", "d": "ᵈ", "e": "ₑ", "f": "ᶠ", "g": "ᵍ", "h": "ₕ",
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

    def function(self):
        return self.__slttmp.function()

    def return_type(self):
        return self.__slttmp.type()

    def return_args(self):
        return self.__slttmp.args()

    def unittest_case(self):
        return self.__testcase

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
                "   EXPECT_TRUE(\"NOT IMPLEMENT\")",
                "}"
            ])
        res: list[str] = []
        for i in range(0, len(self.__testcase)):
            res.append("\n".join([
                "",
                "TEST(q{}, sample_input{}) {{".format(self.id(),
                                                      str(i+1).zfill(2)),
                "  l{}::Solution solver;".format(self.id())] + [
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
