// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Pivot Index
//
// https://leetcode.com/problems/find-pivot-index/
//
// Question ID: 724
// Difficult  : Easy
// Solve Date : 2022/08/24 21:08

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |724. Find Pivot Index|:
//
// Given an array of integers |nums|, calculate the pivot index of this array.
// The pivot index is the index where the sum of all the numbers strictly to the
// left of the index is equal to the sum of all the numbers strictly to the
// index's right. If the index is on the left edge of the array, then the left
// sum is |0| because there are no elements to the left. This also applies to
// the right edge of the array. Return the leftmost pivot index. If no such
// index exists, return |-1|.
//

LEETCODE_BEGIN_RESOLVING(724, FindPivotIndex, Solution);

class Solution {
public:
  int pivotIndex(vector<int> &nums) {
    auto presum = vector<int>(nums.begin(), nums.end());
    auto beg    = presum.begin();
    for (auto it = presum.begin() + 1; it != presum.end(); ++it) {
      *it += *(it - 1);
    }

    while (beg != presum.end()) {
      if (*beg == presum.back() - (beg == presum.begin() ? 0 : *(beg - 1))) {
        /// distance: O(1)
        return distance(presum.begin(), beg);
      }
      ++beg;
    }

    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |-1000 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,7,3,6,5,6]
// Output: 3
//
// The pivot index is 3.
// Left sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11
// Right sum = nums[4] + nums[5] = 5 + 6 = 11

LEETCODE_SOLUTION_UNITTEST(724, FindPivotIndex, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 7, 3, 6, 5, 6};
  int         expect   = 3;
  int         actual   = solution->pivotIndex(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3]
// Output: -1
//
// There is no index that satisfies the conditions in the problem statement.

LEETCODE_SOLUTION_UNITTEST(724, FindPivotIndex, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  int         expect   = -1;
  int         actual   = solution->pivotIndex(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [2,1,-1]
// Output: 0
//
// The pivot index is 0.
// Left sum = 0 (no elements to the left of index 0)
// Right sum = nums[1] + nums[2] = 1 + -1 = 0

LEETCODE_SOLUTION_UNITTEST(724, FindPivotIndex, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, -1};
  int         expect   = 0;
  int         actual   = solution->pivotIndex(nums);
  LCD_EXPECT_EQ(expect, actual);
}
