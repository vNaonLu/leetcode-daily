// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Subarray Product Less Than K
//
// https://leetcode.com/problems/subarray-product-less-than-k/
//
// Question ID: 713
// Difficult  : Medium
// Solve Date : 2021/09/23 08:00

#include <array>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |713. Subarray Product Less Than K|:
//
// Given an array of integers |nums| and an integer |k|, return the number of
// contiguous subarrays where the product of all the elements in the subarray is
// strictly less than |k|.  
//

LEETCODE_BEGIN_RESOLVING(713, SubarrayProductLessThanK, Solution);

class Solution {
public:
  int numSubarrayProductLessThanK(vector<int> &nums, int k) {
    if (k <= 1)
      return 0;
    int res     = 0;
    int product = 1;
    int r = 0, l = 0;
    for (; r < nums.size(); ++r) {
      product *= nums[r];
      while (product >= k)
        product /= nums[l++];
      res += r - l + 1;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 3 * 10⁴|
// * |1 <= nums[i] <= 1000|
// * |0 <= k <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [10,5,2,6], k = 100
// Output: 8
//
// The 8 subarrays that have product less than 100 are:
// [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
// Note that [10, 5, 2] is not included as the product of 100 is not strictly
// less than k.

LEETCODE_SOLUTION_UNITTEST(713, SubarrayProductLessThanK, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 5, 2, 6};
  int         k        = 100;
  int         expect   = 8;
  int         actual   = solution->numSubarrayProductLessThanK(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3], k = 0
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(713, SubarrayProductLessThanK, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  int         k        = 0;
  int         expect   = 0;
  int         actual   = solution->numSubarrayProductLessThanK(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
