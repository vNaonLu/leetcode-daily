// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Valid Parentheses
//
// https://leetcode.com/problems/valid-parentheses/
//
// Question ID: 20
// Difficult  : Easy
// Solve Date : 2021/09/13 08:00

#include <iosfwd>
#include <stack>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |20. Valid Parentheses|:
//
// Given a string |s| containing just the characters |'('|, |')'|, |'{'|, |'}'|,
// |'['| and |']'|, determine if the input string is valid. An input string is
// valid if:
//
//  1. Open brackets must be closed by the same type of brackets.
//
//  2. Open brackets must be closed in the correct order.
//
//  3. Every close bracket has a corresponding open bracket of the same type.
//  
//

LEETCODE_BEGIN_RESOLVING(20, ValidParentheses, Solution);

class Solution {
public:
  bool isValid(string s) {
    stack<char> st;
    for (const auto &c : s) {
      if (c == ')') {
        if (st.empty() || st.top() != '(')
          return false;
        st.pop();
      } else if (c == ']') {
        if (st.empty() || st.top() != '[')
          return false;
        st.pop();
      } else if (c == '}') {
        if (st.empty() || st.top() != '{')
          return false;
        st.pop();
      } else
        st.push(c);
    }
    return st.empty();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁴|
// * |s| consists of parentheses only |'()[]{}'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "()"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(20, ValidParentheses, example_1) {
  auto   solution = MakeSolution();
  string s        = "()";
  bool   expect   = true;
  bool   actual   = solution->isValid(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "()[]{}"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(20, ValidParentheses, example_2) {
  auto   solution = MakeSolution();
  string s        = "()[]{}";
  bool   expect   = true;
  bool   actual   = solution->isValid(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "(]"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(20, ValidParentheses, example_3) {
  auto   solution = MakeSolution();
  string s        = "(]";
  bool   expect   = false;
  bool   actual   = solution->isValid(s);
  LCD_EXPECT_EQ(expect, actual);
}
