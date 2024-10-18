// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Count Number of Maximum Bitwise-OR Subsets
//
// https://leetcode.com/problems/count-number-of-maximum-bitwise-or-subsets/
//
// Question ID: 2044
// Difficult  : Medium
// Solve Date : 2024/10/18 17:08

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2044. Count Number of Maximum Bitwise-OR Subsets|:
//
// Given an integer array |nums|, find the maximum possible bitwise OR of a
// subset of |nums| and return the number of different non-empty subsets with
// the maximum bitwise OR. An array |a| is a subset of an array |b| if |a| can
// be obtained from |b| by deleting some (possibly zero) elements of |b|. Two
// subsets are considered different if the indices of the elements chosen are
// different. The bitwise OR of an array |a| is equal to |a[0] OR a[1] OR ... OR
// a[a.length - 1]| (0-indexed).
//
//

LEETCODE_BEGIN_RESOLVING(2044, CountNumberOfMaximumBitwiseORSubsets, Solution);

class Solution {
public:
  int countMaxOrSubsets(vector<int> &nums) {
    int res = 0;
    int mx  = accumulate(nums.begin(), nums.end(), 0,
                         [](auto x, auto y) { return x | y; });
    dfs(nums, 0, 0, mx, &res);
    return res;
  }

private:
  void dfs(const vector<int> &nums, int idx, int curr, int mx, int *cnt) {
    if (curr == mx) {
      ++*cnt;
    }

    for (int i = idx; i < nums.size(); ++i) {
      dfs(nums, i + 1, curr | nums[i], mx, cnt);
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 16|
// * |1 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,1]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2044, CountNumberOfMaximumBitwiseORSubsets,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1};
  int         expect   = 2;
  int         actual   = solution->countMaxOrSubsets(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,2,2]
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(2044, CountNumberOfMaximumBitwiseORSubsets,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 2};
  int         expect   = 7;
  int         actual   = solution->countMaxOrSubsets(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,2,1,5]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(2044, CountNumberOfMaximumBitwiseORSubsets,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 1, 5};
  int         expect   = 6;
  int         actual   = solution->countMaxOrSubsets(nums);
  LCD_EXPECT_EQ(expect, actual);
}
