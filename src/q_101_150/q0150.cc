// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Evaluate Reverse Polish Notation
//
// https://leetcode.com/problems/evaluate-reverse-polish-notation/
//
// Question ID: 150
// Difficult  : Medium
// Solve Date : 2022/04/28 18:15

#include <iosfwd>
#include <stack>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |150. Evaluate Reverse Polish Notation|:
//
// You are given an array of strings |tokens| that represents an arithmetic
// expression in a [Reverse Polish Notation]. Evaluate the expression. Return an
// integer that represents the value of the expression. Note that:
//
//  • The valid operators are |'+'|, |'-'|, |'*'|, and |'/'|.
//
//  • Each operand may be an integer or another expression.
//
//  • The division between two integers always truncates toward zero.
//
//  • There will not be any division by zero.
//
//  • The input represents a valid arithmetic expression in a reverse polish
//  notation.
//
//  • The answer and all the intermediate calculations can be represented in a
//  32-bit integer.
//  
//

LEETCODE_BEGIN_RESOLVING(150, EvaluateReversePolishNotation, Solution);

class Solution {
private:
  pair<int, int> get_twice(stack<int> &s) {
    assert(s.size() >= 2);
    pair<int, int> x;
    x.second = s.top();
    s.pop();
    x.first = s.top();
    s.pop();
    return x;
  }

public:
  int evalRPN(vector<string> &tokens) {
    stack<int> nums;

    for (auto &x : tokens) {
      if (x.size() == 1) {
        if (x[0] == '+') {
          auto [x, y] = get_twice(nums);
          nums.emplace(x + y);
          continue;
        } else if (x[0] == '-') {
          auto [x, y] = get_twice(nums);
          nums.emplace(x - y);
          continue;
        } else if (x[0] == '*') {
          auto [x, y] = get_twice(nums);
          nums.emplace(x * y);
          continue;
        } else if (x[0] == '/') {
          auto [x, y] = get_twice(nums);
          nums.emplace(x / y);
          continue;
        }
      }

      nums.emplace(stoi(x));
    }

    return nums.top();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= tokens.length <= 10⁴|
// * |tokens[i]| is either an operator: |"+"|, |"-"|, |"*"|, or |"/"|, or an
// integer in the range |[-200, 200]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: tokens = ["2","1","+","3","*"]
// Output: 9
//
// ((2 + 1) * 3) = 9

LEETCODE_SOLUTION_UNITTEST(150, EvaluateReversePolishNotation, example_1) {
  auto           solution = MakeSolution();
  vector<string> tokens   = {"2", "1", "+", "3", "*"};
  int            expect   = 9;
  int            actual   = solution->evalRPN(tokens);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: tokens = ["4","13","5","/","+"]
// Output: 6
//
// (4 + (13 / 5)) = 6

LEETCODE_SOLUTION_UNITTEST(150, EvaluateReversePolishNotation, example_2) {
  auto           solution = MakeSolution();
  vector<string> tokens   = {"4", "13", "5", "/", "+"};
  int            expect   = 6;
  int            actual   = solution->evalRPN(tokens);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
// Output: 22
//
// ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
// = ((10 * (6 / (12 * -11))) + 17) + 5
// = ((10 * (6 / -132)) + 17) + 5
// = ((10 * 0) + 17) + 5
// = (0 + 17) + 5
// = 17 + 5
// = 22

LEETCODE_SOLUTION_UNITTEST(150, EvaluateReversePolishNotation, example_3) {
  auto           solution = MakeSolution();
  vector<string> tokens   = {"10", "6", "9",  "3", "+", "-11", "*",
                             "/",  "*", "17", "+", "5", "+"};
  int            expect   = 22;
  int            actual   = solution->evalRPN(tokens);
  LCD_EXPECT_EQ(expect, actual);
}
