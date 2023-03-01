// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Ugly Number II
//
// https://leetcode.com/problems/ugly-number-ii/
//
// Question ID: 264
// Difficult  : Medium
// Solve Date : 2021/10/20 13:30

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |264. Ugly Number II|:
//
// An ugly number is a positive integer whose prime factors are limited to |2|,
// |3|, and |5|. Given an integer |n|, return the |nᵗʰ| ugly number.  
//

LEETCODE_BEGIN_RESOLVING(264, UglyNumberII, Solution);

class Solution {
public:
  int nthUglyNumber(int n) {
    vector<int> dp(n, 1);
    int         fac2 = 0, fac3 = 0, fac5 = 0;
    for (int i = 1; i < n; ++i) {
      dp[i] = min({dp[fac2] * 2, dp[fac3] * 3, dp[fac5] * 5});
      if (dp[i] == dp[fac2] * 2) {
        ++fac2;
      }
      if (dp[i] == dp[fac3] * 3) {
        ++fac3;
      }
      if (dp[i] == dp[fac5] * 5) {
        ++fac5;
      }
    }
    return dp.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 1690|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 10
// Output: 12
//
// [1, 2, 3, 4, 5, 6, 8, 9, 10, 12] is the sequence of the first 10 ugly
// numbers.

LEETCODE_SOLUTION_UNITTEST(264, UglyNumberII, example_1) {
  auto solution = MakeSolution();
  int  n        = 10;
  int  expect   = 12;
  int  actual   = solution->nthUglyNumber(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: 1
//
// 1 has no prime factors, therefore all of its prime factors are limited to 2,
// 3, and 5.

LEETCODE_SOLUTION_UNITTEST(264, UglyNumberII, example_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 1;
  int  actual   = solution->nthUglyNumber(n);
  LCD_EXPECT_EQ(expect, actual);
}
