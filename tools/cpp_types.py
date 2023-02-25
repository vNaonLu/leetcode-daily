#!/usr/bin/env python3
import regex
import sys
# prevent generating __pycache__
sys.dont_write_bytecode = True


from utils import *


class _CPPTypeAbstract:
    def __init__(self, type_name: str):
        self.__include_headers: set[str] = set(["<iosfwd>"])
        self.__type_name = type_name

    def __str__(self) -> str:
        return self.__type_name

    def __call__(self, value: str) -> str:
        return self.evaluateInput(value)

    def destroy(self) -> str | None:
        return None

    def evaluateInput(self, value: str) -> str:
        assert False, "_CPPTypeAbstract Not Implement."

    def evaluateInputRegex(self) -> str:
        assert False, "_CPPTypeAbstract Not Implement."

    def getTypeName(self) -> str:
        return self.__type_name

    def isVaild(self):
        return False

    def _appendHeader(self, header):
        self.__include_headers.add(header)

    def getHeaders(self):
        return self.__include_headers

    def expectEuql(self, lhs: str, rhs: str):
        return f'EXPECT_EQ({lhs}, {rhs})'


class CPPTypeValid(_CPPTypeAbstract):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def isVaild(self):
        return True


class CPPTypeVoid(CPPTypeValid):
    @staticmethod
    def deduceType(type_name: str):
        mat = regex.match("^(?:void)$", type_name)
        return (mat and mat.group(0)) or None

    def __init__(self, type_name: str):
        super().__init__(CPPTypeVoid.deduceType(type_name))

    def evaluateInput(self, value: str) -> str:
        assert False, "void shouldn't evaluate any input."


class CPPTypeBool(CPPTypeValid):
    @staticmethod
    def deduceType(type_name: str):
        mat = regex.match("^(?:bool)$", type_name)
        return (mat and mat.group(0)) or None

    def __init__(self, type_name: str):
        super().__init__(CPPTypeBool.deduceType(type_name))

    def evaluateInputRegex(self) -> str:
        return "^(?:false|true|False|True|FALSE|TRUE|1|0)$"

    def evaluateInput(self, value: str) -> str:
        LOG = prompt.Log.getInstance()
        mat = regex.match(self.evaluateInputRegex(), value, regex.IGNORECASE)
        if not mat:
            LOG.failure("CPPTypeBool failed to parse: {}",
                        LOG.format(val, flag=LOG.HIGHTLIGHT))
            return "false"
        return mat.group(0)


class CPPTypeChar(CPPTypeValid):
    @staticmethod
    def deduceType(type_name: str):
        mat = regex.match("^(?:char)$", type_name)
        return (mat and mat.group(0)) or None

    def __init__(self, type_name: str):
        super().__init__(CPPTypeChar.deduceType(type_name))

    def evaluateInputRegex(self) -> str:
        return "^(?:'\w'|\"\w\")$"

    def evaluateInput(self, value: str) -> str:
        LOG = prompt.Log.getInstance()
        mat_pair = regex.match(self.evaluateInputRegex(), value)
        if not mat_pair:
            LOG.failure("CPPTypeChar failed to parse: {}",
                        LOG.format(val, flag=LOG.HIGHTLIGHT))
            return "'\\0'"
        mat = regex.search("\w", value)
        return "'{}'".format((mat and mat.group(0)) or '\\0')


class CPPTypeInt(CPPTypeValid):
    @staticmethod
    def deduceType(type_name: str):
        mat = regex.match(
            "^(?:u?int(?:(?:8|16|32|64)_t)?|(?:unsigned )?(long )?(?:long|int))$", type_name)
        return (mat and mat.group(0)) or None

    def __init__(self, type_name: str):
        super().__init__(CPPTypeInt.deduceType(type_name))

    def evaluateInputRegex(self) -> str:
        return "^[+-]?[\d]+$"

    def evaluateInput(self, value: str) -> str:
        LOG = prompt.Log.getInstance()
        mat = regex.match(self.evaluateInputRegex(), value)
        if not mat:
            LOG.failure("CPPTypeInt failed to parse: {}",
                        LOG.format(val, flag=LOG.HIGHTLIGHT))
            return "0"
        return mat.group(0)


class CPPTypeFloat(CPPTypeValid):
    @staticmethod
    def deduceType(type_name: str):
        mat = regex.match("^(?:float)$", type_name)
        return (mat and mat.group(0)) or None

    def __init__(self, type_name):
        super().__init__(CPPTypeFloat.deduceType(type_name))

    def expectEuql(self, lhs: str, rhs: str):
        return f'EXPECT_FLOAT_EQ({lhs}, {rhs})'

    def evaluateInputRegex(self) -> str:
        return "^[+-]?[\d]+(?:\.\d*f?)?$"

    def evaluateInput(self, value: str) -> str:
        LOG = prompt.Log.getInstance()
        mat = regex.match(self.evaluateInputRegex(), value)
        if not mat:
            LOG.failure("CPPTypeFloat failed to parse: {}",
                        LOG.format(val, flag=LOG.HIGHTLIGHT))
            return "0.0f"
        return mat.group(0)


class CPPTypeDouble(CPPTypeValid):
    @staticmethod
    def deduceType(type_name: str):
        mat = regex.match("^(?:double)$", type_name)
        return (mat and mat.group(0)) or None

    def __init__(self, type_name: str):
        super().__init__(CPPTypeDouble.deduceType(type_name))

    def expectEuql(self, lhs: str, rhs: str):
        return f'EXPECT_DOUBLE_EQ({lhs}, {rhs})'

    def evaluateInputRegex(self) -> str:
        return "^[+-]?[\d]+(?:\.\d*)?$"

    def evaluateInput(self, value: str) -> str:
        LOG = prompt.Log.getInstance()
        mat = regex.match(self.evaluateInputRegex(), value)
        if not mat:
            LOG.failure("CPPTypeDouble failed to parse: {}",
                        LOG.format(val, flag=LOG.HIGHTLIGHT))
            return "0.0"
        return mat.group(0)


class CPPTypeString(CPPTypeValid):
    @staticmethod
    def deduceType(type_name: str):
        mat = regex.match("^(?:(?:std::)?string)$", type_name)
        return (mat and mat.group(0)) or None

    def __init__(self, type_name: str):
        super().__init__(CPPTypeString.deduceType(type_name))
        self._appendHeader("<string>")

    def evaluateInputRegex(self) -> str:
        return "^(?:'[\w\W]*?'|\"[\w\W]*?\")$"

    def evaluateInput(self, value: str) -> str:
        LOG = prompt.Log.getInstance()
        mat_pair = regex.match(self.evaluateInputRegex(), value)
        if not mat_pair:
            LOG.failure("CPPTypeString failed to parse: {}",
                        LOG.format(val, flag=LOG.HIGHTLIGHT))
            return '""'
        mat = regex.search(".*", value[1:-1])
        return '"{}"'.format((mat and mat.group(0)) or "")


class CPPTypeVector(CPPTypeValid):
    @staticmethod
    def deduceType(type_name: str):
        mat = regex.match(
            "^((?:std::)?vector<(?P<template_type>[\w\W]+)>) *&?$", type_name)
        return mat

    def __init__(self, type_name: str):
        mat = CPPTypeVector.deduceType(type_name)
        self._template_type = deduceCPPType(mat.group("template_type"))
        super().__init__(mat.group(1))
        self._appendHeader("<vector>")
        for header in self._template_type.getHeaders():
            self._appendHeader(header)

    def evaluateInputRegex(self) -> str:
        assert self._template_type
        inner = self._template_type.evaluateInputRegex()[1:-1]
        return f'^(?:\[(?:(?:(?: *{inner}) *,?)*)?\])$'

    def evaluateInput(self, value: str) -> str:
        LOG = prompt.Log.getInstance()
        assert self._template_type
        content: list[str] = []
        LOG.funcVerbose("bracket regex: {}", self.evaluateInputRegex())
        mat_bracket = regex.match(self.evaluateInputRegex(), value)
        if not mat_bracket:
            LOG.failure("CPPTypeVector ({}) failed to parse: {}", self.getTypeName(),
                        LOG.format(value, flag=LOG.HIGHTLIGHT))
            return "{{}}"
        inner = value[1:-1]
        inner_regex = f'(?:( *{self._template_type.evaluateInputRegex()[1:-1]}) *,?)'
        LOG.verbose("search inner with: {}", inner_regex)
        LOG.verbose("search inner content: {}", inner)
        for elem in regex.findall(inner_regex, inner):
            elem_ = str(elem).strip()
            LOG.funcVerbose("element: {}", elem_)
            content.append(self._template_type.evaluateInput(elem_))
        return "{{{}}}".format(",".join(content))

    def isVaild(self):
        return not not self._template_type


class CPPTypeListNode(CPPTypeValid):
    @staticmethod
    def deduceType(type_name: str):
        # only support pointer
        mat = regex.match("^(?:ListNode) *\*$", type_name)
        return (mat and mat.group(0)) or None

    def __init__(self, type_name: str):
        super().__init__(CPPTypeListNode.deduceType(type_name))
        self.__content_type = CPPTypeInt("int")
        self.__content_regex = self.__content_type.evaluateInputRegex()[1:-1]
        self._appendHeader("\"leetcode/list_node.h\"")

    def destroy(self) -> str:
        return "ListNode::ReleaseAll()"

    def expectEuql(self, lhs: str, rhs: str):
        return f'EXPECT_LISTNODE_EQ({lhs}, {rhs})'

    def evaluateInputRegex(self) -> str:
        content = self.__content_regex
        return f'^(?:\[(?:(?:(?: *{content}) *,?)*)?\])$'

    def evaluateInput(self, value: str) -> str:
        LOG = prompt.Log.getInstance()
        content: list[str] = []
        LOG.funcVerbose("bracket regex: {}", self.evaluateInputRegex())
        mat_bracket = regex.match(self.evaluateInputRegex(), value)
        if not mat_bracket:
            LOG.failure("CPPTypeListNode failed to parse: {}",
                        LOG.format(value, flag=LOG.HIGHTLIGHT))
            return "ListNode::FromVector({{}})"
        inner = value[1:-1]
        inner_regex = f'(?:( *{self.__content_regex}) *,?)'
        LOG.verbose("search inner with: {}", inner_regex)
        LOG.verbose("search inner content: {}", inner)
        for elem in regex.findall(inner_regex, inner):
            elem_ = str(elem).strip()
            LOG.funcVerbose("element: {}", elem_)
            content.append(self.__content_type.evaluateInput(elem_))
        return "ListNode::FromVector({{{}}}/*, looped_index*/)".format(",".join(content))


class CPPTypeTreeNode(CPPTypeValid):
    @staticmethod
    def deduceType(type_name: str):
        # only support pointer
        mat = regex.match("^(?:TreeNode) *\*$", type_name)
        return (mat and mat.group(0)) or None

    def __init__(self, type_name: str):
        super().__init__(CPPTypeTreeNode.deduceType(type_name))
        self.__content_type = CPPTypeInt("int")
        self.__content_regex = f'(?:{self.__content_type.evaluateInputRegex()[1:-1]}|null)'
        self._appendHeader("\"leetcode/tree_node.h\"")

    def destroy(self) -> str:
        return "TreeNode::ReleaseAll()"

    def expectEuql(self, lhs: str, rhs: str):
        return f'EXPECT_TREENODE_EQ({lhs}, {rhs})'

    def evaluateInputRegex(self) -> str:
        content = self.__content_regex
        return f'^(?:\[(?:(?:(?: *{content}) *,?)*)?\])$'

    def evaluateInput(self, value: str) -> str:
        LOG = prompt.Log.getInstance()
        content: list[str] = []
        LOG.funcVerbose("bracket regex: {}", self.evaluateInputRegex())
        mat_bracket = regex.match(self.evaluateInputRegex(), value)
        if not mat_bracket:
            LOG.failure("CPPTypeTreeNode failed to parse: {}",
                        LOG.format(value, flag=LOG.HIGHTLIGHT))
            return "TreeNode::FromVector({{}})"
        inner = value[1:-1]
        inner_regex = f'(?:( *{self.__content_regex}) *,?)'
        LOG.verbose("search inner with: {}", inner_regex)
        LOG.verbose("search inner content: {}", inner)
        for elem in regex.findall(inner_regex, inner):
            elem_ = str(elem).strip()
            LOG.funcVerbose("element: {}", elem_)
            if elem_ != "null":
                content.append(self.__content_type.evaluateInput(elem_))
            else:
                content.append("null")
        return "TreeNode::FromVector({{{}}})".format(",".join(content))


def deduceCPPType(type: str) -> _CPPTypeAbstract:
    LOG = prompt.Log.getInstance()
    if CPPTypeVoid.deduceType(type):
        return CPPTypeVoid(type)
    if CPPTypeBool.deduceType(type):
        return CPPTypeBool(type)
    if CPPTypeChar.deduceType(type):
        return CPPTypeChar(type)
    if CPPTypeInt.deduceType(type):
        return CPPTypeInt(type)
    if CPPTypeFloat.deduceType(type):
        return CPPTypeFloat(type)
    if CPPTypeDouble.deduceType(type):
        return CPPTypeDouble(type)
    if CPPTypeString.deduceType(type):
        return CPPTypeString(type)
    if CPPTypeVector.deduceType(type):
        return CPPTypeVector(type)
    if CPPTypeListNode.deduceType(type):
        return CPPTypeListNode(type)
    if CPPTypeTreeNode.deduceType(type):
        return CPPTypeTreeNode(type)
    LOG.warn("no matched CPPType: {}",
                LOG.format(type, flag=LOG.HIGHTLIGHT))
    return None


# TEST field
if __name__ == "__main__":
    LOG = prompt.Log.getInstance(verbose=True)
    t = deduceCPPType("vector<string>&")
    test_val: list[str] = [
        "'a'",
        '"ab"',
        '"b"',
        '"b\'',
        "true",
        "True",
        "\"False\"",
        "1 0",
        "1",
        "10.5",
        "-12f3",
        "\"-123\"",
        "\"-123\'",
        "\'-123\'",
        "-123",
        "-123.f",
        "+-123",
        "+12333.0324f",
        "+12333",
        "[123, 4356, 657, 768, 8797, 8]",
        "[123, 4356, null, 657, 768, null, 8797, 8]",
        "[[123, 4356, 657], [768, 8797, 8]]",
        "[123.4, 4356, 657, 768.2, 8797.0, 8]",
        "[[123.4], [4356, 657, 768.2, 8797.0], [8]]",
        "['c', 'c', 'f', 'f', 'f']",
        "['c', 'ccc', 'dsf', 'daaf, fdf', 'ff']",
        "[['c', 'ccc'], ['dsf'], ['daaf, fdf', 'ff']]",
        "[[['c', 'ccc'], ['dsf']], [['daaf, fdf', 'ff']]]",
    ]

    if not t:
        import sys
        sys.exit()

    LOG.log(f'{"type"}     => {t}')
    LOG.log(f'{"include"}  => {t.getHeaders()}')
    LOG.log(f'{"expected"} => {t.expectEuql("expect", "actual")}')
    LOG.log(f'{"is valid"} => {t.isVaild()}')

    if not t.isVaild():
        import sys
        sys.exit()

    for val in test_val:
        LOG.log("---------------------")
        LOG.log("target: {}", val)
        LOG.log("{} obj = {};", LOG.format(
            t, flag=LOG.DARK_GREEN), LOG.format(t(val)))
