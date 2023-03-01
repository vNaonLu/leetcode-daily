// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Basic Calculator
//
// https://leetcode.com/problems/basic-calculator/
//
// Question ID: 224
// Difficult  : Hard
// Solve Date : 2021/09/11 08:00

#include <iosfwd>
#include <stack>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |224. Basic Calculator|:
//
// Given a string |s| representing a valid expression, implement a basic
// calculator to evaluate it, and return the result of the evaluation. Note: You
// are not allowed to use any built-in function which evaluates strings as
// mathematical expressions, such as |eval()|.  
//

LEETCODE_BEGIN_RESOLVING(224, BasicCalculator, Solution);

class Solution {
public:
  int calculate(string s) {
    int        res = 0, val = 0;
    int        sign = 1;
    stack<int> cal;
    for (int i = 0; i < s.size(); ++i) {
      while (i < s.size() && isdigit(s[i])) {
        val = val * 10 + (s[i] - '0');
        ++i;
      }
      res += val * sign;
      val = 0;
      if (s[i] == '+') {
        sign = 1;
      } else if (s[i] == '-') {
        sign = -1;
      } else if (s[i] == '(') {
        cal.push(res);
        cal.push(sign);
        res  = 0;
        sign = 1;
      } else if (s[i] == ')') {
        res *= cal.top();
        cal.pop();
        res += cal.top();
        cal.pop();
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 3 * 10⁵|
// * |s| consists of digits, |'+'|, |'-'|, |'('|, |')'|, and |' '|.
// * |s| represents a valid expression.
// * |'+'| is not used as a unary operation (i.e., |"+1"| and |"+(2 + 3)"| is
// invalid).
// * |'-'| could be used as a unary operation (i.e., |"-1"| and |"-(2 + 3)"| is
// valid).
// * There will be no two consecutive operators in the input.
// * Every number and running calculation will fit in a signed 32-bit integer.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "1 + 1"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(224, BasicCalculator, example_1) {
  auto   solution = MakeSolution();
  string s        = "1 + 1";
  int    expect   = 2;
  int    actual   = solution->calculate(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = " 2-1 + 2 "
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(224, BasicCalculator, example_2) {
  auto   solution = MakeSolution();
  string s        = " 2-1 + 2 ";
  int    expect   = 3;
  int    actual   = solution->calculate(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "(1+(4+5+2)-3)+(6+8)"
// Output: 23
//

LEETCODE_SOLUTION_UNITTEST(224, BasicCalculator, example_3) {
  auto   solution = MakeSolution();
  string s        = "(1+(4+5+2)-3)+(6+8)";
  int    expect   = 23;
  int    actual   = solution->calculate(s);
  LCD_EXPECT_EQ(expect, actual);
}
