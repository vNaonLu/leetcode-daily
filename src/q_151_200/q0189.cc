// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Rotate Array
//
// https://leetcode.com/problems/rotate-array/
//
// Question ID: 189
// Difficult  : Medium
// Solve Date : 2021/09/06 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |189. Rotate Array|:
//
// Given an integer array |nums|, rotate the array to the right by |k| steps,
// where |k| is non-negative.  
//

LEETCODE_BEGIN_RESOLVING(189, RotateArray, Solution);

class Solution {
public:
  void rotate(vector<int> &nums, int k) {
    int         n = nums.size();
    vector<int> tmp(nums.end() - k % n, nums.end());
    nums.insert(nums.begin(), tmp.begin(), tmp.end());
    nums.resize(n);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |-2³¹ <= nums[i] <= 2³¹ - 1|
// * |0 <= k <= 10⁵|
// * Try to come up with as many solutions as you can. There are at least three
// different ways to solve this problem.
// * Could you do it in-place with |O(1)| extra space?
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4,5,6,7], k = 3
// Output: [5,6,7,1,2,3,4]
//
// rotate 1 steps to the right: [7,1,2,3,4,5,6]
// rotate 2 steps to the right: [6,7,1,2,3,4,5]
// rotate 3 steps to the right: [5,6,7,1,2,3,4]

LEETCODE_SOLUTION_UNITTEST(189, RotateArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5, 6, 7};
  int         k        = 3;
  vector<int> expect   = {5, 6, 7, 1, 2, 3, 4};
  solution->rotate(nums, k);
  EXPECT_EQ(expect, nums);
}

// [Example #2]
//  Input: nums = [-1,-100,3,99], k = 2
// Output: [3,99,-1,-100]
//
// rotate 1 steps to the right: [99,-1,-100,3]
// rotate 2 steps to the right: [3,99,-1,-100]

LEETCODE_SOLUTION_UNITTEST(189, RotateArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, -100, 3, 99};
  int         k        = 2;
  vector<int> expect   = {3, 99, -1, -100};
  solution->rotate(nums, k);
  EXPECT_EQ(expect, nums);
}
