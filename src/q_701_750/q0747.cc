// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Largest Number At Least Twice of Others
//
// https://leetcode.com/problems/largest-number-at-least-twice-of-others/
//
// Question ID: 747
// Difficult  : Easy
// Solve Date : 2022/10/03 14:16

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |747. Largest Number At Least Twice of Others|:
//
// You are given an integer array |nums| where the largest integer is unique.
// Determine whether the largest element in the array is at least twice as much
// as every other number in the array. If it is, return the index of the largest
// element, or return |-1| otherwise.
//

LEETCODE_BEGIN_RESOLVING(747, LargestNumberAtLeastTwiceOfOthers, Solution);

class Solution {
public:
  int dominantIndex(vector<int> &nums) {
    auto mx = max_element(nums.begin(), nums.end());
    for (auto it = nums.begin(); it != nums.end(); ++it) {
      if (it != mx && *mx < *it * 2) {
        return -1;
      }
    }
    return distance(nums.begin(), mx);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 50|
// * |0 <= nums[i] <= 100|
// * The largest element in |nums| is unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,6,1,0]
// Output: 1
//
// 6 is the largest integer.
// For every other number in the array x, 6 is at least twice as big as x.
// The index of value 6 is 1, so we return 1.

LEETCODE_SOLUTION_UNITTEST(747, LargestNumberAtLeastTwiceOfOthers, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 6, 1, 0};
  int         expect   = 1;
  int         actual   = solution->dominantIndex(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4]
// Output: -1
//
// 4 is less than twice the value of 3, so we return -1.

LEETCODE_SOLUTION_UNITTEST(747, LargestNumberAtLeastTwiceOfOthers, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         expect   = -1;
  int         actual   = solution->dominantIndex(nums);
  LCD_EXPECT_EQ(expect, actual);
}
