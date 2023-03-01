// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Wildcard Matching
//
// https://leetcode.com/problems/wildcard-matching/
//
// Question ID: 44
// Difficult  : Hard
// Solve Date : 2021/12/24 18:29

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |44. Wildcard Matching|:
//
// Given an input string ( |s|) and a pattern ( |p|), implement wildcard pattern
// matching with support for |'?'| and |'*'| where:
//
//  • |'?'| Matches any single character.
//
//  • |'*'| Matches any sequence of characters (including the empty sequence).
// The matching should cover the entire input string (not partial).
//  
//

LEETCODE_BEGIN_RESOLVING(44, WildcardMatching, Solution);

class Solution {
public:
  bool isMatch(string s, string p) {
    int                 sn = s.size(), pn = p.size();
    vector<vector<int>> dp(sn + 1, vector<int>(pn + 1, 0));
    dp[0][0] = 1;
    for (int i = 1; i < pn + 1; i++)
      dp[0][i] = p[i - 1] == '*' ? dp[0][i - 1] : 0;

    for (int i = 1; i < sn + 1; i++) {
      for (int j = 1; j < pn + 1; j++) {
        dp[i][j] = p[j - 1] == '*'
                       ? (dp[i - 1][j] || dp[i][j - 1])
                       : ((s[i - 1] == p[j - 1] || p[j - 1] == '?') &&
                          dp[i - 1][j - 1]);
      }
    }
    return dp[sn][pn];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= s.length, p.length <= 2000|
// * |s| contains only lowercase English letters.
// * |p| contains only lowercase English letters, |'?'| or |'*'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aa", p = "a"
// Output: false
//
// "a" does not match the entire string "aa".

LEETCODE_SOLUTION_UNITTEST(44, WildcardMatching, example_1) {
  auto   solution = MakeSolution();
  string s        = "aa";
  string p        = "a";
  bool   expect   = false;
  bool   actual   = solution->isMatch(s, p);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aa", p = "*"
// Output: true
//
//  '*' matches any sequence.

LEETCODE_SOLUTION_UNITTEST(44, WildcardMatching, example_2) {
  auto   solution = MakeSolution();
  string s        = "aa";
  string p        = "*";
  bool   expect   = true;
  bool   actual   = solution->isMatch(s, p);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "cb", p = "?a"
// Output: false
//
//  '?' matches 'c', but the second letter is 'a', which does not match 'b'.

LEETCODE_SOLUTION_UNITTEST(44, WildcardMatching, example_3) {
  auto   solution = MakeSolution();
  string s        = "cb";
  string p        = "?a";
  bool   expect   = false;
  bool   actual   = solution->isMatch(s, p);
  LCD_EXPECT_EQ(expect, actual);
}
