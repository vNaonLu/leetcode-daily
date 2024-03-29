#!/usr/bin/env python3
from functools import partial
from typing import Callable
import json
import sys
import requests
import browser_cookie3
# prevent generating __pycache__
sys.dont_write_bytecode = True

import prompt

_LEETCODE_QUESTIONS_QUERY_URL = "https://leetcode.com/api/problems/all/"
HOME_URL = 'https://leetcode.com/'
LOGIN_URL = 'https://leetcode.com/accounts/login/'
ALL_PROBLEMS_URL = 'https://leetcode.com/problemset/all'
GRAPHQL_URL = 'https://leetcode.com/graphql'
PROBLEM_URL = 'https://leetcode.com/problems/{}/'
SUBMIT_URL = 'https://leetcode.com/problems/{}/submit/'
SUBMISSION_CHECK_URL = 'https://leetcode.com/submissions/detail/{}/check/'
USER_AGENT = r'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/111.0.0.0 Safari/537.36'

REQUEST_OK = 0
REQUEST_TIMEOUT = 1
REQUEST_FAILED = 2


def __toString(state: int):
    global REQUEST_OK, REQUEST_TIMEOUT, REQUEST_FAILED
    if state == REQUEST_OK:
        return "OK"
    elif state == REQUEST_TIMEOUT:
        return "Timed Out"
    elif state == REQUEST_FAILED:
        return "Failure"
    assert False


def getProblemURL(slug: str):
    return PROBLEM_URL.format(slug)


def getSubmitUrl(slug: str):
    return SUBMIT_URL.format(slug)


def getSubmissionCheckUrl(submission_id: str):
    return SUBMISSION_CHECK_URL.format(submission_id)


def safeRequest(func: Callable):
    LOG = prompt.Log.getInstance()

    try:
        resp = func()
        LOG.funcVerbose("request succeeded.")
        return REQUEST_OK, resp
    except requests.exceptions.Timeout:
        LOG.funcVerbose("request timed out.")
        return REQUEST_TIMEOUT, None
    except requests.exceptions.RequestException as e:
        LOG.funcVerbose("failed to request: {}", e)
        return REQUEST_FAILED, None


__QUESTIONS_LIST_CACHE = None


def requestQuestionsList(timeout: int = 5):
    global __QUESTIONS_LIST_CACHE
    LOG = prompt.Log.getInstance()

    if __QUESTIONS_LIST_CACHE:
        LOG.funcVerbose("cached questions list found. skip the request.")
        return REQUEST_OK, __QUESTIONS_LIST_CACHE

    LOG.funcVerbose("cached questions list not found.")

    URL = _LEETCODE_QUESTIONS_QUERY_URL
    HEADERS = {
      'User-Agent': USER_AGENT,
      'Connection': 'keep-alive',
      'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7',
      'Sec-Ch-Ua': '"Not A(Brand";v="99", "Google Chrome";v="121", "Chromium";v="121"',
      'Sec-Ch-Ua-Mobile': '?0',
      'Sec-Ch-Ua-Platform': '"macOS"',
      'Sec-Fetch-Dest': 'document',
      'Sec-Fetch-Mode': 'navigate',
      'Sec-Fetch-Site': 'none',
      'Sec-Fetch-User': '?1',
      'Upgrade-Insecure-Requests': '1'}

    LOG.funcVerbose("request URL    : {}", URL)
    LOG.funcVerbose("request headers: {}", HEADERS)
    LOG.funcVerbose("timeout        : {}", timeout)

    COOKIES = browser_cookie3.chrome(domain_name='.leetcode.com')
    TASK = LOG.createTaskLog("Request Questions List")

    TASK.begin("requesting to: {}", URL)
    state, resp = safeRequest(
        partial(requests.Session().get, URL, headers=HEADERS, timeout=timeout, cookies=COOKIES))

    LOG.funcVerbose("request finished: {}", state)

    if state == REQUEST_OK:
        TASK.done("successfully requested from: {}", URL, is_success=True)
        LOG.funcVerbose("cached the result of questions list.")
        __QUESTIONS_LIST_CACHE = resp
        LOG.verbose("http code=%d" % resp.status_code)
        LOG.verbose("http resp=%s" % resp.content.decode('utf-8'))
        return state, resp

    TASK.done("failed to request ({}): {}",
              __toString(state), URL, is_success=False)
    return state, None


def requestGraphQL(payload: str, *, timeout: int = 5, headers: object, name: str = "", session=requests.Session(), cookies=None):
    LOG = prompt.Log.getInstance()

    LOG.funcVerbose("request URL    : {}", GRAPHQL_URL)
    LOG.funcVerbose("request headers: {}", headers)
    LOG.funcVerbose("payload        : {}", payload)
    LOG.funcVerbose("timeout        : {}", timeout)

    if name != "":
        TASK = LOG.createTaskLog(name)
        TASK.begin()
        state, resp = safeRequest(partial(session.post, GRAPHQL_URL, headers=headers,
                                timeout=timeout, data=payload.encode('utf-8'), cookies=cookies))
        LOG.funcVerbose("request finished: {}", state)

        if state == REQUEST_OK:
            TASK.done("successfully requested", is_success=True)
            return state, resp

        TASK.done("failed to request ({})",
                  __toString(state), is_success=False)
        return state, None
    else:
        state, resp = safeRequest(partial(session.post, GRAPHQL_URL, headers=headers,
                                timeout=timeout, data=payload.encode('utf-8'), cookies=cookies))
        if state == REQUEST_OK:
            return state, resp
        return state, None


def requestQuestionInformation(slug: int, *, timeout: int = 5):
    param = {
        'operationName': "getQuestionDetail",
        'variables': {'titleSlug': slug},
        'query': '''query getQuestionDetail($titleSlug: String!) {
            question(titleSlug: $titleSlug) {
                questionFrontendId
                questionTitle
                content
                difficulty
                titleSlug
                codeSnippets {
                    lang
                    langSlug
                    code
                    __typename
                }
            }
        }'''}

    HEADERS = {
        'User-Agent': USER_AGENT,
        'Connection': 'keep-alive',
        'Content-Type': 'application/json',
        'Referer': 'https://leetcode.com/problems/' + slug,
        'Sec-Ch-Ua': '"Not A(Brand";v="99", "Google Chrome";v="121", "Chromium";v="121"',
        'Sec-Ch-Ua-Mobile': '?0',
        'Sec-Ch-Ua-Platform': '"macOS"',
        'Sec-Fetch-Dest': 'document',
        'Sec-Fetch-Mode': 'navigate',
        'Sec-Fetch-Site': 'none',
        'Sec-Fetch-User': '?1',
        'Upgrade-Insecure-Requests': '1'
    }

    COOKIES = browser_cookie3.chrome(domain_name='.leetcode.com')
    return requestGraphQL(json.dumps(param), headers=HEADERS, timeout=timeout, name='Request Questions Information', cookies=COOKIES)
