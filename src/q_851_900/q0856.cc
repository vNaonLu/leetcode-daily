#include <gtest/gtest.h>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 856.
 *      Score of Parentheses
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given a balanced parentheses string ‘s’ , return “the “score” of the
 *   string”
 *   The “score” of a balanced parentheses string is based on the following
 *       -  ‘'()'’ has score ‘1’
 *       -  ‘AB’ has score ‘A + B’ , where ‘A’ and ‘B’ are balanced
 *   parentheses
 *       -  ‘(A)’ has score ‘2 × A’ , where ‘A’ is a balanced parentheses
 *   string.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘2 ≤ s.length ≤ 50’
 *   • ‘s’ consists of only ‘'('’ and ‘')'’ .
 *   • ‘s’ is a balanced parentheses string.
 *
 */

struct q856 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    int scoreOfParentheses(string s) {
      stack<int> stk;
      stk.push(0);

      for (const auto &c : s) {
        if (c == '(') {
          stk.emplace(0);
        } else {
          int v = stk.top(); stk.pop();
          int w = stk.top(); stk.pop();
          stk.emplace(w + max(2 * v, 1));
        }
      }

      return stk.top();
    }
  };

  class Solution *solution;
};

TEST_F(q856, sample_input01) {
  solution = new Solution();
  string s = "()";
  int exp = 1;
  int act = solution->scoreOfParentheses(s);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q856, sample_input02) {
  solution = new Solution();
  string s = "(())";
  int exp = 2;
  int act = solution->scoreOfParentheses(s);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q856, sample_input03) {
  solution = new Solution();
  string s = "()()";
  int exp = 2;
  int act = solution->scoreOfParentheses(s);
  EXPECT_EQ(act, exp);
  delete solution;
}