#!/usr/bin/env python3

from filesystem import SolutionFile
from questions import QuestionsList
from cpp_solution import CPPSolution
from utils import SRC_ABSOLUTE, QUESTIONS_LIST_ABSOLUTE
from logs import *
import net, json

LOG = prompt.Log.getInstance(verbose=True)
qid = 2251
questions_detail = QuestionsList(QUESTIONS_LIST_ABSOLUTE)[qid]
LOG.log("request")
state, resp = net.requestQuestionInformation(questions_detail.slug)
LOG.log("request done")
sln = CPPSolution(json.loads(resp.content.decode('utf-8'))['data']['question'])
LOG.log("parse done")
content = sln.solutionTemplate()
print(content)
