// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Different Ways to Add Parentheses
//
// https://leetcode.com/problems/different-ways-to-add-parentheses/
//
// Question ID: 241
// Difficult  : Medium
// Solve Date : 2022/11/14 20:47

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |241. Different Ways to Add Parentheses|:
//
// Given a string |expression| of numbers and operators, return all possible
// results from computing all the different possible ways to group numbers and
// operators. You may return the answer in any order. The test cases are
// generated such that the output values fit in a 32-bit integer and the number
// of different results does not exceed |10⁴|.
//

LEETCODE_BEGIN_RESOLVING(241, DifferentWaysToAddParentheses, Solution);

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

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= expression.length <= 20|
// * |expression| consists of digits and the operator |'+'|, |'-'|, and |'*'|.
// * All the integer values in the input expression are in the range |[0, 99]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: expression = "2-1-1"
// Output: [0,2]
//
// ((2-1)-1) = 0
// (2-(1-1)) = 2

LEETCODE_SOLUTION_UNITTEST(241, DifferentWaysToAddParentheses, example_1) {
  auto        solution   = MakeSolution();
  string      expression = "2-1-1";
  vector<int> expect     = {0, 2};
  vector<int> actual     = solution->diffWaysToCompute(expression);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: expression = "2*3-4*5"
// Output: [-34,-14,-10,-10,10]
//
// (2*(3-(4*5))) = -34
// ((2*3)-(4*5)) = -14
// ((2*(3-4))*5) = -10
// (2*((3-4)*5)) = -10
// (((2*3)-4)*5) = 10

LEETCODE_SOLUTION_UNITTEST(241, DifferentWaysToAddParentheses, example_2) {
  auto        solution   = MakeSolution();
  string      expression = "2*3-4*5";
  vector<int> expect     = {-34, -14, -10, -10, 10};
  vector<int> actual     = solution->diffWaysToCompute(expression);
  EXPECT_ANYORDER_EQ(expect, actual);
}
