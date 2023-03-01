// Copyright 2023 Naon Lu
//
// This file describes the solution of
// K Inverse Pairs Array
//
// https://leetcode.com/problems/k-inverse-pairs-array/
//
// Question ID: 629
// Difficult  : Hard
// Solve Date : 2022/07/17 14:25

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |629. K Inverse Pairs Array|:
//
// For an integer array |nums|, an inverse pair is a pair of integers |[i, j]|
// where |0 <= i < j < nums.length| and |nums[i] > nums[j]|. Given two integers
// n and k, return the number of different arrays consist of numbers from |1| to
// |n| such that there are exactly |k| inverse pairs. Since the answer can be
// huge, return it modulo |10⁹ + 7|.
//

LEETCODE_BEGIN_RESOLVING(629, KInversePairsArray, Solution);

class Solution {
private:
  constexpr static int kMod = 1e9 + 7;

public:
  int kInversePairs(int n, int k) {
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j <= k; ++j) {
        if (j == 0) {
          dp[i][j] = 1;
        } else {
          int val =
              (dp[i - 1][j] + kMod - ((j - i) >= 0 ? dp[i - 1][j - i] : 0)) %
              kMod;
          dp[i][j] = (dp[i][j - 1] + val) % kMod;
        }
      }
    }

    return (dp.back().back() + kMod - (k > 0 ? dp.back()[k - 1] : 0)) % kMod;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 1000|
// * |0 <= k <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, k = 0
// Output: 1
//
// Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0
// inverse pairs.

LEETCODE_SOLUTION_UNITTEST(629, KInversePairsArray, example_1) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  k        = 0;
  int  expect   = 1;
  int  actual   = solution->kInversePairs(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, k = 1
// Output: 2
//
// The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.

LEETCODE_SOLUTION_UNITTEST(629, KInversePairsArray, example_2) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  k        = 1;
  int  expect   = 2;
  int  actual   = solution->kInversePairs(n, k);
  LCD_EXPECT_EQ(expect, actual);
}
