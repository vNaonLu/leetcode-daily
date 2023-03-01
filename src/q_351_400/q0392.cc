// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Is Subsequence
//
// https://leetcode.com/problems/is-subsequence/
//
// Question ID: 392
// Difficult  : Easy
// Solve Date : 2021/10/28 14:32

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |392. Is Subsequence|:
//
// Given two strings |s| and |t|, return |true| if |s| is a subsequence of |t|,
// or |false| otherwise. A subsequence of a string is a new string that is
// formed from the original string by deleting some (can be none) of the
// characters without disturbing the relative positions of the remaining
// characters. (i.e., |"ace"| is a subsequence of |"abcde"| while |"aec"| is
// not).  
//

LEETCODE_BEGIN_RESOLVING(392, IsSubsequence, Solution);

class Solution {
public:
  bool isSubsequence(string s, string t) {
    auto sbeg = s.begin();
    auto tbeg = t.begin();
    while (tbeg != t.end() && sbeg != s.end()) {
      if (*sbeg == *tbeg++) {
        ++sbeg;
      }
    }
    return sbeg == s.end();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= s.length <= 100|
// * |0 <= t.length <= 10⁴|
// * |s| and |t| consist only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abc", t = "ahbgdc"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(392, IsSubsequence, example_1) {
  auto   solution = MakeSolution();
  string s        = "abc";
  string t        = "ahbgdc";
  bool   expect   = true;
  bool   actual   = solution->isSubsequence(s, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "axc", t = "ahbgdc"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(392, IsSubsequence, example_2) {
  auto   solution = MakeSolution();
  string s        = "axc";
  string t        = "ahbgdc";
  bool   expect   = false;
  bool   actual   = solution->isSubsequence(s, t);
  LCD_EXPECT_EQ(expect, actual);
}
