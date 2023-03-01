// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Dice Rolls With Target Sum
//
// https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/
//
// Question ID: 1155
// Difficult  : Medium
// Solve Date : 2022/02/10 15:42

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1155. Number of Dice Rolls With Target Sum|:
//
// You have |n| dice, and each die has |k| faces numbered from |1| to |k|.
// Given three integers |n|, |k|, and |target|, return the number of possible
// ways (out of the |kⁿ| total ways) to roll the dice, so the sum of the face-up
// numbers equals |target|. Since the answer may be too large, return it modulo
// |10⁹ + 7|.  
//

LEETCODE_BEGIN_RESOLVING(1155, NumberOfDiceRollsWithTargetSum, Solution);

class Solution {
private:
  static constexpr int kMod = 1e+9 + 7;

public:
  int numRollsToTarget(int n, int k, int target) {
    if (n > target || n * k < target)
      return 0;
    vector<int> dp(target + 1, 0), next(target + 1, 0);
    for (int i = 1; i < dp.size(); ++i)
      dp[i] += dp[i - 1] + (i <= k);
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j <= target; ++j) {
        if (j <= i) {
          next[j] = 0;
        } else {
          next[j] = ((next[j - 1] + dp[j - 1] - dp[max(0, j - k - 1)]) % kMod +
                     kMod) %
                    kMod;
        }
      }
      swap(dp, next);
    }
    return (dp[target] - dp[target - 1] + kMod) % kMod;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n, k <= 30|
// * |1 <= target <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1, k = 6, target = 3
// Output: 1
//
// You throw one die with 6 faces.
// There is only one way to get a sum of 3.

LEETCODE_SOLUTION_UNITTEST(1155, NumberOfDiceRollsWithTargetSum, example_1) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  k        = 6;
  int  target   = 3;
  int  expect   = 1;
  int  actual   = solution->numRollsToTarget(n, k, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2, k = 6, target = 7
// Output: 6
//
// You throw two dice, each with 6 faces.
// There are 6 ways to get a sum of 7: 1+6, 2+5, 3+4, 4+3, 5+2, 6+1.

LEETCODE_SOLUTION_UNITTEST(1155, NumberOfDiceRollsWithTargetSum, example_2) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  k        = 6;
  int  target   = 7;
  int  expect   = 6;
  int  actual   = solution->numRollsToTarget(n, k, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 30, k = 30, target = 500
// Output: 222616187
//
// The answer must be returned modulo 10⁹ + 7.

LEETCODE_SOLUTION_UNITTEST(1155, NumberOfDiceRollsWithTargetSum, example_3) {
  auto solution = MakeSolution();
  int  n        = 30;
  int  k        = 30;
  int  target   = 500;
  int  expect   = 222616187;
  int  actual   = solution->numRollsToTarget(n, k, target);
  LCD_EXPECT_EQ(expect, actual);
}
