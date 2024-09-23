// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Add to Make Parentheses Valid
//
// https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/
//
// Question ID: 921
// Difficult  : Medium
// Solve Date : 2024/09/24 00:50

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |921. Minimum Add to Make Parentheses Valid|:
//
// A parentheses string is valid if and only if:
//
//  • It is the empty string,
//
//  • It can be written as |AB| ( |A| concatenated with |B|), where |A| and |B|
//  are valid strings, or
//
//  • It can be written as |(A)|, where |A| is a valid string.
// You are given a parentheses string |s|. In one move, you can insert a
// parenthesis at any position of the string.
//
//  • For example, if |s = "()))"|, you can insert an opening parenthesis to be
//  |"(()))"| or a closing parenthesis to be |"())))"|.
// Return the minimum number of moves required to make |s| valid.
//
//

LEETCODE_BEGIN_RESOLVING(921, MinimumAddToMakeParenthesesValid, Solution);

class Solution {
public:
  int minAddToMakeValid(string s) {
    int res = 0;
    int loc = 0;
    for (auto c : s) {
      if (c == '(') {
        ++loc;
      } else {
        --loc;
      }

      if (loc < 0) {
        res += abs(loc);
        loc = 0;
      }
    }

    res += loc;
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 1000|
// * |s[i]| is either |'('| or |')'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "())"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(921, MinimumAddToMakeParenthesesValid, example_1) {
  auto   solution = MakeSolution();
  string s        = "())";
  int    expect   = 1;
  int    actual   = solution->minAddToMakeValid(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "((("
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(921, MinimumAddToMakeParenthesesValid, example_2) {
  auto   solution = MakeSolution();
  string s        = "(((";
  int    expect   = 3;
  int    actual   = solution->minAddToMakeValid(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "()))(("
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(921, MinimumAddToMakeParenthesesValid,
                           extra_testcase_1) {
  auto   solution = MakeSolution();
  string s        = "()))((";
  int    expect   = 4;
  int    actual   = solution->minAddToMakeValid(s);
  LCD_EXPECT_EQ(expect, actual);
}
