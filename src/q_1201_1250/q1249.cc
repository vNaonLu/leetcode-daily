// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Remove to Make Valid Parentheses
//
// https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/
//
// Question ID: 1249
// Difficult  : Medium
// Solve Date : 2021/10/02 14:42

#include <iosfwd>
#include <set>
#include <stack>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1249. Minimum Remove to Make Valid Parentheses|:
//
// Given a string s of |'('| , |')'| and lowercase English characters.
// Your task is to remove the minimum number of parentheses ( |'('| or |')'|, in
// any positions ) so that the resulting parentheses string is valid and return
// any valid string. Formally, a parentheses string is valid if and only if:
//
//  • It is the empty string, contains only lowercase characters, or
//
//  • It can be written as |AB| ( |A| concatenated with |B|), where |A| and |B|
//  are valid strings, or
//
//  • It can be written as |(A)|, where |A| is a valid string.
//  
//

LEETCODE_BEGIN_RESOLVING(1249, MinimumRemoveToMakeValidParentheses, Solution);

class Solution {
public:
  string minRemoveToMakeValid(string s) {
    string     res;
    stack<int> left_parentheses;
    set<int>   removes;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == '(') {
        left_parentheses.push(i);
      } else if (s[i] == ')') {
        if (left_parentheses.empty()) {
          removes.insert(i);
        } else {
          left_parentheses.pop();
        }
      }
    }
    while (!left_parentheses.empty()) {
      removes.insert(left_parentheses.top());
      left_parentheses.pop();
    }
    for (int i = 0; i < s.size(); ++i) {
      if (removes.count(i))
        continue;
      res.push_back(s[i]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s[i]| is either |'('| , |')'|, or lowercase English letter |.|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "lee(t(c)o)de)"
// Output: "lee(t(c)o)de"
//
// "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.

LEETCODE_SOLUTION_UNITTEST(1249, MinimumRemoveToMakeValidParentheses,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "lee(t(c)o)de)";
  string expect   = "lee(t(c)o)de";
  string actual   = solution->minRemoveToMakeValid(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "a)b(c)d"
// Output: "ab(c)d"
//

LEETCODE_SOLUTION_UNITTEST(1249, MinimumRemoveToMakeValidParentheses,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "a)b(c)d";
  string expect   = "ab(c)d";
  string actual   = solution->minRemoveToMakeValid(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "))(("
// Output: ""
//
// An empty string is also valid.

LEETCODE_SOLUTION_UNITTEST(1249, MinimumRemoveToMakeValidParentheses,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "))((";
  string expect   = "";
  string actual   = solution->minRemoveToMakeValid(s);
  LCD_EXPECT_EQ(expect, actual);
}
