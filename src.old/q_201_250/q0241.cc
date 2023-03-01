#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/anyorder.hpp>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 241.
 *      Different Ways to Add Parentheses
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given a string ‘expression’ of numbers and operators, return “all
 *   possible results from computing all the different possible ways to
 *   group numbers and operators” . You may return the answer in “any
 *   order”
 *   The test cases are generated such that the output values fit in a
 *   32-bit integer and the number of different results does not exceed
 *   ‘10⁴’ .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ expression.length ≤ 20’
 *   • ‘expression’ consists of digits and the operator ‘'+'’ , ‘'-'’ , and
 * ‘'×'’ . • All the integer values in the input expression are in the range
 * ‘[0, 99]’ .
 *
 */

struct q241 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  private:
    vector<int> helper(string exp, unordered_map<string, vector<int>> &dp) {
      auto res = vector<int>();
      auto n   = exp.size();
      for (int i = 0; i < n; ++i) {
        auto c = exp[i];
        if (c == '+' || c == '-' || c == '*') {
          auto sub1 = exp.substr(0, i);
          auto sub2 = exp.substr(i + 1);
          auto res1 = vector<int>();
          auto res2 = vector<int>();

          auto f = dp.find(sub1);
          if (f != dp.end()) {
            res1 = f->second;
          } else {
            res1 = helper(sub1, dp);
          }

          f = dp.find(sub2);
          if (f != dp.end()) {
            res2 = f->second;
          } else {
            res2 = helper(sub2, dp);
          }

          for (auto x1 : res1) {
            for (auto x2 : res2) {
              if (c == '+') {
                res.emplace_back(x1 + x2);
              } else if (c == '-') {
                res.emplace_back(x1 - x2);
              } else {
                res.emplace_back(x1 * x2);
              }
            }
          }
        }
      }
      if (res.empty()) {
        res.emplace_back(stoi(exp));
      }
      return dp[exp] = res;
    }

  public:
    vector<int> diffWaysToCompute(string expression) {
      auto dp = unordered_map<string, vector<int>>();
      return helper(expression, dp);
    }
  };

  class Solution *solution;
};

TEST_F(q241, sample_input01) {
  solution               = new Solution();
  string      expression = "2-1-1";
  vector<int> exp        = {0, 2};
  // Try EXPECT_EQ_ANY_ORDER_RECURSIVE
  // if the element is also matched in any order.
  EXPECT_EQ_ANY_ORDER(solution->diffWaysToCompute(expression), exp);
  delete solution;
}

TEST_F(q241, sample_input02) {
  solution               = new Solution();
  string      expression = "2*3-4*5";
  vector<int> exp        = {-34, -14, -10, -10, 10};
  // Try EXPECT_EQ_ANY_ORDER_RECURSIVE
  // if the element is also matched in any order.
  EXPECT_EQ_ANY_ORDER(solution->diffWaysToCompute(expression), exp);
  delete solution;
}