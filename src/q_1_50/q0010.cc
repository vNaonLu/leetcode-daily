// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Regular Expression Matching
//
// https://leetcode.com/problems/regular-expression-matching/
//
// Question ID: 10
// Difficult  : Hard
// Solve Date : 2021/10/10 14:20

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |10. Regular Expression Matching|:
//
// Given an input string |s| and a pattern |p|, implement regular expression
// matching with support for |'.'| and |'*'| where:
//
//  • |'.'| Matches any single character.​​​​
//
//  • |'*'| Matches zero or more of the preceding element.
// The matching should cover the entire input string (not partial).
//  
//

LEETCODE_BEGIN_RESOLVING(10, RegularExpressionMatching, Solution);

class Solution {
public:
  bool isMatch(string s, string p) {
    int                  m = s.size() + 1, n = p.size() + 1;
    vector<vector<bool>> dp(m, vector<bool>(n, false));
    dp[0][0] = true;

    for (int j = 1; j < n; ++j)
      if (p[j - 1] == '*')
        dp[0][j] = dp[0][j - 2];

    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        if (s[i - 1] == p[j - 1] || p[j - 1] == '.') {
          dp[i][j] = dp[i - 1][j - 1];
        } else if (p[j - 1] == '*') {
          dp[i][j] = dp[i][j - 2];
          if (s[i - 1] == p[j - 2] || p[j - 2] == '.')
            dp[i][j] = dp[i][j - 2] | dp[i - 1][j];
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
// * |1 <= s.length <= 20|
// * |1 <= p.length <= 20|
// * |s| contains only lowercase English letters.
// * |p| contains only lowercase English letters, |'.'|, and  |'*'|.
// * It is guaranteed for each appearance of the character |'*'|, there will be
// a previous valid character to match.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aa", p = "a"
// Output: false
//
// "a" does not match the entire string "aa".

LEETCODE_SOLUTION_UNITTEST(10, RegularExpressionMatching, example_1) {
  auto   solution = MakeSolution();
  string s        = "aa";
  string p        = "a";
  bool   expect   = false;
  bool   actual   = solution->isMatch(s, p);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aa", p = "a*"
// Output: true
//
// '*' means zero or more of the preceding element, 'a'. Therefore, by repeating
// 'a' once, it becomes "aa".

LEETCODE_SOLUTION_UNITTEST(10, RegularExpressionMatching, example_2) {
  auto   solution = MakeSolution();
  string s        = "aa";
  string p        = "a*";
  bool   expect   = true;
  bool   actual   = solution->isMatch(s, p);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "ab", p = ".*"
// Output: true
//
// ".*" means "zero or more (*) of any character (.)".

LEETCODE_SOLUTION_UNITTEST(10, RegularExpressionMatching, example_3) {
  auto   solution = MakeSolution();
  string s        = "ab";
  string p        = ".*";
  bool   expect   = true;
  bool   actual   = solution->isMatch(s, p);
  LCD_EXPECT_EQ(expect, actual);
}
