#!/usr/bin/env python3
from functools import partial
from requests.cookies import RequestsCookieJar
from enum import Enum
import regex
import json
import requests
import sys
# prevent generating __pycache__
sys.dont_write_bytecode = True

import net
from utils import *


class Submission:
    class Result(Enum):
        PASSED = 0
        NOT_SIGNED_IN = 1
        HTTP_ERROR = 2

        WRONG_ANSWER = 3
        RUNTIME_ERROR = 4
        COMPILE_ERROR = 5
        TLE_ERROR = 6
        UNDEFINED = 7

    def __init__(self, *, resp: requests.Response = None):
        LOG = prompt.Log.getInstance()
        self.result: Submission.Result = Submission.Result.NOT_SIGNED_IN
        self.error_msg: str = ""
        self.last_input: str = ""
        self.expect_output: str = ""
        if resp is not None:
            if resp.status_code != 200:
                LOG.funcVerbose("get status code: {}", resp.status_code)
                self.result = Submission.Result.HTTP_ERROR
                return

            content = json.loads(resp.content.decode('utf-8'))
            LOG.funcVerbose("get content: {}", resp.content.decode('utf-8'))
            msg = content["status_msg"]

            if msg == "Accepted":
                self.result = Submission.Result.PASSED
            elif msg == "Compile Error":
                self.result = Submission.Result.COMPILE_ERROR
                self.error_msg = content['compile_error']
            elif msg == "Runtime Error":
                self.result = Submission.Result.RUNTIME_ERROR
                self.error_msg = content['runtime_error']
            elif msg == "Wrong Answer":
                self.result = Submission.Result.WRONG_ANSWER
                self.last_input = content['last_testcase']
                self.expect_output = content['expected_output']
            elif msg == "Time Limit Exceeded":
                self.result = Submission.Result.TLE_ERROR
                self.last_input = content['last_testcase']
                self.expect_output = content['expected_output']
            else:
                self.result = Submission.Result.UNDEFINED

    def __bool__(self):
        return self.result == Submission.Result.PASSED


class LeetCodeSession:

    LEETCODE_SESSION_KEY = "LEETCODE_SESSION"
    FINISH = "Finish"

    class QuestionOfToday:
        def __init__(self, content: object) -> None:
            self.id = int(content['question']['frontendQuestionId'])
            self.paid_only = content['question']['paidOnly']
            self.difficulty = content['question']['difficulty']
            self.title = content['question']['title']
            self.slug = content['question']['titleSlug']
            self.done = content['userStatus'] == LeetCodeSession.FINISH

    def __init__(self) -> None:
        LOG = prompt.Log.getInstance()
        self.__cookies: dict[str, str] = {}
        self.__session_cache: Path = None
        self.__session = requests.session()
        self.__recaptcha_key: str = ""
        self.__is_signed_in: bool = False
        self.__login_as: str = ""

        TASK = LOG.createTaskLog("Establish LeetCode Session")

        TASK.begin("connecting to LeetCode...")
        self.__initWithHomePage()
        TASK.log("initializing...")
        self.__initWithGlobalData()
        TASK.done("established", is_success=True)

        for name, val in self.__cookies.items():
            LOG.funcVerbose("initialized cookies: {} = {}", name, val)
        LOG.funcVerbose("initialized recaptcha_key: {}", self.__recaptcha_key)

    def isSignedIn(self) -> bool:
        LOG = prompt.Log.getInstance()
        if self.__is_signed_in:
            self.__initUserData()

            if not self.__is_signed_in:
                LOG.log("logged out due to expired session.")
                self.logout()

        return self.__is_signed_in and self.__login_as != ""

    def getLogInName(self):
        return self.__login_as

    def __updateCookies(self, cookies: RequestsCookieJar):
        LOG = prompt.Log.getInstance()
        for cookie in cookies:
            LOG.funcVerbose("update cookie: {} = {}",
                            cookie.name, cookie.value)
            self.__cookies[cookie.name] = cookie.value

    def __request(self, req_func: Callable, callback: Callable) -> bool:
        resp: requests.Response = req_func()
        self.__updateCookies(resp.cookies)

        if resp.status_code != 200:
            return False

        callback and callback(resp)
        return True

    def __reqGet(self, url: str, *, headers: object, timeout: int = 5, callback: Callable = None) -> bool:
        return self.__request(partial(self.__session.get, url,
                                      headers=headers, timeout=timeout, cookies=self.__cookies), callback=callback)

    def __reqPost(self, url: str, *, headers: object, payload: str, timeout: int = 5, callback: Callable = None) -> bool:
        return self.__request(partial(self.__session.post, url, data=payload.encode('utf-8'),
                                      headers=headers, timeout=timeout, cookies=self.__cookies), callback=callback)

    def __initWithHomePage(self):
        HEADERS = {
            'User-Agent': net.USER_AGENT,
            'Content-Type': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7',
            'Referer': net.HOME_URL
        }
        while not self.__reqGet(net.HOME_URL, headers=HEADERS):
            pass

    def __handleGlobalData(self, resp: requests.Response):
        content = json.loads(resp.content.decode('utf-8'))['data']
        self.__recaptcha_key = content['recaptchaKey']

    def __initWithGlobalData(self):
        PARAMS = r'{"operationName":"globalData","variables":{},"query":"query globalData {\n  recaptchaKey\n  recaptchaKeyV2\n}\n"}'
        HEADERS = {
            'User-Agent': net.USER_AGENT,
            'Connection': 'keep-alive',
            'Content-Type': 'application/json',
            'Referer': net.HOME_URL
        }
        while not self.__reqPost(net.GRAPHQL_URL, headers=HEADERS, payload=PARAMS, callback=self.__handleGlobalData):
            pass

    def __handleUserData(self, resp: requests.Response):
        content = json.loads(resp.content.decode('utf-8')
                             )['data']['userStatus']
        self.__login_as = content['username']
        self.__is_signed_in = content['isSignedIn']

    def __initUserData(self):
        PARAMS = r'{"operationName":"globalData","variables":{},"query":"query globalData {\n  userStatus {\n    isSignedIn\n    isAdmin\n    isStaff\n    isSuperuser\n    isMockUser\n    isTranslator\n    isPremium\n    isVerified\n    checkedInToday\n    username\n    realName\n    avatar\n    optedIn\n    requestRegion\n    region\n    activeSessionId\n    permissions\n    notificationStatus {\n      lastModified\n      numUnread\n      __typename\n    }\n    completedFeatureGuides\n    __typename\n  }\n}\n"}'
        HEADERS = {
            'User-Agent': net.USER_AGENT,
            'Connection': 'keep-alive',
            'Content-Type': 'application/json',
            'Referer': net.HOME_URL
        }
        return self.__reqPost(net.GRAPHQL_URL, headers=HEADERS, payload=PARAMS, callback=self.__handleUserData)

    def getQuestionOfToday(self):
        PARAMS = r'{"query":"\n    query questionOfToday {\n  activeDailyCodingChallengeQuestion {\n    userStatus\n    question {\n      difficulty\n      frontendQuestionId: questionFrontendId\n      paidOnly: isPaidOnly\n      title\n      titleSlug\n      }\n  }\n}\n    ","variables":{}}'
        HEADERS = {
            'User-Agent': net.USER_AGENT,
            'Connection': 'keep-alive',
            'Content-Type': 'application/json',
            'Referer': net.ALL_PROBLEMS_URL
        }
        state, resp = net.requestGraphQL(
            PARAMS, headers=HEADERS, session=self.__session, cookies=self.__cookies)

        if state != net.REQUEST_OK or not isinstance(resp, requests.Response) or resp.status_code != 200:
            return None

        self.__updateCookies(resp.cookies)
        content = json.loads(resp.content.decode(
            'utf-8'))['data']['activeDailyCodingChallengeQuestion']
        return LeetCodeSession.QuestionOfToday(content)

    def clearLeetCodeSessionCache(self):
        LOG = prompt.Log.getInstance()
        assert self.__session_cache is not None
        self.__session_cache.unlink(missing_ok=True)
        LOG.funcVerbose("removed the leetcode session cache.")

    def logout(self):
        del self.__cookies[self.LEETCODE_SESSION_KEY]
        self.__is_signed_in = False
        self.__login_as = ""

    def loginWithLeetCodeSession(self, session: str, *, use_cache: bool = True) -> bool:
        LOG = prompt.Log.getInstance()

        CACHE_PATH = PROJECT_ROOT.joinpath(f'.{session}.session{LDTCONFIG_EXTENSION}')

        assert self.__session_cache is None or self.__session_cache == CACHE_PATH
        self.__session_cache = CACHE_PATH

        if not use_cache:
            self.clearLeetCodeSessionCache()

        if not self.__is_signed_in or not self.__login_as:
            if not self.__session_cache.exists():
                LOG.funcVerbose("leetcode session not found.")
                if not self.__session_cache.parent.exists():
                    self.__session_cache.parent.mkdir(exist_ok=True)
                    LOG.funcVerbose("create a directory: {}",
                                    self.__session_cache.parent)

                content = inputByEditor(concat(
                    f'',
                    f'',
                    f'# please enter the session cookie to sign in LeetCode site.',
                    f'# lines starting with \'#\' will be ignored.',
                ))
                content = regex.sub("^ *#[\w\W]*?\n*$",
                                    "", content, flags=regex.MULTILINE)
                content = content.strip()
                self.__session_cache.write_text(content)

            TASK = LOG.createTaskLog("Login to LeetCode")
            TASK.begin("loading the session content...")
            session = self.__session_cache.read_text()
            if not session:
                TASK.done("empty session content.", is_success=False)
                return False

            TASK.log("trying to initialize user data...")
            self.__cookies[self.LEETCODE_SESSION_KEY] = session

            if self.__initUserData():
                if self.__is_signed_in:
                    TASK.done("signed in as: {}", LOG.format(
                        self.__login_as, flag=LOG.HIGHTLIGHT | LOG.BOLD), is_success=True)
                else:
                    TASK.done("session expired.", is_success=False)
                    self.clearLeetCodeSessionCache()
            else:
                TASK.done("failed to request user data.", is_success=False)

        return self.__is_signed_in

    def submitSolution(self, *, backend_id: int, slug: str, content: str) -> Submission:
        LOG = prompt.Log.getInstance()
        if not self.isSignedIn():
            return Submission()

        PROBLEM_PAGE = net.getProblemURL(slug)

        LOG.funcVerbose(
            "trying to submit the solution for: {}. {}\n {}", backend_id, slug, content)

        PARAMS = {
            "lang": "cpp",
            "question_id": backend_id,
            "typed_code": content
        }

        HEADERS = {
            'User-Agent': net.USER_AGENT,
            'Connection': 'keep-alive',
            'Content-Type': 'application/json',
            'Referer': PROBLEM_PAGE,
            'Origin': net.HOME_URL,
        }

        self.__reqGet(PROBLEM_PAGE, headers=HEADERS)

        HEADERS["x-csrftoken"] = self.__cookies['csrftoken']
        REQ = partial(self.__session.post, url=net.getSubmitUrl(
            slug), headers=HEADERS, data=json.dumps(PARAMS).encode('utf-8'), cookies=self.__cookies)
        stat, resp = net.safeRequest(REQ)

        if stat != net.REQUEST_OK or not isinstance(resp, requests.Response) or resp.status_code != 200:
            return Submission(resp)

        self.__updateCookies(resp.cookies)

        SUBMISSION_ID = json.loads(
            resp.content.decode('utf-8'))['submission_id']
        LOG.funcVerbose("got submission id: {}", SUBMISSION_ID)

        result = None
        while result is None:
            time.sleep(1.5)
            HEADERS["x-csrftoken"] = self.__cookies['csrftoken']
            REQ = partial(self.__session.get, url=net.getSubmissionCheckUrl(
                SUBMISSION_ID), headers=HEADERS, cookies=self.__cookies)
            stat, resp = net.safeRequest(REQ)
            if stat != net.REQUEST_OK or not isinstance(resp, requests.Response) or resp.status_code != 200:
                continue
            resp_content = json.loads(resp.content.decode('utf-8'))
            LOG.funcVerbose("got submission state: {}", resp_content['state'])

            if resp_content['state'] != "PENDING":
                result = Submission(resp=resp)

        return result


if __name__ == "__main__":
    LOG = prompt.Log.getInstance(verbose=True)
    session = LeetCodeSession()

    LOG.log(session.loginWithLeetCodeSession())
    # q = session.getQuestionOfToday()
    # LOG.log(f'question of today: {q.id}')
    # LOG.log(f'is finished      : {q.done}')

    # ans = '''class Solution {
    # public:
    #     vector<int> twoSum(vector<int>& nums, int target) {
    #         return vector<int>{-1, -1};
    #     }
    # };'''

    # r = session.submitSolution(id=1, slug='two-sum', content=ans)
    # LOG.log('get result: {}', r.result)
