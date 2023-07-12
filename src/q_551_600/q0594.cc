// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Harmonious Subsequence
//
// https://leetcode.com/problems/longest-harmonious-subsequence/
//
// Question ID: 594
// Difficult  : Easy
// Solve Date : 2023/07/12 19:52

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |594. Longest Harmonious Subsequence|:
//
// We define a harmonious array as an array where the difference between its
// maximum value and its minimum value is exactly |1|.
//
// Given an integer array |nums|, return the length of its longest harmonious
// subsequence among all its possible subsequences.
//
// A subsequence of array is a sequence that can be derived from the array by
// deleting some or no elements without changing the order of the remaining
// elements.
//
//
//

LEETCODE_BEGIN_RESOLVING(594, LongestHarmoniousSubsequence, Solution);

class Solution {
public:
  int findLHS(vector<int> &nums) {
    unordered_map<int, int> freq;
    int                     res = 0;
    for (auto x : nums) {
      ++freq[x];
    }

    for (auto [nxt, cnt] : freq) {
      auto it = freq.find(nxt + 1);
      if (it == freq.end()) {
        continue;
      }

      res = max(res, cnt + it->second);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 2 * 10⁴|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,2,2,5,2,3,7]
// Output: 5
//
// The longest harmonious subsequence is [3,2,2,2,3].

LEETCODE_SOLUTION_UNITTEST(594, LongestHarmoniousSubsequence, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 2, 2, 5, 2, 3, 7};
  int         expect   = 5;
  int         actual   = solution->findLHS(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(594, LongestHarmoniousSubsequence, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         expect   = 2;
  int         actual   = solution->findLHS(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,1,1,1]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(594, LongestHarmoniousSubsequence, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1, 1};
  int         expect   = 0;
  int         actual   = solution->findLHS(nums);
  LCD_EXPECT_EQ(expect, actual);
}
