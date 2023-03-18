#!/usr/bin/env python3
import regex
import sys
# prevent generating __pycache__
sys.dont_write_bytecode = True


from utils import *


class _QuestionContentInformation:

    class _QuestionDescription:
        def __init__(self) -> None:
            self.content: str = ""

        def __str__(self) -> str:
            return self.content

    class _QuestionExample:
        def __init__(self) -> None:
            self.input: str = ""
            self.output: str = ""
            self.explanation: str = ""

    class _QuestionConstraints:
        def __init__(self) -> None:
            self.content: str = ""

        def __str__(self) -> str:
            return self.content

    def __init__(self) -> None:
        self.description = _QuestionContentInformation._QuestionDescription()
        self.examples: list[_QuestionContentInformation._QuestionExample] = []
        self.constraints: list[_QuestionContentInformation._QuestionConstraints] = [
        ]


class QuestionContentAnalyzer:
    def __init__(self) -> None:
        assert False, "QuestionContentAnalyzer shouldn't be constructed."

    @staticmethod
    def _parseAndCutConstraintsSection(content, result: _QuestionContentInformation) -> str:
        LOG = prompt.Log.getInstance()
        con_regex = "[^\n]*Constraints:([\w\W]*)$"
        LOG.funcVerbose("parse the constraints section with regex: {}", con_regex)
        mat = regex.search(con_regex, content)
        if not mat:
            LOG.warn("constraint section not found.")
            return content
        content = regex.sub(con_regex, "", content)
        con_list_regex = "<li>([\w\W]*?)<\/li>"
        LOG.funcVerbose("find constraints section: {}", mat.group(1))
        LOG.funcVerbose("parse the constraints items with regex: {}", con_list_regex)
        for item in regex.findall(con_list_regex, mat.group(1)):
            LOG.funcVerbose("constraint found: {}", item)
            cons = _QuestionContentInformation._QuestionConstraints()
            cons.content = parseHtml(item)
            result.constraints.append(cons)
        return content

    @staticmethod
    def _parseExamplesSection(content: str, result: _QuestionContentInformation) -> str:
        LOG = prompt.Log.getInstance()
        reg = '[^\n]<strong(?: class="example")?>Example([\w\W]*)$'
        LOG.funcVerbose("parse the examples section with regex: {}", reg)
        mat = regex.search(reg, content)
        if not mat:
            LOG.warn("exmaples section not found.")
            return content

        content = regex.sub(reg, "", content)
        example_regex = "<pre>(?:[\w\W]*?)<(?:strong|b)>Input:? *<\/(?:strong|b)>([\w\W]*?)<(?:strong|b)>Output:? *<\/(?:strong|b)>([\w\W]*?)(?:<(?:strong|b)>Explanation:? *<\/(?:strong|b)>([\w\W]*?))?<\/pre>"
        LOG.funcVerbose("find examples section: {}", mat.group(1))
        LOG.funcVerbose("parse the examples items with regex: {}", example_regex)
        for item in regex.findall(example_regex, mat.group(1)):
            LOG.funcVerbose("example found: {}", item)
            example = _QuestionContentInformation._QuestionExample()
            example.input = parseHtml(str(item[0]).strip(), show_raw_data=True)
            example.output = parseHtml(str(item[1]).strip(), show_raw_data=True)
            example.explanation = parseHtml(str(item[2]).strip())
            result.examples.append(example)
        return content

    @staticmethod
    def parse(content: str) -> _QuestionContentInformation:
        THIS = QuestionContentAnalyzer
        result = _QuestionContentInformation()
        content = THIS._parseAndCutConstraintsSection(content, result)
        result.description.content = parseHtml(THIS._parseExamplesSection(content,
                                                                          result))
        return result


if __name__ == "__main__":
    import json
    import pprint
    import net
    from questions import *
    LOG = prompt.Log.getInstance(verbose=True)
    questions_list = QuestionsList(QUESTIONS_LIST_ABSOLUTE)

    id = int(sys.argv[1])
    slug = questions_list[id].slug

    state, resp = net.requestQuestionInformation(slug)

    if not (state == net.REQUEST_OK and
            isinstance(resp, net.requests.Response) and resp.status_code == 200):
        LOG.failure("network error")
        sys.exit()

    raw_content = json.loads(resp.content.decode('utf-8'))['data']['question']
    pprint.pprint(raw_content)
    res = QuestionContentAnalyzer.parse(raw_content["content"])
    LOG.success("parsed successfully.")

    LOG.log("Description:", flag=LOG.IMPORTANT)
    LOG.print(res.description)
    LOG.log("Examples:", flag=LOG.IMPORTANT)
    for e in res.examples:
        LOG.print(f"input: {e.input}")
        LOG.print(f"output: {e.output}")
        LOG.print(f"explanation: {e.explanation}")
        LOG.print("")
    LOG.log("Constraints:", flag=LOG.IMPORTANT)
    for c in res.constraints:
        LOG.print(f'  - {c}')
