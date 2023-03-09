#!/usr/bin/env python3
import json
import sys
# prevent generating __pycache__
sys.dont_write_bytecode = True


from utils import *
import net


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
    if not(state == net.REQUEST_OK and \
            isinstance(resp, net.requests.Response) and resp.status_code == 200):
        LOG.failure("network error")
        return None

    content = json.loads(resp.content.decode('utf-8'))['data']['activeDailyCodingChallengeQuestion']['question']
    return QuestionOfToday(content)


LOG = prompt.Log.getInstance(verbose=True)

q = getQuestionOfToday()
LOG.log(f'id         = {q.id}')
LOG.log(f'title      = {q.title}')
LOG.log(f'slug       = {q.slug}')
LOG.log(f'difficulty = {q.difficulty}')
LOG.log(f'paid       = {q.paid_only}')
