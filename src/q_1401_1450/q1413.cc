// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Value to Get Positive Step by Step Sum
//
// https://leetcode.com/problems/minimum-value-to-get-positive-step-by-step-sum/
//
// Question ID: 1413
// Difficult  : Easy
// Solve Date : 2021/11/11 21:28

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1413. Minimum Value to Get Positive Step by Step Sum|:
//
// Given an array of integers  |nums|, you start with an initial positive value
// startValue. In each iteration, you calculate the step by step sum of
// startValue plus elements in |nums| (from left to right). Return the minimum
// positive value of startValue such that the step by step sum is never less
// than 1.  
//

LEETCODE_BEGIN_RESOLVING(1413, MinimumValueToGetPositiveStepByStepSum,
                         Solution);

class Solution {
public:
  int minStartValue(vector<int> &nums) {
    int res     = 1;
    int current = res;
    for (const auto &x : nums) {
      int next = current + x;
      if (next < 1) {
        res += 1 - next;
        current = 1;
      } else {
        current = next;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |-100 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [-3,2,-3,4,2]
// Output: 5
//
// If you choose startValue = 4, in the third iteration your step by step sum is
// less than 1. step by step sum startValue = 4 | startValue = 5 | nums
//  (4 -3 ) = 1 | (5 -3 ) = 2 | -3
//  (1 +2 ) = 3 | (2 +2 ) = 4 | 2
//  (3 -3 ) = 0 | (4 -3 ) = 1 | -3
//  (0 +4 ) = 4 | (1 +4 ) = 5 | 4
//  (4 +2 ) = 6 | (5 +2 ) = 7 | 2

LEETCODE_SOLUTION_UNITTEST(1413, MinimumValueToGetPositiveStepByStepSum,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-3, 2, -3, 4, 2};
  int         expect   = 5;
  int         actual   = solution->minStartValue(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2]
// Output: 1
//
// Minimum start value should be positive.

LEETCODE_SOLUTION_UNITTEST(1413, MinimumValueToGetPositiveStepByStepSum,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2};
  int         expect   = 1;
  int         actual   = solution->minStartValue(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,-2,-3]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(1413, MinimumValueToGetPositiveStepByStepSum,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, -2, -3};
  int         expect   = 5;
  int         actual   = solution->minStartValue(nums);
  LCD_EXPECT_EQ(expect, actual);
}
