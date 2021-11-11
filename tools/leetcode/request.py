import requests
import json


__session = requests.Session()
__leetcode_quest_url = "https://leetcode.com/api/problems/all/"
__leetcode_gphql_url = "https://leetcode.com/graphql"
__user_agent = r'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/44.0.2403.157 Safari/537.36'


def questions():
    request_count = 10
    while request_count > 0:
        resp = __session.get(
            __leetcode_quest_url,
            headers={
                'User-Agent': __user_agent,
                'Connection': 'keep-alive'
            },
            timeout=10)
        request_count -= 1
        if resp.status_code == 200:
            break

    if resp.status_code != 200:
        return None
    raw_list = json.loads(resp.content.decode('utf-8'))
    ques_list = raw_list["stat_status_pairs"]
    return ques_list


def question_slug(frontend_id: int):
    qlist = questions()
    if qlist:
        for q in qlist:
            if frontend_id == q['stat']['frontend_question_id']:
                return q['stat']['question__title_slug']
    return None


def question_details(ques_slug: str):
    param = {
        'operationName': "getQuestionDetail",
        'variables': {'titleSlug': ques_slug},
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
    request_count = 10
    while request_count > 0:
        resp = __session.post(
            __leetcode_gphql_url,
            data=json.dumps(param).encode("utf8"),
            headers={
                'User-Agent': __user_agent, 'Connection':
                'keep-alive', 'Content-Type': 'application/json',
                'Referer': 'https://leetcode.com/problems/' + ques_slug
            },
            timeout=10)
        request_count -= 1
        if resp.status_code == 200:
            break
    return None
    if resp.status_code == 200:
        raw_data = json.loads(resp.content.decode("utf8"))
        return raw_data['data']['question']
    return None
