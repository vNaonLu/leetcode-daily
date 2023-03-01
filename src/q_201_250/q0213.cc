// Copyright 2023 Naon Lu
//
// This file describes the solution of
// House Robber II
//
// https://leetcode.com/problems/house-robber-ii/
//
// Question ID: 213
// Difficult  : Medium
// Solve Date : 2021/09/30 13:33

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |213. House Robber II|:
//
// You are a professional robber planning to rob houses along a street. Each
// house has a certain amount of money stashed. All houses at this place are
// arranged in a circle. That means the first house is the neighbor of the last
// one. Meanwhile, adjacent houses have a security system connected, and it will
// automatically contact the police if two adjacent houses were broken into on
// the same night. Given an integer array |nums| representing the amount of
// money of each house, return the maximum amount of money you can rob tonight
// without alerting the police.  
//

LEETCODE_BEGIN_RESOLVING(213, HouseRobberII, Solution);

class Solution {
private:
  int helper(vector<int> &prices) {
    if (prices.empty())
      return 0;
    if (prices.size() == 1)
      return prices[0];
    vector<int> res(prices.size(), 0);
    res[0] = prices[0];
    res[1] = max(prices[1], prices[0]);
    for (int i = 2; i < prices.size(); ++i)
      res[i] = max(res[i - 1], res[i - 2] + prices[i]);
    return res.back();
  }

public:
  int rob(vector<int> &nums) {
    if (nums.empty())
      return 0;
    else if (nums.size() == 1)
      return nums[0];
    vector<int> rob_first(nums.begin(), nums.end() - 1);
    vector<int> not_rob_first(nums.begin() + 1, nums.end());
    return max(helper(rob_first), helper(not_rob_first));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |0 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,3,2]
// Output: 3
//
// You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because
// they are adjacent houses.

LEETCODE_SOLUTION_UNITTEST(213, HouseRobberII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 2};
  int         expect   = 3;
  int         actual   = solution->rob(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,1]
// Output: 4
//
// Rob house 1 (money = 1) and then rob house 3 (money = 3).
// Total amount you can rob = 1 + 3 = 4.

LEETCODE_SOLUTION_UNITTEST(213, HouseRobberII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 1};
  int         expect   = 4;
  int         actual   = solution->rob(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(213, HouseRobberII, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  int         expect   = 3;
  int         actual   = solution->rob(nums);
  LCD_EXPECT_EQ(expect, actual);
}
