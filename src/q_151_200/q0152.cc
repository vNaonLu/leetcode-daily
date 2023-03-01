// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Product Subarray
//
// https://leetcode.com/problems/maximum-product-subarray/
//
// Question ID: 152
// Difficult  : Medium
// Solve Date : 2021/10/15 10:17

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |152. Maximum Product Subarray|:
//
// Given an integer array |nums|, find a subarray that has the largest product,
// and return the product. The test cases are generated so that the answer will
// fit in a 32-bit integer.  
//

LEETCODE_BEGIN_RESOLVING(152, MaximumProductSubarray, Solution);

class Solution {
public:
  int maxProduct(vector<int> &nums) {
    int res = nums[0], prod = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
      if (prod == 0)
        prod = 1;
      prod *= nums[i];
      res = max(res, prod);
    }
    prod = 1;
    for (int i = nums.size() - 1; i >= 0; --i) {
      if (prod == 0)
        prod = 1;
      prod *= nums[i];
      res = max(res, prod);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 2 * 10⁴|
// * |-10 <= nums[i] <= 10|
// * The product of any prefix or suffix of |nums| is guaranteed to fit in a
// 32-bit integer.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,3,-2,4]
// Output: 6
//
// [2,3] has the largest product 6.

LEETCODE_SOLUTION_UNITTEST(152, MaximumProductSubarray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, -2, 4};
  int         expect   = 6;
  int         actual   = solution->maxProduct(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-2,0,-1]
// Output: 0
//
// The result cannot be 2, because [-2,-1] is not a subarray.

LEETCODE_SOLUTION_UNITTEST(152, MaximumProductSubarray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-2, 0, -1};
  int         expect   = 0;
  int         actual   = solution->maxProduct(nums);
  LCD_EXPECT_EQ(expect, actual);
}
