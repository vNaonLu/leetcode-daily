// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sort Colors
//
// https://leetcode.com/problems/sort-colors/
//
// Question ID: 75
// Difficult  : Medium
// Solve Date : 2021/09/20 08:00

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |75. Sort Colors|:
//
// Given an array |nums| with |n| objects colored red, white, or blue, sort them
// [in-place] so that objects of the same color are adjacent, with the colors in
// the order red, white, and blue. We will use the integers |0|, |1|, and |2| to
// represent the color red, white, and blue, respectively. You must solve this
// problem without using the library's sort function.  
//

LEETCODE_BEGIN_RESOLVING(75, SortColors, Solution);

class Solution {
public:
  void sortColors(vector<int> &nums) {
    vector<int> count(3, 0);
    for (const auto &x : nums)
      ++count[x];
    fill(nums.begin(), nums.begin() + count[0], 0);
    fill(nums.begin() + count[0], nums.begin() + count[0] + count[1], 1);
    fill(nums.begin() + count[0] + count[1], nums.end(), 2);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= n <= 300|
// * |nums[i]| is either |0|, |1|, or |2|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,0,2,1,1,0]
// Output: [0,0,1,1,2,2]
//

LEETCODE_SOLUTION_UNITTEST(75, SortColors, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 0, 2, 1, 1, 0};
  vector<int> expect   = {0, 0, 1, 1, 2, 2};
  solution->sortColors(nums);
  LCD_EXPECT_EQ(expect, nums);
}

// [Example #2]
//  Input: nums = [2,0,1]
// Output: [0,1,2]
//

LEETCODE_SOLUTION_UNITTEST(75, SortColors, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 0, 1};
  vector<int> expect   = {0, 1, 2};
  solution->sortColors(nums);
  LCD_EXPECT_EQ(expect, nums);
}
