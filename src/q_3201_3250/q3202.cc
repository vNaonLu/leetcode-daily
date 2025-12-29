// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find the Maximum Length of Valid Subsequence II
//
// https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/
//
// Question ID: 3202
// Difficult  : Medium
// Solve Date : 2025/07/17 19:25

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3202. Find the Maximum Length of Valid Subsequence II|:
//
// You are given an integer array |nums| and a positive integer |k|.
// A subsequence |sub| of |nums| with length |x| is called valid if it
// satisfies:
//
//  • |(sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] +
//  sub[x - 1]) % k.|
// Return the length of the longest valid subsequence of |nums|.
//
//

LEETCODE_BEGIN_RESOLVING(3202, FindTheMaximumLengthOfValidSubsequenceII,
                         Solution);

class Solution {
public:
  int maximumLength(vector<int> &nums, int k) {
    int res = 2;
    for (int i = 0; i < k; ++i) {
      vector<int> dp(k);
      for (auto x : nums) {
        auto m   = x % k;
        auto pos = (i - m + k) % k;
        dp[m]    = 1 + dp[pos];
      }

      res = max(res, *max_element(dp.begin(), dp.end()));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 10³|
// * |1 <= nums[i] <= 10⁷|
// * |1 <= k <= 10³|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4,5], k = 2
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3202, FindTheMaximumLengthOfValidSubsequenceII,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  int         k        = 2;
  int         expect   = 5;
  int         actual   = solution->maximumLength(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,4,2,3,1,4], k = 3
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3202, FindTheMaximumLengthOfValidSubsequenceII,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 4, 2, 3, 1, 4};
  int         k        = 3;
  int         expect   = 4;
  int         actual   = solution->maximumLength(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
