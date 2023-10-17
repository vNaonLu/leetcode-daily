// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Number of Operations to Convert Time
//
// https://leetcode.com/problems/minimum-number-of-operations-to-convert-time/
//
// Question ID: 2224
// Difficult  : Easy
// Solve Date : 2023/10/16 22:02

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2224. Minimum Number of Operations to Convert Time|:
//
// You are given two strings |current| and |correct| representing two 24-hour
// times. 24-hour times are formatted as |"HH:MM"|, where |HH| is between |00|
// and |23|, and |MM| is between |00| and |59|. The earliest 24-hour time is
// |00:00|, and the latest is |23:59|. In one operation you can increase the
// time |current| by |1|, |5|, |15|, or |60| minutes. You can perform this
// operation any number of times. Return the minimum number of operations needed
// to convert |current| to |correct|.
//
//

LEETCODE_BEGIN_RESOLVING(2224, MinimumNumberOfOperationsToConvertTime,
                         Solution);

class Solution {
public:
  int convertTime(string current, string correct) {
    int beg = 60 * (10 * (current[0] - '0') + current[1] - '0') +
              10 * (current[3] - '0') + current[4] - '0';
    int end = 60 * (10 * (correct[0] - '0') + correct[1] - '0') +
              10 * (correct[3] - '0') + correct[4] - '0';
    int res = 0;
    while (beg != end) {
      if (end - 60 >= beg) {
        beg += 60;
      } else if (end - 15 >= beg) {
        beg += 15;
      } else if (end - 5 >= beg) {
        beg += 5;
      } else {
        ++beg;
      }
      ++res;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |current| and |correct| are in the format |"HH:MM"|
// * |current <= correct|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: current = "02:30", correct = "04:35"
// Output: 3
// Explanation:
// We can convert current to correct in 3 operations as follows:
// - Add 60 minutes to current. current becomes "03:30".
// - Add 60 minutes to current. current becomes "04:30".
// - Add 5 minutes to current. current becomes "04:35".
// It can be proven that it is not possible to convert current to correct in
// fewer than 3 operations.
//

LEETCODE_SOLUTION_UNITTEST(2224, MinimumNumberOfOperationsToConvertTime,
                           example_1) {
  auto   solution = MakeSolution();
  string current  = "02:30";
  string correct  = "04:35";
  int    expect   = 3;
  int    actual   = solution->convertTime(current, correct);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: current = "11:00", correct = "11:01"
// Output: 1
//
// We only have to add one minute to current, so the minimum number of
// operations needed is 1.

LEETCODE_SOLUTION_UNITTEST(2224, MinimumNumberOfOperationsToConvertTime,
                           example_2) {
  auto   solution = MakeSolution();
  string current  = "11:00";
  string correct  = "11:01";
  int    expect   = 1;
  int    actual   = solution->convertTime(current, correct);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "00:00"
// "23:59"
// Output: 32
//

LEETCODE_SOLUTION_UNITTEST(2224, MinimumNumberOfOperationsToConvertTime,
                           extra_testcase_1) {
  auto   solution = MakeSolution();
  string current  = "00:00";
  string correct  = "23:59";
  int    expect   = 32;
  int    actual   = solution->convertTime(current, correct);
  LCD_EXPECT_EQ(expect, actual);
}
