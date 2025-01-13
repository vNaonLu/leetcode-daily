// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Check if a Parentheses String Can Be Valid
//
// https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/
//
// Question ID: 2116
// Difficult  : Medium
// Solve Date : 2025/01/12 16:29

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2116. Check if a Parentheses String Can Be Valid|:
//
// A parentheses string is a non-empty string consisting only of |'('| and
// |')'|. It is valid if any of the following conditions is true:
//
//  • It is |()|.
//
//  • It can be written as |AB| ( |A| concatenated with |B|), where |A| and |B|
//  are valid parentheses strings.
//
//  • It can be written as |(A)|, where |A| is a valid parentheses string.
// You are given a parentheses string |s| and a string |locked|, both of length
// |n|. |locked| is a binary string consisting only of |'0'|s and |'1'|s. For
// each index |i| of |locked|,
//
//  • If |locked[i]| is |'1'|, you cannot change |s[i]|.
//
//  • But if |locked[i]| is |'0'|, you can change |s[i]| to either |'('| or
//  |')'|.
// Return |true| if you can make |s| a valid parentheses string. Otherwise,
// return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(2116, CheckIfAParenthesesStringCanBeValid, Solution);

class Solution {
public:
  bool canBeValid(string s, string locked) {
    int n = s.size();
    if (n & 1) {
      return false;
    }

    int mn = 0;
    int mx = 0;
    for (int i = 0; i < n; ++i) {
      auto c    = s[i];
      auto op   = c == '(';
      auto wild = locked[i] == '0';
      if (!op || wild) {
        --mn;
      } else {
        ++mn;
      }

      if (op || wild) {
        ++mx;
      } else {
        --mx;
      }

      if (mx < 0) {
        return false;
      }

      mn = max(mn, 0);
    }
    return mn == 0;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == s.length == locked.length|
// * |1 <= n <= 10⁵|
// * |s[i]| is either |'('| or |')'|.
// * |locked[i]| is either |'0'| or |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "))()))", locked = "010100"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(2116, CheckIfAParenthesesStringCanBeValid,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "))()))";
  string locked   = "010100";
  bool   expect   = true;
  bool   actual   = solution->canBeValid(s, locked);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "()()", locked = "0000"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(2116, CheckIfAParenthesesStringCanBeValid,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "()()";
  string locked   = "0000";
  bool   expect   = true;
  bool   actual   = solution->canBeValid(s, locked);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = ")", locked = "0"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(2116, CheckIfAParenthesesStringCanBeValid,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = ")";
  string locked   = "0";
  bool   expect   = false;
  bool   actual   = solution->canBeValid(s, locked);
  LCD_EXPECT_EQ(expect, actual);
}
