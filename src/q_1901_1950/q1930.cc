// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Unique Length-3 Palindromic Subsequences
//
// https://leetcode.com/problems/unique-length-3-palindromic-subsequences/
//
// Question ID: 1930
// Difficult  : Medium
// Solve Date : 2023/11/15 19:00

#include <iosfwd>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1930. Unique Length-3 Palindromic Subsequences|:
//
// Given a string |s|, return the number of unique palindromes of length three
// that are a subsequence of |s|. Note that even if there are multiple ways to
// obtain the same subsequence, it is still only counted once. A palindrome is a
// string that reads the same forwards and backwards. A subsequence of a string
// is a new string generated from the original string with some characters (can
// be none) deleted without changing the relative order of the remaining
// characters.
//
//  • For example, |"ace"| is a subsequence of |"abcde"|.
//
//

LEETCODE_BEGIN_RESOLVING(1930, UniqueLength3PalindromicSubsequences, Solution);

class Solution {
public:
  int countPalindromicSubsequence(string s) {
    int         res = 0;
    vector<int> f(26, numeric_limits<int>::max());
    vector<int> l(26, 0);
    for (int i = 0; i < s.size(); ++i) {
      f[s[i] - 'a'] = min(f[s[i] - 'a'], i);
      l[s[i] - 'a'] = i;
    }
    for (int i = 0; i < 26; ++i) {
      if (f[i] < l[i]) {
        res +=
            unordered_set<char>(s.begin() + f[i] + 1, s.begin() + l[i]).size();
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= s.length <= 10⁵|
// * |s| consists of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aabca"
// Output: 3
//
// The 3 palindromic subsequences of length 3 are:
// - "aba" (subsequence of "aabca")
// - "aaa" (subsequence of "aabca")
// - "aca" (subsequence of "aabca")

LEETCODE_SOLUTION_UNITTEST(1930, UniqueLength3PalindromicSubsequences,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "aabca";
  int    expect   = 3;
  int    actual   = solution->countPalindromicSubsequence(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "adc"
// Output: 0
//
// There are no palindromic subsequences of length 3 in "adc".

LEETCODE_SOLUTION_UNITTEST(1930, UniqueLength3PalindromicSubsequences,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "adc";
  int    expect   = 0;
  int    actual   = solution->countPalindromicSubsequence(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "bbcbaba"
// Output: 4
//
// The 4 palindromic subsequences of length 3 are:
// - "bbb" (subsequence of "bbcbaba")
// - "bcb" (subsequence of "bbcbaba")
// - "bab" (subsequence of "bbcbaba")
// - "aba" (subsequence of "bbcbaba")

LEETCODE_SOLUTION_UNITTEST(1930, UniqueLength3PalindromicSubsequences,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "bbcbaba";
  int    expect   = 4;
  int    actual   = solution->countPalindromicSubsequence(s);
  LCD_EXPECT_EQ(expect, actual);
}
