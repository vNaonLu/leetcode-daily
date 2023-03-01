// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Palindromic Substrings
//
// https://leetcode.com/problems/palindromic-substrings/
//
// Question ID: 647
// Difficult  : Medium
// Solve Date : 2022/05/22 14:26

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |647. Palindromic Substrings|:
//
// Given a string |s|, return the number of palindromic substrings in it.
// A string is a palindrome when it reads the same backward as forward.
// A substring is a contiguous sequence of characters within the string.
//

LEETCODE_BEGIN_RESOLVING(647, PalindromicSubstrings, Solution);

class Solution {
public:
  int countSubstrings(string s) {
    int                 n = s.size(), res = 0;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
      dp[i][i] = 1;
      ++res;
    }

    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if ((j + 1 == i && s[i] == s[j]) ||
            (dp[j + 1][i - 1] == 1 && s[i] == s[j])) {
          dp[j][i] = 1;
          ++res;
        }
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 1000|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abc"
// Output: 3
//
// Three palindromic strings: "a", "b", "c".

LEETCODE_SOLUTION_UNITTEST(647, PalindromicSubstrings, example_1) {
  auto   solution = MakeSolution();
  string s        = "abc";
  int    expect   = 3;
  int    actual   = solution->countSubstrings(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aaa"
// Output: 6
//
// Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".

LEETCODE_SOLUTION_UNITTEST(647, PalindromicSubstrings, example_2) {
  auto   solution = MakeSolution();
  string s        = "aaa";
  int    expect   = 6;
  int    actual   = solution->countSubstrings(s);
  LCD_EXPECT_EQ(expect, actual);
}
