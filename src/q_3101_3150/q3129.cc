// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Find All Possible Stable Binary Arrays I
//
// https://leetcode.com/problems/find-all-possible-stable-binary-arrays-i/
//
// Question ID: 3129
// Difficult  : Medium
// Solve Date : 2026/03/09 17:57

#include <iosfwd>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3129. Find All Possible Stable Binary Arrays I|:
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

LEETCODE_BEGIN_RESOLVING(3129, FindAllPossibleStableBinaryArraysI, Solution);

class Solution {
public:
  int numberOfStableArrays(int zero, int one, int limit) {
    static int          MOD = 1e9 + 7;
    vector<vector<int>> dp0(zero + 1, vector<int>(one + 1, 0));
    vector<vector<int>> dp1(zero + 1, vector<int>(one + 1, 0));

    for (int i = 1; i <= min(zero, limit); i++) {
      dp0[i][0] = 1;
    }

    for (int j = 1; j <= min(one, limit); j++) {
      dp1[0][j] = 1;
    }

    for (int i = 1; i <= zero; i++) {
      for (int j = 1; j <= one; j++) {
        long long val0 = (long long)dp0[i - 1][j] + dp1[i - 1][j];
        if (i - limit - 1 >= 0) {
          val0 -= dp1[i - limit - 1][j];
        }
        dp0[i][j] = (val0 % MOD + MOD) % MOD;

        long long val1 = (long long)dp0[i][j - 1] + dp1[i][j - 1];
        if (j - limit - 1 >= 0) {
          val1 -= dp0[i][j - limit - 1];
        }
        dp1[i][j] = (val1 % MOD + MOD) % MOD;
      }
    }
    return ((long long)dp0[zero][one] + dp1[zero][one]) % MOD;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= zero, one, limit <= 200|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: zero = 1, one = 1, limit = 2
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3129, FindAllPossibleStableBinaryArraysI,
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

LEETCODE_SOLUTION_UNITTEST(3129, FindAllPossibleStableBinaryArraysI,
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

LEETCODE_SOLUTION_UNITTEST(3129, FindAllPossibleStableBinaryArraysI,
                           example_3) {
  auto solution = MakeSolution();
  int  zero     = 3;
  int  one      = 3;
  int  limit    = 2;
  int  expect   = 14;
  int  actual   = solution->numberOfStableArrays(zero, one, limit);
  LCD_EXPECT_EQ(expect, actual);
}
