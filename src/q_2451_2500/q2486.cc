// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Append Characters to String to Make Subsequence
//
// https://leetcode.com/problems/append-characters-to-string-to-make-subsequence/
//
// Question ID: 2486
// Difficult  : Medium
// Solve Date : 2024/06/03 19:07

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2486. Append Characters to String to Make Subsequence|:
//
// You are given two strings |s| and |t| consisting of only lowercase English
// letters. Return the minimum number of characters that need to be appended to
// the end of |s| so that |t| becomes a subsequence of |s|. A subsequence is a
// string that can be derived from another string by deleting some or no
// characters without changing the order of the remaining characters.
//
//

LEETCODE_BEGIN_RESOLVING(2486, AppendCharactersToStringToMakeSubsequence,
                         Solution);

class Solution {
public:
  int appendCharacters(string s, string t) {
    int m = s.size();
    int n = t.size();
    int i = 0;
    int j = 0;
    while (i < m && j < n) {
      if (s[i] == t[j]) {
        ++j;
      }
      ++i;
    }
    return n - j;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length, t.length <= 10⁵|
// * |s| and |t| consist only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "coaching", t = "coding"
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2486, AppendCharactersToStringToMakeSubsequence,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "coaching";
  string t        = "coding";
  int    expect   = 4;
  int    actual   = solution->appendCharacters(s, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcde", t = "a"
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2486, AppendCharactersToStringToMakeSubsequence,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "abcde";
  string t        = "a";
  int    expect   = 0;
  int    actual   = solution->appendCharacters(s, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "z", t = "abcde"
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(2486, AppendCharactersToStringToMakeSubsequence,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "z";
  string t        = "abcde";
  int    expect   = 5;
  int    actual   = solution->appendCharacters(s, t);
  LCD_EXPECT_EQ(expect, actual);
}
