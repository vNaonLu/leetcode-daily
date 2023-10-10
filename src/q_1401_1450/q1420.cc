// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Build Array Where You Can Find The Maximum Exactly K Comparisons
//
// https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/
//
// Question ID: 1420
// Difficult  : Hard
// Solve Date : 2023/10/07 18:55

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1420. Build Array Where You Can Find The Maximum Exactly K
// Comparisons|:
//
// You are given three integers |n|, |m| and |k|. Consider the following
// algorithm to find the maximum element of an array of positive integers:
// ![img](https://assets.leetcode.com/uploads/2020/04/02/e.png)
// You should build the array arr which has the following properties:
//
//  • |arr| has exactly |n| integers.
//
//  • |1 <= arr[i] <= m| where |(0 <= i < n)|.
//
//  • After applying the mentioned algorithm to |arr|, the value |search_cost|
//  is equal to |k|.
// Return the number of ways to build the array |arr| under the mentioned
// conditions. As the answer may grow large, the answer must be computed modulo
// |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(1420,
                         BuildArrayWhereYouCanFindTheMaximumExactlyKComparisons,
                         Solution);

class Solution {
public:
  int numOfArrays(int n, int m, int k) {
    vector<vector<vector<int>>> dp(51,
                                   vector<vector<int>>(101, vector<int>(51)));
    vector<vector<vector<int>>> pre(51,
                                    vector<vector<int>>(101, vector<int>(51)));
    for (int j = 0; j <= m; ++j) {
      dp[1][j][1]  = 1;
      pre[1][j][1] = j;
    }
    for (int len = 2; len <= n; ++len) {
      for (int mx = 1; mx <= m; ++mx) {
        for (int cost = 1; cost <= k; ++cost) {
          dp[len][mx][cost] = (1ll * mx * dp[len - 1][mx][cost]) % kMod;
          dp[len][mx][cost] =
              (dp[len][mx][cost] + pre[len - 1][mx - 1][cost - 1]) % kMod;
          pre[len][mx][cost] =
              (pre[len][mx - 1][cost] + dp[len][mx][cost]) % kMod;
        }
      }
    }
    return pre[n][m][k];
  }

private:
  constexpr static int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 50|
// * |1 <= m <= 100|
// * |0 <= k <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2, m = 3, k = 1
// Output: 6
//
// The possible arrays are [1, 1], [2, 1], [2, 2], [3, 1], [3, 2] [3, 3]

LEETCODE_SOLUTION_UNITTEST(
    1420, BuildArrayWhereYouCanFindTheMaximumExactlyKComparisons, example_1) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  m        = 3;
  int  k        = 1;
  int  expect   = 6;
  int  actual   = solution->numOfArrays(n, m, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5, m = 2, k = 3
// Output: 0
//
// There are no possible arrays that satisify the mentioned conditions.

LEETCODE_SOLUTION_UNITTEST(
    1420, BuildArrayWhereYouCanFindTheMaximumExactlyKComparisons, example_2) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  m        = 2;
  int  k        = 3;
  int  expect   = 0;
  int  actual   = solution->numOfArrays(n, m, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 9, m = 1, k = 1
// Output: 1
//
// The only possible array is [1, 1, 1, 1, 1, 1, 1, 1, 1]

LEETCODE_SOLUTION_UNITTEST(
    1420, BuildArrayWhereYouCanFindTheMaximumExactlyKComparisons, example_3) {
  auto solution = MakeSolution();
  int  n        = 9;
  int  m        = 1;
  int  k        = 1;
  int  expect   = 1;
  int  actual   = solution->numOfArrays(n, m, k);
  LCD_EXPECT_EQ(expect, actual);
}
