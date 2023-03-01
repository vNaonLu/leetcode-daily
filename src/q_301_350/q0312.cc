// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Burst Balloons
//
// https://leetcode.com/problems/burst-balloons/
//
// Question ID: 312
// Difficult  : Hard
// Solve Date : 2022/01/01 14:36

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |312. Burst Balloons|:
//
// You are given |n| balloons, indexed from |0| to |n - 1|. Each balloon is
// painted with a number on it represented by an array |nums|. You are asked to
// burst all the balloons. If you burst the |iᵗʰ| balloon, you will get |nums[i
// - 1] * nums[i] * nums[i + 1]| coins. If |i - 1| or |i + 1| goes out of bounds
// of the array, then treat it as if there is a balloon with a |1| painted on
// it. Return the maximum coins you can collect by bursting the balloons wisely.
//  
//

LEETCODE_BEGIN_RESOLVING(312, BurstBalloons, Solution);

class Solution {
public:
  int maxCoins(vector<int> &nums) {
    int                 n = nums.size() + 2;
    vector<vector<int>> dp(n, vector<int>(n));
    vector<int>         nnums(n, 1);
    int                 i = 0;
    for (auto num : nums)
      nnums[i++] = num;
    for (int len = 2; len <= n; ++len) {
      for (int i = 0; i <= n - len; ++i) {
        int j = i + len - 1;
        for (int k = i + 1; k < j; ++k)
          dp[i][j] = max(dp[i][j],
                         dp[i][k] + dp[k][j] + nnums[i] * nnums[k] * nnums[j]);
      }
    }
    return dp.front().back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= n <= 300|
// * |0 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,1,5,8]
// Output: 167
//
// nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
// coins = 3*1*5 + 3*5*8 + 1*3*8 + 1*8*1 = 167

LEETCODE_SOLUTION_UNITTEST(312, BurstBalloons, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, 5, 8};
  int         expect   = 167;
  int         actual   = solution->maxCoins(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,5]
// Output: 10
//

LEETCODE_SOLUTION_UNITTEST(312, BurstBalloons, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 5};
  int         expect   = 10;
  int         actual   = solution->maxCoins(nums);
  LCD_EXPECT_EQ(expect, actual);
}
