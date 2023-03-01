// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Longest Increasing Subsequence
//
// https://leetcode.com/problems/number-of-longest-increasing-subsequence/
//
// Question ID: 673
// Difficult  : Medium
// Solve Date : 2021/10/04 12:25

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |673. Number of Longest Increasing Subsequence|:
//
// Given an integer array  |nums|, return the number of longest increasing
// subsequences. Notice that the sequence has to be strictly increasing.  
//

LEETCODE_BEGIN_RESOLVING(673, NumberOfLongestIncreasingSubsequence, Solution);

class Solution {
public:
  int findNumberOfLIS(vector<int> &nums) {
    int                    n = nums.size();
    vector<pair<int, int>> dp(n, make_pair(1, 1));
    int                    mx = 1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
        if (nums[i] > nums[j]) {
          int p       = dp[i].first;
          dp[i].first = max(dp[i].first, 1 + dp[j].first);
          if (p != dp[i].first) {
            dp[i].second = dp[j].second;
          } else if (dp[i].first == 1 + dp[j].first) {
            dp[i].second += dp[j].second;
          }
          mx = max(mx, dp[i].first);
        }
      }
    }
    int res = 0;
    for (auto i : dp) {
      if (i.first == mx)
        res += i.second;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 2000|
// * |-10⁶ <= nums[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,5,4,7]
// Output: 2
//
// The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].

LEETCODE_SOLUTION_UNITTEST(673, NumberOfLongestIncreasingSubsequence,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 5, 4, 7};
  int         expect   = 2;
  int         actual   = solution->findNumberOfLIS(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,2,2,2,2]
// Output: 5
//
// The length of the longest increasing subsequence is 1, and there are 5
// increasing subsequences of length 1, so output 5.

LEETCODE_SOLUTION_UNITTEST(673, NumberOfLongestIncreasingSubsequence,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 2, 2, 2};
  int         expect   = 5;
  int         actual   = solution->findNumberOfLIS(nums);
  LCD_EXPECT_EQ(expect, actual);
}
