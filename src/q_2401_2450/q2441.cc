// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Largest Positive Integer That Exists With Its Negative
//
// https://leetcode.com/problems/largest-positive-integer-that-exists-with-its-negative/
//
// Question ID: 2441
// Difficult  : Easy
// Solve Date : 2023/03/05 12:42

#include <iosfwd>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2441. Largest Positive Integer That Exists With Its
// Negative|:
//
// Given an integer array |nums| that does not contain any zeros, find the
// largest positive integer |k| such that |-k| also exists in the array. Return
// the positive integer |k|. If there is no such integer, return |-1|.
//

LEETCODE_BEGIN_RESOLVING(2441, LargestPositiveIntegerThatExistsWithItsNegative,
                         Solution);

class Solution {
public:
  int findMaxK(vector<int> &nums) {
    int                res = -1;
    unordered_set<int> memo;
    for (auto x : nums) {
      memo.emplace(x);
      if (memo.count(-x)) {
        res = max(res, abs(x));
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |-1000 <= nums[i] <= 1000|
// * |nums[i] != 0|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [-1,2,-3,3]
// Output: 3
//
// 3 is the only valid k we can find in the array.

LEETCODE_SOLUTION_UNITTEST(2441,
                           LargestPositiveIntegerThatExistsWithItsNegative,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, 2, -3, 3};
  int         expect   = 3;
  int         actual   = solution->findMaxK(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-1,10,6,7,-7,1]
// Output: 7
//
// Both 1 and 7 have their corresponding negative values in the array. 7 has a
// larger value.

LEETCODE_SOLUTION_UNITTEST(2441,
                           LargestPositiveIntegerThatExistsWithItsNegative,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, 10, 6, 7, -7, 1};
  int         expect   = 7;
  int         actual   = solution->findMaxK(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [-10,8,6,7,-2,-3]
// Output: -1
//
// There is no a single valid k, we return -1.

LEETCODE_SOLUTION_UNITTEST(2441,
                           LargestPositiveIntegerThatExistsWithItsNegative,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-10, 8, 6, 7, -2, -3};
  int         expect   = -1;
  int         actual   = solution->findMaxK(nums);
  LCD_EXPECT_EQ(expect, actual);
}
