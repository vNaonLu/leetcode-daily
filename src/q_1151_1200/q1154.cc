// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Day of the Year
//
// https://leetcode.com/problems/day-of-the-year/
//
// Question ID: 1154
// Difficult  : Easy
// Solve Date : 2022/11/13 13:49

#include <array>
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1154. Day of the Year|:
//
// Given a string |date| representing a [Gregorian calendar] date formatted as
// |YYYY-MM-DD|, return the day number of the year.
//

LEETCODE_BEGIN_RESOLVING(1154, DayOfTheYear, Solution);

class Solution {
private:
  inline constexpr static array<int, 12> days = {31, 28, 31, 30, 31, 30,
                                                 31, 31, 30, 31, 30, 31};

public:
  int dayOfYear(string date) {
    auto y = stoi(date.substr(0, 4));
    auto m = stoi(date.substr(5, 2));
    auto d = stoi(date.substr(8, 2));
    if (m > 2 && y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)) {
      ++d;
    }
    while (--m > 0) {
      d += days[m - 1];
    }
    return d;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |date.length == 10|
// * |date[4] == date[7] == '-'|, and all other |date[i]|'s are digits
// * |date| represents a calendar date between Jan 1ˢᵗ, 1900 and Dec 31ᵗʰ, 2019.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: date = "2019-01-09"
// Output: 9
//
// Given date is the 9th day of the year in 2019.

LEETCODE_SOLUTION_UNITTEST(1154, DayOfTheYear, example_1) {
  auto   solution = MakeSolution();
  string date     = "2019-01-09";
  int    expect   = 9;
  int    actual   = solution->dayOfYear(date);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: date = "2019-02-10"
// Output: 41
//

LEETCODE_SOLUTION_UNITTEST(1154, DayOfTheYear, example_2) {
  auto   solution = MakeSolution();
  string date     = "2019-02-10";
  int    expect   = 41;
  int    actual   = solution->dayOfYear(date);
  LCD_EXPECT_EQ(expect, actual);
}
