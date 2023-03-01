// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Non-decreasing Array
//
// https://leetcode.com/problems/non-decreasing-array/
//
// Question ID: 665
// Difficult  : Medium
// Solve Date : 2022/06/25 12:24

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |665. Non-decreasing Array|:
//
// Given an array |nums| with |n| integers, your task is to check if it could
// become non-decreasing by modifying at most one element. We define an array is
// non-decreasing if |nums[i] <= nums[i + 1]| holds for every |i| (0-based) such
// that ( |0 <= i <= n - 2|).
//

LEETCODE_BEGIN_RESOLVING(665, NonDecreasingArray, Solution);

class Solution {
public:
  bool checkPossibility(vector<int> &nums) {
    int cnt = 0;
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i - 1] > nums[i]) {
        if (++cnt > 1) {
          return false;
        }
        if (i == 1 || nums[i - 2] <= nums[i]) {
          nums[i - 1] = nums[i];
        } else {
          nums[i] = nums[i - 1];
        }
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= n <= 10⁴|
// * |-10⁵ <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,2,3]
// Output: true
//
// You could modify the first 4 to 1 to get a non-decreasing array.

LEETCODE_SOLUTION_UNITTEST(665, NonDecreasingArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 2, 3};
  bool        expect   = true;
  bool        actual   = solution->checkPossibility(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,2,1]
// Output: false
//
// You cannot get a non-decreasing array by modifying at most one element.

LEETCODE_SOLUTION_UNITTEST(665, NonDecreasingArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 2, 1};
  bool        expect   = false;
  bool        actual   = solution->checkPossibility(nums);
  LCD_EXPECT_EQ(expect, actual);
}
