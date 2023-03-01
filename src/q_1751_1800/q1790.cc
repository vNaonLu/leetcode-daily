// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check if One String Swap Can Make Strings Equal
//
// https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/
//
// Question ID: 1790
// Difficult  : Easy
// Solve Date : 2022/04/17 12:45

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1790. Check if One String Swap Can Make Strings Equal|:
//
// You are given two strings |s1| and |s2| of equal length. A string swap is an
// operation where you choose two indices in a string (not necessarily
// different) and swap the characters at these indices. Return |true| if it is
// possible to make both strings equal by performing at most one string swap on
// exactly one of the strings. Otherwise, return |false|.  
//

LEETCODE_BEGIN_RESOLVING(1790, CheckIfOneStringSwapCanMakeStringsEqual,
                         Solution);

class Solution {
public:
  bool areAlmostEqual(string s1, string s2) {
    vector<int> diff_pos;
    int         pos = 0;
    auto        s1b = s1.begin(), s2b = s2.begin();
    while (s1b != s1.end() && s2b != s2.end() && diff_pos.size() <= 2) {
      if (*(s1b++) != *(s2b++)) {
        diff_pos.emplace_back(pos);
      }
      ++pos;
    }

    if (diff_pos.empty()) {

      return true;
    } else if (diff_pos.size() == 2 && s1[diff_pos[0]] == s2[diff_pos[1]] &&
               s1[diff_pos[1]] == s2[diff_pos[0]]) {

      return true;
    }

    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s1.length, s2.length <= 100|
// * |s1.length == s2.length|
// * |s1| and |s2| consist of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s1 = "bank", s2 = "kanb"
// Output: true
//
// For example, swap the first character with the last character of s2 to make
// "bank".

LEETCODE_SOLUTION_UNITTEST(1790, CheckIfOneStringSwapCanMakeStringsEqual,
                           example_1) {
  auto   solution = MakeSolution();
  string s1       = "bank";
  string s2       = "kanb";
  bool   expect   = true;
  bool   actual   = solution->areAlmostEqual(s1, s2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s1 = "attack", s2 = "defend"
// Output: false
//
// It is impossible to make them equal with one string swap.

LEETCODE_SOLUTION_UNITTEST(1790, CheckIfOneStringSwapCanMakeStringsEqual,
                           example_2) {
  auto   solution = MakeSolution();
  string s1       = "attack";
  string s2       = "defend";
  bool   expect   = false;
  bool   actual   = solution->areAlmostEqual(s1, s2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s1 = "kelb", s2 = "kelb"
// Output: true
//
// The two strings are already equal, so no string swap operation is required.

LEETCODE_SOLUTION_UNITTEST(1790, CheckIfOneStringSwapCanMakeStringsEqual,
                           example_3) {
  auto   solution = MakeSolution();
  string s1       = "kelb";
  string s2       = "kelb";
  bool   expect   = true;
  bool   actual   = solution->areAlmostEqual(s1, s2);
  LCD_EXPECT_EQ(expect, actual);
}
