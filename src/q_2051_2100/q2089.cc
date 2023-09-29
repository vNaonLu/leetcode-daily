// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Target Indices After Sorting Array
//
// https://leetcode.com/problems/find-target-indices-after-sorting-array/
//
// Question ID: 2089
// Difficult  : Easy
// Solve Date : 2023/09/29 17:02

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2089. Find Target Indices After Sorting Array|:
//
// You are given a 0-indexed integer array |nums| and a target element |target|.
// A target index is an index |i| such that |nums[i] == target|.
// Return a list of the target indices of |nums| after sorting |nums| in
// non-decreasing order. If there are no target indices, return an empty list.
// The returned list must be sorted in increasing order.
//
//

LEETCODE_BEGIN_RESOLVING(2089, FindTargetIndicesAfterSortingArray, Solution);

class Solution {
public:
  vector<int> targetIndices(vector<int> &nums, int target) {
    vector<int> res;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] == target) {
        res.emplace_back(i);
      }

      if (nums[i] > target) {
        break;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i], target <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,5,2,3], target = 2
// Output: [1,2]
//
// After sorting, nums is [1,2,2,3,5].
// The indices where nums[i] == 2 are 1 and 2.

LEETCODE_SOLUTION_UNITTEST(2089, FindTargetIndicesAfterSortingArray,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 5, 2, 3};
  int         target   = 2;
  vector<int> expect   = {1, 2};
  vector<int> actual   = solution->targetIndices(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,5,2,3], target = 3
// Output: [3]
//
// After sorting, nums is [1,2,2,3,5].
// The index where nums[i] == 3 is 3.

LEETCODE_SOLUTION_UNITTEST(2089, FindTargetIndicesAfterSortingArray,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 5, 2, 3};
  int         target   = 3;
  vector<int> expect   = {3};
  vector<int> actual   = solution->targetIndices(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,5,2,3], target = 5
// Output: [4]
//
// After sorting, nums is [1,2,2,3,5].
// The index where nums[i] == 5 is 4.

LEETCODE_SOLUTION_UNITTEST(2089, FindTargetIndicesAfterSortingArray,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 5, 2, 3};
  int         target   = 5;
  vector<int> expect   = {4};
  vector<int> actual   = solution->targetIndices(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}
