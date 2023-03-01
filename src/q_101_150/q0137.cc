// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Single Number II
//
// https://leetcode.com/problems/single-number-ii/
//
// Question ID: 137
// Difficult  : Medium
// Solve Date : 2022/08/21 23:55

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |137. Single Number II|:
//
// Given an integer array |nums| whereevery element appears three times except
// for one, which appears exactly once. Find the single element and return it.
// You mustimplement a solution with a linear runtime complexity and useonly
// constantextra space.
//

LEETCODE_BEGIN_RESOLVING(137, SingleNumberII, Solution);

class Solution {
public:
  int singleNumber(vector<int> &nums) {
    auto res = 0;

    for (int i = 0; i < sizeof(int) * 8; ++i) {
      auto n    = 0;
      auto mask = 1 << i;
      for (auto x : nums) {
        if (x & mask) {
          ++n;
        }
      }

      if (n % 3 != 0) {
        res |= mask;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 3 * 10⁴|
// * |-2³¹ <= nums[i] <= 2³¹ - 1|
// * Each element in |nums| appears exactly three times except for one element
// which appears once.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,2,3,2]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(137, SingleNumberII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 3, 2};
  int         expect   = 3;
  int         actual   = solution->singleNumber(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,1,0,1,0,1,99]
// Output: 99
//

LEETCODE_SOLUTION_UNITTEST(137, SingleNumberII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 0, 1, 0, 1, 99};
  int         expect   = 99;
  int         actual   = solution->singleNumber(nums);
  LCD_EXPECT_EQ(expect, actual);
}
