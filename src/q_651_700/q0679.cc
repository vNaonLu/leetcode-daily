// Copyright 2025 Naon Lu
//
// This file describes the solution of
// 24 Game
//
// https://leetcode.com/problems/24-game/
//
// Question ID: 679
// Difficult  : Hard
// Solve Date : 2025/08/18 20:37

#include <cmath>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |679. 24 Game|:
//
// You are given an integer array |cards| of length |4|. You have four cards,
// each containing a number in the range |[1, 9]|. You should arrange the
// numbers on these cards in a mathematical expression using the operators
// |['+', '-', '*', '/']| and the parentheses |'('| and |')'| to get the
// value 24. You are restricted with the following rules:
//
//  • The division operator |'/'| represents real division, not integer
//  division.
//
//
//    • For example, |4 / (1 - 2 / 3) = 4 / (1 / 3) = 12|.
//
//
//
//  • Every operation done is between two numbers. In particular, we cannot use
//  |'-'| as a unary operator.
//
//
//    • For example, if |cards = [1, 1, 1, 1]|, the expression |"-1 - 1 - 1 -
//    1"| is not allowed.
//
//
//
//  • You cannot concatenate numbers together
//
//
//    • For example, if |cards = [1, 2, 1, 2]|, the expression |"12 + 12"| is
//    not valid.
//
//
// Return |true| if you can get such expression that evaluates to |24|, and
// |false| otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(679, 24Game, Solution);

class Solution {
public:
  bool judgePoint24(vector<int> &cards) {
    vector<double> nums(cards.begin(), cards.end());
    return dfs(nums);
  }

private:
  bool dfs(auto &nums) {
    if (nums.size() == 1) {
      return fabs(nums[0] - 24.0) < EPS;
    }

    for (int i = 0; i < nums.size(); i++) {
      for (int j = 0; j < nums.size(); j++) {
        if (i == j) {
          continue;
        }

        vector<double> next;
        for (int k = 0; k < nums.size(); k++) {
          if (k != i && k != j) {
            next.push_back(nums[k]);
          }
        }

        for (double val : compute(nums[i], nums[j])) {
          next.push_back(val);
          if (dfs(next)) {
            return true;
          }
          next.pop_back();
        }
      }
    }
    return false;
  }
  vector<double> compute(double a, double b) {
    vector<double> res{a + b, a - b, b - a, b * a};
    if (fabs(b) > EPS) {
      res.emplace_back(a / b);
    }
    if (fabs(a) > EPS) {
      res.emplace_back(b / a);
    }
    return res;
  }
  constexpr static double EPS = 1e-6;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |cards.length == 4|
// * |1 <= cards[i] <= 9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: cards = [4,1,8,7]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(679, 24Game, example_1) {
  auto        solution = MakeSolution();
  vector<int> cards    = {4, 1, 8, 7};
  bool        expect   = true;
  bool        actual   = solution->judgePoint24(cards);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: cards = [1,2,1,2]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(679, 24Game, example_2) {
  auto        solution = MakeSolution();
  vector<int> cards    = {1, 2, 1, 2};
  bool        expect   = false;
  bool        actual   = solution->judgePoint24(cards);
  LCD_EXPECT_EQ(expect, actual);
}
