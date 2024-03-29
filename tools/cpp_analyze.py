#!/usr/bin/env python3
import regex
import sys
# prevent generating __pycache__
sys.dont_write_bytecode = True


from utils import *
from cpp_types import _CPPTypeAbstract, deduceCPPType


class _CPPCodeSnippetInformation:

    class _CPPSolutionFunction:
        def __init__(self, *, func_name: str, return_type: _CPPTypeAbstract) -> None:
            self.name: str = func_name
            self.arg_types: dict[str, _CPPTypeAbstract] = {}
            self.input_args: list[str] = []
            # if self.return_type is None then the function is a constructor
            self.return_type: _CPPTypeAbstract = return_type

        def __bool__(self):
            LOG = prompt.Log.getInstance()
            if self.name == "":
                LOG.failure("empty function name.")
                return False
            if self.return_type is not None and not self.return_type:
                LOG.failure("invalid return type: {}", self.return_type)
                return False
            for type in self.arg_types.values():
                if type is not None and not type:
                    LOG.funcVerbose("invalid type: {}", LOG.format(type, flag=LOG.DARK_RED))
                    return False
            return True

        def __call__(self, *args) -> str:
            LOG = prompt.Log.getInstance()
            if len(args) != len(self.input_args):
                LOG.failure("the length between arguments not matched.")
                return ""
            return '{}{}({})'.format("Make" if not self.return_type else "", self.name, ','.join([*args]))

    class _CPPSolutionClass:
        def __init__(self) -> None:
            self.name: str = ""
            self.member_func: list[_CPPCodeSnippetInformation._CPPSolutionFunction] = []
            self.constructor: list[_CPPCodeSnippetInformation._CPPSolutionFunction] = []

        def __bool__(self):
            LOG = prompt.Log.getInstance()
            if self.name == "":
                LOG.failure("empty class name.")
                return False
            if len(self.member_func) == 0:
                LOG.failure("no member function in: {}", self.name)
                return False
            for func in self.member_func:
                if not func:
                    return False
            return True

    def __init__(self) -> None:
        # name -> cpptype
        self.raw: str = ""
        self.type: int = CPPCodeSnippetAnalyzer.TYPE_UNDEFINED
        self.classblock = _CPPCodeSnippetInformation._CPPSolutionClass()

    def __bool__(self):
        return self.classblock.__bool__()


class CPPCodeSnippetAnalyzer:
    TYPE_UNDEFINED = 0
    TYPE_REGULAR = 1
    TYPE_STRUCTURED = 2

    def __init__(self) -> None:
        assert False, "_CPPCodeSnippetAnalyzer shouldn't be constructed."

    def _trimComment(code: str):
        code = regex.sub("//[^\n]*?\n", "", code)
        code = regex.sub("\/\*[\w\W]*?\*\/", "", code)
        return code.strip()

    _CLASS_PARSER = '(?:class +(?P<classname>\w+) *(?:: *(?:private|public|protected)? *\w+(?:<[\w\W]*?>)? *)?{(?P<class_define>[\w\W]*)?};)'
    _TYPE_PARSER = '( *(?:const *)?(?:(?:unsigned +)?long +long|\w+) *(?:<[\w\W]*?>)?(?: *(?:[*&])+ *| +))'
    _FUNC_ARGS_PARSER = _TYPE_PARSER + '(\w+) *?,?'
    _FUNC_PARSER =  _TYPE_PARSER + '(\w+) *\(((?:' + _TYPE_PARSER + '\w+ *,?)*)?\) *(?:(?:const)?(?: *noexcept)? *)?{(?:[^}]*)?}'
    _CONSTRUCTOR_PARSER = ' *\(((?:' + _TYPE_PARSER + '\w+ *,?)*)?\) *(?:: *(?:private|public|protected)? *\w+(?:<[\w\W]*?>)? *\([\w\W]*?\) *)?{(?:[^}]*)?}'

    @staticmethod
    def parse(maybe_code_snippet: str):
        assert isinstance(maybe_code_snippet, str)
        LOG = prompt.Log.getInstance()
        result = _CPPCodeSnippetInformation()
        trimmed = maybe_code_snippet.strip()
        trimmed = CPPCodeSnippetAnalyzer._trimComment(trimmed)
        trimmed = trimmed.replace('\xa0', '')

        LOG.funcVerbose("parse the code snippet:\n {}", trimmed)
        LOG.funcVerbose("            with regex: {}", CPPCodeSnippetAnalyzer._CLASS_PARSER)
        mat = regex.match(CPPCodeSnippetAnalyzer._CLASS_PARSER, trimmed)
        result.raw = trimmed

        if not mat:
            LOG.failure("failed to parse code snippet: {}", repr(maybe_code_snippet))
            LOG.failure("                  with regex: {}", LOG.format(CPPCodeSnippetAnalyzer._CLASS_PARSER,
                                                                       flag=LOG.VERBOSE))
            return result
        
        class_block = result.classblock
        class_block.name = mat.group("classname").strip()
        class_definition = mat.group("class_define").strip()
        LOG.funcVerbose("parsed successfully.")
        LOG.funcVerbose("  found class name: {}", class_block.name)
        LOG.funcVerbose("      found define:\n {}", class_definition)

        constructor = class_block.name + CPPCodeSnippetAnalyzer._CONSTRUCTOR_PARSER
        LOG.funcVerbose("search for constructor with regex: {}", constructor)
        ctor_mat = regex.search(constructor, class_definition)
        if ctor_mat or class_block.name != "Solution":
            result.type = CPPCodeSnippetAnalyzer.TYPE_STRUCTURED
            args = ""
            if ctor_mat:
                args = ctor_mat.group(1).strip()
                LOG.funcVerbose("found a constructor, treat it as a structured solution.")
                LOG.funcVerbose("          constructor: {}", ctor_mat)
            else:
                LOG.funcVerbose("constructor not found while class name is not |Solution|, treat it as a structured solution.")
            LOG.funcVerbose("             its args: {}", args)
            f = _CPPCodeSnippetInformation._CPPSolutionFunction(func_name=class_block.name,
                                                                return_type=None)
            LOG.funcVerbose("parse args with regex: {}", CPPCodeSnippetAnalyzer._FUNC_ARGS_PARSER)
            for arg in regex.findall(CPPCodeSnippetAnalyzer._FUNC_ARGS_PARSER, args):
                arg_type = deduceCPPType(arg[0].strip())
                arg_name = arg[1].strip()
                LOG.funcVerbose("found argument with type |{}| and name |{}|", arg_type, arg_name)
                f.input_args.append(arg_name)
                f.arg_types[arg_name] = arg_type
            class_block.constructor.append(f)
        else:
            LOG.funcVerbose("constructor not found, treat it as a regular solution.")
            result.type = CPPCodeSnippetAnalyzer.TYPE_REGULAR
            f = _CPPCodeSnippetInformation._CPPSolutionFunction(func_name=class_block.name,
                                                                return_type=None)
            class_block.constructor.append(f)

        LOG.funcVerbose("parse the class definition:\n {}", class_definition)
        LOG.funcVerbose("                with regex: {}", CPPCodeSnippetAnalyzer._FUNC_PARSER)
        for func_mat in regex.findall(CPPCodeSnippetAnalyzer._FUNC_PARSER, class_definition):
            fun_name = str(func_mat[1]).strip()
            args = str(func_mat[2]).strip()
            ret_type = deduceCPPType(str(func_mat[0]).strip())

            if fun_name == "":
                LOG.funcVerbose("function name is empty.")
                continue

            LOG.funcVerbose("found a function.")
            LOG.funcVerbose("   function name: {}", fun_name)
            LOG.funcVerbose("     return type: {}", ret_type)
            LOG.funcVerbose("       arguments: {}", args)
            f = _CPPCodeSnippetInformation._CPPSolutionFunction(func_name=fun_name,
                                                                return_type=ret_type)
            LOG.funcVerbose("parse arguments with regex: {}", CPPCodeSnippetAnalyzer._FUNC_ARGS_PARSER)
            for arg in regex.findall(CPPCodeSnippetAnalyzer._FUNC_ARGS_PARSER, args):
                arg_type = deduceCPPType(arg[0].strip())
                arg_name = str(arg[1]).strip()
                LOG.funcVerbose("found argument with type |{}| and name |{}|", arg_type, arg_name)
                f.input_args.append(arg_name)
                f.arg_types[arg_name] = arg_type

            class_block.member_func.append(f)

        if not result:
            result.type = CPPCodeSnippetAnalyzer.TYPE_UNDEFINED

        return result


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

    result = CPPCodeSnippetAnalyzer.parse(q1)
    LOG.print(result)
    LOG.print("is valid: {}", not not result)

    if result:
        obj = result.classblock.name.lower()
        LOG.log("class name: {}", result.classblock.name)
        ctor = result.classblock.constructor[0]
        ctor_args = [f'args{i}' for i in range(len(ctor.input_args))]
        LOG.log("auto {} = {};", obj, ctor(*ctor_args))

        for f in result.classblock.member_func:
            LOG.log(" -- function name: {}", f.name)
            args = [f'args{i}' for i in range(len(f.input_args))]
            LOG.log(f'auto actual = {result.classblock.name}->{f(*args)};')

            for name, type in f.arg_types.items():
                LOG.log("    -- {} {}", type, name)
