// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Longest Balanced Substring I
//
// https://leetcode.com/problems/longest-balanced-substring-i/
//
// Question ID: 3713
// Difficult  : Medium
// Solve Date : 2026/02/12 16:04

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3713. Longest Balanced Substring I|:
//
// You are given a string |s| consisting of lowercase English letters.
// A substring of |s| is called balanced if all distinct characters in the
// substring appear the same number of times. Return the length of the longest
// balanced substring of |s|.
//
//

LEETCODE_BEGIN_RESOLVING(3713, LongestBalancedSubstringI, Solution);

class Solution {
public:
  static int longestBalanced(string &s) {
    int         cnt = 1, n = s.size();
    vector<int> freq(26);
    for (int l = 0; l < n; l++) {
      freq.clear();
      freq.resize(26, 0);
      int uniq = 0, maxF = 0, cntMax = 0;
      for (int r = l; r < n; r++) {
        int f = ++freq[s[r] - 'a'];
        uniq += (f == 1);
        const bool gr = f > maxF, eq = f == maxF, less = !(gr | eq);
        maxF            = (-gr & f) + (-!gr & maxF);
        cntMax          = (-gr & 1) + (-eq & (cntMax + 1)) + (-less & cntMax);
        const bool need = (uniq == cntMax & cnt < r - l + 1);
        cnt             = (-need & (r - l + 1)) + (-!need & cnt);
      }
    }
    return cnt;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 1000|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abbac"
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3713, LongestBalancedSubstringI, example_1) {
  auto   solution = MakeSolution();
  string s        = "abbac";
  int    expect   = 4;
  int    actual   = solution->longestBalanced(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "zzabccy"
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3713, LongestBalancedSubstringI, example_2) {
  auto   solution = MakeSolution();
  string s        = "zzabccy";
  int    expect   = 4;
  int    actual   = solution->longestBalanced(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "aba"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3713, LongestBalancedSubstringI, example_3) {
  auto   solution = MakeSolution();
  string s        = "aba";
  int    expect   = 2;
  int    actual   = solution->longestBalanced(s);
  LCD_EXPECT_EQ(expect, actual);
}
