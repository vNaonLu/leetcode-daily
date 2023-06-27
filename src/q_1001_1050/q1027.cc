// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Arithmetic Subsequence
//
// https://leetcode.com/problems/longest-arithmetic-subsequence/
//
// Question ID: 1027
// Difficult  : Medium
// Solve Date : 2023/06/23 18:49

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1027. Longest Arithmetic Subsequence|:
//
// Given an array |nums| of integers, return the length of the longest
// arithmetic subsequence in |nums|. Note that:
//
//  • A subsequence is an array that can be derived from another array by
//  deleting some or no elements without changing the order of the remaining
//  elements.
//
//  • A sequence |seq| is arithmetic if |seq[i + 1] - seq[i]| are all the same
//  value (for |0 <= i < seq.length - 1|).
//
//

LEETCODE_BEGIN_RESOLVING(1027, LongestArithmeticSubsequence, Solution);

class Solution {
public:
  int longestArithSeqLength(vector<int> &nums) {
    int                             res = 0;
    int                             n   = nums.size();
    vector<unordered_map<int, int>> m(n + 1);
    for (int i = n - 1; i >= 0; --i) {
      for (int j = n - 1; j > i; --j) {
        int diff = nums[j] - nums[i];
        if (m[j].count(diff)) {
          m[i][diff] = m[j][diff] + 1;
        } else {
          m[i][diff] = 2;
        }
        res = max(res, m[i][diff]);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 1000|
// * |0 <= nums[i] <= 500|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,6,9,12]
// Output: 4
//
// The whole array is an arithmetic sequence with steps of length = 3.

LEETCODE_SOLUTION_UNITTEST(1027, LongestArithmeticSubsequence, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 6, 9, 12};
  int         expect   = 4;
  int         actual   = solution->longestArithSeqLength(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [9,4,7,2,10]
// Output: 3
//
// The longest arithmetic subsequence is [4,7,10].

LEETCODE_SOLUTION_UNITTEST(1027, LongestArithmeticSubsequence, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {9, 4, 7, 2, 10};
  int         expect   = 3;
  int         actual   = solution->longestArithSeqLength(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [20,1,15,3,10,5,8]
// Output: 4
//
// The longest arithmetic subsequence is [20,15,10,5].

LEETCODE_SOLUTION_UNITTEST(1027, LongestArithmeticSubsequence, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {20, 1, 15, 3, 10, 5, 8};
  int         expect   = 4;
  int         actual   = solution->longestArithSeqLength(nums);
  LCD_EXPECT_EQ(expect, actual);
}
