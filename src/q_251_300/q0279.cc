// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Perfect Squares
//
// https://leetcode.com/problems/perfect-squares/
//
// Question ID: 279
// Difficult  : Medium
// Solve Date : 2021/10/14 11:56

#include <iosfwd>
#include <limits>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |279. Perfect Squares|:
//
// Given an integer |n|, return the least number of perfect square numbers that
// sum to |n|. A perfect square is an integer that is the square of an integer;
// in other words, it is the product of some integer with itself. For example,
// |1|, |4|, |9|, and |16| are perfect squares while |3| and |11| are not.  
//

LEETCODE_BEGIN_RESOLVING(279, PerfectSquares, Solution);

class Solution {
public:
  int numSquares(int n) {
    vector<int> dp(n + 1, numeric_limits<int>::max());
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
      for (int j = 1; j * j <= i; ++j) {
        dp[i] = min(dp[i], 1 + dp[i - j * j]);
      }
    }
    return dp.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 12
// Output: 3
//
// 12 = 4 + 4 + 4.

LEETCODE_SOLUTION_UNITTEST(279, PerfectSquares, example_1) {
  auto solution = MakeSolution();
  int  n        = 12;
  int  expect   = 3;
  int  actual   = solution->numSquares(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 13
// Output: 2
//
// 13 = 4 + 9.

LEETCODE_SOLUTION_UNITTEST(279, PerfectSquares, example_2) {
  auto solution = MakeSolution();
  int  n        = 13;
  int  expect   = 2;
  int  actual   = solution->numSquares(n);
  LCD_EXPECT_EQ(expect, actual);
}
