#!/usr/bin/env python3
from cpp_analyze import *
from cpp_analyze import _CPPCodeSnippetInformation
from cpp_types import _CPPTypeAbstract, CPPTypeVector
import regex
import sys
# prevent generating __pycache__
sys.dont_write_bytecode = True


class _UnitTestFlavor:
    def __init__(self, *,
                 instance: str,
                 function: _CPPCodeSnippetInformation._CPPSolutionFunction,
                 compare_in_any_order: bool = False) -> None:
        self._instance: str = instance
        self._function: _CPPCodeSnippetInformation._CPPSolutionFunction = function
        self._in_any_order = compare_in_any_order

    def clear(self):
        pass

    def addInput(self, input: str) -> bool:
        return False

    def addExpect(self, output: str) -> bool:
        return False

    def genUnitTestSnippet(self, *, variable_prefix: str = ""):
        return ""

    def genExtraInputFromSubmissionResult(self, *, variable_prefix: str = "", input: str, output: str):
        return ""

    def parseExtraInput(self, input: str) -> tuple[str, str]:
        return None, None

    def genExtraInputPrompt(self, *, id: int, title: str):
        return ""

    def getHeaders(self):
        res: set[str] = set()
        for tp in self._function.arg_types.values():
            for header in tp.getHeaders():
                res.add(header)
        if self._function.return_type:
            for header in self._function.return_type.getHeaders():
                res.add(header)
        return res

    def getTypeCollection(self, *, variable_prefix: str = ""):
        res: dict[__builtins__._ClassInfo, list[str]] = {}
        for name in self._function.input_args:
            tp = self._function.arg_types[name]
            if tp.__class__ not in res:
                res[tp.__class__] = []
            res[tp.__class__].append(variable_prefix + name)
        return res


class _UnitTestUnsupportFlavor(_UnitTestFlavor):
    def __init__(self, *,
                 instance: str,
                 function: _CPPCodeSnippetInformation._CPPSolutionFunction,
                 compare_in_any_order: bool = False) -> None:
        super().__init__(instance=instance, function=function,
                         compare_in_any_order=compare_in_any_order)

    def getHeaders(self):
        res: set[str] = set()
        for tp in self._function.arg_types.values():
            for header in tp.getHeaders():
                res.add(header)
        if self._function.return_type:
            for header in self._function.return_type.getHeaders():
                res.add(header)
        return res


class _UnitTestRegularFlavor(_UnitTestFlavor):
    def __init__(self, *,
                 constructor: _CPPCodeSnippetInformation._CPPSolutionFunction,
                 instance: str,
                 function: _CPPCodeSnippetInformation._CPPSolutionFunction,
                 compare_in_any_order: bool = False) -> None:
        super().__init__(instance=instance, function=function,
                         compare_in_any_order=compare_in_any_order)
        self._ctor = constructor
        self._inputs: list[tuple[str, str]] = None
        self._inplace_case = False
        if self._function.return_type and self._function.return_type.getTypeName() == "void":
            self._inplace_case = True
        self._actual = "actual" if not self._inplace_case else self._function.input_args[0]
        self._return_type = self._function.return_type if not self._inplace_case else self._function.arg_types[
            self._actual]
        self._output: str = None
        assert self._ctor, "invalid consturctor"

    def clear(self):
        self._inputs = None
        self._output = None

    def _verifyExtraInput(self, input: str, output: str):
        LOG = prompt.Log.getInstance()

        input_str = ""
        output_str = ""
        input = input.replace('\xa0', '')
        LOG.funcVerbose("parse the input: {}", input)
        for name in self._function.input_args:
            tp = self._function.arg_types[name]
            reg = f'{name}[ \\n]*=[ \\n]*({tp.evaluateInputRegex()[1:-1]})'
            LOG.funcVerbose("     with regex: {}", reg)
            mat = regex.search(reg, input)
            if not mat:
                LOG.failure("falied to parse input: {}", repr(input))
                return None, None
            LOG.funcVerbose("    found value: {}", mat.group(1))
            input_str += f'{name} = {mat.group(1)}, '

        input_str = input_str[:-2]

        output = output.replace('\xa0', '')
        reg = self._return_type.evaluateInputRegex()[1:-1]
        LOG.funcVerbose("parse the output: {}", output)
        LOG.funcVerbose("      with regex: {}", reg)
        mat = regex.search(reg, output)
        if not mat:
            LOG.failure("falied to parse output: {}", output)
            return None, None

        LOG.funcVerbose("     found value: {}", mat.group(0))
        output_str = mat.group(0)
        return input_str, output_str

    def addInput(self, input: str) -> bool:
        assert self._inputs is None, "duplicately added input."

        self._inputs = []
        LOG = prompt.Log.getInstance()

        input = input.replace('\xa0', '')
        LOG.funcVerbose("parse the input: {}", input)
        for name in self._function.input_args:
            tp = self._function.arg_types[name]
            reg = f'{name}[ \\n]*=[ \\n]*({tp.evaluateInputRegex()[1:-1]})'
            LOG.funcVerbose("     with regex: {}", reg)
            mat = regex.search(reg, input)
            if not mat:
                LOG.failure("falied to parse input: {}", repr(input))
                return False
            LOG.funcVerbose("    found value: {}", mat.group(1))
            self._inputs.append((name, mat.group(1)))
        return True

    def addExpect(self, output: str):
        assert self._output is None, "duplicately added output."

        if not self._return_type:
            return False

        LOG = prompt.Log.getInstance()
        self._output = ""
        output = output.replace('\xa0', '')
        reg = self._return_type.evaluateInputRegex()[1:-1]
        LOG.funcVerbose("parse the output: {}", output)
        LOG.funcVerbose("      with regex: {}", reg)
        mat = regex.search(reg, output)
        if not mat:
            LOG.failure("falied to parse output: {}", output)
            return False

        LOG.funcVerbose("     found value: {}", mat.group(0))
        self._output = mat.group(0)
        return True

    def genUnitTestSnippet(self, *, variable_prefix: str = ""):
        result = ""
        # consturct
        LOG = prompt.Log.getInstance()
        LOG.funcVerbose("generating the unittest snippet.")
        result += f'auto {variable_prefix}{self._instance} = {self._ctor()};'
        gc = self.getTypeCollection()
        for name, input in self._inputs:
            tp = self._function.arg_types[name]
            result += f'{tp} {name} = {tp(input)};'

        if self._inplace_case:
            tp = self._function.arg_types[self._function.input_args[0]]
            if tp.__class__ not in gc:
                gc[tp.__class__] = []
            gc[tp.__class__].append("expect")
            result += f'{tp} expect = {tp(self._output)};'
            result += f'{variable_prefix}{self._instance}->{self._function(*self._function.input_args)};'
        else:
            if self._return_type.__class__ not in gc:
                gc[self._return_type.__class__] = []
            gc[self._return_type.__class__].append("expect")
            gc[self._return_type.__class__].append(self._actual)
            result += f'{self._return_type} expect = {self._return_type(self._output)};'
            result += f'{self._return_type} {self._actual} = {variable_prefix}{self._instance}->{self._function(*self._function.input_args)};'

        if self._in_any_order and isinstance(self._return_type, CPPTypeVector):
            result += f'EXPECT_ANYORDER_EQ(expect, {self._actual});'
        else:
            result += f'LCD_EXPECT_EQ(expect, {self._actual});'

        for cls, variables in gc.items():
            assert issubclass(cls, _CPPTypeAbstract)
            destroy = cls.destroy(*variables)
            if destroy and destroy != "":
                result += f'{destroy};'

        return result

    def genExtraInputFromSubmissionResult(self, *, variable_prefix: str = "", input: str, output: str):
        LOG = prompt.Log.getInstance()
        args = input.splitlines()

        if len(args) != len(self._function.input_args):
            LOG.failure("the length of input arguments does not same as function args.")
            return ""

        inputs_args = []
        for idx in range(len(args)):
            name = self._function.input_args[idx]
            inputs_args.append(f'{name} = {args[idx].strip()}')

        if not self.addInput('\n'.join(inputs_args)):
            return ""

        if not self.addExpect(output):
            return ""

        return self.genUnitTestSnippet(variable_prefix=variable_prefix)

    def parseExtraInput(self, input: str) -> bool:
        LOG = prompt.Log.getInstance()
        LOG.funcVerbose("got input:\n{}", input)
        input = regex.sub("^ *#[\w\W]*?\n*$", "", input, flags=regex.MULTILINE)
        input = regex.sub(" *\n+ *", "\n", input)
        input = input.strip()
        LOG.funcVerbose("substitute input to:\n{}", input)
        lines = list(filter(lambda str: str != ' ', input.splitlines()))
        if len(lines) < 2:
            LOG.failure("failed to parse extra input: expect more than {} lines got {}",
                        LOG.format('2', flag=LOG.IMPORTANT), LOG.format(len(lines), flag=LOG.HIGHTLIGHT))
            return None, None
        input_str = '\n'.join(lines[0:-1])
        output_str = lines[-1]
        return self._verifyExtraInput(input_str, output_str)

    def genExtraInputPrompt(self, *, id: int, title: str):
        args = '\n'.join([f'{name} = ' for name in self._function.input_args])
        function_snippets = str(self._function.return_type) + ' '
        arguments = [
            f'{self._function.arg_types[name]} {name}' for name in self._function.input_args]
        function_snippets += self._function(*arguments)

        return concat(
            f'# input:',
            f'{args}',
            f'',
            f'# expected output:',
            f'',
            f'',
            f'# please enter the input and expected output of the unittest in following format.',
            f'# several lines show the argument name and its input (e.g. Name = Input), and the last',
            f'# line shows the expected output value.',
            f'# function snippets:',
            f'',
            f'# {function_snippets}',
            f'',
            f'# lines starting with \'#\' will be ignored.',
        )


class _UnitTestStageFlavorSingleStage(_UnitTestFlavor):
    def __init__(self, *,
                 instance: str,
                 function: _CPPCodeSnippetInformation._CPPSolutionFunction,
                 compare_in_any_order: bool = False):
        super().__init__(instance=instance, function=function,
                         compare_in_any_order=compare_in_any_order)
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

        input = input.replace('\xa0', '')
        LOG.funcVerbose("parse the input: {}", input)
        LOG.funcVerbose("     with regex: {}", reg)

        mat = regex.search(reg, input)
        if not mat:
            LOG.failure("falied to parse arguments for {}: {}",
                        self._function.name, input)
            return False

        for name in self._function.input_args:
            tp = self._function.arg_types[name]
            val = tp(mat.group(name))
            self._inputs.append((name, val))
            LOG.funcVerbose("    found value: {}", val)
        return True

    def addExpect(self, output: str):
        assert self._expect is None, "duplicately added output."
        output = output.replace('\xa0', '')
        self._expect = output
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
            res += f'LCD_EXPECT_EQ({variable_prefix}expect, {variable_prefix}actual);'
        return res

    def getTypeCollection(self, *, variable_prefix: str = ""):
        res = super().getTypeCollection(variable_prefix=variable_prefix)
        f = self._function
        if not self._isConstructor() and f.return_type.getTypeName() != "void":
            if f.return_type.__class__ not in res:
                res[f.return_type.__class__] = []
            res[f.return_type.__class__].append("expect")
            res[f.return_type.__class__].append("actual")
        return res


class _UnitTestStageFlavor(_UnitTestFlavor):
    def __init__(self, *,
                 instance: str, snippet_info: _CPPCodeSnippetInformation, compare_in_any_order: bool = False):
        super().__init__(instance=instance, function=None,
                         compare_in_any_order=compare_in_any_order)
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
                function_name).strip()).group(0)[1:-1].strip()
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
                return False

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

    def getHeaders(self):
        res: set[str] = set()
        for func in self._class_info.member_func:
            for tp in func.arg_types.values():
                for header in tp.getHeaders():
                    res.add(header)
            if func.return_type:
                for header in func.return_type.getHeaders():
                    res.add(header)
        for tp in self._class_info.constructor[0].arg_types.values():
            for header in tp.getHeaders():
                res.add(header)
        if func.return_type:
            for header in func.return_type.getHeaders():
                res.add(header)
        return res

    def genUnitTestSnippet(self, *, variable_prefix: str = ""):
        result = ""
        idx = 0
        for step in self._stages:
            obj_prefix = f's{idx}_'
            result += step.genUnitTestSnippet(variable_prefix=obj_prefix)
            idx += 1

        destory_map = {}
        idx = 0
        for step in self._stages:
            obj_prefix = f's{idx}_'
            mp = step.getTypeCollection(variable_prefix=obj_prefix)
            for cls, variables in mp.items():
                if cls not in destory_map:
                    destory_map[cls] = []
                destory_map[cls] += variables
            idx += 1

        for cls, variables in destory_map.items():
            assert issubclass(cls, _CPPTypeAbstract)
            destroy = cls.destroy(*variables)
            if destroy and destroy != "":
                result += f'{destroy};'

        return result

    def genExtraInputFromSubmissionResult(self, *, variable_prefix: str = "", input: str, output: str):
        if not self.addInput('\n'.join(input)):
            return ""

        if not self.addExpect(output):
            return ""

        return self.genUnitTestSnippet(variable_prefix=variable_prefix)

    def _verifyExtraInput(self, input: str, output: str):
        LOG = prompt.Log.getInstance()
        input = input.replace('\xa0', '')

        input_funcs: list[str] = []
        input_args: list[list[str]] = []
        outputs: list[str] = []
        input_str = ""
        output_str = ""

        # Inputs
        stages: list[_UnitTestStageFlavorSingleStage] = []
        # Parse input as vector<string> like.
        command_regex = "(?:'[\w\W]*?'|\"[\w\W]*?\")"
        input_func_regex = f"(?:\[(?:(?:(?: *{command_regex}) *,?)*)?\])"
        LOG.funcVerbose("parse input: {}", input)
        LOG.funcVerbose("parse input with regex: {}", input_func_regex)
        mat = regex.search(input_func_regex, input)
        if not mat:
            LOG.failure("falied to parse commands int input: {}", input)
            return None, None

        # Getting the function name and initialize the teststep
        input_inner_func_regex = f"(?: *({command_regex}) *,?)"
        commands_input = mat.group(0)[1:-1]
        LOG.funcVerbose("parse input commands with regex: {}",
                        input_inner_func_regex)
        for function_name in regex.findall(input_inner_func_regex, commands_input):
            name = regex.search(command_regex, str(
                function_name).strip()).group(0)[1:-1].strip()
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
                return None, None

            input_funcs.append(f'"{(f.name)}"')
            stages.append(_UnitTestStageFlavorSingleStage(instance=self._instance,
                                                          function=f))

        idx = 0
        input_args_regex = f"(?:\[(?:(?:"
        for step in stages:
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
            return None, None
        idx = 0
        for step in stages:
            step.addInput(mat.group(f"step_{idx}").strip())
            input_args.append('[{}]'.format(
                ','.join([str(val) for _, val in step._inputs])))
            idx += 1
        input_str = '[{}] [{}]'.format(
            ','.join(input_funcs), ','.join(input_args))

        # Outputs
        idx = 0
        output_regex = f"(?:\[(?:(?:"
        for step in stages:
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
            return None, None

        idx = 0
        for step in stages:
            step.addExpect(mat.group(f"step_{idx}"))
            outputs.append(step._expect)
            idx += 1
        output_str = '[{}]'.format(','.join(outputs))

        return input_str, output_str

    def parseExtraInput(self, input: str) -> bool:
        LOG = prompt.Log.getInstance()
        LOG.funcVerbose("got input:\n{}", input)
        input = regex.sub("^ *#[\w\W]*?\n*$", "", input, flags=regex.MULTILINE)
        input = regex.sub(" *\n+ *", "\n", input)
        input = input.strip()
        LOG.funcVerbose("substitute input to:\n{}", input)
        lines = list(filter(lambda str: str != ' ', input.splitlines()))
        if len(lines) != 3:
            LOG.failure("failed to parse extra input: expect {} lines got {}",
                        LOG.format('3', flag=LOG.IMPORTANT), LOG.format(len(lines), flag=LOG.HIGHTLIGHT))
            return None, None
        return self._verifyExtraInput(f'{lines[0]}{lines[1]}', lines[2])

    def genExtraInputPrompt(self, *, id: int, title: str):
        info = self._class_info
        valid_functions: list[str] = []

        ctor_args_types = [str(info.constructor[0].arg_types[name])
                           for name in info.constructor[0].input_args]
        valid_functions.append(info.constructor[0](*ctor_args_types))

        for func in info.member_func:
            args_types = [str(func.arg_types[name])
                          for name in func.input_args]
            valid_functions.append(f'{func.return_type} {func(*args_types)}')

        return concat(
            f'# input:',
            f'[]',
            f'[]',
            f'',
            f'# expect output:',
            f'[]',
            f'',
            f'# please enter the input and expected output of the unittest in the following format.',
            f'# first line shows function names array, second line shows arguments array for specific functions',
            f'# and third line shows the expected output array. note that |null| should be explicit if the',
            f'# function does not return anything.',
            f'# valid functions:',
            f'',
            '# - {}'.format('\n# - '.join(valid_functions)),
            f'',
            f'# lines starting with \'#\' will be ignored.',
        )


class CPPCodeSnippet:
    def __init__(self, code_snippet: str, compare_in_any_order: bool = False) -> None:
        LOG = prompt.Log.getInstance()
        self.snippet_info = CPPCodeSnippetAnalyzer.parse(code_snippet.strip())
        self._unittest_flavor: _UnitTestFlavor = None

        if self.snippet_info.type == CPPCodeSnippetAnalyzer.TYPE_REGULAR:
            class_block = self.snippet_info.classblock
            self._unittest_flavor = _UnitTestRegularFlavor(constructor=class_block.constructor[0],
                                                           instance=self._getSolutionObjectName(),
                                                           function=class_block.member_func[0],
                                                           compare_in_any_order=compare_in_any_order)
            LOG.funcVerbose("attached unittest regular flavor.")

        elif self.snippet_info.type == CPPCodeSnippetAnalyzer.TYPE_STRUCTURED:
            self._unittest_flavor = _UnitTestStageFlavor(instance=self._getSolutionObjectName(),
                                                         snippet_info=self.snippet_info,
                                                         compare_in_any_order=compare_in_any_order)
            LOG.funcVerbose("attached unittest stages flavor.")

        else:
            class_block = self.snippet_info.classblock
            self._unittest_flavor = _UnitTestUnsupportFlavor(instance=self._getSolutionObjectName(),
                                                             function=class_block.member_func[0],
                                                             compare_in_any_order=compare_in_any_order)
            LOG.failure("unsupport this type of question.")

    def __bool__(self):
        return self._unittest_flavor and self.snippet_info.__bool__()

    def solutionDefine(self):
        return self.snippet_info.raw

    def _genSkipped(self):
        return 'GTEST_SKIP() << "Unittest Not Implemented";'

    def getClassName(self):
        return self.snippet_info.classblock.name

    def _getSolutionObjectName(self):
        return '_'.join(filter(lambda e: e != "", regex.split("([A-Z][a-z]+)", self.getClassName()))).lower()

    def getHeaders(self):
        return self._unittest_flavor.getHeaders()

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

    def genUnitTestFromSubmissionResult(self, *, intput: str, output: str) -> str:
        self._unittest_flavor.clear()
        result = self._unittest_flavor.genExtraInputFromSubmissionResult(input=input, output=output)
        if result != "":
            return result
        return self._genSkipped()

    def genExtraInputPrompt(self, *, id: int, title: str):
        return self._unittest_flavor.genExtraInputPrompt(id=id, title=title)

    def parseExtraInput(self, input: str) -> tuple[str, str]:
        return self._unittest_flavor.parseExtraInput(input)


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

    q783 = '\n'.join([
        '/**',
        ' * Definition for a binary tree node.',
        ' * struct TreeNode {',
        ' *     int val;',
        ' *     TreeNode *left;',
        ' *     TreeNode *right;',
        ' *     TreeNode() : val(0), left(nullptr), right(nullptr) {}',
        ' *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}',
        ' *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}',
        ' * };',
        ' */',
        'class Solution {',
        'public:',
        '    int minDiffInBST(TreeNode* root) {',
        '        ',
        '    }',
        '};',
    ])
    q783_input = "root = [4,2,6,1,3]"
    q783_output = '1'

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

    q = q146
    input = q146_input
    output = q146_output
    code = CPPCodeSnippet(q)
    a = code.genUnitTest(input=input, output=output)
    LOG.print(a.replace(';', ';\n'))
    a = code.genUnitTest(input=input, output=output)
    LOG.print(a.replace(';', ';\n'))
