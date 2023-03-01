// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Product of Array Except Self
//
// https://leetcode.com/problems/product-of-array-except-self/
//
// Question ID: 238
// Difficult  : Medium
// Solve Date : 2021/09/23 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |238. Product of Array Except Self|:
//
// Given an integer array |nums|, return an array |answer| such that |answer[i]|
// is equal to the product of all the elements of |nums| except |nums[i]|. The
// product of any prefix or suffix of |nums| is guaranteed to fit in a 32-bit
// integer. You must write an algorithm that runs in  |O(n)| time and without
// using the division operation.  
//

LEETCODE_BEGIN_RESOLVING(238, ProductOfArrayExceptSelf, Solution);

class Solution {
public:
  vector<int> productExceptSelf(vector<int> &nums) {
    vector<int> res(nums.size(), 0);
    long        total_prod = 1;
    int         zero_cnt   = 0;
    for (const auto &n : nums) {
      if (n == 0) {
        ++zero_cnt;
      } else {
        total_prod *= n;
      }
    }
    if (zero_cnt <= 1) {
      for (int i = 0; i < nums.size(); ++i) {
        res[i] = zero_cnt == 0 ? total_prod / nums[i]
                               : (nums[i] == 0 ? total_prod : 0);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 10⁵|
// * |-30 <= nums[i] <= 30|
// * The product of any prefix or suffix of |nums| is guaranteed to fit in a
// 32-bit integer.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4]
// Output: [24,12,8,6]
//

LEETCODE_SOLUTION_UNITTEST(238, ProductOfArrayExceptSelf, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  vector<int> expect   = {24, 12, 8, 6};
  vector<int> actual   = solution->productExceptSelf(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-1,1,0,-3,3]
// Output: [0,0,9,0,0]
//

LEETCODE_SOLUTION_UNITTEST(238, ProductOfArrayExceptSelf, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, 1, 0, -3, 3};
  vector<int> expect   = {0, 0, 9, 0, 0};
  vector<int> actual   = solution->productExceptSelf(nums);
  LCD_EXPECT_EQ(expect, actual);
}
