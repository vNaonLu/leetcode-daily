// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Partition Equal Subset Sum
//
// https://leetcode.com/problems/partition-equal-subset-sum/
//
// Question ID: 416
// Difficult  : Medium
// Solve Date : 2021/12/12 15:04

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |416. Partition Equal Subset Sum|:
//
// Given an integer array |nums|, return |true| if you can partition the array
// into two subsets such that the sum of the elements in both subsets is equal
// or |false| otherwise.  
//

LEETCODE_BEGIN_RESOLVING(416, PartitionEqualSubsetSum, Solution);

class Solution {
public:
  bool canPartition(vector<int> &nums) {
    uint32_t sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2)
      return false;
    sum /= 2;
    vector<bool> dp(sum + 1, false);
    dp[0] = true;
    for (const auto &x : nums) {
      for (int i = sum; i >= x; --i) {
        dp[i] = dp[i] | dp[i - x];
      }
    }
    return dp.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 200|
// * |1 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,5,11,5]
// Output: true
//
// The array can be partitioned as [1, 5, 5] and [11].

LEETCODE_SOLUTION_UNITTEST(416, PartitionEqualSubsetSum, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 5, 11, 5};
  bool        expect   = true;
  bool        actual   = solution->canPartition(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,5]
// Output: false
//
// The array cannot be partitioned into equal sum subsets.

LEETCODE_SOLUTION_UNITTEST(416, PartitionEqualSubsetSum, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 5};
  bool        expect   = false;
  bool        actual   = solution->canPartition(nums);
  LCD_EXPECT_EQ(expect, actual);
}
