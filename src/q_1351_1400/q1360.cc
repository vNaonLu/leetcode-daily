// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Days Between Two Dates
//
// https://leetcode.com/problems/number-of-days-between-two-dates/
//
// Question ID: 1360
// Difficult  : Easy
// Solve Date : 2023/06/20 20:36

#include <iosfwd>
#include <numeric>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1360. Number of Days Between Two Dates|:
//
// Write a program to count the number of days between two dates.
// The two dates are given as strings, their format is |YYYY-MM-DD| as shown in
// the examples.
//
//

LEETCODE_BEGIN_RESOLVING(1360, NumberOfDaysBetweenTwoDates, Solution);

class Solution {
public:
  int daysBetweenDates(string date1, string date2) {
    int d1 = daysFrom1971(date1);
    int d2 = daysFrom1971(date2);
    return abs(d2 - d1);
  }

private:
  vector<int> kDays = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  bool isLeap(int y) { return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0); }

  int daysFrom1971(string &s) {
    int y = stoi(s.substr(0, 4));
    int m = stoi(s.substr(5, 2));
    int d = stoi(s.substr(8));
    for (int i = 1971; i < y; ++i) {
      d += (isLeap(i) ? 366 : 365);
    }
    return d + (m > 2 && isLeap(y)) +
           accumulate(kDays.begin(), kDays.begin() + m - 1, 0);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The given dates are valid dates between the years |1971| and |2100|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: date1 = "2019-06-29", date2 = "2019-06-30"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1360, NumberOfDaysBetweenTwoDates, example_1) {
  auto   solution = MakeSolution();
  string date1    = "2019-06-29";
  string date2    = "2019-06-30";
  int    expect   = 1;
  int    actual   = solution->daysBetweenDates(date1, date2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: date1 = "2020-01-15", date2 = "2019-12-31"
// Output: 15
//

LEETCODE_SOLUTION_UNITTEST(1360, NumberOfDaysBetweenTwoDates, example_2) {
  auto   solution = MakeSolution();
  string date1    = "2020-01-15";
  string date2    = "2019-12-31";
  int    expect   = 15;
  int    actual   = solution->daysBetweenDates(date1, date2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "1971-06-29"
// "2010-09-23"
// Output: 14331
//

LEETCODE_SOLUTION_UNITTEST(1360, NumberOfDaysBetweenTwoDates,
                           extra_testcase_1) {
  auto   solution = MakeSolution();
  string date1    = "1971-06-29";
  string date2    = "2010-09-23";
  int    expect   = 14331;
  int    actual   = solution->daysBetweenDates(date1, date2);
  LCD_EXPECT_EQ(expect, actual);
}
