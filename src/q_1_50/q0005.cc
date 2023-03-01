// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Palindromic Substring
//
// https://leetcode.com/problems/longest-palindromic-substring/
//
// Question ID: 5
// Difficult  : Medium
// Solve Date : 2021/09/27 14:03

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |5. Longest Palindromic Substring|:
//
// Given a string |s|, return the longest palindromic substring in |s|.
//  
//

LEETCODE_BEGIN_RESOLVING(5, LongestPalindromicSubstring, Solution);

class Solution {
private:
  int helper(const string &s, int l, int r) {
    while (l >= 0 && r < s.size() && s[l] == s[r]) {
      ++r;
      --l;
    }
    return r - l - 1;
  }

public:
  string longestPalindrome(string s) {
    if (s.empty())
      return "";
    int l = 0, maxl = 1;
    for (int i = 0; i < s.size(); ++i) {
      int len = max(helper(s, i, i), helper(s, i, i + 1));
      if (len > maxl) {
        maxl = len;
        l    = i - (len - 1) / 2;
      }
    }
    return s.substr(l, maxl);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 1000|
// * |s| consist of only digits and English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "babad"
// Output: "bab"
//
// "aba" is also a valid answer.

LEETCODE_SOLUTION_UNITTEST(5, LongestPalindromicSubstring, example_1) {
  auto   solution = MakeSolution();
  string s        = "babad";
  string expect   = "bab";
  string actual   = solution->longestPalindrome(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "cbbd"
// Output: "bb"
//

LEETCODE_SOLUTION_UNITTEST(5, LongestPalindromicSubstring, example_2) {
  auto   solution = MakeSolution();
  string s        = "cbbd";
  string expect   = "bb";
  string actual   = solution->longestPalindrome(s);
  LCD_EXPECT_EQ(expect, actual);
}
