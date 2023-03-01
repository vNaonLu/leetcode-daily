// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Consecutive Sequence
//
// https://leetcode.com/problems/longest-consecutive-sequence/
//
// Question ID: 128
// Difficult  : Medium
// Solve Date : 2022/07/05 18:24

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |128. Longest Consecutive Sequence|:
//
// Given an unsorted array of integers |nums|, return the length of the longest
// consecutive elements sequence. You must write an algorithm that runs in
// |O(n)|time.
//

LEETCODE_BEGIN_RESOLVING(128, LongestConsecutiveSequence, Solution);

class Solution {
public:
  int longestConsecutive(vector<int> &nums) {
    int                     res = 0;
    unordered_map<int, int> hash;
    for (const auto &n : nums) {
      if (hash[n] != 0)
        continue;

      int l = hash[n - 1], r = hash[n + 1];
      int len = hash[n + 1] + hash[n - 1] + 1;
      res     = max(len, res);
      hash[n] = hash[n + r] = hash[n - l] = len;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= nums.length <= 10⁵|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [100,4,200,1,3,2]
// Output: 4
//
// The longest consecutive elements sequence is |[1, 2, 3, 4]|. Therefore its
// length is 4.

LEETCODE_SOLUTION_UNITTEST(128, LongestConsecutiveSequence, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {100, 4, 200, 1, 3, 2};
  int         expect   = 4;
  int         actual   = solution->longestConsecutive(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,3,7,2,5,8,4,6,0,1]
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(128, LongestConsecutiveSequence, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
  int         expect   = 9;
  int         actual   = solution->longestConsecutive(nums);
  LCD_EXPECT_EQ(expect, actual);
}
