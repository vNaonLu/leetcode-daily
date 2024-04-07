// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Valid Parenthesis String
//
// https://leetcode.com/problems/valid-parenthesis-string/
//
// Question ID: 678
// Difficult  : Medium
// Solve Date : 2024/04/08 01:08

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |678. Valid Parenthesis String|:
//
// Given a string |s| containing only three types of characters: |'('|, |')'|
// and |'*'|, return |true| if |s| is valid. The following rules define a valid
// string:
//
//  • Any left parenthesis |'('| must have a corresponding right parenthesis
//  |')'|.
//
//  • Any right parenthesis |')'| must have a corresponding left parenthesis
//  |'('|.
//
//  • Left parenthesis |'('| must go before the corresponding right parenthesis
//  |')'|.
//
//  • |'*'| could be treated as a single right parenthesis |')'| or a single
//  left parenthesis |'('| or an empty string |""|.
//
//

LEETCODE_BEGIN_RESOLVING(678, ValidParenthesisString, Solution);

class Solution {
public:
  bool checkValidString(string s) {
    int mn = 0;
    int mx = 0;
    for (auto c : s) {
      if (c == '(') {
        ++mn;
        ++mx;
      } else if (c == ')') {
        --mn;
        --mx;
      } else {
        --mn;
        ++mx;
      }
      if (mx < 0) {
        return false;
      }

      if (mn < 0) {
        mn = 0;
      }
    }
    return 0 == mn;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s[i]| is |'('|, |')'| or |'*'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "()"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(678, ValidParenthesisString, example_1) {
  auto   solution = MakeSolution();
  string s        = "()";
  bool   expect   = true;
  bool   actual   = solution->checkValidString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "(*)"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(678, ValidParenthesisString, example_2) {
  auto   solution = MakeSolution();
  string s        = "(*)";
  bool   expect   = true;
  bool   actual   = solution->checkValidString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "(*))"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(678, ValidParenthesisString, example_3) {
  auto   solution = MakeSolution();
  string s        = "(*))";
  bool   expect   = true;
  bool   actual   = solution->checkValidString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input:
//  "((((()(()()()*()(((((*)()*(**(())))))(())()())(((())())())))))))(((((())*)))()))(()((*()*(*)))(*)()"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(678, ValidParenthesisString, extra_testcase_1) {
  auto   solution = MakeSolution();
  string s = "((((()(()()()*()(((((*)()*(**(())))))(())()())(((())())())))))))("
             "((((())*)))()))(()((*()*(*)))(*)()";
  bool   expect = true;
  bool   actual = solution->checkValidString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: "************************************************************"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST_WITH_TIMED_OUT(678, ValidParenthesisString,
                                          extra_testcase_2, 4011) {
  auto   solution = MakeSolution();
  string s = "************************************************************";
  bool   expect = true;
  bool   actual = solution->checkValidString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #3]
//  Input:
//  "**************************************************))))))))))))))))))))))))))))))))))))))))))))))))))"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST_WITH_TIMED_OUT(678, ValidParenthesisString,
                                          extra_testcase_3, 4009) {
  auto   solution = MakeSolution();
  string s = "**************************************************)))))))))))))))"
             ")))))))))))))))))))))))))))))))))))";
  bool   expect = true;
  bool   actual = solution->checkValidString(s);
  LCD_EXPECT_EQ(expect, actual);
}
