// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Pivot Integer
//
// https://leetcode.com/problems/find-the-pivot-integer/
//
// Question ID: 2485
// Difficult  : Easy
// Solve Date : 2023/02/19 22:48

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2485. Find the Pivot Integer|:
//
// Given a positive integer |n|, find the pivot integer |x| such that:
//
//  • The sum of all elements between |1| and |x| inclusively equals the sum of
//  all elements between |x| and |n| inclusively.
// Return the pivot integer |x|. If no such integer exists, return |-1|. It is
// guaranteed that there will be at most one pivot index for the given input.
//

LEETCODE_BEGIN_RESOLVING(2485, FindThePivotInteger, Solution);

class Solution {
public:
  int pivotInteger(int n) {
    int lsum = 0;
    int rsum = 0;
    for (int i = 0; i <= n; ++i) {
      lsum += i;
    }
    for (int i = n; i > 0; --i) {
      rsum += i;
      if (lsum == rsum) {
        return i;
      }
      lsum -= i;
    }

    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 8
// Output: 6
//
// 6 is the pivot integer since: 1 + 2 + 3 + 4 + 5 + 6 = 6 + 7 + 8 = 21.

LEETCODE_SOLUTION_UNITTEST(2485, FindThePivotInteger, example_1) {
  auto solution = MakeSolution();
  int  n        = 8;
  int  expect   = 6;
  int  actual   = solution->pivotInteger(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: 1
//
// 1 is the pivot integer since: 1 = 1.

LEETCODE_SOLUTION_UNITTEST(2485, FindThePivotInteger, example_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 1;
  int  actual   = solution->pivotInteger(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 4
// Output: -1
//
// It can be proved that no such integer exist.

LEETCODE_SOLUTION_UNITTEST(2485, FindThePivotInteger, example_3) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  expect   = -1;
  int  actual   = solution->pivotInteger(n);
  LCD_EXPECT_EQ(expect, actual);
}
