// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Uncommon Subsequence I
//
// https://leetcode.com/problems/longest-uncommon-subsequence-i/
//
// Question ID: 521
// Difficult  : Easy
// Solve Date : 2023/07/03 21:27

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |521. Longest Uncommon Subsequence I|:
//
// Given two strings |a| and |b|, return the length of the longest uncommon
// subsequence between |a| and |b|. If the longest uncommon subsequence does not
// exist, return |-1|. An uncommon subsequence between two strings is a string
// that is a subsequence of one but not the other. A subsequence of a string |s|
// is a string that can be obtained after deleting any number of characters from
// |s|.
//
//  • For example, |"abc"| is a subsequence of |"aebdc"| because you can delete
//  the underlined characters in |"aebdc"| to get |"abc"|. Other subsequences of
//  |"aebdc"| include |"aebdc"|, |"aeb"|, and |""| (empty string).
//
//

LEETCODE_BEGIN_RESOLVING(521, LongestUncommonSubsequenceI, Solution);

class Solution {
public:
  int findLUSlength(string a, string b) {
    return a == b ? -1 : (a.size() > b.size() ? a.size() : b.size());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= a.length, b.length <= 100|
// * |a| and |b| consist of lower-case English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: a = "aba", b = "cdc"
// Output: 3
//
// One longest uncommon subsequence is "aba" because "aba" is a subsequence of
// "aba" but not "cdc". Note that "cdc" is also a longest uncommon subsequence.

LEETCODE_SOLUTION_UNITTEST(521, LongestUncommonSubsequenceI, example_1) {
  auto   solution = MakeSolution();
  string a        = "aba";
  string b        = "cdc";
  int    expect   = 3;
  int    actual   = solution->findLUSlength(a, b);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: a = "aaa", b = "bbb"
// Output: 3
//
//  The longest uncommon subsequences are "aaa" and "bbb".

LEETCODE_SOLUTION_UNITTEST(521, LongestUncommonSubsequenceI, example_2) {
  auto   solution = MakeSolution();
  string a        = "aaa";
  string b        = "bbb";
  int    expect   = 3;
  int    actual   = solution->findLUSlength(a, b);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: a = "aaa", b = "aaa"
// Output: -1
//
//  Every subsequence of string a is also a subsequence of string b. Similarly,
//  every subsequence of string b is also a subsequence of string a.

LEETCODE_SOLUTION_UNITTEST(521, LongestUncommonSubsequenceI, example_3) {
  auto   solution = MakeSolution();
  string a        = "aaa";
  string b        = "aaa";
  int    expect   = -1;
  int    actual   = solution->findLUSlength(a, b);
  LCD_EXPECT_EQ(expect, actual);
}
