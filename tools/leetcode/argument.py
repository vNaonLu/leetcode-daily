import re


class Argument:
    def __init__(self, typename: str):
        self._content: Argument = None
        self._type: str = typename if typename != None else "void"
        self._includes: list[str] = ["iostream"]

    def get_statement(self, name: str, value: str):
        return "{} {} = {};".format(self._type, name,
                                    self._parse_value(value))

    def _parse_value(self, value: str):
        return value

    def type(self):
        return self._type

    def is_valid(self):
        return False

    def get_includes(self):
        return self._includes

    @staticmethod
    def generate(typename: str):
        vector_match = re.search(" *(?P<type>vector<(?P<content>[\w*]+)>)",
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


class IntegerArgument(Argument):
    def __init__(self, typename: str):
        Argument.__init__(self, typename)

    def _parse_value(self, string: str):
        match = re.search("(?P<val>[\d+-]+)", string)
        if match != None:
            return str(match.group("val"))
        return "0"

    def is_valid(self):
        return True


class FloatArgument(Argument):
    def __init__(self, typename: str):
        Argument.__init__(self, typename)

    def _parse_value(self, string: str):
        match = re.search("(?P<val>[\d.+-]+)", string)
        if match != None:
            return str(match.group("val"))
        return "0.0"

    def is_valid(self):
        return True

class BooleanArgument(Argument):
    def __init__(self, typename: str):
        Argument.__init__(self, typename)

    def _parse_value(self, string: str):
        match = re.search("(?P<val>true|false|True|False)", string)
        if match != None:
            return str(match.group("val"))
        return "False"

    def is_valid(self):
        return True

class CharArgument(Argument):
    def __init__(self, typename: str):
        Argument.__init__(self, typename)

    def _parse_value(self, string: str):
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

    def _parse_value(self, string: str):
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

    def _parse_value(self, string: str):
        match = re.search("\[(?P<val>[\w\W]*)\]", string)
        if match != None:
            element = re.findall("(\[[\w\"\',]*\]|\"[^\n]+?\"|[\d.+-]+)",
                                 match.group("val"))
            return "{{{}}}".format(
                ", ".join([self._content._parse_value(e) for e in element]))
        return "{}"

    def is_valid(self):
        return self._content.is_valid()

class ListNodeArgument(Argument):
    def __init__(self, typename: str):
        Argument.__init__(self, typename)
        self._content = Argument.generate("vector<int>")
        self._includes.append("leetcode/listnode.hpp")

    def _parse_value(self, string: str):
        return "ListNode::generate({})".format(self._content._parse_value(string))

    def is_valid(self):
        return self._content.is_valid()

class TreeNodeArgument(Argument):
    def __init__(self, typename: str):
        Argument.__init__(self, typename)
        self._content = Argument.generate("vector<int>")
        self._includes.append("leetcode/treenode.hpp")

    def _parse_value(self, string: str):
        val = self._content._parse_value(string)
        val = re.sub("null", "NULL_TREENODE", val)
        return "TreeNode::generate({})".format(self._content._parse_value(string))

    def is_valid(self):
        return self._content.is_valid()
