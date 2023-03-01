// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Split Array into Consecutive Subsequences
//
// https://leetcode.com/problems/split-array-into-consecutive-subsequences/
//
// Question ID: 659
// Difficult  : Medium
// Solve Date : 2022/08/19 18:17

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |659. Split Array into Consecutive Subsequences|:
//
// You are given an integer array |nums| that is sorted in non-decreasing order.
// Determine if it is possible to split |nums| into one or more subsequences
// such that both of the following conditions are true:
//
//  • Each subsequence is a consecutive increasing sequence (i.e. each integer
//  is exactly one more than the previous integer).
//
//  • All subsequences have a length of |3| or more.
// Return |true| if you can split |nums| according to the above conditions, or
// |false| otherwise. A subsequence of an array is a new array that is formed
// from the original array by deleting some (can be none) of the elements
// without disturbing the relative positions of the remaining elements. (i.e.,
// |[1,3,5]| is a subsequence of |[1,2,3,4,5]| while |[1,3,2]| is not).
//

LEETCODE_BEGIN_RESOLVING(659, SplitArrayIntoConsecutiveSubsequences, Solution);

class Solution {
public:
  bool isPossible(vector<int> &nums) {
    auto freq = unordered_map<int, int>();
    auto need = unordered_map<int, int>();
    for (auto x : nums) {
      ++freq[x];
    }

    for (auto x : nums) {
      if (freq[x] == 0) {
        /// all are taken
        continue;
      }

      if (need[x] > 0) {
        --need[x];
        --freq[x];

        ++need[x + 1];
      } else if (freq[x] > 0 && freq[x + 1] > 0 && freq[x + 2] > 0) {
        --freq[x];
        --freq[x + 1];
        --freq[x + 2];

        ++need[x + 3];
      } else {

        return false;
      }
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |-1000 <= nums[i] <= 1000|
// * |nums| is sorted in non-decreasing order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,3,4,5]
// Output: true
//
// nums can be split into the following subsequences:
// [1,2,3,3,4,5] --> 1, 2, 3
// [1,2,3,3,4,5] --> 3, 4, 5

LEETCODE_SOLUTION_UNITTEST(659, SplitArrayIntoConsecutiveSubsequences,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 3, 4, 5};
  bool        expect   = true;
  bool        actual   = solution->isPossible(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,3,4,4,5,5]
// Output: true
//
// nums can be split into the following subsequences:
// [1,2,3,3,4,4,5,5] --> 1, 2, 3, 4, 5
// [1,2,3,3,4,4,5,5] --> 3, 4, 5

LEETCODE_SOLUTION_UNITTEST(659, SplitArrayIntoConsecutiveSubsequences,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 3, 4, 4, 5, 5};
  bool        expect   = true;
  bool        actual   = solution->isPossible(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3,4,4,5]
// Output: false
//
// It is impossible to split nums into consecutive increasing subsequences of
// length 3 or more.

LEETCODE_SOLUTION_UNITTEST(659, SplitArrayIntoConsecutiveSubsequences,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 4, 5};
  bool        expect   = false;
  bool        actual   = solution->isPossible(nums);
  LCD_EXPECT_EQ(expect, actual);
}
