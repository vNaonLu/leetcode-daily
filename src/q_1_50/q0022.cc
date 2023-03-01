// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Generate Parentheses
//
// https://leetcode.com/problems/generate-parentheses/
//
// Question ID: 22
// Difficult  : Medium
// Solve Date : 2021/09/29 13:19

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |22. Generate Parentheses|:
//
// Given |n| pairs of parentheses, write a function to generate all combinations
// of well-formed parentheses.  
//

LEETCODE_BEGIN_RESOLVING(22, GenerateParentheses, Solution);

class Solution {
private:
  void helper(vector<string> &res, string &c, const int &n, int l = 0,
              int r = 0) {
    if (c.size() == n * 2) {
      res.push_back(c);
    } else {
      if (l < n) {
        c.push_back('(');
        helper(res, c, n, l + 1, r);
        c.pop_back();
      }
      if (r < l) {
        c.push_back(')');
        helper(res, c, n, l, r + 1);
        c.pop_back();
      }
    }
  }

public:
  vector<string> generateParenthesis(int n) {
    vector<string> res;
    string         tmp = "";
    helper(res, tmp, n);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 8|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3
// Output: ["((()))","(()())","(())()","()(())","()()()"]
//

LEETCODE_SOLUTION_UNITTEST(22, GenerateParentheses, example_1) {
  auto           solution = MakeSolution();
  int            n        = 3;
  vector<string> expect   = {"((()))", "(()())", "(())()", "()(())", "()()()"};
  vector<string> actual   = solution->generateParenthesis(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: ["()"]
//

LEETCODE_SOLUTION_UNITTEST(22, GenerateParentheses, example_2) {
  auto           solution = MakeSolution();
  int            n        = 1;
  vector<string> expect   = {"()"};
  vector<string> actual   = solution->generateParenthesis(n);
  LCD_EXPECT_EQ(expect, actual);
}
