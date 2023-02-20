#!/usr/bin/env python3
from functools import partial
from typing import Callable
import sys
import requests
# prevent generating __pycache__
sys.dont_write_bytecode = True

import prompt

_LEETCODE_QUESTIONS_QUERY_URL = "https://leetcode.com/api/problems/all/"
_LEETCODE_GRAPHQL_API_URL = "https://leetcode.com/graphql"
_USER_AGENT = r'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/44.0.2403.157 Safari/537.36'

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


def _safeRequest(func: Callable):
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
    HEADERS = {'User-Agent': _USER_AGENT, 'Connection': 'keep-alive'}

    LOG.funcVerbose("request URL    : {}", URL)
    LOG.funcVerbose("request headers: {}", HEADERS)
    LOG.funcVerbose("timeout        : {}", timeout)

    TASK = LOG.createTaskLog("Request Questions List")

    TASK.begin("requesting to: {}", URL)
    state, resp = _safeRequest(
        partial(requests.Session().get, URL, headers=HEADERS, timeout=timeout))

    LOG.funcVerbose("request finished: {}", state)

    if state == REQUEST_OK:
        TASK.done("successfully requested from: {}", URL, is_success=True)
        LOG.funcVerbose("cached the result of questions list.")
        __QUESTIONS_LIST_CACHE = resp
        return state, resp
    
    TASK.done("failed to request ({}): {}",
              __toString(state), URL, is_success=False)
    return state, None


def requestQuestionInformation(slug: int, *, timeout: int = 5):
    import json
    LOG = prompt.Log.getInstance()
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

    URL = _LEETCODE_GRAPHQL_API_URL
    HEADERS = {
        'User-Agent': _USER_AGENT,
        'Connection': 'keep-alive',
        'Content-Type': 'application/json',
        'Referer': 'https://leetcode.com/problems/' + slug
    }

    LOG.funcVerbose("request URL    : {}", URL)
    LOG.funcVerbose("request headers: {}", HEADERS)
    LOG.funcVerbose("timeout        : {}", timeout)

    TASK = LOG.createTaskLog("Request Questions Information")
    TASK.begin("requesting to: {}", URL)
    state, resp = _safeRequest(
        partial(requests.Session().post,
                URL,
                headers=HEADERS, timeout=timeout, data=json.dumps(param).encode('utf-8')))
    LOG.funcVerbose("request finished: {}", state)

    if state == REQUEST_OK:
        TASK.done("successfully requested from: {}", URL, is_success=True)
        return state, resp

    TASK.done("failed to request ({}): {}",
              __toString(state), URL, is_success=False)
    return state, None
