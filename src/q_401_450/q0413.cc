// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Arithmetic Slices
//
// https://leetcode.com/problems/arithmetic-slices/
//
// Question ID: 413
// Difficult  : Medium
// Solve Date : 2021/10/02 14:23

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |413. Arithmetic Slices|:
//
// An integer array is called arithmetic if it consists of at least three
// elements and if the difference between any two consecutive elements is the
// same.
//
//  • For example, |[1,3,5,7,9]|, |[7,7,7,7]|, and |[3,-1,-5,-9]| are arithmetic
//  sequences.
// Given an integer array |nums|, return the number of arithmetic subarrays of
// |nums|. A subarray is a contiguous subsequence of the array.  
//

LEETCODE_BEGIN_RESOLVING(413, ArithmeticSlices, Solution);

class Solution {
public:
  int numberOfArithmeticSlices(vector<int> &nums) {
    if (nums.size() < 3)
      return 0;
    int res = 0, cnt = 1;
    for (int i = 0; i < nums.size() - 2; ++i) {
      if (nums[i + 2] - nums[i + 1] == nums[i + 1] - nums[i]) {
        ++cnt;
      } else {
        res += cnt * (cnt - 1) / 2;
        cnt = 1;
      }
    }
    res += cnt * (cnt - 1) / 2;
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 5000|
// * |-1000 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4]
// Output: 3
//
// We have 3 arithmetic slices in nums: [1, 2, 3], [2, 3, 4] and [1,2,3,4]
// itself.

LEETCODE_SOLUTION_UNITTEST(413, ArithmeticSlices, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         expect   = 3;
  int         actual   = solution->numberOfArithmeticSlices(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(413, ArithmeticSlices, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  int         expect   = 0;
  int         actual   = solution->numberOfArithmeticSlices(nums);
  LCD_EXPECT_EQ(expect, actual);
}
