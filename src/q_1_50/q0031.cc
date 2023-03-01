// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Next Permutation
//
// https://leetcode.com/problems/next-permutation/
//
// Question ID: 31
// Difficult  : Medium
// Solve Date : 2021/11/27 14:02

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |31. Next Permutation|:
//
// A permutation of an array of integers is an arrangement of its members into a
// sequence or linear order.
//
//  • For example, for |arr = [1,2,3]|, the following are all the permutations
//  of |arr|: |[1,2,3], [1,3,2], [2, 1, 3], [2, 3, 1], [3,1,2], [3,2,1]|.
// The next permutation of an array of integers is the next lexicographically
// greater permutation of its integer. More formally, if all the permutations of
// the array are sorted in one container according to their lexicographical
// order, then the next permutation of that array is the permutation that
// follows it in the sorted container. If such arrangement is not possible, the
// array must be rearranged as the lowest possible order (i.e., sorted in
// ascending order).
//
//  • For example, the next permutation of |arr = [1,2,3]| is |[1,3,2]|.
//
//  • Similarly, the next permutation of |arr = [2,3,1]| is |[3,1,2]|.
//
//  • While the next permutation of |arr = [3,2,1]| is |[1,2,3]| because
//  |[3,2,1]| does not have a lexicographical larger rearrangement.
// Given an array of integers |nums|, find the next permutation of |nums|.
// The replacement must be [in place] and use only constant extra memory.
//  
//

LEETCODE_BEGIN_RESOLVING(31, NextPermutation, Solution);

class Solution {
public:
  void nextPermutation(vector<int> &nums) {
    bool permute = false;
    for (int i = nums.size() - 2; i > -1; i--) {
      if (nums[i] < nums[i + 1]) {
        int j = nums.size() - 1;
        while (j > i && nums[j] <= nums[i])
          j--;
        swap(nums[i], nums[j]);
        reverse(nums.begin() + i + 1, nums.end());
        permute = true;
        break;
      }
    }
    if (!permute)
      reverse(nums.begin(), nums.end());
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
//  Input: nums = [1,2,3]
// Output: [1,3,2]
//

LEETCODE_SOLUTION_UNITTEST(31, NextPermutation, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  vector<int> expect   = {1, 3, 2};
  solution->nextPermutation(nums);
  LCD_EXPECT_EQ(expect, nums);
}

// [Example #2]
//  Input: nums = [3,2,1]
// Output: [1,2,3]
//

LEETCODE_SOLUTION_UNITTEST(31, NextPermutation, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 1};
  vector<int> expect   = {1, 2, 3};
  solution->nextPermutation(nums);
  LCD_EXPECT_EQ(expect, nums);
}

// [Example #3]
//  Input: nums = [1,1,5]
// Output: [1,5,1]
//

LEETCODE_SOLUTION_UNITTEST(31, NextPermutation, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 5};
  vector<int> expect   = {1, 5, 1};
  solution->nextPermutation(nums);
  LCD_EXPECT_EQ(expect, nums);
}
