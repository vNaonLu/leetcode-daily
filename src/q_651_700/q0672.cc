// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Bulb Switcher II
//
// https://leetcode.com/problems/bulb-switcher-ii/
//
// Question ID: 672
// Difficult  : Medium
// Solve Date : 2024/06/04 18:38

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |672. Bulb Switcher II|:
//
// There is a room with |n| bulbs labeled from |1| to |n| that all are turned on
// initially, and four buttons on the wall. Each of the four buttons has a
// different functionality where:
//
//  • Button 1: Flips the status of all the bulbs.
//
//  • Button 2: Flips the status of all the bulbs with even labels (i.e., |2, 4,
//  ...|).
//
//  • Button 3: Flips the status of all the bulbs with odd labels (i.e., |1, 3,
//  ...|).
//
//  • Button 4: Flips the status of all the bulbs with a label |j = 3k + 1|
//  where |k = 0, 1, 2, ...| (i.e., |1, 4, 7, 10, ...|).
// You must make exactly |presses| button presses in total. For each press, you
// may pick any of the four buttons to press. Given the two integers |n| and
// |presses|, return the number of different possible statuses after performing
// all |presses| button presses.
//
//

LEETCODE_BEGIN_RESOLVING(672, BulbSwitcherII, Solution);

class Solution {
public:
  int flipLights(int n, int presses) {
    if (presses == 0 || n == 0) {
      return 1;
    }
    if (n == 1) {
      return 2;
    }
    if (n == 2) {
      return presses == 1 ? 3 : 4;
    }
    if (presses == 1) {
      return 4;
    }
    return presses == 2 ? 7 : 8;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 1000|
// * |0 <= presses <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1, presses = 1
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(672, BulbSwitcherII, example_1) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  presses  = 1;
  int  expect   = 2;
  int  actual   = solution->flipLights(n, presses);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2, presses = 1
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(672, BulbSwitcherII, example_2) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  presses  = 1;
  int  expect   = 3;
  int  actual   = solution->flipLights(n, presses);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 3, presses = 1
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(672, BulbSwitcherII, example_3) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  presses  = 1;
  int  expect   = 4;
  int  actual   = solution->flipLights(n, presses);
  LCD_EXPECT_EQ(expect, actual);
}
