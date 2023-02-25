#!/usr/bin/env python3
from cpp_analyze import *
from cpp_analyze import _CPPCodeSnippetInformation
import regex
import sys
# prevent generating __pycache__
sys.dont_write_bytecode = True


class CPPCodeSnippet:
    def __init__(self, code_snippet: str) -> None:
        self.snippet_info = CPPCodeSnippetAnalyzer.parse(code_snippet.strip())

    def __bool__(self):
        return self.snippet_info and self.snippet_info.__bool__()

    def solutionDefine(self):
        return self.snippet_info.raw

    def _genSkipped(self):
        return 'GTEST_SKIP() << "Unittest Not Implemented";'

    def _getSolutionObjectName(self):
        return '_'.join(filter(lambda e: e != "", regex.split("([A-Z][a-z]+)", self.snippet_info.classblock.name))).lower()

    def _genUnitTestAsRegularSolution(self, input: str, output: str):
        assert self.snippet_info.type == CPPCodeSnippetAnalyzer.TYPE_REGULAR

        LOG = prompt.Log.getInstance()
        result = ""
        class_block = self.snippet_info.classblock
        ctor = class_block.constructor[0]
        func = class_block.member_func[0]
        obj = self._getSolutionObjectName()
        result = f'auto {obj} = {ctor()};'

        for name in func.input_args:
            tp = func.arg_types[name]
            input_regex = f'{name} *= *({tp.evaluateInputRegex()[1:-1]})'
            LOG.funcVerbose("parse input for {} with regex: {}",
                            name, input_regex)
            mat = regex.search(input_regex, input)
            if not mat:
                LOG.failure("falied to parse input: {}", input)
                return self._genSkipped()
            result += f'{tp} {name} = {tp(mat.group(1))};'

        is_inplace_case = func.return_type.getTypeName() == "void"
        actual = "actual" if not is_inplace_case else func.input_args[0]
        tp = func.return_type if not is_inplace_case else func.arg_types[actual]

        output_regex = tp.evaluateInputRegex()[1:-1]
        LOG.funcVerbose("parse output with regex: {}", output_regex)
        mat = regex.search(output_regex, output)
        if not mat:
            LOG.failure("falied to parse output: {}", output)
            return self._genSkipped()

        result += f'{tp} expect = {tp(mat.group(0))};'
        if is_inplace_case:
            result += f'{obj}->{func(*func.input_args)};'
        else:
            result += f'{func.return_type} {actual} = {obj}->{func(*func.input_args)};'
        result += f'{tp.expectEuql("expect", actual)};'

        for name in func.input_args:
            tp = func.arg_types[name]
            dtor = tp.destroy()
            if dtor and dtor != "":
                result += dtor + ";"

        return result

    def _genUnitTestAsStructuredSolution(self, input: str, output: str):
        assert self.snippet_info.type == CPPCodeSnippetAnalyzer.TYPE_STRUCTURED

        LOG = prompt.Log.getInstance()
        result = ""
        class_block = self.snippet_info.classblock

        class TestStep:
            def __init__(self) -> None:
                self.function: _CPPCodeSnippetInformation._CPPSolutionFunction = None
                self.args_val: list[str] = []
                self.expect: str = ""

        test_steps: list[TestStep] = []

        # first line of input is formatted in vector<string>-like
        command_regex = "(?:'[\w\W]*?'|\"[\w\W]*?\")"
        input_func_regex = f"(?:\[(?:(?:(?: *{command_regex}) *,?)*)?\])"
        LOG.funcVerbose("parse input: {}", input)
        LOG.funcVerbose("parse input with regex: {}", input_func_regex)
        mat = regex.search(input_func_regex, input)
        if not mat:
            LOG.failure("falied to parse commands int input: {}", input)
            return self._genSkipped()
        secondline_input = regex.sub(input_func_regex, "", input).strip(" \n")

        # Getting the function name and initialize the teststep
        input_inner_func_regex = f"(?: *({command_regex}) *,?)"
        commands_input = mat.group(0)[1:-1]
        LOG.funcVerbose("parse input commands with regex: {}",
                        input_inner_func_regex)
        for elem in regex.findall(input_inner_func_regex, commands_input):
            name = regex.search(command_regex, str(
                elem).strip()).group(0)[1:-1]
            LOG.funcVerbose("find function name: {}", name)
            f: _CPPCodeSnippetInformation._CPPSolutionFunction = None
            if name == class_block.name:
                f = class_block.constructor[0]
            else:
                for mem_f in class_block.member_func:
                    if name == mem_f.name:
                        f = mem_f
                        break

            if not f:
                LOG.failure("test function not found: {}", name)
                return self._genSkipped()
            step = TestStep()
            step.function = f
            test_steps.append(step)

        # Parse arguments in each test step
        # Gen regex for parsing input
        idx = 0
        input_args_regex = f"(?:\[(?:(?:"
        for step in test_steps:
            func = step.function
            tps = [func.arg_types[n] for n in func.input_args]
            input_args_regex += f"(?: *\[ *(?P<step_{idx}>"
            for tp in tps:
                reg = tp.evaluateInputRegex()[1:-1]
                input_args_regex += f"(?: *(?:{reg})) *,?"
            input_args_regex += f")) *\] *,?"
            idx += 1
        input_args_regex += ")*)?\])"
        LOG.funcVerbose("parse arguments input: {}", secondline_input)
        LOG.funcVerbose("parse input arguments with regex: {}",
                        input_args_regex)

        mat = regex.match(input_args_regex, secondline_input)
        if not mat:
            LOG.failure("falied to parse arguments: {}", secondline_input)
            return self._genSkipped()

        idx = 0
        for step in test_steps:
            step.args_val = mat.group(f"step_{idx}").strip()
            idx += 1

        # Gen regex for parse output
        idx = 0
        output_regex = f"(?:\[(?:(?:"
        for step in test_steps:
            output_regex += f"(?: *(?P<step_{idx}>"
            f = step.function
            if not f.return_type or f.return_type.getTypeName() == "void":
                output_regex += "null"
            else:
                reg = f.return_type.evaluateInputRegex()[1:-1]
                output_regex += f"(?: *(?:{reg}))"
            output_regex += f")) *,?"
            idx += 1
        output_regex += ")*)?\])"
        LOG.funcVerbose("parse output: {}", output)
        LOG.funcVerbose("parse output with regex: {}", output_regex)

        mat = regex.match(output_regex, output)
        if not mat:
            LOG.failure("falied to parse arguments: {}", output)
            return self._genSkipped()

        idx = 0
        for step in test_steps:
            step.expect = mat.group(f"step_{idx}")
            idx += 1

        # Gen test steps
        idx = 0
        for step in test_steps:
            idx += 1
            f = step.function
            obj_prefix = f's{idx}_'

            ## Gen argument regex
            arg_idx = 0
            arg_regex = ""
            for tp in [f.arg_types[t] for t in f.input_args]:
                arg_regex += f' *(?P<step_{arg_idx}>{tp.evaluateInputRegex()[1:-1]}) *,'
                arg_idx += 1
            # slice last ','
            arg_regex = arg_regex[:-1]
            LOG.funcVerbose("parse arguments for {}: {}", f.name, step.args_val)
            LOG.funcVerbose("parse arguments with regex: {}", arg_regex)

            mat = regex.search(arg_regex, step.args_val)
            if not mat:
                LOG.failure("falied to parse arguments for {}: {}",
                            f.name, step.args_val)
                return self._genSkipped()

            arg_idx = 0
            for name in f.input_args:
                tp = f.arg_types[name]
                result += f'{tp} {obj_prefix}{name} = '
                result += '{};'.format(tp(mat.group(f"step_{arg_idx}")))
                arg_idx += 1

            args = [obj_prefix + n for n in f.input_args]
            if not f.return_type:
                # construct case
                result += f'auto {self._getSolutionObjectName()} = {f(*args)};'
            elif f.return_type.getTypeName() == "void":
                result += f'{self._getSolutionObjectName()}->{f(*args)};'
            else:
                result += f'{f.return_type} {obj_prefix}expect = {f.return_type(step.expect)};'
                result += f'{f.return_type} {obj_prefix}actual = {self._getSolutionObjectName()}->{f(*args)};'
                result += f'{f.return_type.expectEuql(obj_prefix + "expect", obj_prefix + "actual")};'
        return result

    def genUnitTest(self, *, input: str, output: str) -> str:
        LOG = prompt.Log.getInstance()
        if self.snippet_info.type == CPPCodeSnippetAnalyzer.TYPE_REGULAR:
            LOG.funcVerbose("generate unittest as regular solution mode.")
            return self._genUnitTestAsRegularSolution(input, output)
        elif self.snippet_info.type == CPPCodeSnippetAnalyzer.TYPE_STRUCTURED:
            LOG.funcVerbose("generate unittest as structured solution mode.")
            return self._genUnitTestAsStructuredSolution(input, output)
        return self._genSkipped()


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

    code = CPPCodeSnippet(q146)
    a = code.genUnitTest(input=q146_input, output=q146_output)
    LOG.print(a.replace(';', ';\n'))
