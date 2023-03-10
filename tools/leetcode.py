#!/usr/bin/env python3
from functools import partial
from requests.cookies import RequestsCookieJar
import regex
import json
import requests
import sys
# prevent generating __pycache__
sys.dont_write_bytecode = True

import net
from utils import *

class QuestionOfToday:
    def __init__(self, content: object) -> None:
        self.id = int(content['frontendQuestionId'])
        self.paid_only = content['paidOnly']
        self.difficulty = content['difficulty']
        self.title = content['title']
        self.slug = content['titleSlug']


def getQuestionOfToday(*, timeout: int = 5) -> QuestionOfToday | None:
    LOG = prompt.Log.getInstance()

    state, resp = net.requestQuestionOfToday(timeout=timeout)
    if not (state == net.REQUEST_OK and
            isinstance(resp, net.requests.Response) and resp.status_code == 200):
        LOG.failure("network error")
        return None

    content = json.loads(resp.content.decode(
        'utf-8'))['data']['activeDailyCodingChallengeQuestion']['question']
    return QuestionOfToday(content)


class LeetCodeSession:

    LEETCODE_SESSION_KEY = "LEETCODE_SESSION"

    def __init__(self) -> None:
        LOG = prompt.Log.getInstance()
        self.__cookies: dict[str, str] = {}
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
        content = json.loads(resp.content.decode('utf-8'))['data']['userStatus']
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
        PARAMS = r'{"query":"\n    query questionOfToday {\n  activeDailyCodingChallengeQuestion {\n    question {\n      difficulty\n      frontendQuestionId: questionFrontendId\n      paidOnly: isPaidOnly\n      title\n      titleSlug\n      }\n  }\n}\n    ","variables":{}}'
        HEADERS = {
            'User-Agent': net.USER_AGENT,
            'Connection': 'keep-alive',
            'Content-Type': 'application/json',
            'Referer': net.ALL_PROBLEMS_URL
        }
        state, resp = net.requestGraphQL(
            PARAMS, headers=HEADERS, name="Request Question of Today", session=self.__session, cookies=self.__cookies)

        if state != net.REQUEST_OK or not isinstance(resp, requests.Response) or resp.status_code != 200:
            return None

        self.__updateCookies(resp.cookies)
        content = json.loads(resp.content.decode(
            'utf-8'))['data']['activeDailyCodingChallengeQuestion']['question']
        return QuestionOfToday(content)

    def clearLeetCodeSessionCache(self):
        LOG = prompt.Log.getInstance()
        LEETCODE_SESSION_ABSOLUTE.unlink(missing_ok=True)
        LOG.funcVerbose("removed the leetcode session cache.")

    def logout(self):
        del self.__cookies[self.LEETCODE_SESSION_KEY]
        self.clearLeetCodeSessionCache()
        self.__is_signed_in = False
        self.__login_as = ""

    def loginWithLeetCodeSession(self, *, use_cache: bool = True) -> bool:
        LOG = prompt.Log.getInstance()

        if not use_cache:
            self.clearLeetCodeSessionCache()

        if not self.__is_signed_in or not self.__login_as:
            if not LEETCODE_SESSION_ABSOLUTE.exists():
                LOG.funcVerbose("leetcode session not found.")
                if not LEETCODE_SESSION_ABSOLUTE.parent.exists():
                    LEETCODE_SESSION_ABSOLUTE.parent.mkdir(exist_ok=True)
                    LOG.funcVerbose("create a directory: {}",
                                    LEETCODE_SESSION_ABSOLUTE.parent)

                content = inputByEditor(concat(
                    f'',
                    f'',
                    f'# please enter the session cookie to sign in LeetCode site.',
                    f'# lines starting with \'#\' will be ignored.',
                ))
                content = regex.sub("^ *#[\w\W]*?\n*$",
                                    "", content, flags=regex.MULTILINE)
                content = content.strip()
                LEETCODE_SESSION_ABSOLUTE.write_text(content)

            TASK = LOG.createTaskLog("Login to LeetCode")
            TASK.begin("loading the session content...")
            session = LEETCODE_SESSION_ABSOLUTE.read_text()
            if not session:
                TASK.done("empty session content.", is_success=False)
                return False

            TASK.log("trying to initialize user data...")
            self.__cookies[self.LEETCODE_SESSION_KEY] = session

            if self.__initUserData():
                if self.__is_signed_in:
                    TASK.done("done.", is_success=True)
                else:
                    TASK.done("session expired.", is_success=False)
                    self.clearLeetCodeSessionCache()
            else:
                TASK.done("failed to request user data.", is_success=False)

        if self.__is_signed_in:
            LOG.success("signed in as: {}", LOG.format(
                self.__login_as, flag=LOG.HIGHTLIGHT | LOG.BOLD))
            return True
        return False


LOG = prompt.Log.getInstance(verbose=True)
session = LeetCodeSession()

q = session.getQuestionOfToday()
LOG.log(f'{q.id}')

LOG.log(session.loginWithLeetCodeSession())
