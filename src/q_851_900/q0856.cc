// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Score of Parentheses
//
// https://leetcode.com/problems/score-of-parentheses/
//
// Question ID: 856
// Difficult  : Medium
// Solve Date : 2022/03/17 18:08

#include <iosfwd>
#include <stack>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |856. Score of Parentheses|:
//
// Given a balanced parentheses string |s|, return the score of the string.
// The score of a balanced parentheses string is based on the following rule:
//
//  • |"()"| has score |1|.
//
//  • |AB| has score |A + B|, where |A| and |B| are balanced parentheses
//  strings.
//
//  • |(A)| has score |2 * A|, where |A| is a balanced parentheses string.
//  
//

LEETCODE_BEGIN_RESOLVING(856, ScoreOfParentheses, Solution);

class Solution {
public:
  int scoreOfParentheses(string s) {
    stack<int> stk;
    stk.push(0);

    for (const auto &c : s) {
      if (c == '(') {
        stk.emplace(0);
      } else {
        int v = stk.top();
        stk.pop();
        int w = stk.top();
        stk.pop();
        stk.emplace(w + max(2 * v, 1));
      }
    }

    return stk.top();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= s.length <= 50|
// * |s| consists of only |'('| and |')'|.
// * |s| is a balanced parentheses string.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "()"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(856, ScoreOfParentheses, example_1) {
  auto   solution = MakeSolution();
  string s        = "()";
  int    expect   = 1;
  int    actual   = solution->scoreOfParentheses(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "(())"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(856, ScoreOfParentheses, example_2) {
  auto   solution = MakeSolution();
  string s        = "(())";
  int    expect   = 2;
  int    actual   = solution->scoreOfParentheses(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "()()"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(856, ScoreOfParentheses, example_3) {
  auto   solution = MakeSolution();
  string s        = "()()";
  int    expect   = 2;
  int    actual   = solution->scoreOfParentheses(s);
  LCD_EXPECT_EQ(expect, actual);
}
