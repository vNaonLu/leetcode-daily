// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Single Number
//
// https://leetcode.com/problems/single-number/
//
// Question ID: 136
// Difficult  : Easy
// Solve Date : 2021/09/18 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |136. Single Number|:
//
// Given a non-empty array of integers |nums|, every element appears twice
// except for one. Find that single one. You must implement a solution with a
// linear runtime complexity and use only constant extra space.  
//

LEETCODE_BEGIN_RESOLVING(136, SingleNumber, Solution);

class Solution {
public:
  int singleNumber(vector<int> &nums) {
    int res = 0;
    for (const auto &n : nums) {
      res ^= n;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 3 * 10⁴|
// * |-3 * 10⁴ <= nums[i] <= 3 * 10⁴|
// * Each element in the array appears twice except for one element which
// appears only once.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,2,1]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(136, SingleNumber, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 1};
  int         expect   = 1;
  int         actual   = solution->singleNumber(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,1,2,1,2]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(136, SingleNumber, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 1, 2, 1, 2};
  int         expect   = 4;
  int         actual   = solution->singleNumber(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(136, SingleNumber, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  int         expect   = 1;
  int         actual   = solution->singleNumber(nums);
  LCD_EXPECT_EQ(expect, actual);
}
