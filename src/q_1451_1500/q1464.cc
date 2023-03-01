// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Product of Two Elements in an Array
//
// https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array/
//
// Question ID: 1464
// Difficult  : Easy
// Solve Date : 2022/03/10 18:29

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1464. Maximum Product of Two Elements in an Array|:
//
// Given the array of integers |nums|, you will choose two different indices |i|
// and |j| of that array. Return the maximum value of |(nums[i]-1)*(nums[j]-1)|.
//  
//

LEETCODE_BEGIN_RESOLVING(1464, MaximumProductOfTwoElementsInAnArray, Solution);

class Solution {
public:
  int maxProduct(vector<int> &nums) {
    int mx = 0, sec = 0;
    for (const auto &x : nums) {
      if (x > mx) {
        sec = max(sec, mx);
        mx  = x;
      } else if (x > sec) {
        sec = x;
      }
    }
    return (mx - 1) * (sec - 1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 500|
// * |1 <= nums[i] <= 10^3|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,4,5,2]
// Output: 12
//
// If you choose the indices i=1 and j=2 (indexed from 0), you will get the
// maximum value, that is, (nums[1]-1)*(nums[2]-1) = (4-1)*(5-1) = 3*4 = 12.

LEETCODE_SOLUTION_UNITTEST(1464, MaximumProductOfTwoElementsInAnArray,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 4, 5, 2};
  int         expect   = 12;
  int         actual   = solution->maxProduct(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,5,4,5]
// Output: 16
//
// Choosing the indices i=1 and j=3 (indexed from 0), you will get the maximum
// value of (5-1)*(5-1) = 16.

LEETCODE_SOLUTION_UNITTEST(1464, MaximumProductOfTwoElementsInAnArray,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 5, 4, 5};
  int         expect   = 16;
  int         actual   = solution->maxProduct(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,7]
// Output: 12
//

LEETCODE_SOLUTION_UNITTEST(1464, MaximumProductOfTwoElementsInAnArray,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 7};
  int         expect   = 12;
  int         actual   = solution->maxProduct(nums);
  LCD_EXPECT_EQ(expect, actual);
}
