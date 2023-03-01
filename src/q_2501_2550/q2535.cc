// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Difference Between Element Sum and Digit Sum of an Array
//
// https://leetcode.com/problems/difference-between-element-sum-and-digit-sum-of-an-array/
//
// Question ID: 2535
// Difficult  : Easy
// Solve Date : 2023/02/18 13:32

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2535. Difference Between Element Sum and Digit Sum of an
// Array|:
//
// You are given a positive integer array |nums|.
//
//  • The element sum is the sum of all the elements in |nums|.
//
//  • The digit sum is the sum of all the digits (not necessarily distinct) that
//  appear in |nums|.
// Return the absolute difference between the element sum and digit sum of
// |nums|. Note that the absolute difference between two integers |x| and |y| is
// defined as ||x - y||.
//

LEETCODE_BEGIN_RESOLVING(2535, DifferenceBetweenElementSumAndDigitSumOfAnArray,
                         Solution);

class Solution {
private:
  int digitSum(int x) {
    int res = 0;
    while (x != 0) {
      res += x % 10;
      x /= 10;
    }
    return res;
  }

public:
  int differenceOfSum(vector<int> &nums) {
    int sum       = 0;
    int digit_sum = 0;
    for (auto x : nums) {
      sum += x;
      digit_sum += digitSum(x);
    }
    return abs(sum - digit_sum);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 2000|
// * |1 <= nums[i] <= 2000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,15,6,3]
// Output: 9
//
// The element sum of nums is 1 + 15 + 6 + 3 = 25.
// The digit sum of nums is 1 + 1 + 5 + 6 + 3 = 16.
// The absolute difference between the element sum and digit sum is |25 - 16|
// = 9.

LEETCODE_SOLUTION_UNITTEST(2535,
                           DifferenceBetweenElementSumAndDigitSumOfAnArray,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 15, 6, 3};
  int         expect   = 9;
  int         actual   = solution->differenceOfSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4]
// Output: 0
//
// The element sum of nums is 1 + 2 + 3 + 4 = 10.
// The digit sum of nums is 1 + 2 + 3 + 4 = 10.
// The absolute difference between the element sum and digit sum is |10 - 10| =
// 0.

LEETCODE_SOLUTION_UNITTEST(2535,
                           DifferenceBetweenElementSumAndDigitSumOfAnArray,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         expect   = 0;
  int         actual   = solution->differenceOfSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}
