// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Make Array Zero by Subtracting Equal Amounts
//
// https://leetcode.com/problems/make-array-zero-by-subtracting-equal-amounts/
//
// Question ID: 2357
// Difficult  : Easy
// Solve Date : 2023/03/01 10:43

#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2357. Make Array Zero by Subtracting Equal Amounts|:
//
// You are given a non-negative integer array |nums|. In one operation, you
// must:
//
//  • Choose a positive integer |x| such that |x| is less than or equal to the
//  smallest non-zero element in |nums|.
//
//  • Subtract |x| from every positive element in |nums|.
// Return the minimum number of operations to make every element in |nums| equal
// to |0|.
//

LEETCODE_BEGIN_RESOLVING(2357, MakeArrayZeroBySubtractingEqualAmounts,
                         Solution);

class Solution {
public:
  int minimumOperations(vector<int> &nums) {
    int                res = 0;
    unordered_set<int> exist;
    for (auto x : nums) {
      if (x != 0 && exist.emplace(x).second) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |0 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,5,0,3,5]
// Output: 3
//
// In the first operation, choose x = 1. Now, nums = [0,4,0,2,4].
// In the second operation, choose x = 2. Now, nums = [0,2,0,0,2].
// In the third operation, choose x = 2. Now, nums = [0,0,0,0,0].

LEETCODE_SOLUTION_UNITTEST(2357, MakeArrayZeroBySubtractingEqualAmounts,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 5, 0, 3, 5};
  int         expect   = 3;
  int         actual   = solution->minimumOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0]
// Output: 0
//
// Each element in nums is already 0 so no operations are needed.

LEETCODE_SOLUTION_UNITTEST(2357, MakeArrayZeroBySubtractingEqualAmounts,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0};
  int         expect   = 0;
  int         actual   = solution->minimumOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}
