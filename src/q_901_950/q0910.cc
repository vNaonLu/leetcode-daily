// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Smallest Range II
//
// https://leetcode.com/problems/smallest-range-ii/
//
// Question ID: 910
// Difficult  : Medium
// Solve Date : 2022/05/08 12:44

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |910. Smallest Range II|:
//
// You are given an integer array |nums| and an integer |k|.
// For each index |i| where |0 <= i < nums.length|, change |nums[i]| to be
// either |nums[i] + k| or |nums[i] - k|. The score of |nums| is the difference
// between the maximum and minimum elements in |nums|. Return the minimum score
// of |nums| after changing the values at each index.  
//

LEETCODE_BEGIN_RESOLVING(910, SmallestRangeII, Solution);

class Solution {
public:
  int smallestRangeII(vector<int> &nums, int k) {
    sort(nums.begin(), nums.end());
    int res = nums.back() - nums.front();
    for (int i = 0; i < nums.size() - 1; ++i) {
      int a = nums[i], b = nums[i + 1];
      int h = max(nums.back() - k, a + k);
      int l = min(nums.front() + k, b - k);
      res   = min(res, h - l);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |0 <= nums[i] <= 10⁴|
// * |0 <= k <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1], k = 0
// Output: 0
//
// The score is max(nums) - min(nums) = 1 - 1 = 0.

LEETCODE_SOLUTION_UNITTEST(910, SmallestRangeII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  int         k        = 0;
  int         expect   = 0;
  int         actual   = solution->smallestRangeII(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,10], k = 2
// Output: 6
//
// Change nums to be [2, 8]. The score is max(nums) - min(nums) = 8 - 2 = 6.

LEETCODE_SOLUTION_UNITTEST(910, SmallestRangeII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 10};
  int         k        = 2;
  int         expect   = 6;
  int         actual   = solution->smallestRangeII(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,3,6], k = 3
// Output: 3
//
// Change nums to be [4, 6, 3]. The score is max(nums) - min(nums) = 6 - 3 = 3.

LEETCODE_SOLUTION_UNITTEST(910, SmallestRangeII, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 6};
  int         k        = 3;
  int         expect   = 3;
  int         actual   = solution->smallestRangeII(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
