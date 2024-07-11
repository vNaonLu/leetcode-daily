// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Reverse Substrings Between Each Pair of Parentheses
//
// https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/
//
// Question ID: 1190
// Difficult  : Medium
// Solve Date : 2024/07/11 21:22

#include <algorithm>
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1190. Reverse Substrings Between Each Pair of Parentheses|:
//
// You are given a string |s| that consists of lower case English letters and
// brackets. Reverse the strings in each pair of matching parentheses, starting
// from the innermost one. Your result should not contain any brackets.
//
//

LEETCODE_BEGIN_RESOLVING(1190, ReverseSubstringsBetweenEachPairOfParentheses,
                         Solution);

class Solution {
public:
  string reverseParentheses(string s) { return helper(s.begin(), s.end()); }

private:
  string helper(auto beg, auto end) {
    string res;
    while (beg != end) {
      if (*beg != '(') {
        res.push_back(*beg++);
        continue;
      }

      int  b  = 1;
      auto it = beg + 1;
      while (it != end) {
        if (*it == '(') {
          ++b;
        } else if (*it == ')') {
          if (--b == 0) {
            break;
          }
        }
        ++it;
      }

      auto s = helper(beg + 1, it);
      reverse(s.begin(), s.end());
      res += s;

      beg = it == end ? it : (it + 1);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 2000|
// * |s| only contains lower case English characters and parentheses.
// * It is guaranteed that all parentheses are balanced.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "(abcd)"
// Output: "dcba"
//

LEETCODE_SOLUTION_UNITTEST(1190, ReverseSubstringsBetweenEachPairOfParentheses,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "(abcd)";
  string expect   = "dcba";
  string actual   = solution->reverseParentheses(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "(u(love)i)"
// Output: "iloveu"
//

LEETCODE_SOLUTION_UNITTEST(1190, ReverseSubstringsBetweenEachPairOfParentheses,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "(u(love)i)";
  string expect   = "iloveu";
  string actual   = solution->reverseParentheses(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "(ed(et(oc))el)"
// Output: "leetcode"
//

LEETCODE_SOLUTION_UNITTEST(1190, ReverseSubstringsBetweenEachPairOfParentheses,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "(ed(et(oc))el)";
  string expect   = "leetcode";
  string actual   = solution->reverseParentheses(s);
  LCD_EXPECT_EQ(expect, actual);
}
