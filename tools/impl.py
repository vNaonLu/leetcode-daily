#!/usr/bin/env python3
import sys
import shutil
from platform import system
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from logs import *
from refs import *
from filesystem import *
from questions import *
import net


def __logListToCntList(logs: list[list[list[ResolveLog]]]):
    return [[len(d) for d in m] for m in logs]


def __flatAnnualLogs(year_logs):
    res = []
    for _, month_log in year_logs:
        month = []
        for _, day_log in month_log:
            month.append(day_log)
        res.append(month)
    return res


def __getLatestDayLogs(logs: ResolveLogsList, days: int):
    res = []
    earliest = sys.maxsize
    for y, year_log in reversed(logs):
        for m, month_log in reversed(year_log):
            month = []
            for d, day_log in reversed(month_log):
                earliest = min([earliest] + [q.timestamp for q in day_log])
                month.append(day_log)
                days -= 1
                if days == 0:
                    break
            month.reverse()
            res.append(month)
            if days == 0:
                return earliest, res
    return earliest, res


def updateQuestionsListImpl(*, questions_list: QuestionsList, list_path: Path):
    import json
    LOG = prompt.Log.getInstance()
    raw_list: list[object] = None
    try_cnt = 0
    while True:
        LOG.verbose("trying to get the questions list from LeetCode.")
        state, resp = net.requestQuestionsList()

        if state == net.REQUEST_OK and \
                isinstance(resp, net.requests.Response) and resp.status_code == 200:

            LOG.verbose("trying to parse the response content.")
            raw_list = json.loads(resp.content.decode('utf-8'))
            raw_list = raw_list["stat_status_pairs"]

            LOG.verbose("got and parsed the questions list from LeetCode.")
            break
        else:
            PMT = prompt.Prompt.getInstance()
            if not PMT.ask("failed to get questions list, try again{}?", "" if try_cnt == 0 else f" ({try_cnt})"):
                LOG.log("skipped getting questions list.")
                break
        try_cnt += 1

    raw_list.sort(key=lambda q: q['stat']['frontend_question_id'])

    if raw_list == None or len(questions_list) == len(raw_list):
        LOG.log("no new question found, skipped append question list.")
    else:
        LOG.log("{} new questions found, append to the questions list.",
                LOG.format(len(raw_list) - len(questions_list), flag=LOG.HIGHTLIGHT))

        for info in raw_list:
            ID = info['stat']['frontend_question_id']
            if ID not in questions_list:
                detail = QuestionDetails()
                detail.id = ID
                detail.backend_id = info['stat']['question_id']
                detail.title = info['stat']['question__title']
                detail.level = info['difficulty']['level']
                detail.slug = info['stat']['question__title_slug']
                detail.paid = info['paid_only']
                questions_list[ID] = detail

    def compareAndReturn(id: int, label: str, old, new):
        if old != new:
            LOG.log("update question #{}'s {}: {} => {}",
                    LOG.format(id, flag=LOG.HIGHTLIGHT), label, old, new)
        return new

    for info in raw_list:
        ID = info['stat']['frontend_question_id']
        DETAIL = questions_list[ID]
        DETAIL.backend_id = compareAndReturn(ID, "backend id", DETAIL.backend_id,
                                             info['stat']['question_id'])
        DETAIL.title = compareAndReturn(ID, "title", DETAIL.title,
                                        info['stat']['question__title'])
        DETAIL.level = compareAndReturn(ID, "difficulty", DETAIL.level,
                                        info['difficulty']['level'])
        DETAIL.slug = compareAndReturn(ID, "slug", DETAIL.slug,
                                       info['stat']['question__title_slug'])
        DETAIL.paid = compareAndReturn(ID, "paid info", DETAIL.paid,
                                       info['paid_only'])

    if not questions_list.isGood():
        LOG.failure("refused to update due to invalid questions list.")
        return False

    LOG.verbose("saving the questions list to: ", list_path)
    if not questions_list.save(list_path):
        LOG.failure("failed to save the question list.")
        return False
    LOG.success("saved the question list: {}",
                LOG.format(list_path, flag=LOG.HIGHTLIGHT))
    return True


def updateResolveReferenceImpl(*, docs_path: Path, assets_path: Path, src_path: Path, questions_list: QuestionsList, resolve_logs: ResolveLogsList):
    assert docs_path.exists() and docs_path.is_dir()
    assert assets_path.exists() and assets_path.is_dir()
    assert src_path.exists() and src_path.is_dir()
    LOG = prompt.Log.getInstance()

    cnt_by_level = [0, 0, 0]
    cnt_solved_by_level = [0, 0, 0]
    unsolved_details: dict[int, QuestionDetails] = {}

    for detail in questions_list:
        unsolved_details[detail.id] = detail
        if not detail.paid:
            cnt_by_level[detail.level - 1] += 1

    for resolve_log in resolve_logs.data():
        detail = questions_list[resolve_log.id]
        cnt_solved_by_level[detail.level - 1] += 1
        del unsolved_details[detail.id]

    LOG.log("loaded {} free questions with {} easy, {} medium and {} hard.",
            LOG.format(sum(cnt_by_level), flag=LOG.HIGHTLIGHT),
            LOG.format(cnt_by_level[0], flag=LOG.HIGHTLIGHT),
            LOG.format(cnt_by_level[1], flag=LOG.HIGHTLIGHT),
            LOG.format(cnt_by_level[2], flag=LOG.HIGHTLIGHT))

    LOG.verbose("update annual resolved references.")
    for y, year_logs in resolve_logs:
        LOG.verbose("generate the {} annual reference.", y)
        doc_file = docs_path.joinpath(f"{y}.md")
        chart_file = assets_path.joinpath(f"{y}_activity.svg")

        annual_logs = __flatAnnualLogs(year_logs)
        chart = ActivityChart(light_title="Activity",
                              orange_title="",
                              begin_time=calendar.timegm(
                                  date(y, 1, 1).timetuple()),
                              solved_array=__logListToCntList(annual_logs))
        chart.save(chart_file)
        LOG.success("saved {} annual activity chart: {}",
                    LOG.format(y, flag=LOG.HIGHTLIGHT),
                    LOG.format(chart_file, flag=LOG.HIGHTLIGHT))

        # TODO: relative directory
        doc = AnnualResolveDocument(year=y, year_log=year_logs,
                                    questions_list=questions_list, src_path="../src")
        doc.save(doc_file)
        LOG.success("saved {} annual documents: {}",
                    LOG.format(y, flag=LOG.HIGHTLIGHT),
                    LOG.format(doc_file, flag=LOG.HIGHTLIGHT))

    LOG.verbose("update summary resolved references.")
    earliest, latest_logs = __getLatestDayLogs(resolve_logs, 365)

    latest_logs.reverse()
    recent_activity_chart_name = assets_path.joinpath("recent_activity.svg")
    recent_activity_chart = ActivityChart(light_title="Recent Activity within",
                                          orange_title="365 Days",
                                          begin_time=earliest,
                                          solved_array=__logListToCntList(latest_logs))

    recent_activity_chart.save(recent_activity_chart_name)
    LOG.success("saved the recent activity chart: {}",
                LOG.format(recent_activity_chart_name, flag=LOG.HIGHTLIGHT))

    problem_resolve_progress_name = assets_path.joinpath("progress.svg")
    solved_doc_name = docs_path.joinpath("solved_solutions.md")
    unsolved_doc_name = docs_path.joinpath("unsolved_solutions.md")
    problem_resolve_progress = ProblemResolveProgress(
        cnt_solved_by_level, cnt_by_level)
    solved_doc = SolvedDocument(
        questions_list=questions_list,
        resolve_logs=resolve_logs.data(),
        src_path="../src")
    unsolved_doc = UnsolvedDocument(unsolved_details=unsolved_details.values())

    problem_resolve_progress.save(problem_resolve_progress_name)
    LOG.success("saved the problems resolve progress: {}",
                LOG.format(problem_resolve_progress_name, flag=LOG.HIGHTLIGHT))
    solved_doc.save(solved_doc_name)
    LOG.success("saved the solved document: {}",
                LOG.format(solved_doc_name, flag=LOG.HIGHTLIGHT))
    unsolved_doc.save(unsolved_doc_name)
    LOG.success("saved the unsolved document: {}",
                LOG.format(unsolved_doc_name, flag=LOG.HIGHTLIGHT))
    return True


def updateReadmeDocument(*, resolve_logs: ResolveLogsList, assets_path: Path, docs_path: Path, readme_path: Path):
    assert docs_path.exists() and docs_path.is_dir()
    assert assets_path.exists() and assets_path.is_dir()
    LOG = prompt.Log.getInstance()

    README = Readme(docs_path=docs_path,
                    assets_path=assets_path,
                    resolve_logs=resolve_logs)
    README.save(readme_path)
    LOG.success("saved the readme: {}",
                LOG.format(readme_path, flag=LOG.HIGHTLIGHT))
    return True


def ldtCatImpl(*, id: int, src_path: Path):
    LOG = prompt.Log.getInstance()
    ARG_ID = id
    ARG_SRC_PATH = src_path

    LOG.log("collecting the details for the solution of question #{}.",
            LOG.format(ARG_ID, flag=LOG.HIGHTLIGHT))
    qf = SolutionFile(ARG_ID, ARG_SRC_PATH)

    LOG.verbose("cat LeetCode solution...")
    LOG.verbose("[source detail beg]")
    LOG.verbose(" - id     : {}", qf.id())
    LOG.verbose(" - target : {}", qf)
    LOG.verbose("[source detail end]")
    LOG.verbose("checking whether the solution exists: {}", qf)

    if not qf.exists():

        LOG.failure("questions #{} is not resolved yet.",
                    LOG.format(ARG_ID, flag=LOG.HIGHTLIGHT))
        return 1

    LOG.verbose("target found and trying to get solution snippet.")

    with qf.open('r') as f:

        LOG.verbose("solution file opened.")

        code_buf = f.read()
        snippet = parseSolution(code_buf)

        if not snippet:
            LOG.failure("failed to parse the solution from file: {}", qf)
            return 1

        solution = clangFormat(snippet)
        LOG.success("the solution for question #{} found:",
                    LOG.format(ARG_ID, flag=LOG.HIGHTLIGHT))
        LOG.print(solution, flag=LOG.DARK_GREEN)

    return 0


def ldtGenImpl(*, src_path: Path, build_path: Path, build_flag: str, compile_commands_flag: str, leetcode_test_flag: str, infra_test_flag: str):
    LOG = prompt.Log.getInstance()
    ARG_SRC_PATH = src_path
    ARG_BUILD_PATH = build_path
    ARG_BUILD_FLAG = build_flag
    ARG_COMPILE_COMMAND_FLAG = compile_commands_flag
    ARG_LEETCODE_TEST_FLAG = leetcode_test_flag
    ARG_INFRA_TEST_FLAG = infra_test_flag

    LOG.verbose(
        "checking whether the CMakeLists.txt exists in the directory: {}", ARG_SRC_PATH)
    if not ARG_SRC_PATH.joinpath("CMakeLists.txt").exists():
        LOG.failure(
            "there is no |CMakeLists.txt| exists in the directory: {}", ARG_SRC_PATH)
        return 1

    cmake = findExecutable("cmake")

    if not cmake:
        LOG.failure("cmake not found.")
        return 1

    CMD = [
        cmake, "-S", ARG_SRC_PATH, "-B", ARG_BUILD_PATH,
        f"-DCMAKE_EXPORT_COMPILE_COMMANDS={ARG_COMPILE_COMMAND_FLAG}",
        f"-DCMAKE_BUILD_TYPE={ARG_BUILD_FLAG}",
        f"-DENABLE_LEETCODE_TEST={ARG_LEETCODE_TEST_FLAG}",
        f"-DENABLE_INFRA_TEST={ARG_INFRA_TEST_FLAG}",
    ]

    LOG.log("generate CMake build files with flag: {}", LOG.format(
        f"-DCMAKE_BUILD_TYPE={ARG_BUILD_FLAG}", flag=LOG.HIGHTLIGHT))
    if ARG_COMPILE_COMMAND_FLAG == "ON":
        LOG.log("generate CMake build files with flag: {}", LOG.format(
            f"-DCMAKE_EXPORT_COMPILE_COMMANDS={ARG_COMPILE_COMMAND_FLAG}", flag=LOG.HIGHTLIGHT))

    if ARG_LEETCODE_TEST_FLAG == "ON":
        LOG.log("generate CMake build files with flag: {}", LOG.format(
            f"-DENABLE_LEETCODE_TEST={ARG_LEETCODE_TEST_FLAG}", flag=LOG.HIGHTLIGHT))

    if ARG_INFRA_TEST_FLAG == "ON":
        LOG.log("generate CMake build files with flag: {}", LOG.format(
            f"-DENABLE_INFRA_TEST={ARG_INFRA_TEST_FLAG}", flag=LOG.HIGHTLIGHT))

    TASK = LOG.createTaskLog("Generate Build Files")

    def stdoutCallback(out: str):
        TASK.log(parseCMakeGenarateLog(out))
        LOG.verbose(out)

    with launchSubprocess(CMD) as proc:
        TASK.begin()
        asyncStdout(proc, stdoutCallback)

        if proc.poll() != 0:
            TASK.done("failed to generate the build files.", is_success=False)
            LOG.print(proc.stderr.read(), flag=LOG.VERBOSE)
            return 1

        TASK.done(is_success=True)

    if ARG_COMPILE_COMMAND_FLAG == "ON":
        compile_commands = ARG_BUILD_PATH.joinpath("compile_commands.json")
        if compile_commands.exists():
            shutil.copy2(compile_commands, PROJECT_ROOT)

    return 0


def ldtBuildImpl(*, build_path: Path, build_args: str = ""):
    LOG = prompt.Log.getInstance()
    ARG_BUILD_PATH = build_path
    ARG_BUILD_ARGS = build_args

    LOG.verbose("check whether the directory exists: {}", ARG_BUILD_PATH)

    if not ARG_BUILD_PATH.exists():
        LOG.failure("the directory not found: {}", ARG_BUILD_PATH)
        return 1

    cmake = findExecutable("cmake")

    if not cmake:
        LOG.failure("cmake not found.")
        return 1

    CMD = [cmake, "--build", ARG_BUILD_PATH, "--"]
    build_args = ARG_BUILD_ARGS.split()

    if len(build_args) > 0:
        CMD += build_args

    TASK = LOG.createTaskLog("Build Project")

    def stdoutCallback(out: str):
        percent, msg = parseBuildLog(out)
        if percent != None and msg != None:
            TASK.log(msg, percent=percent)
        LOG.verbose(out)

    try:
        with launchSubprocess(CMD) as proc:
            TASK.begin()
            asyncStdout(proc, stdoutCallback)

            if proc.poll() != 0:
                TASK.done("failed to build in {}.",
                          ARG_BUILD_PATH, is_success=False)
                LOG.print(proc.stderr.read(), flag=LOG.VERBOSE)
                return 1

            TASK.done("successfully built in {}.",
                      ARG_BUILD_PATH, is_success=True)
            return 0
    except KeyboardInterrupt:
        if TASK.isActive():
            TASK.done("interrupted by user.", is_success=False)
        return 1


def ldtRunImpl(*, build_path: Path, infra_test: bool, ids: list[int] = []):
    LOG = prompt.Log.getInstance()
    ARG_BUILD_PATH = build_path
    ARG_INFRA_TEST = infra_test
    ARG_IDS = ids

    LOG.verbose("check whether the directory exists: {}", ARG_BUILD_PATH)

    if not ARG_BUILD_PATH.exists():
        LOG.failure("the directory not found: {}", ARG_BUILD_PATH)
        return 1

    with chDir(ARG_BUILD_PATH):

        executable_name = ARG_BUILD_PATH

        if ARG_INFRA_TEST:
            LOG.verbose("run the infrastructure unit tests.")
            executable_name = "leetcode_helper_test"
        else:
            LOG.verbose("run the LeetCode solution unit tests.")
            executable_name = "leetcode_test"

        if system() == "Windows":
            executable_name += ".exe"

        executable = ARG_BUILD_PATH.joinpath(executable_name)

        LOG.verbose("check whether the executable exists: {}", executable)

        if not executable.exists():
            LOG.failure("the target executable not found: {}", executable)
            LOG.print("please run |ldt build| first.")
            return 1

        CMD = [executable]

        if len(ARG_IDS) > 0:
            if ARG_INFRA_TEST:
                LOG.warn("discard the specified ids due to |--infra| enabled")
                ARG_IDS = []
            else:
                solutions = [f'q{id}_*' for id in ARG_IDS]
                CMD.append("--gtest_filter={}".format(":".join(solutions)))

        TASK = LOG.createTaskLog("Run Tests")

        PROCESS_RAN_TIMEOUT = -999

        with launchSubprocess(CMD) as proc:
            TASK.begin("running the unittests...")
            returncode = 0
            result = ""

            try:
                result, _ = proc.communicate(timeout=10)
                returncode = proc.wait()
            except subprocess.TimeoutExpired:
                TASK.log("aborting process due to timeout...")
                proc.kill()
                result, _ = proc.communicate()
                returncode = PROCESS_RAN_TIMEOUT

            TASK.log("analyzing the test logs...")
            LOG.funcVerbose(f'\n{result}')

            skipped_cases = regex.findall('^\[  SKIPPED \] ([\w_.]+)$', result, regex.MULTILINE)
            skipped_ids = set([int(regex.search('q(\d+)_\w+\.\w+', test).group(1)) for test in skipped_cases])

            if returncode == 0:
                missing_ids = []
                if not infra_test and len(ARG_IDS) > 0:
                    passed_ids = set([int(d) for d in regex.findall('\[       OK \] q(\d+)_\w+\.\w+ \(\d+ ms\)', result)])
                    LOG.funcVerbose("passed ids: {}", passed_ids)
                    LOG.funcVerbose("skipped ids: {}", skipped_ids)
                    for id in ARG_IDS:
                        if id not in passed_ids and id not in skipped_ids:
                            LOG.failure("the unittest for solution #{} not found.", LOG.format(
                                id, flag=LOG.HIGHTLIGHT))
                            missing_ids.append(str(id))
                if len(missing_ids) == 0:
                    TASK.done("all unittests passed.", is_success=True)
                else:
                    TASK.done("missing unittests for solution(s): {}", ', '.join(missing_ids), is_success=False)
                    returncode = 1
            else:
                failed_tests = regex.findall('^\[  FAILED  \] ([\w_.]+)$', result, regex.MULTILINE)
                failed_ids = set([int(regex.search('q(\d+)_\w+\.\w+', test).group(1)) for test in failed_tests])

                LOG.failure("the following test(s) ran failed:")
                for test in failed_tests:
                    id = regex.search('q(\d+)_\w+\.\w+', test).group(1)
                    fid = LOG.format(id, flag=LOG.HIGHTLIGHT)
                    LOG.log(' - {}', regex.sub(f'q{id}_', f'q{fid}_', test))
                    LOG.print(parseFailedBlock(result, test), flag=LOG.VERBOSE)

                target_failed = []
                if not infra_test and len(ARG_IDS) > 0:
                    target_failed = list(filter(lambda d : d in failed_ids, ARG_IDS))

                if len(target_failed) == 0:
                    TASK.done("some unittest(s) ran failed.", is_success=False)
                else:
                    TASK.done("failed to pass unittest(s) for solutions: {}", ', '.join(
                        [str(d) for d in target_failed]), is_success=False)

            if len(skipped_cases) > 0:
                LOG.warn("the following test(s) have been skipped:")
                for test in skipped_cases:
                    id = regex.search('q(\d+)_\w+\.\w+', test).group(1)
                    fid = LOG.format(id, flag=LOG.HIGHTLIGHT)
                    LOG.log(' - {}', regex.sub(f'q{id}_', f'q{fid}_', test))

            return returncode


def ldtRemoveImpl(*, src_path: Path, resolve_logs: ResolveLogsFile, ids: list[int]):
    LOG = prompt.Log.getInstance()
    ARG_SRC_PATH = src_path
    ARG_IDS = ids

    logs_remove_cnt = 0
    for id in ARG_IDS:
        LOG.verbose("check whether the solution with id {} exists.", id)
        rm_file = LOG.createTaskLog(f"Remove Solution #{id}")
        rm_file.begin("searching in: {}", ARG_SRC_PATH)
        target_file = SolutionFile(id, ARG_SRC_PATH)
        if not target_file.exists():
            rm_file.done("the solution #{} not found: {}",
                         LOG.format(id, flag=LOG.HIGHTLIGHT),
                         LOG.format(target_file, flag=LOG.HIGHTLIGHT), is_success=False)
        else:
            target_file.unlink(missing_ok=True)
            rm_file.done("the solution #{} has been removed: {}",
                         LOG.format(id, flag=LOG.HIGHTLIGHT),
                         LOG.format(target_file, flag=LOG.HIGHTLIGHT), is_success=True)

        rm_logs = LOG.createTaskLog(f"Remove Resolve Logs #{id}")
        rm_logs.begin("searching in resolve logs: {}", resolve_logs)
        if not resolve_logs.removeById(id):
            rm_logs.done("the resolve log for solution #{} not found.",
                         LOG.format(id, flag=LOG.HIGHTLIGHT), is_success=False)
        else:
            rm_logs.done("the resolve log for solution #{} has been removed.",
                         LOG.format(id, flag=LOG.HIGHTLIGHT), is_success=True)
            logs_remove_cnt += 1

    if logs_remove_cnt > 0:
        resolve_logs.save()
        LOG.success("the resolve log has been saved: {}",
                    LOG.format(resolve_logs, flag=LOG.HIGHTLIGHT))
    return 0
