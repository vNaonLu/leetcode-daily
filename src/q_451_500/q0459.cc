// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Repeated Substring Pattern
//
// https://leetcode.com/problems/repeated-substring-pattern/
//
// Question ID: 459
// Difficult  : Easy
// Solve Date : 2022/04/27 18:40

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |459. Repeated Substring Pattern|:
//
// Given a string |s|, check if it can be constructed by taking a substring of
// it and appending multiple copies of the substring together.  
//

LEETCODE_BEGIN_RESOLVING(459, RepeatedSubstringPattern, Solution);

class Solution {
public:
  bool repeatedSubstringPattern(string s) {
    vector<int> kmp(s.size(), 0);
    for (int i = 0, j = 1; j < s.size(); ++j) {
      while (i > 0 && s[i] != s[j]) {
        i = kmp[i - 1];
      }

      if (s[i] == s[j]) {
        kmp[j] = ++i;
      }
    }

    return kmp.back() && kmp.back() % (s.size() - kmp.back()) == 0;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁴|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abab"
// Output: true
//
// It is the substring "ab" twice.

LEETCODE_SOLUTION_UNITTEST(459, RepeatedSubstringPattern, example_1) {
  auto   solution = MakeSolution();
  string s        = "abab";
  bool   expect   = true;
  bool   actual   = solution->repeatedSubstringPattern(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aba"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(459, RepeatedSubstringPattern, example_2) {
  auto   solution = MakeSolution();
  string s        = "aba";
  bool   expect   = false;
  bool   actual   = solution->repeatedSubstringPattern(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "abcabcabcabc"
// Output: true
//
// It is the substring "abc" four times or the substring "abcabc" twice.

LEETCODE_SOLUTION_UNITTEST(459, RepeatedSubstringPattern, example_3) {
  auto   solution = MakeSolution();
  string s        = "abcabcabcabc";
  bool   expect   = true;
  bool   actual   = solution->repeatedSubstringPattern(s);
  LCD_EXPECT_EQ(expect, actual);
}
