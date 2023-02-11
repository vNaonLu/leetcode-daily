import time
import math
from . import local


def question_detail(question: local.QuestionDetails):
    qfile = local.QuestionSource(question.id(), "./src")
    src = "" if not question.paid_only() else "🔒"
    title = "[{}](https://leetcode.com/problems/{}/)".format(question.title(),
                                                             question.slug())
    if question.done():
        src = "[📎]({})".format(qfile.src())
    return "|{}|{}|{}|{}|".format(src, question.id(), title,
                                  "Hard" if question.level() == 3 else ("Medium" if question.level() == 2 else "Easy"))


def problem_solves_process_svg(solve: int, total: int):
    circle_len = 46 * 2 * math.pi
    solve_len = circle_len * solve / total

    return "\n".join([
        '<?xml version="1.0" encoding="UTF-8" standalone="no"?>',
        '<svg height="100" width="100" viewBox="0 0 100 100" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" style="transform: rotate(-90deg);">',
        '   <circle fill="none" cx="50px" cy="50px" r="46" stroke="#747474" stroke-width="3" stroke-linecap="round"/>',
        '   <circle fill="none" cx="50px" cy="50px" r="46" stroke="#ffa116" stroke-width="5" stroke-linecap="round" stroke-dasharray="{} {}" stroke-dashoffset="0" data-difficult="ALL" />'.format(
            solve_len, circle_len - solve_len),
        '</svg>',
    ])


__kLeetCodeLightGray = "#eff2f699"
__kLeetCodeDarkGray = "#ebebf54d"
__kLeetCodeWhite = "#ffffff"
__kLeetCodeOrange = "#ffa116"
__kLeetCodeGray = "#747474"
__kPanelBackground = "#404040"


def __problem_solves_state(title: str, solve: int, total: int, margin_top: str = "0rem"):
    kStatePanelCss = "".join([
        "font-size: .75rem;",
        "line-height: 1rem;",
        "align-items: flex-end;",
        "width: 100%;",
        "display: flex;",
    ])
    kStateTitleCss = "".join([
        "width: 53px;",
        "color: {};".format(__kLeetCodeLightGray),
    ])
    kStateCenterCss = "".join([
        "display: flex;",
        "flex: 1 1 0%;",
        "align-items: center;"
    ])
    kStateCenterSolvedCss = "".join([
        "line-height: 20px",
        "font-weight: 500",
        "font-size: 1rem;",
        "margin-right: 5px;",
        "color: {};".format(__kLeetCodeWhite),
    ])
    kStateCenterTotalCss = "".join([
        "color: {};".format(__kLeetCodeGray),
        "font-weight: 500",
        "font-size: .75rem",
        "font-height: 1rem;",
        "color: {};".format(__kLeetCodeDarkGray),
    ])
    kStateTailCss = "".join([
        "display: inline;"
    ])
    kStateCompleteCss = "".join([
        "margin-left: 0.375rem;",
        "color: {};".format(__kLeetCodeWhite),
    ])
    kStateProgressPanelCss = "".join([
        "border-radius: 9999px;",
        "width: 228px;",
        "height: 0.25rem;",
        "position: relative;"
    ])
    kProgressBackgroundCss = "".join([
        "background-color: {};".format(__kLeetCodeGray),
        "width: 100%;",
        "height: 100%;",
        "position: absolute;"
    ])
    kProgressForeCss = "".join([
        "background-color: {};".format(__kLeetCodeOrange),
        "width: {:.4f}%;".format(solve / total * 100.0),
        "height: 100%;",
        "position: absolute;",
        "border-radius: 9999px;",
    ])

    return "\n           ".join([
        '<div style="margin-top: {};">'.format(margin_top),
        '   <div style="{}">'.format(kStatePanelCss),
        '       <div style="{}">{}</div>'.format(kStateTitleCss, title),
        '       <div style="{}">'.format(kStateCenterCss),
        '           <span style="{}">{}</span>'.format(
            kStateCenterSolvedCss, solve),
        '           <span style="{}">/{}</span>'.format(
            kStateCenterTotalCss, total),
        '       </div>',
        '       <div style="{}">'.format(kStateTailCss),
        '           <span>',
        '               <span style="color: {};">Complete</span>'.format(
            __kLeetCodeLightGray),
        '               <span style="{}">{:.2f}%</span>'.format(
            kStateCompleteCss, solve / total * 100.0),
        '           </span>',
        '       </div>',
        '   </div>',
        '   <div style="{}">'.format(kStateProgressPanelCss),
        '       <div style="{}"></div>'.format(kProgressBackgroundCss),
        '       <div style="{}"></div>'.format(kProgressForeCss),
        '   </div>',
        '</div>',
    ])


def problems_solves_panel(easy: int, medium: int, hard: int, total_easy: int, total_medium: int, total_hard: int):
    kPanelCss = "".join([
        "min-height: 186px;",
        "height: 186px;",
        "width: min-content;",
        "padding-top: 1rem;",
        "padding-bottom: 0.75rem;",
        "background-color: {};".format(__kPanelBackground),
        "border-radius: 0.5rem"
    ])
    kStatPanelCss = "".join([
        "margin-left: 2rem;",
        "margin-right: 2rem;",
        "align-items: center;",
        "display: flex;"
    ])
    kCirclePanelCss = "".join([
        "min-width: 100px;",
        "justify-content: center;",
        "display: flex;",
        "margin-right: 2rem;",
        "margin-top: 1.5rem;"
    ])
    kCircleCss = "".join([
        "z-index: 0;",
        "max-width: 100px",
        "max-height: 100px;",
        "position: relative;"
    ])
    kCircleDetailCss = "".join([
        "text-align: center;",
        "position: absolute;",
        "transform: translate(-50%, -50%);"
        "top: 50%;",
        "left: 50%;",
    ])
    kCircleDetailNumberCss = "".join([
        "font-size: 24px;",
        "font-weight: 500;",
        "color: {};".format(__kLeetCodeWhite)
    ])
    kCircleDetailFontCss = "".join([
        "font-size: .75rem;",
        "line-height: 1rem;",
        "color: {};".format(__kLeetCodeLightGray)
    ])
    kStatePanelCss = "".join([
        "max-width: 228px;",
        "flex-direction: column;",
        "display: flex;",
        "width: 100%;",
    ])

    return "\n".join([
        '<div style="{}">'.format(kPanelCss),
        '   <div style="diplay: flex; flex-direction: row; font-weight: 500; padding-left: 13px; padding-right: 13px">',
        '       <span style="color: {};">Solved </span>'.format(__kLeetCodeLightGray),
        '       <span style="color: {};">Free Problems</span>'.format(__kLeetCodeOrange),
        '   </div>',
        '   <div style="{}">'.format(kStatPanelCss),
        '      <div style="{}">'.format(kCirclePanelCss),
        '           <div style="{}">'.format(kCircleCss),
        '               <img src="/vNaonLu/daily-leetcode/raw/master/assets/progress.svg">',
        '               <div style="{}">'.format(kCircleDetailCss),
        '                   <div>',
        '                       <div style="{}">{}</div>'.format(kCircleDetailNumberCss, easy + medium + hard),
        '                       <div style="{}">Solved</div>'.format(kCircleDetailFontCss),
        '                   </div>',
        '               </div>',
        '           </div>',
        '      </div>',
        '      <div style="{}">'.format(kStatePanelCss),
        '           {}'.format(
            __problem_solves_state("Easy", easy, total_easy)),
        '           {}'.format(__problem_solves_state(
            "Medium", medium, total_medium, margin_top="1rem")),
        '           {}'.format(__problem_solves_state(
            "Hard", hard, total_hard, margin_top="1rem")),
        '      </div>',
        '   </div>',
        '</div>',
    ])


def __table_row(line: list[str], details: local.QuestionDetails, base: str):
    qfile = local.QuestionSource(details.id(), base)
    line[2] += "[{}](https://leetcode.com/problems/{}/)".format("#{}. {}".format(details.id(), details.title()),
                                                                details.slug())
    line[3] += "{}".format("Hard" if details.level() == 3 else (
        "Medium" if details.level() == 2 else "Easy"))
    line[4] += "[q{}.cc]({})".format(qfile.id(), qfile.src())
    return line


def table_row(date: str, details: list[local.QuestionDetails], base: str = "./src"):
    line: list[str] = ["", date, "", "", "", "", ""]
    line = __table_row(line, details[0], base)
    for i in range(1, len(details)):
        for j in range(2, 6):
            line[j] += "<br>"
        line = __table_row(line, details[i], base)
    return "|".join(line)


def log_readme(title: str, solved_logs: list[local.Log], ques_data: local.QuestionList):
    day_map: dict[int, list[local.QuestionDetails]] = {}
    for log in solved_logs:
        d = int(time.strftime("%j",
                              time.localtime(log.timestamp())))
        if d not in day_map:
            day_map[d] = []
        details = ques_data.get(log.id())
        day_map[d].append(details)

    table_content: list[str] = []
    for date, details_list in sorted(day_map.items(), key=lambda t: t[0], reverse=True):
        details_list.sort(key=lambda e: e.id())
        table_content.append(table_row("Day {}".format(date),
                                       details_list, "../src"))

    return "\n".join([
        "## {}".format(title),
        "",
        "||Question Title|Difficulty|Solution|",
        "|:--|:--|:--|:-:|",
        "\n".join(table_content),
        "",
        ""])
