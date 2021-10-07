import re
import regex


class Argument:
    def __init__(self, typename: str):
        self._content: Argument = None
        self._type: str = typename if typename != None else "void"
        self._includes: list[str] = ["iostream"]

    def get_statement(self, name: str, value: str):
        return "{} {} = {};".format(self._type, name,
                                    self.parse_value(value))

    def parse_value(self, value: str):
        return value

    def type(self):
        return self._type

    def is_valid(self):
        return False

    def get_includes(self):
        return self._includes

    def expect_compare(self, first_arg: str, second_arg: str):
        return "EXPECT_EQ({}, {});".format(first_arg, second_arg)

    @staticmethod
    def generate(typename: str):
        vector_match = re.search(" *(?P<type>vector<(?P<content>[\w<>*]+)>)",
                                 typename)
        if vector_match != None:
            return VectorArgument(vector_match.group("type"),
                                  vector_match.group("content"))
        list_match = re.search(" *(?P<type>ListNode *\*)", typename)
        if list_match != None:
            return ListNodeArgument(list_match.group("type"))
        tree_match = re.search(" *(?P<type>TreeNode *\*)", typename)
        if tree_match != None:
            return TreeNodeArgument(tree_match.group("type"))
        void_match = re.search(" *(?P<type>void)", typename)
        if void_match != None:
            return VoidArgument(void_match.group("type"))
        integer_match = re.search(" *(?P<type>int|long)", typename)
        if integer_match != None:
            return IntegerArgument(integer_match.group("type"))
        float_match = re.search(" *(?P<type>double|float)", typename)
        if float_match != None:
            return FloatArgument(float_match.group("type"))
        bool_match = re.search(" *(?P<type>bool)", typename)
        if bool_match != None:
            return BooleanArgument(bool_match.group("type"))
        char_match = re.search(" *(?P<type>char)", typename)
        if char_match != None:
            return CharArgument(char_match.group("type"))
        string_match = re.search(" *(?P<type>string)", typename)
        if string_match != None:
            return StringArgument(string_match.group("type"))
        return Argument(None)


class CustomArgument(Argument):
    def __init__(self, typename: str):
        Argument.__init__(self, typename)

    def is_valid(self):
        return True


class VoidArgument(Argument):
    def __init__(self, typename: str):
        Argument.__init__(self, typename)

    def is_valid(self):
        return True


class IntegerArgument(Argument):
    def __init__(self, typename: str):
        Argument.__init__(self, typename)

    def parse_value(self, string: str):
        match = re.search("(?P<val>[\d+-]+)", string)
        if match != None:
            return str(match.group("val"))
        return "0"

    def is_valid(self):
        return True


class FloatArgument(Argument):
    def __init__(self, typename: str):
        Argument.__init__(self, typename)

    def parse_value(self, string: str):
        match = re.search("(?P<val>[\d.+-]+)", string)
        if match != None:
            return str(match.group("val"))
        return "0.0"

    def is_valid(self):
        return True


class BooleanArgument(Argument):
    def __init__(self, typename: str):
        Argument.__init__(self, typename)

    def parse_value(self, string: str):
        match = re.search("(?P<val>true|false|True|False)", string)
        if match != None:
            return str(match.group("val"))
        return "False"

    def is_valid(self):
        return True


class CharArgument(Argument):
    def __init__(self, typename: str):
        Argument.__init__(self, typename)

    def parse_value(self, string: str):
        match = re.search("(?P<val>\'[\w\W]*\'|\"[\w\W]*\")", string)
        if match != None:
            return str(re.sub("\"", "\'", match.group("val")))
        return "\'\'"

    def is_valid(self):
        return True


class StringArgument(Argument):
    def __init__(self, typename: str):
        Argument.__init__(self, typename)
        self._includes.append("string")

    def parse_value(self, string: str):
        match = re.search("(?P<val>\'[\w\W]*\'|\"[\w\W]*\")", string)
        if match != None:
            return str(match.group("val"))
        return "\"\""

    def is_valid(self):
        return True


class VectorArgument(Argument):
    def __init__(self, typename: str, content: str):
        Argument.__init__(self, typename)
        self._content = Argument.generate(content)
        self._includes.append("vector")

    def parse_value(self, string: str):
        match = re.search("\[(?P<val>[\w\W]*)\]", string)
        if match != None:
            element = regex.findall("(\"[\w\W]*?\"|[\d.+-]+|\[(?:[^\[\]]|(?R))*\])",
                                 match.group("val"))
            return "{{{}}}".format(
                ", ".join([self._content.parse_value(e) for e in element]))
        return "{}"

    def is_valid(self):
        return self._content.is_valid()


class ListNodeArgument(Argument):
    def __init__(self, typename: str):
        Argument.__init__(self, typename)
        self._includes.append("leetcode/listnode.hpp")

    def parse_value(self, string: str):
        match = re.search("\[(?P<val>[\w\W]*)\]", string)
        if match != None:
            element = re.findall("([\d.+-]+)", match.group("val"))
            return "ListNode::generate({{{}}})".format(", ".join(element))
        return "ListNode::generate({})"

    def is_valid(self):
        return True

    def expect_compare(self, first_arg: str, second_arg: str):
        return "EXPECT_LISTNODE_EQ({}, {});".format(first_arg, second_arg)


class TreeNodeArgument(Argument):
    def __init__(self, typename: str):
        Argument.__init__(self, typename)
        self._includes.append("leetcode/treenode.hpp")

    def parse_value(self, string: str):
        match = re.search("\[(?P<val>[\w\W]*)\]", string)
        if match != None:
            element = re.findall("([\d.+-]+|null)", match.group("val"))
            return "TreeNode::generate({{{}}})".format(", ".join([
                re.sub("null", "NULL_TREENODE", e) for e in element
            ]))
        return "TreeNode::generate({})"

    def is_valid(self):
        return True

    def expect_compare(self, first_arg: str, second_arg: str):
        return "EXPECT_TREENODE_EQ({}, {});".format(first_arg, second_arg)
