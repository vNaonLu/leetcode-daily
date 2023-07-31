// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Soup Servings
//
// https://leetcode.com/problems/soup-servings/
//
// Question ID: 808
// Difficult  : Medium
// Solve Date : 2023/07/29 16:02

#include <iosfwd>
#include <map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |808. Soup Servings|:
//
// There are two types of soup: type A and type B. Initially, we have |n| ml of
// each type of soup. There are four kinds of operations:
//
//  1. Serve |100| ml of soup A and |0| ml of soup B,
//
//  2. Serve |75| ml of soup A and |25| ml of soup B,
//
//  3. Serve |50| ml of soup A and |50| ml of soup B, and
//
//  4. Serve |25| ml of soup A and |75| ml of soup B.
// When we serve some soup, we give it to someone, and we no longer have it.
// Each turn, we will choose from the four operations with an equal probability
// |0.25|. If the remaining volume of soup is not enough to complete the
// operation, we will serve as much as possible. We stop once we no longer have
// some quantity of both types of soup. Note that we do not have an operation
// where all |100| ml's of soup B are used first. Return the probability that
// soup A will be empty first, plus half the probability that A and B become
// empty at the same time. Answers within |10⁻⁵| of the actual answer will be
// accepted.
//
//

LEETCODE_BEGIN_RESOLVING(808, SoupServings, Solution);

class Solution {
public:
  double soupServings(int n) {
    map<pair<double, double>, double> mp;
    return n >= 4800 ? 1.0 : serve(&mp, n, n);
  }

private:
  double serve(map<pair<double, double>, double> *mp, int a, int b) {
    if (a <= 0 && b <= 0) {
      return 0.5;
    }
    if (a <= 0 && b > 0) {
      return 1.0;
    }
    if (a > 0 && b <= 0) {
      return 0;
    }
    auto find = mp->find({a, b});
    if (find != mp->end()) {
      return find->second;
    }

    double op1           = serve(mp, a - 100, b);
    double op2           = serve(mp, a - 75, b - 25);
    double op3           = serve(mp, a - 50, b - 50);
    double op4           = serve(mp, a - 25, b - 75);
    return (*mp)[{a, b}] = 0.25 * (op1 + op2 + op3 + op4);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |0 <= n <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 50
// Output: 0.62500
//
// If we choose the first two operations, A will become empty first.
// For the third operation, A and B will become empty at the same time.
// For the fourth operation, B will become empty first.
// So the total probability of A becoming empty first plus half the probability
// that A and B become empty at the same time, is 0.25 * (1 + 1 + 0.5 + 0) =
// 0.625.

LEETCODE_SOLUTION_UNITTEST(808, SoupServings, example_1) {
  auto   solution = MakeSolution();
  int    n        = 50;
  double expect   = 0.62500;
  double actual   = solution->soupServings(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 100
// Output: 0.71875
//

LEETCODE_SOLUTION_UNITTEST(808, SoupServings, example_2) {
  auto   solution = MakeSolution();
  int    n        = 100;
  double expect   = 0.71875;
  double actual   = solution->soupServings(n);
  LCD_EXPECT_EQ(expect, actual);
}
