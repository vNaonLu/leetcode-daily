// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Longest Balanced Substring of a Binary String
//
// https://leetcode.com/problems/find-the-longest-balanced-substring-of-a-binary-string/
//
// Question ID: 2609
// Difficult  : Easy
// Solve Date : 2023/12/07 19:39

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2609. Find the Longest Balanced Substring of a Binary
// String|:
//
// You are given a binary string |s| consisting only of zeroes and ones.
// A substring of |s| is considered balanced if all zeroes are before ones and
// the number of zeroes is equal to the number of ones inside the substring.
// Notice that the empty substring is considered a balanced substring. Return
// the length of the longest balanced substring of |s|. A substring is a
// contiguous sequence of characters within a string.
//
//

LEETCODE_BEGIN_RESOLVING(2609, FindTheLongestBalancedSubstringOfABinaryString,
                         Solution);

class Solution {
public:
  int findTheLongestBalancedSubstring(string s) {
    int  res = 0;
    auto beg = s.begin();
    while (beg != s.end()) {
      if (*beg != '0') {
        ++beg;
        continue;
      }

      auto it = beg;
      while (it != s.end() && *it != '1') {
        ++it;
      }
      int zeros = distance(beg, it);

      if (it == s.end()) {
        break;
      }

      beg = it;
      while (it != s.end() && *it != '0') {
        ++it;
      }

      int ones = distance(beg, it);
      res      = max(res, min(zeros, ones) * 2);
      beg      = it;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 50|
// * |'0' <= s[i] <= '1'|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "01000111"
// Output: 6
//
// The longest balanced substring is "000111", which has length 6.

LEETCODE_SOLUTION_UNITTEST(2609, FindTheLongestBalancedSubstringOfABinaryString,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "01000111";
  int    expect   = 6;
  int    actual   = solution->findTheLongestBalancedSubstring(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "00111"
// Output: 4
//
// The longest balanced substring is "0011", which has length 4.

LEETCODE_SOLUTION_UNITTEST(2609, FindTheLongestBalancedSubstringOfABinaryString,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "00111";
  int    expect   = 4;
  int    actual   = solution->findTheLongestBalancedSubstring(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "111"
// Output: 0
//
// There is no balanced substring except the empty substring, so the answer is
// 0.

LEETCODE_SOLUTION_UNITTEST(2609, FindTheLongestBalancedSubstringOfABinaryString,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "111";
  int    expect   = 0;
  int    actual   = solution->findTheLongestBalancedSubstring(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "0"
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2609, FindTheLongestBalancedSubstringOfABinaryString,
                           extra_testcase_1) {
  auto   solution = MakeSolution();
  string s        = "0";
  int    expect   = 0;
  int    actual   = solution->findTheLongestBalancedSubstring(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: "001101"
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2609, FindTheLongestBalancedSubstringOfABinaryString,
                           extra_testcase_2) {
  auto   solution = MakeSolution();
  string s        = "001101";
  int    expect   = 4;
  int    actual   = solution->findTheLongestBalancedSubstring(s);
  LCD_EXPECT_EQ(expect, actual);
}
