// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Max Pair Sum in an Array
//
// https://leetcode.com/problems/max-pair-sum-in-an-array/
//
// Question ID: 2815
// Difficult  : Easy
// Solve Date : 2024/01/09 21:07

#include <algorithm>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2815. Max Pair Sum in an Array|:
//
// You are given a 0-indexed integer array |nums|. You have to find the maximum
// sum of a pair of numbers from |nums| such that the maximum digit in both
// numbers are equal. Return the maximum sum or |-1| if no such pair exists.
//
//

LEETCODE_BEGIN_RESOLVING(2815, MaxPairSumInAnArray, Solution);

class Solution {
public:
  int maxSum(vector<int> &nums) {
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
      string first = to_string(nums[i]);
      sort(first.begin(), first.end());

      for (int j = i + 1; j < nums.size(); ++j) {
        string second = to_string(nums[j]);
        sort(second.begin(), second.end());
        if (first.back() == second.back()) {
          res = max(res, nums[i] + nums[j]);
        }
      }
    }
    return res == 0 ? -1 : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 100|
// * |1 <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [51,71,17,24,42]
// Output: 88
//
// For i = 1 and j = 2, nums[i] and nums[j] have equal maximum digits with a
// pair sum of 71 + 17 = 88. For i = 3 and j = 4, nums[i] and nums[j] have equal
// maximum digits with a pair sum of 24 + 42 = 66. It can be shown that there
// are no other pairs with equal maximum digits, so the answer is 88.

LEETCODE_SOLUTION_UNITTEST(2815, MaxPairSumInAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {51, 71, 17, 24, 42};
  int         expect   = 88;
  int         actual   = solution->maxSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4]
// Output: -1
//
// No pair exists in nums with equal maximum digits.

LEETCODE_SOLUTION_UNITTEST(2815, MaxPairSumInAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         expect   = -1;
  int         actual   = solution->maxSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}
