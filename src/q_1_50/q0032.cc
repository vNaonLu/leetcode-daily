#include <gtest/gtest.h>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 32.
 *     Longest Valid Parentheses
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given a string containing just the characters ‘'('’ and ‘')'’ , find
 *   the length of the longest valid (well-formed) parentheses substring.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘0 ≤ s.length ≤ 3 × 10⁴’
 *   • ‘s[i]’ is ‘'('’ , or ‘')'’ .
 *
 */

struct q32 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    int longestValidParentheses(string s) {
      int res = 0;
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

  class Solution *solution;
};

TEST_F(q32, sample_input01) {
  solution = new Solution();
  string s = "(()";
  int exp = 2;
  EXPECT_EQ(solution->longestValidParentheses(s), exp);
  delete solution;
}

TEST_F(q32, sample_input02) {
  solution = new Solution();
  string s = ")()())";
  int exp = 4;
  EXPECT_EQ(solution->longestValidParentheses(s), exp);
  delete solution;
}

TEST_F(q32, sample_input03) {
  solution = new Solution();
  string s = "";
  int exp = 0;
  EXPECT_EQ(solution->longestValidParentheses(s), exp);
  delete solution;
}