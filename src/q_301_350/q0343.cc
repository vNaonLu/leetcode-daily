// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Integer Break
//
// https://leetcode.com/problems/integer-break/
//
// Question ID: 343
// Difficult  : Medium
// Solve Date : 2021/10/06 12:45

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |343. Integer Break|:
//
// Given an integer |n|, break it into the sum of |k| positive integers, where
// |k >= 2|, and maximize the product of those integers. Return the maximum
// product you can get.  
//

LEETCODE_BEGIN_RESOLVING(343, IntegerBreak, Solution);

class Solution {
public:
  int integerBreak(int n) {
    vector<int> dp = {0, 1, 1, 2, 4, 6, 9, 12};
    if (dp.size() > n)
      return dp[n];
    int sz = dp.size();
    dp.resize(n + 1, 0);
    for (int i = sz; i <= n; ++i)
      for (int j = i - 2; j >= 2; --j)
        dp[i] = max(dp[i], j * dp[i - j]);
    return dp[n];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= n <= 58|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2
// Output: 1
//
// 2 = 1 + 1, 1 × 1 = 1.

LEETCODE_SOLUTION_UNITTEST(343, IntegerBreak, example_1) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  expect   = 1;
  int  actual   = solution->integerBreak(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 10
// Output: 36
//
// 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.

LEETCODE_SOLUTION_UNITTEST(343, IntegerBreak, example_2) {
  auto solution = MakeSolution();
  int  n        = 10;
  int  expect   = 36;
  int  actual   = solution->integerBreak(n);
  LCD_EXPECT_EQ(expect, actual);
}
