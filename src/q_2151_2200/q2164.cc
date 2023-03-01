// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sort Even and Odd Indices Independently
//
// https://leetcode.com/problems/sort-even-and-odd-indices-independently/
//
// Question ID: 2164
// Difficult  : Easy
// Solve Date : 2023/01/23 14:30

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2164. Sort Even and Odd Indices Independently|:
//
// You are given a 0-indexed integer array |nums|. Rearrange the values of
// |nums| according to the following rules:
//
//  1. Sort the values at odd indices of |nums| in non-increasing order.
//
//
//    • For example, if |nums = [4,1,2,3]| before this step, it becomes
//    |[4,3,2,1]| after. The values at odd indices |1| and |3| are sorted in
//    non-increasing order.
//
//
//
//  2. Sort the values at even indices of |nums| in non-decreasing order.
//
//
//    • For example, if |nums = [4,1,2,3]| before this step, it becomes
//    |[2,1,4,3]| after. The values at even indices |0| and |2| are sorted in
//    non-decreasing order.
//
//
// Return the array formed after rearranging the values of |nums|.
//

LEETCODE_BEGIN_RESOLVING(2164, SortEvenAndOddIndicesIndependently, Solution);

class Solution {
public:
  vector<int> sortEvenOdd(vector<int> &nums) {
    vector<vector<int>> tmp(2);
    vector<int>         res;
    for (int i = 0; i < nums.size(); ++i) {
      tmp[i & 1].emplace_back(nums[i]);
    }
    sort(tmp[0].begin(), tmp[0].end());
    sort(tmp[1].begin(), tmp[1].end(), greater<int>());
    for (int i = 0; i < max(tmp[0].size(), tmp[1].size()); ++i) {
      if (i < tmp[0].size()) {
        res.emplace_back(tmp[0][i]);
      }
      if (i < tmp[1].size()) {
        res.emplace_back(tmp[1][i]);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,1,2,3]
// Output: [2,3,4,1]
//
// First, we sort the values present at odd indices (1 and 3) in non-increasing
// order. So, nums changes from [4,1,2,3] to [4,3,2,1]. Next, we sort the values
// present at even indices (0 and 2) in non-decreasing order. So, nums changes
// from [4,1,2,3] to [2,3,4,1]. Thus, the array formed after rearranging the
// values is [2,3,4,1].

LEETCODE_SOLUTION_UNITTEST(2164, SortEvenAndOddIndicesIndependently,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 1, 2, 3};
  vector<int> expect   = {2, 3, 4, 1};
  vector<int> actual   = solution->sortEvenOdd(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,1]
// Output: [2,1]
//
// Since there is exactly one odd index and one even index, no rearrangement of
// values takes place. The resultant array formed is [2,1], which is the same as
// the initial array.

LEETCODE_SOLUTION_UNITTEST(2164, SortEvenAndOddIndicesIndependently,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1};
  vector<int> expect   = {2, 1};
  vector<int> actual   = solution->sortEvenOdd(nums);
  LCD_EXPECT_EQ(expect, actual);
}
