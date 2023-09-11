// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Ascending Subarray Sum
//
// https://leetcode.com/problems/maximum-ascending-subarray-sum/
//
// Question ID: 1800
// Difficult  : Easy
// Solve Date : 2023/09/09 13:04

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1800. Maximum Ascending Subarray Sum|:
//
// Given an array of positive integers |nums|, return the maximum possible sum
// of an ascending subarray in |nums|. A subarray is defined as a contiguous
// sequence of numbers in an array. A subarray |[numsₗ, numsₗ₊₁, ..., numsᵣ₋₁,
// numsᵣ]| is ascending if for all |i| where |l <= i < r|, |nums_{i } <
// numsᵢ₊₁|. Note that a subarray of size |1| is ascending.
//
//

LEETCODE_BEGIN_RESOLVING(1800, MaximumAscendingSubarraySum, Solution);

class Solution {
public:
  int maxAscendingSum(vector<int> &nums) {
    int res  = 0;
    int cur  = 0;
    int prev = 0;
    for (auto x : nums) {
      if (x > prev) {
        cur += x;
        res = max(res, cur);
      } else {
        cur = x;
      }
      prev = x;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [10,20,30,5,10,50]
// Output: 65
//
// [5,10,50] is the ascending subarray with the maximum sum of 65.

LEETCODE_SOLUTION_UNITTEST(1800, MaximumAscendingSubarraySum, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 20, 30, 5, 10, 50};
  int         expect   = 65;
  int         actual   = solution->maxAscendingSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [10,20,30,40,50]
// Output: 150
//
// [10,20,30,40,50] is the ascending subarray with the maximum sum of 150.

LEETCODE_SOLUTION_UNITTEST(1800, MaximumAscendingSubarraySum, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 20, 30, 40, 50};
  int         expect   = 150;
  int         actual   = solution->maxAscendingSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [12,17,15,13,10,11,12]
// Output: 33
//
// [10,11,12] is the ascending subarray with the maximum sum of 33.

LEETCODE_SOLUTION_UNITTEST(1800, MaximumAscendingSubarraySum, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {12, 17, 15, 13, 10, 11, 12};
  int         expect   = 33;
  int         actual   = solution->maxAscendingSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}
