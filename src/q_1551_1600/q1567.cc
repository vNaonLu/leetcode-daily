// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Length of Subarray With Positive Product
//
// https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/
//
// Question ID: 1567
// Difficult  : Medium
// Solve Date : 2021/10/15 10:28

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1567. Maximum Length of Subarray With Positive Product|:
//
// Given an array of integers |nums|, find the maximum length of a subarray
// where the product of all its elements is positive. A subarray of an array is
// a consecutive sequence of zero or more values taken out of that array. Return
// the maximum length of a subarray with positive product.  
//

LEETCODE_BEGIN_RESOLVING(1567, MaximumLengthOfSubarrayWithPositiveProduct,
                         Solution);

class Solution {
public:
  int getMaxLen(vector<int> &nums) {
    int res       = 0;
    int positives = 0, negatives = 0;
    for (const int &x : nums) {
      if (x == 0) {
        positives = 0;
        negatives = 0;
      } else if (x < 0) {
        swap(negatives, positives);
        ++negatives;
        positives = positives == 0 ? 0 : positives + 1;
      } else {
        ++positives;
        negatives = negatives == 0 ? 0 : negatives + 1;
      }
      res = max(res, positives);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,-2,-3,4]
// Output: 4
//
// The array nums already has a positive product of 24.

LEETCODE_SOLUTION_UNITTEST(1567, MaximumLengthOfSubarrayWithPositiveProduct,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, -2, -3, 4};
  int         expect   = 4;
  int         actual   = solution->getMaxLen(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,1,-2,-3,-4]
// Output: 3
//
// The longest subarray with positive product is [1,-2,-3] which has a product
// of 6. Notice that we cannot include 0 in the subarray since that'll make the
// product 0 which is not positive.

LEETCODE_SOLUTION_UNITTEST(1567, MaximumLengthOfSubarrayWithPositiveProduct,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, -2, -3, -4};
  int         expect   = 3;
  int         actual   = solution->getMaxLen(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [-1,-2,-3,0,1]
// Output: 2
//
// The longest subarray with positive product is [-1,-2] or [-2,-3].

LEETCODE_SOLUTION_UNITTEST(1567, MaximumLengthOfSubarrayWithPositiveProduct,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, -2, -3, 0, 1};
  int         expect   = 2;
  int         actual   = solution->getMaxLen(nums);
  LCD_EXPECT_EQ(expect, actual);
}
