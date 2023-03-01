// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sum of All Subset XOR Totals
//
// https://leetcode.com/problems/sum-of-all-subset-xor-totals/
//
// Question ID: 1863
// Difficult  : Easy
// Solve Date : 2022/07/13 18:12

#include <iosfwd>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1863. Sum of All Subset XOR Totals|:
//
// The XOR total of an array is defined as the bitwise |XOR| of all its
// elements, or |0| if the array is empty.
//
//  • For example, the XOR total of the array |[2,5,6]| is |2 XOR 5 XOR 6 = 1|.
// Given an array |nums|, return the sum of all XOR totals for every subset of
// |nums|. Note: Subsets with the same elements should be counted multiple
// times. An array |a| is a subset of an array |b| if |a| can be obtained from
// |b| by deleting some (possibly zero) elements of |b|.
//

LEETCODE_BEGIN_RESOLVING(1863, SumOfAllSubsetXORTotals, Solution);

class Solution {
private:
  template <typename Iterator>
  int helper(Iterator beg, Iterator end, int curr = 0) {
    if (beg == end) {
      return curr;
    }

    return helper(beg + 1, end, curr) + helper(beg + 1, end, curr ^ *beg);
  }

public:
  int subsetXORSum(vector<int> &nums) {

    return helper(nums.begin(), nums.end());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 12|
// * |1 <= nums[i] <= 20|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3]
// Output: 6
//
// The 4 subsets of [1,3] are:
// - The empty subset has an XOR total of 0.
// - [1] has an XOR total of 1.
// - [3] has an XOR total of 3.
// - [1,3] has an XOR total of 1 XOR 3 = 2.
// 0 + 1 + 3 + 2 = 6

LEETCODE_SOLUTION_UNITTEST(1863, SumOfAllSubsetXORTotals, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3};
  int         expect   = 6;
  int         actual   = solution->subsetXORSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5,1,6]
// Output: 28
//
// The 8 subsets of [5,1,6] are:
// - The empty subset has an XOR total of 0.
// - [5] has an XOR total of 5.
// - [1] has an XOR total of 1.
// - [6] has an XOR total of 6.
// - [5,1] has an XOR total of 5 XOR 1 = 4.
// - [5,6] has an XOR total of 5 XOR 6 = 3.
// - [1,6] has an XOR total of 1 XOR 6 = 7.
// - [5,1,6] has an XOR total of 5 XOR 1 XOR 6 = 2.
// 0 + 5 + 1 + 6 + 4 + 3 + 7 + 2 = 28

LEETCODE_SOLUTION_UNITTEST(1863, SumOfAllSubsetXORTotals, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 1, 6};
  int         expect   = 28;
  int         actual   = solution->subsetXORSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,4,5,6,7,8]
// Output: 480
//
// The sum of all XOR totals for every subset is 480.

LEETCODE_SOLUTION_UNITTEST(1863, SumOfAllSubsetXORTotals, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 4, 5, 6, 7, 8};
  int         expect   = 480;
  int         actual   = solution->subsetXORSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}
