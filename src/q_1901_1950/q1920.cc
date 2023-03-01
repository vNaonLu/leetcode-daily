// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Build Array from Permutation
//
// https://leetcode.com/problems/build-array-from-permutation/
//
// Question ID: 1920
// Difficult  : Easy
// Solve Date : 2022/08/11 12:04

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1920. Build Array from Permutation|:
//
// Given a zero-based permutation |nums| (0-indexed), build an array |ans| of
// the same length where |ans[i] = nums[nums[i]]| for each |0 <= i <
// nums.length| and return it. A zero-based permutation |nums| is an array of
// distinct integers from |0| to |nums.length - 1| (inclusive).
//

LEETCODE_BEGIN_RESOLVING(1920, BuildArrayFromPermutation, Solution);

class Solution {
public:
  vector<int> buildArray(vector<int> &nums) {
    auto res    = vector<int>(nums.size(), 0);
    auto num_it = nums.begin();
    auto res_it = res.begin();
    while (num_it != nums.end()) {
      *res_it++ = *(nums.begin() + *num_it++);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |0 <= nums[i] < nums.length|
// * The elements in |nums| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [0,2,1,5,3,4]
// Output: [0,1,2,4,5,3]
// Explanation: The array ans is built as follows:
// ans = [nums[nums[0]], nums[nums[1]], nums[nums[2]], nums[nums[3]],
// nums[nums[4]], nums[nums[5]]]
//  = [nums[0], nums[2], nums[1], nums[5], nums[3], nums[4]]
//  = [0,1,2,4,5,3]
//

LEETCODE_SOLUTION_UNITTEST(1920, BuildArrayFromPermutation, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 2, 1, 5, 3, 4};
  vector<int> expect   = {0, 1, 2, 4, 5, 3};
  vector<int> actual   = solution->buildArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5,0,1,2,3,4]
// Output: [4,5,0,1,2,3]
//
// The array ans is built as follows:
// ans = [nums[nums[0]], nums[nums[1]], nums[nums[2]], nums[nums[3]],
// nums[nums[4]], nums[nums[5]]]
//  = [nums[5], nums[0], nums[1], nums[2], nums[3], nums[4]]
//  = [4,5,0,1,2,3]

LEETCODE_SOLUTION_UNITTEST(1920, BuildArrayFromPermutation, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 0, 1, 2, 3, 4};
  vector<int> expect   = {4, 5, 0, 1, 2, 3};
  vector<int> actual   = solution->buildArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}
