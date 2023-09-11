// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Latest Time by Replacing Hidden Digits
//
// https://leetcode.com/problems/latest-time-by-replacing-hidden-digits/
//
// Question ID: 1736
// Difficult  : Easy
// Solve Date : 2023/09/06 09:44

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1736. Latest Time by Replacing Hidden Digits|:
//
// You are given a string |time| in the form of | hh:mm|, where some of the
// digits in the string are hidden (represented by |?|). The valid times are
// those inclusively between |00:00| and |23:59|. Return the latest valid time
// you can get from |time| by replacing the hidden digits.
//
//

LEETCODE_BEGIN_RESOLVING(1736, LatestTimeByReplacingHiddenDigits, Solution);

class Solution {
public:
  string maximumTime(string time) {
    string res = time;
    if (res[0] == '?') {
      res[0] = (res[1] != '?' && res[1] >= '4') ? '1' : '2';
    }
    if (res[1] == '?') {
      res[1] = res[0] == '2' ? '3' : '9';
    }
    if (res[3] == '?') {
      res[3] = '5';
    }
    if (res[4] == '?') {
      res[4] = '9';
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |time| is in the format |hh:mm|.
// * It is guaranteed that you can produce a valid time from the given string.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: time = "2?:?0"
// Output: "23:50"
//
// The latest hour beginning with the digit '2' is 23 and the latest minute
// ending with the digit '0' is 50.

LEETCODE_SOLUTION_UNITTEST(1736, LatestTimeByReplacingHiddenDigits, example_1) {
  auto   solution = MakeSolution();
  string time     = "2?:?0";
  string expect   = "23:50";
  string actual   = solution->maximumTime(time);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: time = "0?:3?"
// Output: "09:39"
//

LEETCODE_SOLUTION_UNITTEST(1736, LatestTimeByReplacingHiddenDigits, example_2) {
  auto   solution = MakeSolution();
  string time     = "0?:3?";
  string expect   = "09:39";
  string actual   = solution->maximumTime(time);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: time = "1?:22"
// Output: "19:22"
//

LEETCODE_SOLUTION_UNITTEST(1736, LatestTimeByReplacingHiddenDigits, example_3) {
  auto   solution = MakeSolution();
  string time     = "1?:22";
  string expect   = "19:22";
  string actual   = solution->maximumTime(time);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "?4:03"
// Output: "14:03"
//

LEETCODE_SOLUTION_UNITTEST(1736, LatestTimeByReplacingHiddenDigits,
                           extra_testcase_1) {
  auto   solution = MakeSolution();
  string time     = "?4:03";
  string expect   = "14:03";
  string actual   = solution->maximumTime(time);
  LCD_EXPECT_EQ(expect, actual);
}
