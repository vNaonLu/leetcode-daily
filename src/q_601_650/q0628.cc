// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Product of Three Numbers
//
// https://leetcode.com/problems/maximum-product-of-three-numbers/
//
// Question ID: 628
// Difficult  : Easy
// Solve Date : 2023/07/06 19:57

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |628. Maximum Product of Three Numbers|:
//
// Given an integer array |nums|, find three numbers whose product is maximum
// and return the maximum product.
//
//

LEETCODE_BEGIN_RESOLVING(628, MaximumProductOfThreeNumbers, Solution);

class Solution {
public:
  int maximumProduct(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    return max({nums[n - 1] * nums[n - 2] * nums[n - 3],
                nums[n - 1] * nums[0] * nums[1]});
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= nums.length <= 10⁴|
// * |-1000 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(628, MaximumProductOfThreeNumbers, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  int         expect   = 6;
  int         actual   = solution->maximumProduct(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4]
// Output: 24
//

LEETCODE_SOLUTION_UNITTEST(628, MaximumProductOfThreeNumbers, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         expect   = 24;
  int         actual   = solution->maximumProduct(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [-1,-2,-3]
// Output: -6
//

LEETCODE_SOLUTION_UNITTEST(628, MaximumProductOfThreeNumbers, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, -2, -3};
  int         expect   = -6;
  int         actual   = solution->maximumProduct(nums);
  LCD_EXPECT_EQ(expect, actual);
}
