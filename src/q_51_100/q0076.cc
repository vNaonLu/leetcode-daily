// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Window Substring
//
// https://leetcode.com/problems/minimum-window-substring/
//
// Question ID: 76
// Difficult  : Hard
// Solve Date : 2022/08/29 22:17

#include <array>
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |76. Minimum Window Substring|:
//
// Given two strings |s| and |t| of lengths |m| and |n| respectively, return the
// minimum window substring of |s| such that every character in |t| (including
// duplicates) is included in the window. If there is no such substring, return
// the empty string |""|. The testcases will be generated such that the answer
// is unique.
//

LEETCODE_BEGIN_RESOLVING(76, MinimumWindowSubstring, Solution);

class Solution {
private:
  template <typename Iterator>
  array<int, 128> count(Iterator beg, Iterator end) {
    auto res = array<int, 128>();
    while (beg != end) {
      ++res[*beg++];
    }
    return res;
  }

public:
  string minWindow(string s, string t) {
    auto sv     = string_view(s);
    auto target = count(t.begin(), t.end());
    auto left   = s.begin();
    auto beg    = s.begin();
    auto res    = string_view(""); /// be aware of the unmatched condition
    auto curr   = (int)0;
    while (beg != s.end()) {
      if (--target[*beg] >= 0) {
        ++curr;
      }

      while (curr == t.size()) {
        if (res.size() > distance(left, beg) + 1 || res.empty()) {
          res = string_view(&(*left), distance(left, beg) + 1);
        }
        if (++target[*left++] > 0) {
          --curr;
        }
      }
      ++beg;
    }
    return string(res.begin(), res.end());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == s.length|
// * |n == t.length|
// * |1 <= m, n <= 10⁵|
// * |s| and |t| consist of uppercase and lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "ADOBECODEBANC", t = "ABC"
// Output: "BANC"
//
// The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

LEETCODE_SOLUTION_UNITTEST(76, MinimumWindowSubstring, example_1) {
  auto   solution = MakeSolution();
  string s        = "ADOBECODEBANC";
  string t        = "ABC";
  string expect   = "BANC";
  string actual   = solution->minWindow(s, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "a", t = "a"
// Output: "a"
//
// The entire string s is the minimum window.

LEETCODE_SOLUTION_UNITTEST(76, MinimumWindowSubstring, example_2) {
  auto   solution = MakeSolution();
  string s        = "a";
  string t        = "a";
  string expect   = "a";
  string actual   = solution->minWindow(s, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "a", t = "aa"
// Output: ""
//
// Both 'a's from t must be included in the window.
// Since the largest window of s only has one 'a', return empty string.

LEETCODE_SOLUTION_UNITTEST(76, MinimumWindowSubstring, example_3) {
  auto   solution = MakeSolution();
  string s        = "a";
  string t        = "aa";
  string expect   = "";
  string actual   = solution->minWindow(s, t);
  LCD_EXPECT_EQ(expect, actual);
}
