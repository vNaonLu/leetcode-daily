// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove Outermost Parentheses
//
// https://leetcode.com/problems/remove-outermost-parentheses/
//
// Question ID: 1021
// Difficult  : Easy
// Solve Date : 2023/06/03 16:03

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1021. Remove Outermost Parentheses|:
//
// A valid parentheses string is either empty |""|, |"(" + A + ")"|, or |A + B|,
// where |A| and |B| are valid parentheses strings, and |+| represents string
// concatenation.
//
//  • For example, |""|, |"()"|, |"(())()"|, and |"(()(()))"| are all valid
//  parentheses strings.
// A valid parentheses string |s| is primitive if it is nonempty, and there does
// not exist a way to split it into |s = A + B|, with |A| and |B| nonempty valid
// parentheses strings. Given a valid parentheses string |s|, consider its
// primitive decomposition: |s = P₁ + P₂ + ... + Pₖ|, where |Pᵢ| are primitive
// valid parentheses strings. Return |s| after removing the outermost
// parentheses of every primitive string in the primitive decomposition of |s|.
//
//

LEETCODE_BEGIN_RESOLVING(1021, RemoveOutermostParentheses, Solution);

class Solution {
public:
  string removeOuterParentheses(string s) {
    int    left = 0;
    string res  = "";
    for (auto c : s) {
      if (c == '(') {
        if (left++ != 0) {
          res += '(';
        }
      } else {
        if (--left != 0) {
          res += ')';
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
// * |1 <= s.length <= 10⁵|
// * |s[i]| is either |'('| or |')'|.
// * |s| is a valid parentheses string.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "(()())(())"
// Output: "()()()"
//
// The input string is "(()())(())", with primitive decomposition "(()())" +
// "(())". After removing outer parentheses of each part, this is "()()" + "()"
// = "()()()".

LEETCODE_SOLUTION_UNITTEST(1021, RemoveOutermostParentheses, example_1) {
  auto   solution = MakeSolution();
  string s        = "(()())(())";
  string expect   = "()()()";
  string actual   = solution->removeOuterParentheses(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "(()())(())(()(()))"
// Output: "()()()()(())"
//
// The input string is "(()())(())(()(()))", with primitive decomposition
// "(()())" + "(())" + "(()(()))". After removing outer parentheses of each
// part, this is "()()" + "()" + "()(())" = "()()()()(())".

LEETCODE_SOLUTION_UNITTEST(1021, RemoveOutermostParentheses, example_2) {
  auto   solution = MakeSolution();
  string s        = "(()())(())(()(()))";
  string expect   = "()()()()(())";
  string actual   = solution->removeOuterParentheses(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "()()"
// Output: ""
//
// The input string is "()()", with primitive decomposition "()" + "()".
// After removing outer parentheses of each part, this is "" + "" = "".

LEETCODE_SOLUTION_UNITTEST(1021, RemoveOutermostParentheses, example_3) {
  auto   solution = MakeSolution();
  string s        = "()()";
  string expect   = "";
  string actual   = solution->removeOuterParentheses(s);
  LCD_EXPECT_EQ(expect, actual);
}
