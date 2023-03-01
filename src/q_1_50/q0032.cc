// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Valid Parentheses
//
// https://leetcode.com/problems/longest-valid-parentheses/
//
// Question ID: 32
// Difficult  : Hard
// Solve Date : 2021/12/01 22:00

#include <iosfwd>
#include <stack>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |32. Longest Valid Parentheses|:
//
// Given a string containing just the characters |'('| and |')'|, return the
// length of the longest valid (well-formed) parentheses substring.  
//

LEETCODE_BEGIN_RESOLVING(32, LongestValidParentheses, Solution);

class Solution {
public:
  int longestValidParentheses(string s) {
    int        res = 0;
    stack<int> stk;
    stk.emplace(-1);
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == '(') {
        stk.emplace(i);
      } else {
        stk.pop();
        if (stk.empty()) {
          stk.emplace(i);
        } else {
          res = max(res, i - stk.top());
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= s.length <= 3 * 10⁴|
// * |s[i]| is |'('|, or |')'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "(()"
// Output: 2
//
// The longest valid parentheses substring is "()".

LEETCODE_SOLUTION_UNITTEST(32, LongestValidParentheses, example_1) {
  auto   solution = MakeSolution();
  string s        = "(()";
  int    expect   = 2;
  int    actual   = solution->longestValidParentheses(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = ")()())"
// Output: 4
//
// The longest valid parentheses substring is "()()".

LEETCODE_SOLUTION_UNITTEST(32, LongestValidParentheses, example_2) {
  auto   solution = MakeSolution();
  string s        = ")()())";
  int    expect   = 4;
  int    actual   = solution->longestValidParentheses(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = ""
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(32, LongestValidParentheses, example_3) {
  auto   solution = MakeSolution();
  string s        = "";
  int    expect   = 0;
  int    actual   = solution->longestValidParentheses(s);
  LCD_EXPECT_EQ(expect, actual);
}
