// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Expression Add Operators
//
// https://leetcode.com/problems/expression-add-operators/
//
// Question ID: 282
// Difficult  : Hard
// Solve Date : 2021/09/18 08:00

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |282. Expression Add Operators|:
//
// Given a string |num| that contains only digits and an integer |target|,
// return all possibilities to insert the binary operators |'+'|, |'-'|, and/or
// |'*'| between the digits of |num| so that the resultant expression evaluates
// to the |target| value. Note that operands in the returned expressions should
// not contain leading zeros.  
//

LEETCODE_BEGIN_RESOLVING(282, ExpressionAddOperators, Solution);

class Solution {
private:
  long T;
  void helper(vector<string> &r, string &s, int beg, long prev, long res,
              string cur = "") {
    if (beg == s.size() && res == T) {
      r.push_back(cur);
      return;
    }
    string sbs    = "";
    long   number = 0;
    for (int i = beg; i < s.size(); ++i) {
      sbs += s[i];
      number = number * 10 + (s[i] - '0');
      if (sbs.size() > 1 && sbs[0] == '0')
        break;
      if (beg == 0) {
        helper(r, s, i + 1, number, number, sbs);
      } else {
        helper(r, s, i + 1, number, number + res, cur + "+" + sbs);
        helper(r, s, i + 1, -number, res - number, cur + "-" + sbs);
        helper(r, s, i + 1, number * prev, (prev * number) + (res - prev),
               cur + "*" + sbs);
      }
    }
  }

public:
  vector<string> addOperators(string num, int target) {
    vector<string> res;
    T = target;
    helper(res, num, 0, 0, 0);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= num.length <= 10|
// * |num| consists of only digits.
// * |-2³¹ <= target <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = "123", target = 6
// Output: ["1*2*3","1+2+3"]
//
// Both "1*2*3" and "1+2+3" evaluate to 6.

LEETCODE_SOLUTION_UNITTEST(282, ExpressionAddOperators, example_1) {
  auto           solution = MakeSolution();
  string         num      = "123";
  int            target   = 6;
  vector<string> expect   = {"1*2*3", "1+2+3"};
  vector<string> actual   = solution->addOperators(num, target);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: num = "232", target = 8
// Output: ["2*3+2","2+3*2"]
//
// Both "2*3+2" and "2+3*2" evaluate to 8.

LEETCODE_SOLUTION_UNITTEST(282, ExpressionAddOperators, example_2) {
  auto           solution = MakeSolution();
  string         num      = "232";
  int            target   = 8;
  vector<string> expect   = {"2*3+2", "2+3*2"};
  vector<string> actual   = solution->addOperators(num, target);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: num = "3456237490", target = 9191
// Output: []
//
// There are no expressions that can be created from "3456237490" to evaluate to
// 9191.

LEETCODE_SOLUTION_UNITTEST(282, ExpressionAddOperators, example_3) {
  auto           solution = MakeSolution();
  string         num      = "3456237490";
  int            target   = 9191;
  vector<string> expect   = {};
  vector<string> actual   = solution->addOperators(num, target);
  LCD_EXPECT_EQ(expect, actual);
}
