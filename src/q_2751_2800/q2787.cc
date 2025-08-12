// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Ways to Express an Integer as Sum of Powers
//
// https://leetcode.com/problems/ways-to-express-an-integer-as-sum-of-powers/
//
// Question ID: 2787
// Difficult  : Medium
// Solve Date : 2025/08/12 20:47

#include <cmath>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2787. Ways to Express an Integer as Sum of Powers|:
//
// Given two positive integers |n| and |x|.
// Return the number of ways |n| can be expressed as the sum of the |xᵗʰ| power
// of unique positive integers, in other words, the number of sets of unique
// integers |[n₁, n₂, ..., nₖ]| where |n = n₁ˣ + n₂ˣ + ... + nₖˣ|. Since the
// result can be very large, return it modulo |10⁹ + 7|. For example, if |n =
// 160| and |x = 3|, one way to express |n| is |n = 2³ + 3³ + 5³|.
//
//

LEETCODE_BEGIN_RESOLVING(2787, WaysToExpressAnIntegerAsSumOfPowers, Solution);

class Solution {
public:
  int numberOfWays(int n, int x) {
    vector<int> powers;
    powers.reserve(n + 1);
    for (int i = 1; pow(i, x) <= n; ++i) {
      powers.emplace_back(pow(i, x));
    }

    vector<int> dp(n + 1);
    dp[0] = 1;
    for (auto p : powers) {
      for (int i = n; i >= p; --i) {
        dp[i] = (dp[i] + dp[i - p]) % kMod;
      }
    }
    return dp.back();
  }

private:
  constexpr static int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 300|
// * |1 <= x <= 5|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 10, x = 2
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2787, WaysToExpressAnIntegerAsSumOfPowers,
                           example_1) {
  auto solution = MakeSolution();
  int  n        = 10;
  int  x        = 2;
  int  expect   = 1;
  int  actual   = solution->numberOfWays(n, x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, x = 1
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2787, WaysToExpressAnIntegerAsSumOfPowers,
                           example_2) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  x        = 1;
  int  expect   = 2;
  int  actual   = solution->numberOfWays(n, x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 6
// 1
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2787, WaysToExpressAnIntegerAsSumOfPowers,
                           extra_testcase_1) {
  auto solution = MakeSolution();
  int  n        = 6;
  int  x        = 1;
  int  expect   = 4;
  int  actual   = solution->numberOfWays(n, x);
  LCD_EXPECT_EQ(expect, actual);
}
