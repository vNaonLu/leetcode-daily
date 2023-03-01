// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Wiggle Subsequence
//
// https://leetcode.com/problems/wiggle-subsequence/
//
// Question ID: 376
// Difficult  : Medium
// Solve Date : 2021/10/27 14:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |376. Wiggle Subsequence|:
//
// A wiggle sequence is a sequence where the differences between successive
// numbers strictly alternate between positive and negative. The first
// difference (if one exists) may be either positive or negative. A sequence
// with one element and a sequence with two non-equal elements are trivially
// wiggle sequences.
//
//  • For example, |[1, 7, 4, 9, 2, 5]| is a wiggle sequence because the
//  differences |(6, -3, 5, -7, 3)| alternate between positive and negative.
//
//  • In contrast, |[1, 4, 7, 2, 5]| and |[1, 7, 4, 5, 5]| are not wiggle
//  sequences. The first is not because its first two differences are positive,
//  and the second is not because its last difference is zero.
// A subsequence is obtained by deleting some elements (possibly zero) from the
// original sequence, leaving the remaining elements in their original order.
// Given an integer array |nums|, return the length of the longest wiggle
// subsequence of |nums|.  
//

LEETCODE_BEGIN_RESOLVING(376, WiggleSubsequence, Solution);

class Solution {
public:
  int wiggleMaxLength(vector<int> &nums) {
    if (nums.size() < 2)
      return nums.size();
    vector<int> up(nums.size(), 1);
    vector<int> down(nums.size(), 1);
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] > nums[i - 1]) {
        up[i]   = down[i - 1] + 1;
        down[i] = down[i - 1];
      } else if (nums[i] < nums[i - 1]) {
        down[i] = up[i - 1] + 1;
        up[i]   = up[i - 1];
      } else {
        down[i] = down[i - 1];
        up[i]   = up[i - 1];
      }
    }
    return max(up.back(), down.back());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |0 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,7,4,9,2,5]
// Output: 6
//
// The entire sequence is a wiggle sequence with differences (6, -3, 5, -7, 3).

LEETCODE_SOLUTION_UNITTEST(376, WiggleSubsequence, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 7, 4, 9, 2, 5};
  int         expect   = 6;
  int         actual   = solution->wiggleMaxLength(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,17,5,10,13,15,10,5,16,8]
// Output: 7
//
// There are several subsequences that achieve this length.
// One is [1, 17, 10, 13, 10, 16, 8] with differences (16, -7, 3, -3, 6, -8).

LEETCODE_SOLUTION_UNITTEST(376, WiggleSubsequence, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 17, 5, 10, 13, 15, 10, 5, 16, 8};
  int         expect   = 7;
  int         actual   = solution->wiggleMaxLength(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3,4,5,6,7,8,9]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(376, WiggleSubsequence, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int         expect   = 2;
  int         actual   = solution->wiggleMaxLength(nums);
  LCD_EXPECT_EQ(expect, actual);
}
