// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Triangular Sum of an Array
//
// https://leetcode.com/problems/find-triangular-sum-of-an-array/
//
// Question ID: 2221
// Difficult  : Medium
// Solve Date : 2022/08/12 21:19

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2221. Find Triangular Sum of an Array|:
//
// You are given a 0-indexed integer array |nums|, where |nums[i]| is a digit
// between |0| and |9| (inclusive). The triangular sum of |nums| is the value of
// the only element present in |nums| after the following process terminates:
//
//  1. Let |nums| comprise of |n| elements. If |n == 1|, end the process.
//  Otherwise, create a new 0-indexed integer array |newNums| of length |n - 1|.
//
//  2. For each index |i|, where |0 <= i <n - 1|, assign the value of
//  |newNums[i]| as |(nums[i] + nums[i+1]) % 10|, where |%| denotes modulo
//  operator.
//
//  3. Replace the array |nums| with |newNums|.
//
//  4. Repeat the entire process starting from step 1.
// Return the triangular sum of |nums|.
//

LEETCODE_BEGIN_RESOLVING(2221, FindTriangularSumOfAnArray, Solution);

class Solution {
public:
  int triangularSum(vector<int> &nums) {
    auto end = nums.end();

    while (nums.begin() + 1 != end) {
      auto beg = nums.begin();
      while (beg + 1 != end) {
        *beg += *(beg + 1);
        *beg %= 10;
        ++beg;
      }
      --end;
    }

    return nums.front();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |0 <= nums[i] <= 9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4,5]
// Output: 8
//
// The above diagram depicts the process from which we obtain the triangular sum
// of the array.

LEETCODE_SOLUTION_UNITTEST(2221, FindTriangularSumOfAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  int         expect   = 8;
  int         actual   = solution->triangularSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5]
// Output: 5
//
// Since there is only one element in nums, the triangular sum is the value of
// that element itself.

LEETCODE_SOLUTION_UNITTEST(2221, FindTriangularSumOfAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5};
  int         expect   = 5;
  int         actual   = solution->triangularSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}
