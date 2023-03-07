#!/usr/bin/env python3
import sys
# prevent generating __pycache__
sys.dont_write_bytecode = True


from content_analyze import *
from content_analyze import _QuestionContentInformation
from cpp_snippet import *
from utils import *


class CPPSolution:
    def __init__(self, obj: object, *,
                 timestamp: int = time.mktime(TODAY.timetuple()),
                 existed_solution: str = None,
                 headers: set[str] = set([])) -> None:
        assert obj
        assert 'content' in obj
        assert 'questionFrontendId' in obj
        assert 'questionTitle' in obj
        assert 'titleSlug' in obj
        assert 'difficulty' in obj
        LOG = prompt.Log.getInstance()
        self._headers = headers
        self._timestamp: int = timestamp
        self._id: int = int(obj['questionFrontendId'])
        self._title: str = obj['questionTitle']
        self._slug: str = obj['titleSlug']
        title_split = [n[0].upper() + n[1:] for n in regex.findall("[\dA-Z]?\w+", self._title)]
        self._cpp_slug: str = ''.join(title_split)
        self._difficulty: str = obj['difficulty']
        self._content_info: _QuestionContentInformation = None
        self._existed_solution = existed_solution
        self._code_snippet: CPPCodeSnippet = None

        if obj["content"] is not None:
            self._content_info = QuestionContentAnalyzer.parse(obj["content"])

        if "codeSnippets" in obj and obj["codeSnippets"]:
            for snippet in obj["codeSnippets"]:
                if snippet['langSlug'] == 'cpp':
                    self._code_snippet = CPPCodeSnippet(
                        snippet['code'],
                        regex.search("(?:in *)?any *order", obj["content"], regex.IGNORECASE) != None
                    )
                    break

        if self._code_snippet is None:
            LOG.failure("no CPP code snippet for CPPSolution.")
        else:
            for h in self._code_snippet.getHeaders():
                self._headers.add(h)

    def __bool__(self):
        return self._code_snippet is not None

    def _includeHeaders(self) -> str:
        res = ""
        headers = sorted(self._headers)
        for header in headers:
            res += f'#include {header}\n'
        return res

    def _solutionInformation(self, *, prefix: str) -> str:
        return concat(
            f'This file describes the solution of',
            f'{self._title}',
            f'',
            f'https://leetcode.com/problems/{self._slug}/',
            f'',
            f'Question ID: {self._id}',
            f'Difficult  : {self._difficulty}',
             'Solve Date : {}'.format(time.strftime('%Y/%m/%d %H:%M',
                                                       time.localtime(self._timestamp))),
            delimiter=f'\n{prefix}')

    def genExtraInputPrompt(self, *, id: int, title: str):
        return self._code_snippet.genExtraInputPrompt(id=id, title=title)

    def parseExtraInput(self, input: str) -> tuple[str, str]:
        return self._code_snippet.parseExtraInput(input)

    def getUnitTest(self, *, name: str, suite_name: str, input: str, output: str, explanation: str = None):
        explanation_str = ""
        if explanation and explanation != "":
            explanation_str = '// {}'.format(explanation.replace("\n", "\n// "))
        res = concat(
            f'// [{name}]',
            '//  Input: {}'.format(input.replace("\n", "\n// ")),
            '// Output: {}'.format(output.replace("\n", "\n// ")),
            f'//',
            f'{explanation_str}',
            f'',
            f'LEETCODE_SOLUTION_UNITTEST({self._id}, {self._cpp_slug}, {suite_name}) {{',
            self._code_snippet.genUnitTest(input=input, output=output),
            f'}}',
            f'',
            f'',
        )
        return res

    def _defaultExamples(self) -> str:
        res = ""
        if not self._content_info:
            return res

        idx = 1
        for example in self._content_info.examples:
            res += self.getUnitTest(
                name=f'Example #{idx}',
                suite_name=f'example_{idx}',
                input=example.input,
                output=example.output,
                explanation=example.explanation
            )
            idx += 1

        return res

    def solutionTemplate(self) -> str:
        solution_body = self._existed_solution or (
            self._code_snippet and self._code_snippet.solutionDefine()) or ""

        class_name = "Solution"
        if self._code_snippet:
            class_name = self._code_snippet.getClassName()

        constrains_section = ""
        if self._content_info and len(self._content_info.constraints) > 0:
            constrains_section = concat(
                f'///////////////////////////////////////////////////////////////////////////////',
                f'// The following is test data for unit test.',
                f'// Note that inputs should be obey the constraints mentioned in LeetCode:',
                f'// * ' + concat(*[c.content for c in self._content_info.constraints], delimiter='\n// * '),
                f'///////////////////////////////////////////////////////////////////////////////',
            )

        description_section = ""
        if self._content_info:
            description_section = regex.sub('\n+$', '\n', self._content_info.description.content, regex.MULTILINE)
            description_section = regex.sub('\n+', '\n// ', description_section)
        else:
            description_section = "This question is marked as premium question."

        return concat(
            f'// Copyright {TODAY.year} Naon Lu',
            f'//',
            f'// ' + self._solutionInformation(prefix='// '),
            f'',
            self._includeHeaders(),
            f'// -- This header must be included after others --',
            f'#include "leetcode/testing/solution_test_helper.h"',
            f'',
            f'using namespace std;',
            f'using namespace lcd;',
            f'',
            f'// Description of |{self._id}. {self._title}|:',
            f'//',
            f'// {description_section}',
            f'',
            f'LEETCODE_BEGIN_RESOLVING({self._id}, {self._cpp_slug}, {class_name});',
            f'',
            f'' + solution_body,
            f'',
            f'LEETCODE_END_RESOLVING({class_name});',
            f'',
            constrains_section,
            f'',
            self._defaultExamples(),
            ''
        )


if __name__ == "__main__":
    import json, pprint
    import net
    from questions import *
    LOG = prompt.Log.getInstance(verbose=True)
    questions_list = QuestionsList(QUESTIONS_LIST_ABSOLUTE)

    id = int(sys.argv[1])
    slug = questions_list[id].slug


    state, resp = net.requestQuestionInformation(slug)

    if not(state == net.REQUEST_OK and \
            isinstance(resp, net.requests.Response) and resp.status_code == 200):
        LOG.failure("network error")
        sys.exit()

    raw_content = json.loads(resp.content.decode('utf-8'))['data']['question']
    cpp_solution = CPPSolution(raw_content)
    LOG.print(clangFormat(cpp_solution.solutionTemplate()))

    inp = inputByEditor(cpp_solution.genExtraInputPrompt(id=1, title="TwoSum"))
    input, expect = cpp_solution.parseExtraInput(inp)
    LOG.log(f'{input}, {expect}')

    if input and expect:
        LOG.print(cpp_solution.getUnitTest(name="Sample",
                suite_name="input_1", input=input, output=expect))
