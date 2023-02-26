#!/usr/bin/env python3
from cpp_analyze import _CPPCodeSnippetInformation
from cpp_analyze import *
import regex
import sys
# prevent generating __pycache__
sys.dont_write_bytecode = True


class _UnitTestFlavor:
    def __init__(self, *, instance: str, function: _CPPCodeSnippetInformation._CPPSolutionFunction) -> None:
        self._instance: str = instance
        self._function: _CPPCodeSnippetInformation._CPPSolutionFunction = function

    def clear(self):
        pass

    def addInput(self, input: str) -> bool:
        return False

    def addExpect(self, output: str) -> bool:
        return False

    def genUnitTestSnippet(self, *, variable_prefix: str = ""):
        return ""

    def getTypeCollection(self):
        res: dict[__builtins__._ClassInfo, list[str]] = {}
        for name in self._function.input_args:
            tp = self._function.arg_types[name]
            if tp.__class__ not in res:
                res[tp.__class_] = []
            res[tp.__class_].append(name)
        return res


class _UnitTestRegularFlavor(_UnitTestFlavor):
    def __init__(self, *,
                 constructor:  _CPPCodeSnippetInformation._CPPSolutionFunction,
                 instance: str,
                 function: _CPPCodeSnippetInformation._CPPSolutionFunction) -> None:
        super().__init__(instance=instance, function=function)
        self._ctor = constructor
        self._inputs: list[tuple[str, str]] = None
        self._inplace_case = self._function.return_type.getTypeName() == "void"
        self._actual = "actual" if not self._inplace_case else self._function.input_args[0]
        self._return_type = self._function.return_type if not self._inplace_case else self._function.arg_types[
            self._actual]
        self._output: str = None
        assert self._ctor, "invalid consturctor"

    def clear(self):
        self._inputs = None
        self._output = None

    def addInput(self, input: str) -> bool:
        assert self._inputs is None, "duplicately added input."

        self._inputs = []
        LOG = prompt.Log.getInstance()

        for name in self._function.input_args:
            tp = self._function.arg_types[name]
            reg = f'{name} *= *({tp.evaluateInputRegex()[1:-1]})'
            LOG.funcVerbose("parse input for {} with regex: {}", name, reg)
            mat = regex.search(reg, input)
            if not mat:
                LOG.failure("falied to parse input: {}", input)
                return False
            self._inputs.append((name, mat.group(1)))
        return True

    def addExpect(self, output: str):
        assert self._output is None, "duplicately added output."

        LOG = prompt.Log.getInstance()
        self._output = ""
        reg = self._return_type.evaluateInputRegex()[1:-1]
        LOG.funcVerbose("parse output: {}", output)
        LOG.funcVerbose("parse output with regex: {}", reg)
        mat = regex.search(reg, output)
        if not mat:
            LOG.failure("falied to parse output: {}", output)
            return False

        self._output = mat.group(0)
        return True

    def genUnitTestSnippet(self, *, variable_prefix: str = ""):
        result = ""
        # consturct
        result += f'auto {variable_prefix}{self._instance} = {self._ctor()};'
        for name, input in self._inputs:
            tp = self._function.arg_types[name]
            result += f'{tp} {name} = {tp(input)};'

        if self._inplace_case:
            result += f'{variable_prefix}{self._instance}->{self._function(*self._function.input_args)};'
        else:
            result += f'{self._return_type} {self._actual} = {variable_prefix}{self._instance}->{self._function(*self._function.input_args)};'

        result += f'{self._return_type.expectEuql("expect", self._actual)};'
        return result


class _UnitTestStageFlavorSingleStage(_UnitTestFlavor):
    def __init__(self, *,
                 instance: str,
                 function: _CPPCodeSnippetInformation._CPPSolutionFunction):
        super().__init__(instance=instance, function=function)
        self._inputs: list[tuple[str, str]] = None
        self._expect: str = None

    def _isConstructor(self):
        return self._function.return_type is None

    def getChainedArgumentsEvaluateRegex(self):
        res = ""
        for tp in [self._function.arg_types[n] for n in self._function.input_args]:
            res += f'(?: *(?:{tp.evaluateInputRegex()[1:-1]}) *),'
        res = res[:-1]
        return res

    def getExpectRegex(self):
        if not self._function.return_type or self._function.return_type.getTypeName() == "void":
            return "^null$"
        return self._function.return_type.evaluateInputRegex()

    def addInput(self, input: str) -> bool:
        assert self._inputs is None, "duplicately added input."

        LOG = prompt.Log.getInstance()
        self._inputs = []

        reg = ""
        for name in self._function.input_args:
            tp = self._function.arg_types[name]
            reg += f' *(?P<{name}>(?:{tp.evaluateInputRegex()[1:-1]})) *,'
        reg = reg[:-1]
        LOG.funcVerbose("parse arguments for {}: {}",
                        self._function.name, input)
        LOG.funcVerbose("parse arguments with regex: {}", reg)

        mat = regex.search(reg, input)
        if not mat:
            LOG.failure("falied to parse arguments for {}: {}",
                        self._function.name, input)
            return False

        for name in self._function.input_args:
            tp = self._function.arg_types[name]
            self._inputs.append((name, tp.evaluateInput(mat.group(name))))
        return True

    def addExpect(self, output: str):
        assert self._expect is None, "duplicately added output."
        if self._function.return_type and self._function.return_type.getTypeName() != "void":
            self._expect = self._function.return_type.evaluateInput(output)
        return True

    def genUnitTestSnippet(self, *, variable_prefix: str = ""):
        res = ""
        f = self._function
        for n, v in self._inputs:
            tp = f.arg_types[n]
            res += f'{tp} {variable_prefix}{n} = {v};'
        variables = [f'{variable_prefix}{n}' for n in f.input_args]
        if self._isConstructor():
            res += f'auto {self._instance} = {f(*variables)};'
        elif f.return_type.getTypeName() == "void":
            res += f'{self._instance}->{f(*variables)};'
        else:
            res += f'{f.return_type} {variable_prefix}expect = {f.return_type(self._expect)};'
            res += f'{f.return_type} {variable_prefix}actual = {self._instance}->{f(*variables)};'
            res += f'{f.return_type.expectEuql(variable_prefix + "expect", variable_prefix + "actual")};'
        return res


class _UnitTestStageFlavor(_UnitTestFlavor):
    def __init__(self, *,
                 instance: str, snippet_info: _CPPCodeSnippetInformation):
        super().__init__(instance=instance, function=None)
        assert snippet_info.type == CPPCodeSnippetAnalyzer.TYPE_STRUCTURED
        self._stages: list[_UnitTestStageFlavorSingleStage] = None
        self._class_info = snippet_info.classblock

    def clear(self):
        self._stages = None

    def addInput(self, input: str) -> bool:
        assert self._stages is None, "duplicately added input."
        LOG = prompt.Log.getInstance()

        self._stages = []
        # Parse input as vector<string> like.
        command_regex = "(?:'[\w\W]*?'|\"[\w\W]*?\")"
        input_func_regex = f"(?:\[(?:(?:(?: *{command_regex}) *,?)*)?\])"
        LOG.funcVerbose("parse input: {}", input)
        LOG.funcVerbose("parse input with regex: {}", input_func_regex)
        mat = regex.search(input_func_regex, input)
        if not mat:
            LOG.failure("falied to parse commands int input: {}", input)
            return False

        # Getting the function name and initialize the teststep
        input_inner_func_regex = f"(?: *({command_regex}) *,?)"
        commands_input = mat.group(0)[1:-1]
        LOG.funcVerbose("parse input commands with regex: {}",
                        input_inner_func_regex)
        for function_name in regex.findall(input_inner_func_regex, commands_input):
            name = regex.search(command_regex, str(
                function_name).strip()).group(0)[1:-1]
            LOG.funcVerbose("find function name: {}", name)
            f: _CPPCodeSnippetInformation._CPPSolutionFunction = None
            if name == self._class_info.name:
                f = self._class_info.constructor[0]
            else:
                for mem_f in self._class_info.member_func:
                    if name == mem_f.name:
                        f = mem_f
                        break
            if not f:
                LOG.failure("test function not found: {}", name)
                return []

            self._stages.append(_UnitTestStageFlavorSingleStage(instance=self._instance,
                                                                function=f))

        idx = 0
        input_args_regex = f"(?:\[(?:(?:"
        for step in self._stages:
            input_args_regex += f"(?: *\[ *(?P<step_{idx}>"
            input_args_regex += step.getChainedArgumentsEvaluateRegex()
            input_args_regex += f")) *\] *,?"
            idx += 1
        input_args_regex += ")*)?\])"
        LOG.funcVerbose("parse arguments input: {}", input)
        LOG.funcVerbose("parse input arguments with regex: {}",
                        input_args_regex)
        mat = regex.search(input_args_regex, input)
        if not mat:
            LOG.failure("falied to parse arguments: {}", input)
            return False
        idx = 0
        for step in self._stages:
            step.addInput(mat.group(f"step_{idx}").strip())
            idx += 1

        return True

    def addExpect(self, output: str) -> bool:
        LOG = prompt.Log.getInstance()
        idx = 0
        output_regex = f"(?:\[(?:(?:"
        for step in self._stages:
            output_regex += f"(?: *(?P<step_{idx}>"
            output_regex += step.getExpectRegex()[1:-1]
            output_regex += f")) *,?"
            idx += 1
        output_regex += ")*)?\])"
        LOG.funcVerbose("parse output: {}", output)
        LOG.funcVerbose("parse output with regex: {}", output_regex)

        mat = regex.match(output_regex, output)
        if not mat:
            LOG.failure("falied to parse arguments: {}", output)
            return False

        idx = 0
        for step in self._stages:
            step.addExpect(mat.group(f"step_{idx}"))
            idx += 1

        return True

    def genUnitTestSnippet(self, *, variable_prefix: str = ""):
        result = ""
        idx = 0
        for step in self._stages:
            obj_prefix = f's{idx}_'
            result += step.genUnitTestSnippet(variable_prefix=obj_prefix)
            idx += 1
        return result


class CPPCodeSnippet:
    def __init__(self, code_snippet: str) -> None:
        LOG = prompt.Log.getInstance()
        self.snippet_info = CPPCodeSnippetAnalyzer.parse(code_snippet.strip())
        self._unittest_flavor: _UnitTestFlavor = None

        if self.snippet_info.type == CPPCodeSnippetAnalyzer.TYPE_REGULAR:
            class_block = self.snippet_info.classblock
            self._unittest_flavor = _UnitTestRegularFlavor(constructor=class_block.constructor[0],
                                                           instance=self._getSolutionObjectName(),
                                                           function=class_block.member_func[0])
            LOG.funcVerbose("attached unittest regular flavor.")

        elif self.snippet_info.type == CPPCodeSnippetAnalyzer.TYPE_STRUCTURED:
            self._unittest_flavor = _UnitTestStageFlavor(instance=self._getSolutionObjectName(),
                                                         snippet_info=self.snippet_info)
            LOG.funcVerbose("attached unittest stages flavor.")

        else:
            LOG.failure("unsupport this type of question.")

    def __bool__(self):
        return self.snippet_info and self.snippet_info.__bool__() and self._unittest_flavor

    def solutionDefine(self):
        return self.snippet_info.raw

    def _genSkipped(self):
        return 'GTEST_SKIP() << "Unittest Not Implemented";'

    def _getSolutionObjectName(self):
        return '_'.join(filter(lambda e: e != "", regex.split("([A-Z][a-z]+)", self.snippet_info.classblock.name))).lower()

    def genUnitTest(self, *, input: str, output: str) -> str:
        LOG = prompt.Log.getInstance()
        self._unittest_flavor.clear()

        if not self._unittest_flavor.addInput(input):
            LOG.failure("failed to parse inputs: {}", input)
            return self._genSkipped()

        if not self._unittest_flavor.addExpect(output):
            LOG.failure("failed to parse output: {}", output)
            return self._genSkipped()

        return self._unittest_flavor.genUnitTestSnippet()


if __name__ == "__main__":
    LOG = prompt.Log.getInstance(verbose=True)
    q116 = '\n'.join([
        '// Definition for a Node.',
        '/*',
        'class Node {',
        'public:',
        '    int val;',
        '    Node* left;',
        '    Node* right;',
        '    Node* next;',
        '',
        '    Node() : val(0), left(NULL), right(NULL), next(NULL) {}',
        '',
        '    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}',
        '',
        '    Node(int _val, Node* _left, Node* _right, Node* _next)',
        '        : val(_val), left(_left), right(_right), next(_next) {}',
        '};',
        '*/',
        '',
        'class Solution {',
        'public:',
        '    Node* connect(Node* root) {',
        '        ',
        '    }',
        '};',
    ])

    q1 = '\n'.join([
        'class Solution {',
        'public:',
        'vector<int> twoSum(vector<int>& nums, int target) {',
        '        ',
        '}',
        '};',
    ])
    q1_input = "nums = [2,7,11,15], target = 9"
    q1_output = "[0,1]"

    q146 = '\n'.join([
        'class LRUCache {',
        'public:',
        'LRUCache(int capacity) {',
        '        ',
        '}',
        '    ',
        'int get(int key) {',
        '        ',
        '}',
        '    ',
        'void put(int key, int value) {',
        '        ',
        '}',
        '};',
        '',
        '/**',
        ' * Your LRUCache object will be instantiated and called as such:',
        ' * LRUCache* obj = new LRUCache(capacity);',
        ' * int param_1 = obj->get(key);',
        ' * obj->put(key,value);',
        ' */',
    ])
    q146_input = '''["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]'''
    q146_output = '[null, null, null, 1, null, -1, null, -1, 3, 4]'

    q234 = '\n'.join([
        '/**',
        ' * Definition for singly-linked list.',
        ' * struct ListNode {',
        ' *     int val;',
        ' *     ListNode *next;',
        ' *     ListNode() : val(0), next(nullptr) {}',
        ' *     ListNode(int x) : val(x), next(nullptr) {}',
        ' *     ListNode(int x, ListNode *next) : val(x), next(next) {}',
        ' * };',
        ' */',
        'class Solution {',
        'public:',
        'bool isPalindrome(ListNode* head) {',
        '        ',
        '}',
        '};',
    ])
    q234_input = "head = [1,2,2,1]"
    q234_output = 'true'

    code = CPPCodeSnippet(q146)
    a = code.genUnitTest(input=q146_input, output=q146_output)
    LOG.print(a.replace(';', ';\n'))
    a = code.genUnitTest(input=q146_input, output=q146_output)
    LOG.print(a.replace(';', ';\n'))
