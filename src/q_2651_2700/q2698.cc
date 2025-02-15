// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find the Punishment Number of an Integer
//
// https://leetcode.com/problems/find-the-punishment-number-of-an-integer/
//
// Question ID: 2698
// Difficult  : Medium
// Solve Date : 2025/02/15 14:14

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2698. Find the Punishment Number of an Integer|:
//
// Given a positive integer |n|, return the punishment number of |n|.
// The punishment number of |n| is defined as the sum of the squares of all
// integers |i| such that:
//
//  • |1 <= i <= n|
//
//  • The decimal representation of |i * i| can be partitioned into contiguous
//  substrings such that the sum of the integer values of these substrings
//  equals |i|.
//
//

LEETCODE_BEGIN_RESOLVING(2698, FindThePunishmentNumberOfAnInteger, Solution);

class Solution {
public:
  int punishmentNumber(int n) {
    int res = 0;
    for (int i = 1; i <= n; ++i) {
      int x = i * i;
      res += (partition(x, i)) ? x : 0;
    }
    return res;
  }

private:
  bool partition(int x, int target) {
    if (x == target) {
      return true;
    }

    if (x == 0) {
      return target == 0;
    }

    int m0 = min(x, 1000);
    for (int m = 10; m <= m0; m *= 10) {
      if (partition(x / m, target - x % m)) {
        return true;
      }
    }

    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 10
// Output: 182
//

LEETCODE_SOLUTION_UNITTEST(2698, FindThePunishmentNumberOfAnInteger,
                           example_1) {
  auto solution = MakeSolution();
  int  n        = 10;
  int  expect   = 182;
  int  actual   = solution->punishmentNumber(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 37
// Output: 1478
//

LEETCODE_SOLUTION_UNITTEST(2698, FindThePunishmentNumberOfAnInteger,
                           example_2) {
  auto solution = MakeSolution();
  int  n        = 37;
  int  expect   = 1478;
  int  actual   = solution->punishmentNumber(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 235
// Output: 96559
//

LEETCODE_SOLUTION_UNITTEST(2698, FindThePunishmentNumberOfAnInteger,
                           extra_testcase_1) {
  auto solution = MakeSolution();
  int  n        = 235;
  int  expect   = 96559;
  int  actual   = solution->punishmentNumber(n);
  LCD_EXPECT_EQ(expect, actual);
}
