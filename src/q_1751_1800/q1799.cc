// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximize Score After N Operations
//
// https://leetcode.com/problems/maximize-score-after-n-operations/
//
// Question ID: 1799
// Difficult  : Hard
// Solve Date : 2023/05/14 19:19

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1799. Maximize Score After N Operations|:
//
// You are given |nums|, an array of positive integers of size |2 * n|. You must
// perform |n| operations on this array. In the |iᵗʰ| operation (1-indexed), you
// will:
//
//  • Choose two elements, |x| and |y|.
//
//  • Receive a score of |i * gcd(x, y)|.
//
//  • Remove |x| and |y| from |nums|.
// Return the maximum score you can receive after performing |n| operations.
// The function |gcd(x, y)| is the greatest common divisor of |x| and |y|.
//
//

LEETCODE_BEGIN_RESOLVING(1799, MaximizeScoreAfterNOperations, Solution);

class Solution {
public:
  int maxScore(vector<int> &nums) {
    vector<int> dp(1 << 14);
    return dfs(nums, (1 << 14) - 1, nums.size() / 2, dp);
  }

private:
  int dfs(vector<int> &nums, int state, int curr, vector<int> &dp) {
    if (curr == 0) {
      return 0;
    }
    if (dp[state]) {
      return dp[state];
    }
    int         res = 0;
    int         n   = nums.size();
    vector<int> total;
    for (int i = 0; i < n; ++i) {
      if (state & (1 << i)) {
        total.emplace_back(i);
      }
    }
    for (int i = 0; i < total.size(); ++i) {
      for (int j = i + 1; j < total.size(); ++j) {
        res = max(res, gcd(nums[total[i]], nums[total[j]]) * curr +
                           dfs(nums,
                               (state & (~((1 << total[i]) | (1 << total[j])))),
                               curr - 1, dp));
      }
    }
    return dp[state] = res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 7|
// * |nums.length == 2 * n|
// * |1 <= nums[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2]
// Output: 1
//
//  The optimal choice of operations is:
// (1 * gcd(1, 2)) = 1

LEETCODE_SOLUTION_UNITTEST(1799, MaximizeScoreAfterNOperations, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2};
  int         expect   = 1;
  int         actual   = solution->maxScore(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,4,6,8]
// Output: 11
//
//  The optimal choice of operations is:
// (1 * gcd(3, 6)) + (2 * gcd(4, 8)) = 3 + 8 = 11

LEETCODE_SOLUTION_UNITTEST(1799, MaximizeScoreAfterNOperations, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 4, 6, 8};
  int         expect   = 11;
  int         actual   = solution->maxScore(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3,4,5,6]
// Output: 14
//
//  The optimal choice of operations is:
// (1 * gcd(1, 5)) + (2 * gcd(2, 4)) + (3 * gcd(3, 6)) = 1 + 4 + 9 = 14

LEETCODE_SOLUTION_UNITTEST(1799, MaximizeScoreAfterNOperations, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5, 6};
  int         expect   = 14;
  int         actual   = solution->maxScore(nums);
  LCD_EXPECT_EQ(expect, actual);
}
