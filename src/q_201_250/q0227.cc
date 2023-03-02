// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Basic Calculator II
//
// https://leetcode.com/problems/basic-calculator-ii/
//
// Question ID: 227
// Difficult  : Medium
// Solve Date : 2021/12/25 20:42

#include <iosfwd>
#include <stack>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |227. Basic Calculator II|:
//
// Given a string |s| which represents an expression, evaluate this expression
// and return its value.  The integer division should truncate toward zero. You
// may assume that the given expression is always valid. All intermediate
// results will be in the range of |[-2³¹, 2³¹ - 1]|. Note: You are not allowed
// to use any built-in function which evaluates strings as mathematical
// expressions, such as |eval()|.  
//

LEETCODE_BEGIN_RESOLVING(227, BasicCalculatorII, Solution);

class Solution {
public:
  int calculate(string s) {
    int        res = 0;
    stack<int> nums;
    char       prev_op = '+';
    int        cur     = 0;
    for (int i = 0; i < s.size(); ++i) {
      char &c = s[i];
      if (isdigit(c))
        cur = cur * 10 + (c - '0');

      if ((!isdigit(c) && !iswspace(c)) || (i == s.size() - 1)) {
        switch (prev_op) {
        case '+':
          nums.emplace(cur);
          break;
        case '-':
          nums.emplace(cur * -1);
          break;
        case '*':
          cur *= nums.top();
          nums.pop();
          nums.emplace(cur);
          break;
        case '/':
          cur = nums.top() / cur;
          nums.pop();
          nums.emplace(cur);
          break;
        default:
          break;
        }
        prev_op = c;
        cur     = 0;
      }
    }
    while (!nums.empty()) {
      res += nums.top();
      nums.pop();
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 3 * 10⁵|
// * |s| consists of integers and operators |('+', '-', '*', '/')| separated by
// some number of spaces.
// * |s| represents a valid expression.
// * All the integers in the expression are non-negative integers in the range
// |[0, 2³¹ - 1]|.
// * The answer is guaranteed to fit in a 32-bit integer.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "3+2*2"
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(227, BasicCalculatorII, example_1) {
  auto   solution = MakeSolution();
  string s        = "3+2*2";
  int    expect   = 7;
  int    actual   = solution->calculate(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = " 3/2 "
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(227, BasicCalculatorII, example_2) {
  auto   solution = MakeSolution();
  string s        = " 3/2 ";
  int    expect   = 1;
  int    actual   = solution->calculate(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = " 3+5 / 2 "
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(227, BasicCalculatorII, example_3) {
  auto   solution = MakeSolution();
  string s        = " 3+5 / 2 ";
  int    expect   = 5;
  int    actual   = solution->calculate(s);
  LCD_EXPECT_EQ(expect, actual);
}
