#!/usr/bin/env python3
import sys
import json
import regex
# prevent generating __pycache__
sys.dont_write_bytecode = True


from impl import *
from cpp_solution import *
from questions import *
from filesystem import *
from utils import *


def _getComplexityInformation(id: int, snippets: str, tc: str, sc: str, notes: str):
    init_msg = [
        f'# The Solution #{id} requires complexities information.',
        f'# Time complexity in the first line:',
        f'# O(',
        f'{tc}',
        f'# )',
        f'',
        f'# Space complexity in the second line:',
        f'# O(',
        f'{sc}',
        f'# )',
        f'',
        f'# Notes in third line if necessary:',
        f'{notes}',
        f'',
        f'# The solution is as follows',
        '# {}'.format(snippets.replace('\n', '\n# '))
    ]
    user_input = inputByEditor('\n'.join(init_msg))
    input_lines = user_input.splitlines()
    if len(input_lines) > 2:
        complexities = []
        for line in input_lines:
            line = line.strip()
            if len(line) > 0 and line[0] != "#":
                complexities.append(line)
        if len(complexities) == 2:
            return complexities[0], complexities[1], ""
        if len(complexities) == 3:
            return complexities[0], complexities[1], complexities[2]
    return "-", "-", ""


LOG = prompt.Log.getInstance(verbose=False)
PMT = prompt.Prompt.getInstance()

OLD_SRC_PATH = PROJECT_ROOT.joinpath("src.old")
RESOLVE_LOG = SRC_ABSOLUTE.joinpath("solution_logs.csv")

old_logs = ResolveLogsFile(QUESTIONS_LOG_ABSOLUTE)
qlist = QuestionsList(QUESTIONS_LIST_ABSOLUTE)
new_logs = ResolveLogsFile(RESOLVE_LOG)

LOG.log("loaded {} questions details from: {}",
        LOG.format(len(qlist), flag=LOG.HIGHTLIGHT),
        LOG.format(QUESTIONS_LIST_ABSOLUTE, flag=LOG.HIGHTLIGHT))

migrated_ids = set([l.id for l in new_logs.data()])
LOG.log("left {} solutions to migrate.", LOG.format(
    len(old_logs) - len(migrated_ids), flag=LOG.HIGHTLIGHT))

try:
    for lg in old_logs.data():
        if lg.id in migrated_ids:
            LOG.log("skip id {} since it has migrated.",
                    LOG.format(lg.id, flag=LOG.HIGHTLIGHT))
            continue

        LOG.log("migrating id {}.", LOG.format(lg.id, flag=LOG.HIGHTLIGHT))

        old_src = SolutionFile(lg.id, OLD_SRC_PATH)
        new_src = SolutionFile(lg.id, SRC_ABSOLUTE)

        raw_content: object = None
        slug = qlist[lg.id].slug
        try_cnt = 0
        while True:
            LOG.verbose(
                "trying to get the information about question #{} from LeetCode.", id)
            state, resp = net.requestQuestionInformation(slug)

            if state == net.REQUEST_OK and \
                    isinstance(resp, net.requests.Response) and resp.status_code == 200:

                LOG.verbose("trying to parse the response content.")
                raw_content = json.loads(
                    resp.content.decode('utf-8'))['data']['question']
                LOG.verbose("got and parsed the questions list from LeetCode.")
                break
            else:
                PMT = prompt.Prompt.getInstance()
                if not PMT.ask("failed to get questions list, try again{}?",
                               "" if try_cnt == 0 else f" ({try_cnt})"):
                    LOG.log("skipped getting questions list.")
                    break
            try_cnt += 1

        LOG.log("generate the CPP solution file.")
        header = set([])
        solution_source = parseSolution(old_src.read_text())

        if regex.search("unordered_map", solution_source):
            header.add("<unordered_map>")
        if regex.search("unordered_set", solution_source):
            header.add("<unordered_set>")
        if regex.search("map", solution_source):
            header.add("<map>")
        if regex.search("set", solution_source):
            header.add("<set>")
        if regex.search("(?:priority_)?queue", solution_source):
            header.add("<queue>")
        if regex.search("stack", solution_source):
            header.add("<stack>")
        if regex.search("list", solution_source):
            header.add("<list>")
        if regex.search("numeric_limits", solution_source):
            header.add("<limits>")
        if regex.search("sort", solution_source):
            header.add("<algorithm>")
        if regex.search("unique_ptr", solution_source):
            header.add("<memory>")
        if regex.search("array", solution_source):
            header.add("<array>")


        cpp_solution = CPPSoltuion(raw_content,
                                   timestamp=lg.timestamp,
                                   existed_solution=solution_source,
                                   headers=header)

        src_parent = new_src.parent
        if not src_parent.exists():
            LOG.log("create directory: {}", LOG.format(src_parent, flag=LOG.HIGHTLIGHT))
            src_parent.mkdir(exist_ok=True)
        new_src.write_text(clangFormat(cpp_solution.solutionTemplate()))

        ldtGenImpl(src_path=PROJECT_ROOT,
                   build_path=BUILD_ABSOLUTE,
                   build_flag="Debug",
                   compile_commands_flag="ON",
                   leetcode_test_flag="ON",
                   infra_test_flag="ON")
        LOG.log("try to run test.")
        passed = False

        while not passed:
            try:
                passed = ldtBuildImpl(build_path=BUILD_ABSOLUTE) == 0 and \
                    ldtRunImpl(build_path=BUILD_ABSOLUTE,
                               infra_test=False, ids=[lg.id]) == 0
            except InterruptedError:
                pass

            if not passed:
                if not PMT.ask("continue?"):
                    sys.exit()
                openEditor(new_src)

        tc, sc, notes = \
            _getComplexityInformation(lg.id,
                                        clangFormat(parseSolution(new_src.read_text())),
                                        lg.tc, lg.sc, lg.notes)
        lg.tc = tc
        lg.sc = sc
        lg.notes = notes

        msg = f"migrated q{lg.id}"
        if lg.tc != "-" and lg.sc != "-":
            msg += f" with TC O({lg.tc}) and SC O({lg.sc})"
            if lg.notes != "":
                msg += f", {lg.notes}"
        msg += "."

        new_logs.addLog(lg)
        new_logs.save()
        LOG.success("{}", LOG.format(msg, flag=LOG.IMPORTANT))


except KeyboardInterrupt:
    LOG.log("interrupted by user.")

new_logs.save()
