#!/usr/bin/env python3
import sys
import time
from datetime import date
# prevent generating __pycache__
sys.dont_write_bytecode = True


from utils import *
from filesystem import *
from questions import *
import logs

def _combineStyle(list: list[str]):
    return ";".join(list + [""])

_LIGHT_GRAY = "#eff2f699"
_DARK_GRAY = "#ebebf54d"
_WHITE = "#ffffff"
_ORANGE = "#ffa116"
_GRAY = "#747474"
_PANEL_BACKGROUND = "#404040"
_BLOCK_SIZE = 8.86
_BLOCK_STEP = 11.52
_BLOCK_STRIDE = 2

_TITLE_STYLE = _combineStyle(["font-weight: 500",
                                 "font-size: 1rem"])
_ROTATE90_STYLE = _combineStyle(["transform: rotate(-90deg)",
                                    "transform-origin: center",
                                    "transform-box: fill-box"])
_STATE_STYLE = _combineStyle(["font-size: .75rem"])
_LIGHT_STYLE = _combineStyle(["color: {}".format(_WHITE),
                                 "fill: {}".format(_WHITE)])
_LIGHT_GRAY_STYLE = _combineStyle(["color: {}".format(_LIGHT_GRAY),
                                     "fill: {}".format(_LIGHT_GRAY)])
_DARK_GRAY_STYLE = _combineStyle(["color: {}".format(_DARK_GRAY),
                                    "fill: {}".format(_DARK_GRAY)])
_GRAY_STYLE = _combineStyle(["color: {}".format(_GRAY),
                                "fill: {}".format(_GRAY)])
_ORANGE_STYLE = _combineStyle(["color: {}".format(_ORANGE),
                                  "fill: {}".format(_ORANGE)])
_BACKGROUND_STYLE = _combineStyle(["color: {}".format(_PANEL_BACKGROUND),
                                      "fill: {}".format(_PANEL_BACKGROUND)])


class ProblemResolveProgress:
    def __init__(self, solved: list[int], total: list[int]):
        self._solved = solved
        self._total = total

    def _progressSVG(self, title: str, cnt: int, total: int, y: int, delimiter=''):
        percent = cnt / total
        total_length = 390 - 160
        fix_y = y + 10
        res = [ 
            '<g>',
            '   <text x="160" y="{}" class="light-gray">{}</text>'.format(y, title),
            '   <text x="225" y="{}" class="light">{}</text>'.format(y, cnt),
            '   <text x="250" y="{}" class="dark-gray">/{}</text>'.format(y, total),
            '   <text x="290" y="{}" class="light-gray">Complete</text>'.format(y),
            '   <text x="350" y="{}" class="light">{:.2f}%</text>'.format(y, percent * 100.0),
            '   <path d="M 160 {} L 390 {}" stroke-linecap="round" stroke-linejoin="round" stroke="#ebebf54d" stroke-width="3"/>'.format(fix_y, fix_y),
            '   <path d="M 160 {} L {} {}" stroke-linecap="round" stroke-linejoin="round" stroke="#ffa116" stroke-width="5"/>'.format(fix_y, percent * total_length + 160, fix_y),
            '</g>',
        ]
        return delimiter.join(res)

    def _SVG(self, delimiter=''):
        circle_len = 46 * 2 * math.pi
        solve_len = circle_len * sum(self._solved) / sum(self._total)
        res =[
            '<svg version="1.1" height="200" width="410" viewBox="0 0 410 200" xmlns="http://www.w3.org/2000/svg">',
            '   <style>*{font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;}</style>',
            '   <style>.title{{{}}}</style>'.format(_TITLE_STYLE),
            '   <style>.rotate-90{{{}}}</style>'.format(_ROTATE90_STYLE),
            '   <style>.state{{{}}}</style>'.format(_STATE_STYLE),
            '   <style>.light{{{}}}</style>'.format(_LIGHT_STYLE),
            '   <style>.light-gray{{{}}}</style>'.format(_LIGHT_GRAY_STYLE),
            '   <style>.dark-gray{{{}}}</style>'.format(_DARK_GRAY_STYLE),
            '   <style>.gray{{{}}}</style>'.format(_GRAY_STYLE),
            '   <style>.orange{{{}}}</style>'.format(_ORANGE_STYLE),
            '   <style>.background{{{}}}</style>'.format(_BACKGROUND_STYLE),
            '   <rect fill="#404040" x="0" y="0" width="410" height="200" rx="0.5rem"/>',  # bg
            '   <g text-anchor="start" text-decoration="1" class="title">',               # title
            '       <text x="20" y="30">',
            '           <tspan class="light">Solved</tspan>',
            '           <tspan class="orange">Free Problems</tspan>',
            '       </text>',
            '   </g>',
            '   <g class="rotate-90">',
            '       <circle fill="none" cx="70" cy="110" r="46" stroke="{}" stroke-width="3" stroke-linecap="round" />'.format(_GRAY),
            '       <circle fill="none" cx="70" cy="110" r="46" stroke="{}" stroke-width="5" stroke-linecap="round" stroke-dasharray="{} {}" stroke-dashoffset="0" data-difficult="ALL" />'.format(
                _ORANGE,  solve_len, circle_len - solve_len),
            '   </g>',
            '   <g class="state">',
            '       <g text-anchor="middle">',
            '          <text x="70" y="110" class="light" font-size="1.2rem">{}</text>'.format(sum(self._solved)),
            '          <text x="70" y="130" class="light-gray">Solved</text>',
            '       </g>',
            self._progressSVG("Easy", self._solved[0], self._total[0], 65),
            self._progressSVG("Medium", self._solved[1], self._total[1], 105),
            self._progressSVG("Hard", self._solved[2], self._total[2], 145),
            '   </g>',
            '</svg>'
        ]
        return delimiter.join(res)

    def save(self, path: Path):
        LOG = prompt.Log.getInstance()

        LOG.funcVerbose("saving the problem resolve progress: {}", path)
        with path.open('w') as f:
            f.write(self._SVG())


class ActivityChart:
    __LEVEL_STYLE = [
        ("level-1-block", _combineStyle(["fill: #ffffff1a"])),
        ("level-2-block", _combineStyle(["fill: #2cb55d80"])),
        ("level-3-block", _combineStyle(["fill: #2cbb5dff"])),
        ("level-4-block", _combineStyle(["fill: #4cc575ff"])),
        ("level-5-block", _combineStyle(["fill: #6bcf8eff"])),
    ]
    
    def __init__(self, *, light_title: str, orange_title: str, begin_time: int, solved_array: list[list[int]]) -> None:
        self._light_title = light_title
        self._orange_title = orange_title
        self._begin_time = begin_time
        self._solved_array = solved_array
        self._flat = [x for v in self._solved_array for x in v]
        mx = max(self._flat)
        stride = mx / len(self.__LEVEL_STYLE)
        self._standard = [0, 1] + [max(2, math.ceil(stride * (i + 1))) for i in range(len(self.__LEVEL_STYLE) - 1)]
        assert len(self._standard) == len(self.__LEVEL_STYLE) + 1

    def _colorDefine(self, cnt: int):
        for i in range(1, len(self._standard)):
            if cnt < self._standard[i]:
                return self.__LEVEL_STYLE[i - 1][0]
        return self.__LEVEL_STYLE[-1][0]

    def _monthSVG(self, *, begin_time: time.struct_time, x: int, y: int, solved_array: list[int], delimiter=''):
        week_x = [x + i * _BLOCK_STEP for i in range(6)]
        day_y  = [y + i * _BLOCK_STEP for i in range(7)]

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
                        curr_x, day_y[d], _BLOCK_SIZE, self._colorDefine(solved_array[curr_idx]))
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
        return (delimiter.join(res), curr_week, (start_day + curr_idx) % 7)

    def _SVG(self, delimiter=''):
        kDaySeconds = int(24 * 60 * 60)

        res = [
            '<svg version="1.1" height="200" width="830" viewBox="0 0 830 200" xmlns="http://www.w3.org/2000/svg">',
            '   <style>*{font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;}</style>',
            '   <style>.title{{{}}}</style>'.format(_TITLE_STYLE),
            '   <style>.rotate-90{{{}}}</style>'.format(_ROTATE90_STYLE),
            '   <style>.state{{{}}}</style>'.format(_STATE_STYLE),
            '   <style>.light{{{}}}</style>'.format(_LIGHT_STYLE),
            '   <style>.light-gray{{{}}}</style>'.format(_LIGHT_GRAY_STYLE),
            '   <style>.dark-gray{{{}}}</style>'.format(_DARK_GRAY_STYLE),
            '   <style>.gray{{{}}}</style>'.format(_GRAY_STYLE),
            '   <style>.orange{{{}}}</style>'.format(_ORANGE_STYLE),
            '   <style>.background{{{}}}</style>'.format(_BACKGROUND_STYLE),
            delimiter.join(['<style>.{}{{{}}}</style>'.format(*l) for l in self.__LEVEL_STYLE]),
            '   <rect fill="#404040" x="0" y="0" width="830" height="200" rx="0.5rem"/>', # bg
            '   <g text-anchor="start" text-decoration="1" class="title">',               # title
            '       <text x="20" y="35">',
            '           <tspan class="light">{}</tspan>'.format(self._light_title),
            '           <tspan class="orange">{}</tspan>'.format(self._orange_title),
            '       </text>',
            '   </g>',
            '<g class="state">',
            '   <text x="670" y="35" class="light-gray"> Total solution: </text>',
            '   <text x="750" y="35" class="light"> {} </text>'.format(sum(self._flat)),
            '   <text x="{}" y="180" class="light-gray" text-anchor="end">Less</text>'.format(
                750 - _BLOCK_STEP * (len(self.__LEVEL_STYLE) + 1) - _BLOCK_STRIDE),
            delimiter.join(['<rect x="{0}" y="171" width="{1}" height="{1}" rx="2" ry="2" class="{2}"/>'.format(
                750 - _BLOCK_STEP * (len(self.__LEVEL_STYLE) - i + 0.5), _BLOCK_SIZE, self.__LEVEL_STYLE[i][0]) for i in range(len(self.__LEVEL_STYLE))]),
            '   <text x="750" y="180" class="light-gray">More</text>',
            '</g>',
        ]

        curr_x = 20
        curr_y = 60
        curr_time = self._begin_time
        for i in range(len(self._solved_array)):
            month = ['<g x="{}" y="{}">'.format(curr_x, curr_y)]
            (svg, cross_weeks, last_day_in_week) = self._monthSVG(
                begin_time=time.localtime(curr_time),
                x=curr_x, y=curr_y, solved_array=self._solved_array[i])
            month += [svg]
            curr_x += (cross_weeks + (1 if last_day_in_week == 0 else 0)) * _BLOCK_STEP + _BLOCK_STRIDE
            curr_time += kDaySeconds * len(self._solved_array[i])
            month += ['</g>']
            res += month

        res += ['</svg>']
        return delimiter.join(res)

    def save(self, path: Path):
        LOG = prompt.Log.getInstance()

        LOG.funcVerbose("saving the activity chart: {}", path)
        with path.open('w') as f:
            f.write(self._SVG())


class AnnualResolveDocument:
    def __init__(self, *, year: int, year_log: logs._YearlyResolvedLogList, questions_list: QuestionsList, src_path: Path):
        LOG = prompt.Log.getInstance()
        self._year = year
        self._src_path = Path(src_path)
        self._log = year_log
        self._questions_list = questions_list
        self._month_to_cnt = []
        self._total_cnt = [0, 0, 0]

        for _ in range(0, 13):
            self._month_to_cnt.append([0, 0, 0])

        LOG.funcVerbose("parsing the count of solution.")
        for m, month_logs in year_log:
            for _, day_logs in month_logs:
                for log in day_logs:
                    detail = questions_list[log.id]
                    self._month_to_cnt[m][detail.level - 1] += 1
        self._total_cnt[0] = sum(x[0] for x in self._month_to_cnt)
        self._total_cnt[1] = sum(x[1] for x in self._month_to_cnt)
        self._total_cnt[2] = sum(x[2] for x in self._month_to_cnt)
        LOG.funcVerbose("parsed {} easy, {} medium and {} hard resolve logs.",
                        self._total_cnt[0],
                        self._total_cnt[1],
                        self._total_cnt[2])

    def _summary(self, *, delimiter = '\n'):
        res = [
            f"# All Submissions in {self._year}",
            f"",
            f"![activity](../assets/{self._year}_activity.svg)",
        ]
        return delimiter.join(res) + delimiter
    
    def _overview(self, *, delimiter = '\n'):
        res = [
            f"## Overview",
            f"",
            f"There are totally **{sum(self._total_cnt)}** questions have been solved in {self._year}, "
            f"including **{self._total_cnt[0]}** questions in easy, **{self._total_cnt[1]}** "
            f"questions in medium and **{self._total_cnt[2]}** questions in hard.",
            f"",
            f"",
            f"Please click on the sections below to see more details for a specific month.",
        ]

        for month in reversed(self._log.months()):
            month_str = time.strftime("%B", date(self._year, month, 1).timetuple())
            res.append(f"- [{month_str}](#{month_str.lower()}-submissions)")
            res.append("")

        return delimiter.join(res)

    def _monthSummary(self, month_str: str, cnt: dict[int]):
        res = [
            f"## {month_str} Submissions",
            f"",
            f"Solved **{sum(cnt)}** questions in {month_str.lower()}:",
            f"- **{cnt[0]}** questions in easy.",
            f"- **{cnt[1]}** questions in medium.",
            f"- **{cnt[2]}** questions in hard.",
            f"",
            f"|   |Question Title|Difficulty|Source|",
            f"|:--|:-------------|:--------:|:-----|",
        ]
        return res

    def _monthTableRowImpl(self, row: list[str], detail: QuestionDetails):
        source = SolutionFile(detail.id, self._src_path)
        row[1] += f"[#{detail.id}. {detail.title}](https://leetcode.com/problems/{detail.slug}/)"
        row[2] += detail.levelString()
        row[3] += f"[src/{source.subdirectory()}/{source.fileName()}]({source})"
        return row

    def _monthTableRow(self, day: int, resolved_logs: list[logs.ResolveLog]):
        res = [
            f"Day {day}",
            "", # title
            "", # level
            "", # source
        ]

        if len(resolved_logs) > 0:
            res = self._monthTableRowImpl(res, self._questions_list[resolved_logs[0].id])
            for resolve in resolved_logs[1:]:
                detail = self._questions_list[resolve.id]
                for col in range(1, len(res)):
                    res[col] += "<br>"
                res = self._monthTableRowImpl(res, detail)
        return "|" + "|".join(res) + "|"

    def _monthsDetails(self, *, delimiter='\n'):
        res = []
        for month in reversed(self._log.months()):
            month_str = time.strftime("%B", date(self._year, month, 1).timetuple())
            res += self._monthSummary(month_str, self._month_to_cnt[month])
            rows = []
            for day, day_logs in self._log[month]:
                rows.append(self._monthTableRow(day, day_logs))
            res += reversed(rows)
        return delimiter.join(res) + delimiter

    def save(self, path: Path):
        LOG = prompt.Log.getInstance()

        LOG.funcVerbose("start to save the {} resolve document: {}", self._year, path)
        with Path(path).open("w") as f:
            f.write(self._summary() + "\n")
            f.write(self._overview() + "\n")
            f.write(self._monthsDetails())


class SolvedDocument:
    def __init__(self, *, questions_list: QuestionsList, resolve_logs: list[ResolveLog], src_path: Path):
        self._src_path = Path(src_path)
        self._questions_list = questions_list
        self._resolve_logs = resolve_logs

        self._resolve_logs.sort(key=lambda l : l.id)

    def _summary(self, delimiter='\n'):
        res = [
            f'# Solved Solutions List',
            f'',
            f'This document contains **{len(self._resolve_logs)}** solved questions. '
            f'To find the solution via its identifier and the `Find-In-Page` feature or typing `ctrl+F` (or `cmd⌘+F`) in the most browsers on the market. ',
            f'',
            # f'Note that some questions have incomplete complexity information and I will finish it one after antoher. '
            f'Some questions which are still being resolved are not shown in this page, more information about unsolved questions can be found at [docs/unsolved_solutions.md](./unsolved_solutions.md).',
        ]
        return delimiter.join(res) + delimiter

    def _tableHeader(self, delimiter='\n'):
        res = [
            f'|Id |Question Title|Source|Added Time (UTC+8)|',
            f'|--:|:-------------|:-----|:-----------------|',
        ]
        return delimiter.join(res) + delimiter

    def _tableRow(self, log: ResolveLog):
        file = SolutionFile(log.id, self._src_path)
        detail = self._questions_list[log.id]
        row = "|"
        row += f"{detail.id}|".format(detail.id)
        row += f"[{detail.title}](https://leetcode.com/problems/{detail.slug}/)|"
        row += f"[src/{file.subdirectory()}/{file.fileName()}]({file})|"
        row += "{}|".format(time.strftime("%Y/%m/%d %H:%M",
                            time.localtime(log.timestamp)))
        return row

    def save(self, path: Path):
        LOG = prompt.Log.getInstance()

        LOG.funcVerbose("start to save the solved document: {}", path)
        with Path(path).open("w") as f:
            f.write(self._summary() + "\n\n")
            f.write(self._tableHeader())
            for log in self._resolve_logs:
                f.write(self._tableRow(log) + '\n') 


class UnsolvedDocument:
    def __init__(self, unsolved_details: list[QuestionDetails]) -> None:
        self._details = unsolved_details

    def _summary(self, delimiter='\n'):
        res = [
            f'# Unsolved Solutions List',
            f'',
            f'There are **{len(self._details)}** questions which have not been solved yet. '
            f'To find the question via its identifier and the `Find-In-Page` feature or typing `ctrl+F` (or `cmd⌘+F`) in the most browsers on the market.',
            f'',
            f'The questions which have been solved are not shown in this page, more information about solved questions can be found at [docs/solved_solutions.md](./solved_solutions.md).',
        ]
        return delimiter.join(res) + delimiter
   
    def _tableHeader(self, delimiter='\n'):
        res = [
            '|Id |Question Title|Difficult|Paid Only|',
            '|--:|:-------------|:-------:|:-------:|',
        ]
        return delimiter.join(res) + delimiter
 
    def _tableRow(self, detail: QuestionDetails):
        row = "|"
        row += f"{detail.id}|".format(detail.id)
        row += f"[{detail.title}](https://leetcode.com/problems/{detail.slug}/)|"
        row += f"{detail.levelString()}|"
        row += "{}|".format("🔒" if detail.paid else "")
        return row

    def save(self, path: Path):
        LOG = prompt.Log.getInstance()

        LOG.funcVerbose("start to save the unsolved document: {}", path)
        with Path(path).open("w") as f:
            f.write(self._summary() + "\n\n")
            f.write(self._tableHeader())
            for d in self._details:
                f.write(self._tableRow(d) + '\n')



if __name__ == "__main__":
    LOG = prompt.Log.getInstance(verbose=True)
    qf = QuestionsList("../src/questions_list.csv")
    log = logs.ResolveLogsList("../src/logs.csv")
    doc = AnnualResolveDocument(
        year=2023, year_log=log[2023], questions_list=qf, src_path=Path("../src").resolve())
    doc.save("test.md")
    
