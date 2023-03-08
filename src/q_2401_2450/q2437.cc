// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Valid Clock Times
//
// https://leetcode.com/problems/number-of-valid-clock-times/
//
// Question ID: 2437
// Difficult  : Easy
// Solve Date : 2023/03/08 20:22

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2437. Number of Valid Clock Times|:
//
// You are given a string of length |5| called |time|, representing the current
// time on a digital clock in the format |"hh:mm"|. The earliest possible time
// is |"00:00"| and the latest possible time is |"23:59"|. In the string |time|,
// the digits represented by the |?|symbol are unknown, and must be replaced
// with a digit from |0| to |9|. Return an integer |answer|, the number of valid
// clock times that can be created by replacing every |?|with a digit from |0|
// to |9|.
//

LEETCODE_BEGIN_RESOLVING(2437, NumberOfValidClockTimes, Solution);

class Solution {
public:
  int countTime(string time) {
    int res = 1;
    if (time[0] == '?' && time[1] == '?') {
      res *= 24;
    } else if (time[0] == '?') {
      res *= time[1] > '3' ? 2 : 3;
    } else if (time[1] == '?') {
      res *= time[0] == '2' ? 4 : 10;
    }
    if (time[3] == '?') {
      res *= 6;
    }
    if (time[4] == '?') {
      res *= 10;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |time| is a valid string of length |5| in the format |"hh:mm"|.
// * |"00" <= hh <= "23"|
// * |"00" <= mm <= "59"|
// * Some of the digits might be replaced with |'?'| and need to be replaced
// with digits from |0| to |9|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: time = "?5:00"
// Output: 2
//
// We can replace the ? with either a 0 or 1, producing "05:00" or "15:00". Note
// that we cannot replace it with a 2, since the time "25:00" is invalid. In
// total, we have two choices.

LEETCODE_SOLUTION_UNITTEST(2437, NumberOfValidClockTimes, example_1) {
  auto   solution = MakeSolution();
  string time     = "?5:00";
  int    expect   = 2;
  int    actual   = solution->countTime(time);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: time = "0?:0?"
// Output: 100
//
// Each ? can be replaced by any digit from 0 to 9, so we have 100 total
// choices.

LEETCODE_SOLUTION_UNITTEST(2437, NumberOfValidClockTimes, example_2) {
  auto   solution = MakeSolution();
  string time     = "0?:0?";
  int    expect   = 100;
  int    actual   = solution->countTime(time);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: time = "??:??"
// Output: 1440
//
// There are 24 possible choices for the hours, and 60 possible choices for the
// minutes. In total, we have 24 * 60 = 1440 choices.

LEETCODE_SOLUTION_UNITTEST(2437, NumberOfValidClockTimes, example_3) {
  auto   solution = MakeSolution();
  string time     = "??:??";
  int    expect   = 1440;
  int    actual   = solution->countTime(time);
  LCD_EXPECT_EQ(expect, actual);
}
