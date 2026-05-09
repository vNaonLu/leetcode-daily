// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Find All Possible Stable Binary Arrays II
//
// https://leetcode.com/problems/find-all-possible-stable-binary-arrays-ii/
//
// Question ID: 3130
// Difficult  : Hard
// Solve Date : 2026/03/10 13:28

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3130. Find All Possible Stable Binary Arrays II|:
//
// You are given 3 positive integers |zero|, |one|, and |limit|.
// A binary array |arr| is called stable if:
//
//  • The number of occurrences of 0 in |arr| is exactly |zero|.
//
//  • The number of occurrences of 1 in |arr| is exactly |one|.
//
//  • Each subarray of |arr| with a size greater than |limit| must contain both
//  0 and 1.
// Return the total number of stable binary arrays.
// Since the answer may be very large, return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(3130, FindAllPossibleStableBinaryArraysII, Solution);

class Solution {
public:
  int numberOfStableArrays(int zero, int one, int limit) {
    const int                         MOD = 1e9 + 7;
    vector<vector<array<int64_t, 2>>> dp(
        zero + 1, vector<array<int64_t, 2>>(one + 1, {0LL, 0LL}));

    for (int i = 1; i <= min(zero, limit); i++)
      dp[i][0][0] = 1;
    for (int j = 1; j <= min(one, limit); j++)
      dp[0][j][1] = 1;

    for (int i = 1; i <= zero; i++) {
      for (int j = 1; j <= one; j++) {
        int64_t over0 = (i - limit >= 1) ? dp[i - limit - 1][j][1] : 0;
        int64_t over1 = (j - limit >= 1) ? dp[i][j - limit - 1][0] : 0;
        dp[i][j][0]   = (dp[i - 1][j][0] + dp[i - 1][j][1] - over0 + MOD) % MOD;
        dp[i][j][1]   = (dp[i][j - 1][0] + dp[i][j - 1][1] - over1 + MOD) % MOD;
      }
    }
    return (dp[zero][one][0] + dp[zero][one][1]) % MOD;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= zero, one, limit <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: zero = 1, one = 1, limit = 2
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3130, FindAllPossibleStableBinaryArraysII,
                           example_1) {
  auto solution = MakeSolution();
  int  zero     = 1;
  int  one      = 1;
  int  limit    = 2;
  int  expect   = 2;
  int  actual   = solution->numberOfStableArrays(zero, one, limit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: zero = 1, one = 2, limit = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3130, FindAllPossibleStableBinaryArraysII,
                           example_2) {
  auto solution = MakeSolution();
  int  zero     = 1;
  int  one      = 2;
  int  limit    = 1;
  int  expect   = 1;
  int  actual   = solution->numberOfStableArrays(zero, one, limit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: zero = 3, one = 3, limit = 2
// Output: 14
//

LEETCODE_SOLUTION_UNITTEST(3130, FindAllPossibleStableBinaryArraysII,
                           example_3) {
  auto solution = MakeSolution();
  int  zero     = 3;
  int  one      = 3;
  int  limit    = 2;
  int  expect   = 14;
  int  actual   = solution->numberOfStableArrays(zero, one, limit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 22
// 16
// 62
// Output: 239974276
//

LEETCODE_SOLUTION_UNITTEST(3130, FindAllPossibleStableBinaryArraysII,
                           extra_testcase_1) {
  auto solution = MakeSolution();
  int  zero     = 22;
  int  one      = 16;
  int  limit    = 62;
  int  expect   = 239974276;
  int  actual   = solution->numberOfStableArrays(zero, one, limit);
  LCD_EXPECT_EQ(expect, actual);
}
