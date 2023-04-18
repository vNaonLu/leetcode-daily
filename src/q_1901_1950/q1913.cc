// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Product Difference Between Two Pairs
//
// https://leetcode.com/problems/maximum-product-difference-between-two-pairs/
//
// Question ID: 1913
// Difficult  : Easy
// Solve Date : 2023/04/18 18:59

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1913. Maximum Product Difference Between Two Pairs|:
//
// The product difference between two pairs |(a, b)| and |(c, d)| is defined as
// |(a * b) - (c * d)|.
//
//
//
//  • For example, the product difference between |(5, 6)| and |(2, 7)| is |(5 *
//  6) - (2 * 7) = 16|.
//
//
// Given an integer array |nums|, choose four distinct indices |w|, |x|, |y|,
// and |z| such that the product difference between pairs |(nums[w], nums[x])|
// and |(nums[y], nums[z])| is maximized.
//
// Return the maximum such product difference.
//
//
//

LEETCODE_BEGIN_RESOLVING(1913, MaximumProductDifferenceBetweenTwoPairs,
                         Solution);

class Solution {
public:
  int maxProductDifference(vector<int> &nums) {
    auto mx = *max_element(nums.begin(), nums.end());
    auto mn = *min_element(nums.begin(), nums.end());
    nth_element(nums.begin(), nums.end() - 2, nums.end());
    auto smx = *(nums.end() - 2);
    nth_element(nums.begin(), nums.begin() + 1, nums.end());
    auto smn = *(nums.begin() + 1);
    return (mx * smx) - (mn * smn);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |4 <= nums.length <= 10⁴|
// * |1 <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [5,6,2,7,4]
// Output: 34
//
// We can choose indices 1 and 3 for the first pair (6, 7) and indices 2 and 4
// for the second pair (2, 4). The product difference is (6 * 7) - (2 * 4) = 34.

LEETCODE_SOLUTION_UNITTEST(1913, MaximumProductDifferenceBetweenTwoPairs,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 6, 2, 7, 4};
  int         expect   = 34;
  int         actual   = solution->maxProductDifference(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,2,5,9,7,4,8]
// Output: 64
//
// We can choose indices 3 and 6 for the first pair (9, 8) and indices 1 and 5
// for the second pair (2, 4). The product difference is (9 * 8) - (2 * 4) = 64.

LEETCODE_SOLUTION_UNITTEST(1913, MaximumProductDifferenceBetweenTwoPairs,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 2, 5, 9, 7, 4, 8};
  int         expect   = 64;
  int         actual   = solution->maxProductDifference(nums);
  LCD_EXPECT_EQ(expect, actual);
}
