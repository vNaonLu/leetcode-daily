// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Combination Sum IV
//
// https://leetcode.com/problems/combination-sum-iv/
//
// Question ID: 377
// Difficult  : Medium
// Solve Date : 2021/10/30 15:09

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |377. Combination Sum IV|:
//
// Given an array of distinct integers |nums| and a target integer |target|,
// return the number of possible combinations that add up to  |target|. The test
// cases are generated so that the answer can fit in a 32-bit integer.  
//

LEETCODE_BEGIN_RESOLVING(377, CombinationSumIV, Solution);

class Solution {
private:
  vector<int> dp;
  bool        init = false;

public:
  int combinationSum4(vector<int> &nums, int target) {
    if (!init) {
      init = true;
      dp.resize(1001, -1);
      dp[0] = 1;
    }
    if (target < 0)
      return 0;
    if (dp[target] != -1)
      return dp[target];
    dp[target] = 0;
    for (const int &c : nums) {
      dp[target] += combinationSum4(nums, target - c);
    }
    return dp[target];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 200|
// * |1 <= nums[i] <= 1000|
// * All the elements of |nums| are unique.
// * |1 <= target <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3], target = 4
// Output: 7
//
// The possible combination ways are:
// (1, 1, 1, 1)
// (1, 1, 2)
// (1, 2, 1)
// (1, 3)
// (2, 1, 1)
// (2, 2)
// (3, 1)
// Note that different sequences are counted as different combinations.

LEETCODE_SOLUTION_UNITTEST(377, CombinationSumIV, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  int         target   = 4;
  int         expect   = 7;
  int         actual   = solution->combinationSum4(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [9], target = 3
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(377, CombinationSumIV, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {9};
  int         target   = 3;
  int         expect   = 0;
  int         actual   = solution->combinationSum4(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}
