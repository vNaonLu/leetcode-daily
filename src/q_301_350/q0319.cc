// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Bulb Switcher
//
// https://leetcode.com/problems/bulb-switcher/
//
// Question ID: 319
// Difficult  : Medium
// Solve Date : 2023/04/27 18:45

#include <cmath>
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |319. Bulb Switcher|:
//
// There are |n| bulbs that are initially off. You first turn on all the bulbs,
// then you turn off every second bulb. On the third round, you toggle every
// third bulb (turning on if it's off or turning off if it's on). For the |iᵗʰ|
// round, you toggle every |i| bulb. For the |nᵗʰ| round, you only toggle the
// last bulb. Return the number of bulbs that are on after |n| rounds.
//
//

LEETCODE_BEGIN_RESOLVING(319, BulbSwitcher, Solution);

class Solution {
public:
  int bulbSwitch(int n) { return sqrt(n); }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= n <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3
// Output: 1
//
// At first, the three bulbs are [off, off, off].
// After the first round, the three bulbs are [on, on, on].
// After the second round, the three bulbs are [on, off, on].
// After the third round, the three bulbs are [on, off, off].
// So you should return 1 because there is only one bulb is on.

LEETCODE_SOLUTION_UNITTEST(319, BulbSwitcher, example_1) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  expect   = 1;
  int  actual   = solution->bulbSwitch(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 0
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(319, BulbSwitcher, example_2) {
  auto solution = MakeSolution();
  int  n        = 0;
  int  expect   = 0;
  int  actual   = solution->bulbSwitch(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(319, BulbSwitcher, example_3) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 1;
  int  actual   = solution->bulbSwitch(n);
  LCD_EXPECT_EQ(expect, actual);
}
