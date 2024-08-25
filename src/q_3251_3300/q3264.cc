// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Final Array State After K Multiplication Operations I
//
// https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-i/
//
// Question ID: 3264
// Difficult  : Easy
// Solve Date : 2024/08/25 15:27

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3264. Final Array State After K Multiplication Operations I|:
//
// You are given an integer array |nums|, an integer |k|, and an integer
// |multiplier|. You need to perform |k| operations on |nums|. In each
// operation:
//
//  • Find the minimum value |x| in |nums|. If there are multiple occurrences of
//  the minimum value, select the one that appears first.
//
//  • Replace the selected minimum value |x| with |x * multiplier|.
// Return an integer array denoting the final state of |nums| after performing
// all |k| operations.
//
//

LEETCODE_BEGIN_RESOLVING(3264, FinalArrayStateAfterKMultiplicationOperationsI,
                         Solution);

class Solution {
public:
  vector<int> getFinalState(vector<int> &nums, int k, int multiplier) {
    vector<int> res = nums;
    while (k--) {
      auto it = min_element(res.begin(), res.end());
      *it *= multiplier;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i] <= 100|
// * |1 <= k <= 10|
// * |1 <= multiplier <= 5|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,1,3,5,6], k = 5, multiplier = 2
// Output: [8,4,6,5,6]
//

LEETCODE_SOLUTION_UNITTEST(3264, FinalArrayStateAfterKMultiplicationOperationsI,
                           example_1) {
  auto        solution   = MakeSolution();
  vector<int> nums       = {2, 1, 3, 5, 6};
  int         k          = 5;
  int         multiplier = 2;
  vector<int> expect     = {8, 4, 6, 5, 6};
  vector<int> actual     = solution->getFinalState(nums, k, multiplier);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2], k = 3, multiplier = 4
// Output: [16,8]
//

LEETCODE_SOLUTION_UNITTEST(3264, FinalArrayStateAfterKMultiplicationOperationsI,
                           example_2) {
  auto        solution   = MakeSolution();
  vector<int> nums       = {1, 2};
  int         k          = 3;
  int         multiplier = 4;
  vector<int> expect     = {16, 8};
  vector<int> actual     = solution->getFinalState(nums, k, multiplier);
  LCD_EXPECT_EQ(expect, actual);
}
