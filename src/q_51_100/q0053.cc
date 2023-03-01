// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Subarray
//
// https://leetcode.com/problems/maximum-subarray/
//
// Question ID: 53
// Difficult  : Medium
// Solve Date : 2021/10/14 12:35

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |53. Maximum Subarray|:
//
// Given an integer array |nums|, find the subarray with the largest sum, and
// return its sum.  
//

LEETCODE_BEGIN_RESOLVING(53, MaximumSubarray, Solution);

class Solution {
public:
  int maxSubArray(vector<int> &nums) {
    int res = nums[0], mx = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
      mx  = max(nums[i], nums[i] + mx);
      res = max(res, mx);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |-10⁴ <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
// Output: 6
//
// The subarray [4,-1,2,1] has the largest sum 6.

LEETCODE_SOLUTION_UNITTEST(53, MaximumSubarray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  int         expect   = 6;
  int         actual   = solution->maxSubArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1]
// Output: 1
//
// The subarray [1] has the largest sum 1.

LEETCODE_SOLUTION_UNITTEST(53, MaximumSubarray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  int         expect   = 1;
  int         actual   = solution->maxSubArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [5,4,-1,7,8]
// Output: 23
//
// The subarray [5,4,-1,7,8] has the largest sum 23.

LEETCODE_SOLUTION_UNITTEST(53, MaximumSubarray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 4, -1, 7, 8};
  int         expect   = 23;
  int         actual   = solution->maxSubArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}
