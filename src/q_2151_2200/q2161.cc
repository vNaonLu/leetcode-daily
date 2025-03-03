// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Partition Array According to Given Pivot
//
// https://leetcode.com/problems/partition-array-according-to-given-pivot/
//
// Question ID: 2161
// Difficult  : Medium
// Solve Date : 2025/03/03 18:22

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2161. Partition Array According to Given Pivot|:
//
// You are given a 0-indexed integer array |nums| and an integer |pivot|.
// Rearrange |nums| such that the following conditions are satisfied:
//
//  • Every element less than |pivot| appears before every element greater than
//  |pivot|.
//
//  • Every element equal to |pivot| appears in between the elements less than
//  and greater than |pivot|.
//
//  • The relative order of the elements less than |pivot| and the elements
//  greater than |pivot| is maintained.
//
//
//    • More formally, consider every |pᵢ|, |pⱼ| where |pᵢ| is the new position
//    of the |iᵗʰ| element and |pⱼ| is the new position of the |jᵗʰ| element. If
//    |i < j| and both elements are smaller (or larger) than |pivot|, then |pᵢ <
//    pⱼ|.
//
//
// Return |nums| after the rearrangement.
//
//

LEETCODE_BEGIN_RESOLVING(2161, PartitionArrayAccordingToGivenPivot, Solution);

class Solution {
public:
  vector<int> pivotArray(vector<int> &nums, int pivot) {
    vector<int> res(nums.size(), 0);
    int         lo = 0;
    int         hi = nums.size() - 1;
    for (int i = 0, j = nums.size() - 1; i < nums.size(); ++i, --j) {
      if (nums[i] < pivot) {
        res[lo++] = nums[i];
      }
      if (nums[j] > pivot) {
        res[hi--] = nums[j];
      }
    }
    while (lo <= hi) {
      res[lo++] = pivot;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |-10⁶ <= nums[i] <= 10⁶|
// * |pivot| equals to an element of |nums|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [9,12,5,10,14,3,10], pivot = 10
// Output: [9,5,3,10,10,12,14]
//

LEETCODE_SOLUTION_UNITTEST(2161, PartitionArrayAccordingToGivenPivot,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {9, 12, 5, 10, 14, 3, 10};
  int         pivot    = 10;
  vector<int> expect   = {9, 5, 3, 10, 10, 12, 14};
  vector<int> actual   = solution->pivotArray(nums, pivot);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-3,4,3,2], pivot = 2
// Output: [-3,2,4,3]
//

LEETCODE_SOLUTION_UNITTEST(2161, PartitionArrayAccordingToGivenPivot,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-3, 4, 3, 2};
  int         pivot    = 2;
  vector<int> expect   = {-3, 2, 4, 3};
  vector<int> actual   = solution->pivotArray(nums, pivot);
  LCD_EXPECT_EQ(expect, actual);
}
