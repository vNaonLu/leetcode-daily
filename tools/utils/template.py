import time
import math
from . import local


def __combine_style(list: list[str]):
    return ";".join(list + [""])


__kLeetCodeLightGray = "#eff2f699"
__kLeetCodeDarkGray = "#ebebf54d"
__kLeetCodeWhite = "#ffffff"
__kLeetCodeOrange = "#ffa116"
__kLeetCodeGray = "#747474"
__kPanelBackground = "#404040"
__kBlockSize = 8.86
__kBlockStep = 11.52
__kBlockStride = 2

__kTitleStyle = __combine_style(["font-weight: 500",
                                "font-size: 1rem"])
__kRotate90Style = __combine_style(["transform: rotate(-90deg)",
                                    "transform-origin: center",
                                    "transform-box: fill-box"])
__kStateStyle = __combine_style(["font-size: .75rem"])
__kLightStyle = __combine_style(["color: {}".format(__kLeetCodeWhite),
                                "fill: {}".format(__kLeetCodeWhite)])
__kLightGrayStyle = __combine_style(["color: {}".format(__kLeetCodeLightGray),
                                    "fill: {}".format(__kLeetCodeLightGray)])
__kDarkGrayStyle = __combine_style(["color: {}".format(__kLeetCodeDarkGray),
                                    "fill: {}".format(__kLeetCodeDarkGray)])
__kGrayStyle = __combine_style(["color: {}".format(__kLeetCodeGray),
                                "fill: {}".format(__kLeetCodeGray)])
__kOrangeStyle = __combine_style(["color: {}".format(__kLeetCodeOrange),
                                  "fill: {}".format(__kLeetCodeOrange)])
__kBackgroundStyle = __combine_style(["color: {}".format(__kPanelBackground),
                                      "fill: {}".format(__kPanelBackground)])



def question_detail(question: local.QuestionDetails):
    qfile = local.QuestionSource(question.id(), "./src")
    src = "" if not question.paid_only() else "🔒"
    title = "[{}](https://leetcode.com/problems/{}/)".format(question.title(),
                                                             question.slug())
    if question.done():
        src = "[📎]({})".format(qfile.src())
    return "|{}|{}|{}|{}|".format(src, question.id(), title,
                                  "Hard" if question.level() == 3 else ("Medium" if question.level() == 2 else "Easy"))


def __activaties_month(begin_time: time.struct_time, x: int, y: int, solved_array: list[int], color_callback):

    week_x = [x + i * __kBlockStep for i in range(6)]
    day_y  = [y + i * __kBlockStep for i in range(7)]

    start_day = int(time.strftime("%w", begin_time))

    res = [
        '<g x="{}" y="{}">'.format(x, y),
    ]

    curr_week = 0
    curr_idx = 0
    while curr_idx < len(solved_array):
        curr_x = week_x[curr_week]
        week_svg = ['<g x="{}" y="{}">'.format(curr_x, y)]
        start_in_week = int((start_day + curr_idx) % 7)
        for d in range(start_in_week, 7):
            week_svg += [
                '<rect x="{0}" y="{1}" width="{2}" height="{2}" rx="2" ry="2" class="{3}" />'.format(
                    curr_x, day_y[d], __kBlockSize, color_callback(solved_array[curr_idx]))
            ]
            curr_idx += 1
            if curr_idx >= len(solved_array):
                break
        curr_week += 1
        week_svg += ["</g>"]
        res += week_svg

    res += [
        '   <text x="{}" y="155" class="light-gray state">{}</text>'.format(
            week_x[0], time.strftime("%b", begin_time)),
        '</g>'
    ]
    return ("\n".join(res), curr_week, (start_day + curr_idx) % 7)


def activities_chart(light_title: str, orange_title: str, begin_time: int, solved_array: list[list[int]]):
    kDaySeconds = int(24 * 60 * 60)

    kLevelStyles = [
        ("level-1-block", __combine_style(["fill: #ffffff1a"])),
        ("level-2-block", __combine_style(["fill: #2cb55d80"])),
        ("level-3-block", __combine_style(["fill: #2cbb5dff"])),
        ("level-4-block", __combine_style(["fill: #4cc575ff"])),
        ("level-5-block", __combine_style(["fill: #6bcf8eff"])),
    ]

    flat = [x for v in solved_array for x in v]

    res = [
        '<svg version="1.1" height="200" width="830" viewBox="0 0 830 200" xmlns="http://www.w3.org/2000/svg">',
        '   <style>*{font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;}</style>',
        '   <style>.title{{{}}}</style>'.format(__kTitleStyle),
        '   <style>.rotate-90{{{}}}</style>'.format(__kRotate90Style),
        '   <style>.state{{{}}}</style>'.format(__kStateStyle),
        '   <style>.light{{{}}}</style>'.format(__kLightStyle),
        '   <style>.light-gray{{{}}}</style>'.format(__kLightGrayStyle),
        '   <style>.dark-gray{{{}}}</style>'.format(__kDarkGrayStyle),
        '   <style>.gray{{{}}}</style>'.format(__kGrayStyle),
        '   <style>.orange{{{}}}</style>'.format(__kOrangeStyle),
        '   <style>.background{{{}}}</style>'.format(__kBackgroundStyle),
        '\n'.join(['<style>.{}{{{}}}</style>'.format(*l) for l in kLevelStyles]),
        '   <rect fill="#404040" x="0" y="0" width="830" height="200" rx="0.5rem"/>', # bg
        '   <g text-anchor="start" text-decoration="1" class="title">',               # title
        '       <text x="20" y="35">',
        '           <tspan class="light">{}</tspan>'.format(light_title),
        '           <tspan class="orange">{}</tspan>'.format(orange_title),
        '       </text>',
        '   </g>',
        '<g class="state">',
        '   <text x="670" y="35" class="light-gray"> Total solution: </text>',
        '   <text x="750" y="35" class="light"> {} </text>'.format(sum(flat)),
        '   <text x="{}" y="180" class="light-gray" text-anchor="end">Less</text>'.format(750 - __kBlockStep * (len(kLevelStyles) + 1) - __kBlockStride),
        '\n'.join(['<rect x="{0}" y="171" width="{1}" height="{1}" rx="2" ry="2" class="{2}"/>'.format(
            750 - __kBlockStep * (len(kLevelStyles) - i + 0.5), __kBlockSize, kLevelStyles[i][0]) for i in range(len(kLevelStyles))]),
        '   <text x="750" y="180" class="light-gray">More</text>',
        '</g>',
    ]

    mx = max(flat)
    stride = mx / len(kLevelStyles)
    std = [0, 1] + [max(2, math.ceil(stride * (i + 1))) for i in range(len(kLevelStyles) - 1)]
    del flat
    assert len(std) == len(kLevelStyles) + 1
    
    def level_defined(cnt: int):
        for i in range(1, len(std)):
            if cnt < std[i]:
                return kLevelStyles[i - 1][0]
        return kLevelStyles[-1][0]


    curr_x = 20
    curr_y = 60
    curr_time = begin_time
    for i in range(len(solved_array)):
        month = ['<g x="{}" y="{}">'.format(curr_x, curr_y)]
        (svg, cross_weeks, last_day_in_week) = __activaties_month(time.localtime(curr_time), curr_x, curr_y, solved_array[i], level_defined)
        month += [svg]
        curr_x += (cross_weeks + (1 if last_day_in_week == 0 else 0)) * __kBlockStep + __kBlockStride
        curr_time += kDaySeconds * len(solved_array[i])
        month += ['</g>']
        res += month

    res += ['</svg>']
    return "\n".join(res)


def __solved_progress_line(title: str, cnt: int, total: int, y: int):
    percent = cnt / total
    total_length = 390 - 160
    fix_y = y + 10
    return "".join([
      '<g>',
      '   <text x="160" y="{}" class="light-gray">{}</text>'.format(y, title),
      '   <text x="225" y="{}" class="light">{}</text>'.format(y, cnt),
      '   <text x="250" y="{}" class="dark-gray">/{}</text>'.format(y, total),
      '   <text x="290" y="{}" class="light-gray">Complete</text>'.format(y),
      '   <text x="350" y="{}" class="light">{:.2f}%</text>'.format(y, percent * 100.0),
      '   <path d="M 160 {} L 390 {}" stroke-linecap="round" stroke-linejoin="round" stroke="#ebebf54d" stroke-width="3"/>'.format(fix_y, fix_y),
      '   <path d="M 160 {} L {} {}" stroke-linecap="round" stroke-linejoin="round" stroke="#ffa116" stroke-width="5"/>'.format(fix_y, percent * total_length + 160, fix_y),
      '</g>',
    ])


def problem_solves_svg(easy: int, medium: int, hard: int, t_easy: int, t_medium: int, t_hard: int):
    assert t_easy > 0 and t_medium > 0 and t_hard > 0, "invalid total count"
    assert easy <= t_easy and medium <= t_medium and hard <= t_hard, "invalid count"
    circle_len = 46 * 2 * math.pi
    solve_len = circle_len * (easy + medium + hard) / (t_easy + t_medium + t_hard)

    return "\n".join([
        '<svg version="1.1" height="200" width="410" viewBox="0 0 410 200" xmlns="http://www.w3.org/2000/svg">',
        '   <style>*{font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;}</style>',
        '   <style>.title{{{}}}</style>'.format(__kTitleStyle),
        '   <style>.rotate-90{{{}}}</style>'.format(__kRotate90Style),
        '   <style>.state{{{}}}</style>'.format(__kStateStyle),
        '   <style>.light{{{}}}</style>'.format(__kLightStyle),
        '   <style>.light-gray{{{}}}</style>'.format(__kLightGrayStyle),
        '   <style>.dark-gray{{{}}}</style>'.format(__kDarkGrayStyle),
        '   <style>.gray{{{}}}</style>'.format(__kGrayStyle),
        '   <style>.orange{{{}}}</style>'.format(__kOrangeStyle),
        '   <style>.background{{{}}}</style>'.format(__kBackgroundStyle),
        '   <rect fill="#404040" x="0" y="0" width="410" height="200" rx="0.5rem"/>', # bg
        '   <g text-anchor="start" text-decoration="1" class="title">',               # title
        '       <text x="20" y="30" class="light">Solved</text>',
        '       <text x="72" y="30" class="orange">Free Problems</text>',
        '   </g>',
        '   <g class="rotate-90">',
        '       <circle fill="none" cx="70" cy="110" r="46" stroke="{}" stroke-width="3" stroke-linecap="round" />'.format(__kLeetCodeGray),
        '       <circle fill="none" cx="70" cy="110" r="46" stroke="{}" stroke-width="5" stroke-linecap="round" stroke-dasharray="{} {}" stroke-dashoffset="0" data-difficult="ALL" />'.format(__kLeetCodeOrange,  solve_len, circle_len - solve_len),
        '   </g>',
        '   <g class="state">',
        '       <g text-anchor="middle">',
        '          <text x="70" y="110" class="light" font-size="1.2rem">{}</text>'.format(easy + medium + hard),
        '          <text x="70" y="130" class="light-gray">Solved</text>',
        '       </g>',
        __solved_progress_line("Easy", easy, t_easy, 65),
        __solved_progress_line("Medium", medium, t_medium, 105),
        __solved_progress_line("Hard", hard, t_hard, 145),
        '   </g>',
        '</svg>'
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
        "## Submissions in {}".format(title),
        "",
        "![activity](../assets/{}_activity.svg)".format(title),
        "",
        "||Question Title|Difficulty|Solution|",
        "|:--|:--|:--|:-:|",
        "\n".join(table_content),
        "",
        ""])
