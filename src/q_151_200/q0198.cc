// Copyright 2023 Naon Lu
//
// This file describes the solution of
// House Robber
//
// https://leetcode.com/problems/house-robber/
//
// Question ID: 198
// Difficult  : Medium
// Solve Date : 2021/09/16 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |198. House Robber|:
//
// You are a professional robber planning to rob houses along a street. Each
// house has a certain amount of money stashed, the only constraint stopping you
// from robbing each of them is that adjacent houses have security systems
// connected and it will automatically contact the police if two adjacent houses
// were broken into on the same night. Given an integer array |nums|
// representing the amount of money of each house, return the maximum amount of
// money you can rob tonight without alerting the police.  
//

LEETCODE_BEGIN_RESOLVING(198, HouseRobber, Solution);

class Solution {
public:
  int rob(vector<int> &nums) {
    vector<int> dp(nums.size() + 1, 0);
    dp[1] = nums[0];
    for (int i = 2; i < nums.size() + 1; ++i) {
      dp[i] = max(nums[i - 1] + dp[i - 2], dp[i - 1]);
    }
    return dp.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |0 <= nums[i] <= 400|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,1]
// Output: 4
//
// Rob house 1 (money = 1) and then rob house 3 (money = 3).
// Total amount you can rob = 1 + 3 = 4.

LEETCODE_SOLUTION_UNITTEST(198, HouseRobber, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 1};
  int         expect   = 4;
  int         actual   = solution->rob(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,7,9,3,1]
// Output: 12
//
// Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
// Total amount you can rob = 2 + 9 + 1 = 12.

LEETCODE_SOLUTION_UNITTEST(198, HouseRobber, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 7, 9, 3, 1};
  int         expect   = 12;
  int         actual   = solution->rob(nums);
  LCD_EXPECT_EQ(expect, actual);
}
