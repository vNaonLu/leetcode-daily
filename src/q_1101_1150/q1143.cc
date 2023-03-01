// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Common Subsequence
//
// https://leetcode.com/problems/longest-common-subsequence/
//
// Question ID: 1143
// Difficult  : Medium
// Solve Date : 2021/10/01 11:36

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1143. Longest Common Subsequence|:
//
// Given two strings |text1| and |text2|, return the length of their longest
// common subsequence. If there is no common subsequence, return |0|. A
// subsequence of a string is a new string generated from the original string
// with some characters (can be none) deleted without changing the relative
// order of the remaining characters.
//
//  • For example, |"ace"| is a subsequence of |"abcde"|.
// A common subsequence of two strings is a subsequence that is common to both
// strings.  
//

LEETCODE_BEGIN_RESOLVING(1143, LongestCommonSubsequence, Solution);

class Solution {
public:
  int longestCommonSubsequence(string text1, string text2) {
    int                 m = text1.size() + 1;
    int                 n = text2.size() + 1;
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        if (text1[i - 1] == text2[j - 1]) {
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
// * |1 <= text1.length, text2.length <= 1000|
// * |text1| and |text2| consist of only lowercase English characters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: text1 = "abcde", text2 = "ace"
// Output: 3
//
// The longest common subsequence is "ace" and its length is 3.

LEETCODE_SOLUTION_UNITTEST(1143, LongestCommonSubsequence, example_1) {
  auto   solution = MakeSolution();
  string text1    = "abcde";
  string text2    = "ace";
  int    expect   = 3;
  int    actual   = solution->longestCommonSubsequence(text1, text2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: text1 = "abc", text2 = "abc"
// Output: 3
//
// The longest common subsequence is "abc" and its length is 3.

LEETCODE_SOLUTION_UNITTEST(1143, LongestCommonSubsequence, example_2) {
  auto   solution = MakeSolution();
  string text1    = "abc";
  string text2    = "abc";
  int    expect   = 3;
  int    actual   = solution->longestCommonSubsequence(text1, text2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: text1 = "abc", text2 = "def"
// Output: 0
//
// There is no such common subsequence, so the result is 0.

LEETCODE_SOLUTION_UNITTEST(1143, LongestCommonSubsequence, example_3) {
  auto   solution = MakeSolution();
  string text1    = "abc";
  string text2    = "def";
  int    expect   = 0;
  int    actual   = solution->longestCommonSubsequence(text1, text2);
  LCD_EXPECT_EQ(expect, actual);
}
