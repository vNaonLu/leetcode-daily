// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Cuts to Divide a Circle
//
// https://leetcode.com/problems/minimum-cuts-to-divide-a-circle/
//
// Question ID: 2481
// Difficult  : Easy
// Solve Date : 2023/05/30 19:54

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2481. Minimum Cuts to Divide a Circle|:
//
// A valid cut in a circle can be:
//
//  • A cut that is represented by a straight line that touches two points on
//  the edge of the circle and passes through its center, or
//
//  • A cut that is represented by a straight line that touches one point on the
//  edge of the circle and its center.
// Some valid and invalid cuts are shown in the figures below.
// ![img](https://assets.leetcode.com/uploads/2022/10/29/alldrawio.png)
// Given the integer |n|, return the minimum number of cuts needed to divide a
// circle into |n| equal slices.
//
//

LEETCODE_BEGIN_RESOLVING(2481, MinimumCutsToDivideACircle, Solution);

class Solution {
public:
  int numberOfCuts(int n) { return n == 1 ? 0 : (n & 1) ? n : n / 2; }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4
// Output: 2
//
// The above figure shows how cutting the circle twice through the middle
// divides it into 4 equal slices.

LEETCODE_SOLUTION_UNITTEST(2481, MinimumCutsToDivideACircle, example_1) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  expect   = 2;
  int  actual   = solution->numberOfCuts(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3
// Output: 3
//
// At least 3 cuts are needed to divide the circle into 3 equal slices.
// It can be shown that less than 3 cuts cannot result in 3 slices of equal size
// and shape. Also note that the first cut will not divide the circle into
// distinct parts.

LEETCODE_SOLUTION_UNITTEST(2481, MinimumCutsToDivideACircle, example_2) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  expect   = 3;
  int  actual   = solution->numberOfCuts(n);
  LCD_EXPECT_EQ(expect, actual);
}
