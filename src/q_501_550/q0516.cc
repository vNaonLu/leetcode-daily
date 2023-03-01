// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Palindromic Subsequence
//
// https://leetcode.com/problems/longest-palindromic-subsequence/
//
// Question ID: 516
// Difficult  : Medium
// Solve Date : 2021/10/26 14:13

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |516. Longest Palindromic Subsequence|:
//
// Given a string |s|, find the longest palindromic subsequence's length in |s|.
// A subsequence is a sequence that can be derived from another sequence by
// deleting some or no elements without changing the order of the remaining
// elements.  
//

LEETCODE_BEGIN_RESOLVING(516, LongestPalindromicSubsequence, Solution);

class Solution {
public:
  int longestPalindromeSubseq(string s) {
    int                 n = s.size();
    string              rvs(s.rbegin(), s.rend());
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (rvs[i - 1] == s[j - 1]) {
          dp[i][j] = 1 + dp[i - 1][j - 1];
        } else {
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }
    return dp.back().back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 1000|
// * |s| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "bbbab"
// Output: 4
//
// One possible longest palindromic subsequence is "bbbb".

LEETCODE_SOLUTION_UNITTEST(516, LongestPalindromicSubsequence, example_1) {
  auto   solution = MakeSolution();
  string s        = "bbbab";
  int    expect   = 4;
  int    actual   = solution->longestPalindromeSubseq(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "cbbd"
// Output: 2
//
// One possible longest palindromic subsequence is "bb".

LEETCODE_SOLUTION_UNITTEST(516, LongestPalindromicSubsequence, example_2) {
  auto   solution = MakeSolution();
  string s        = "cbbd";
  int    expect   = 2;
  int    actual   = solution->longestPalindromeSubseq(s);
  LCD_EXPECT_EQ(expect, actual);
}
