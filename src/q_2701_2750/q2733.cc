// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Neither Minimum nor Maximum
//
// https://leetcode.com/problems/neither-minimum-nor-maximum/
//
// Question ID: 2733
// Difficult  : Easy
// Solve Date : 2023/12/20 20:31

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2733. Neither Minimum nor Maximum|:
//
// Given an integer array |nums| containing distinct positive integers, find and
// return any number from the array that is neither the minimum nor the maximum
// value in the array, or |-1| if there is no such number. Return the selected
// integer.
//
//

LEETCODE_BEGIN_RESOLVING(2733, NeitherMinimumNorMaximum, Solution);

class Solution {
public:
  int findNonMinOrMax(vector<int> &nums) {
    int mx = *max_element(nums.begin(), nums.end());
    int mn = *min_element(nums.begin(), nums.end());
    for (auto x : nums) {
      if (mx > x && x > mn) {
        return x;
      }
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i] <= 100|
// * All values in |nums| are distinct
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,2,1,4]
// Output: 2
//
// In this example, the minimum value is 1 and the maximum value is 4.
// Therefore, either 2 or 3 can be valid answers.

LEETCODE_SOLUTION_UNITTEST(2733, NeitherMinimumNorMaximum, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 1, 4};
  int         expect   = 3;
  int         actual   = solution->findNonMinOrMax(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2]
// Output: -1
//
// Since there is no number in nums that is neither the maximum nor the minimum,
// we cannot select a number that satisfies the given condition. Therefore,
// there is no answer.

LEETCODE_SOLUTION_UNITTEST(2733, NeitherMinimumNorMaximum, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2};
  int         expect   = -1;
  int         actual   = solution->findNonMinOrMax(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [2,1,3]
// Output: 2
//
// Since 2 is neither the maximum nor the minimum value in nums, it is the only
// valid answer.

LEETCODE_SOLUTION_UNITTEST(2733, NeitherMinimumNorMaximum, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 3};
  int         expect   = 2;
  int         actual   = solution->findNonMinOrMax(nums);
  LCD_EXPECT_EQ(expect, actual);
}
