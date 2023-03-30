// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Day of the Week
//
// https://leetcode.com/problems/day-of-the-week/
//
// Question ID: 1185
// Difficult  : Easy
// Solve Date : 2023/03/30 19:51

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1185. Day of the Week|:
//
// Given a date, return the corresponding day of the week for that date.
// The input is given as three integers representing the |day|, |month| and
// |year| respectively. Return the answer as one of the following values
// |{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
// "Saturday"}|.
//
//

LEETCODE_BEGIN_RESOLVING(1185, DayOfTheWeek, Solution);

class Solution {
private:
  inline static const vector<string> kWeekName = {
      "Monday", "Tuesday",  "Wednesday", "Thursday",
      "Friday", "Saturday", "Sunday"};
  inline static const vector<int> kDaysInMonth = {31, 28, 31, 30, 31, 30,
                                                  31, 31, 30, 31, 30, 31};

  bool isLeapYear(int year) {
    return (year % 100 != 0 && year % 4 == 0) || (year % 400 == 0);
  }

public:
  string dayOfTheWeek(int day, int month, int year) {
    int days = 0;
    days += 365 * (year - 1);
    days += (year - 1) / 4;
    days -= (year - 1) / 100;
    days += (year - 1) / 400;
    for (int i = 0; i < month - 1; ++i) {
      days += kDaysInMonth[i];
    }
    if (month > 2 && isLeapYear(year)) {
      ++days;
    }
    days += day - 1;
    return kWeekName[days % 7];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The given dates are valid dates between the years |1971| and |2100|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: day = 31, month = 8, year = 2019
// Output: "Saturday"
//

LEETCODE_SOLUTION_UNITTEST(1185, DayOfTheWeek, example_1) {
  auto   solution = MakeSolution();
  int    day      = 31;
  int    month    = 8;
  int    year     = 2019;
  string expect   = "Saturday";
  string actual   = solution->dayOfTheWeek(day, month, year);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: day = 18, month = 7, year = 1999
// Output: "Sunday"
//

LEETCODE_SOLUTION_UNITTEST(1185, DayOfTheWeek, example_2) {
  auto   solution = MakeSolution();
  int    day      = 18;
  int    month    = 7;
  int    year     = 1999;
  string expect   = "Sunday";
  string actual   = solution->dayOfTheWeek(day, month, year);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: day = 15, month = 8, year = 1993
// Output: "Sunday"
//

LEETCODE_SOLUTION_UNITTEST(1185, DayOfTheWeek, example_3) {
  auto   solution = MakeSolution();
  int    day      = 15;
  int    month    = 8;
  int    year     = 1993;
  string expect   = "Sunday";
  string actual   = solution->dayOfTheWeek(day, month, year);
  LCD_EXPECT_EQ(expect, actual);
}
