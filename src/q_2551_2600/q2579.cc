// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Total Number of Colored Cells
//
// https://leetcode.com/problems/count-total-number-of-colored-cells/
//
// Question ID: 2579
// Difficult  : Medium
// Solve Date : 2025/03/05 12:29

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2579. Count Total Number of Colored Cells|:
//
// There exists an infinitely large two-dimensional grid of uncolored unit
// cells. You are given a positive integer |n|, indicating that you must do the
// following routine for |n| minutes:
//
//  • At the first minute, color any arbitrary unit cell blue.
//
//  • Every minute thereafter, color blue every uncolored cell that touches a
//  blue cell.
// Below is a pictorial representation of the state of the grid after minutes 1,
// 2, and 3.
// ![img](https://assets.leetcode.com/uploads/2023/01/10/example-copy-2.png)
// Return the number of colored cells at the end of |n| minutes.
//
//

LEETCODE_BEGIN_RESOLVING(2579, CountTotalNumberOfColoredCells, Solution);

class Solution {
public:
  long long coloredCells(int n) { return 1ll + 2ll * n * (n - 1); }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2579, CountTotalNumberOfColoredCells, example_1) {
  auto      solution = MakeSolution();
  int       n        = 1;
  long long expect   = 1;
  long long actual   = solution->coloredCells(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(2579, CountTotalNumberOfColoredCells, example_2) {
  auto      solution = MakeSolution();
  int       n        = 2;
  long long expect   = 5;
  long long actual   = solution->coloredCells(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 3
// Output: 13
//

LEETCODE_SOLUTION_UNITTEST(2579, CountTotalNumberOfColoredCells,
                           extra_testcase_1) {
  auto      solution = MakeSolution();
  int       n        = 3;
  long long expect   = 13;
  long long actual   = solution->coloredCells(n);
  LCD_EXPECT_EQ(expect, actual);
}
