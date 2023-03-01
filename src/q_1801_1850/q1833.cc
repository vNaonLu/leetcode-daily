// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Ice Cream Bars
//
// https://leetcode.com/problems/maximum-ice-cream-bars/
//
// Question ID: 1833
// Difficult  : Medium
// Solve Date : 2023/01/06 16:15

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1833. Maximum Ice Cream Bars|:
//
// It is a sweltering summer day, and a boy wants to buy some ice cream bars.
// At the store, there are |n| ice cream bars. You are given an array |costs| of
// length |n|, where |costs[i]| is the price of the |iᵗʰ| ice cream bar in
// coins. The boy initially has |coins| coins to spend, and he wants to buy as
// many ice cream bars as possible. Note: The boy can buy the ice cream bars in
// any order. Return the maximum number of ice cream bars the boy can buy with
// |coins| coins. You must solve the problem by counting sort.
//

LEETCODE_BEGIN_RESOLVING(1833, MaximumIceCreamBars, Solution);

class Solution {
public:
  int maxIceCream(vector<int> &costs, int coins) {
    int                                            res = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (auto x : costs) {
      pq.emplace(x);
    }
    while (coins > 0 && !pq.empty()) {
      auto x = pq.top();
      pq.pop();
      if (x <= coins) {
        coins -= x;
        ++res;
      } else {
        break;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |costs.length == n|
// * |1 <= n <= 10⁵|
// * |1 <= costs[i] <= 10⁵|
// * |1 <= coins <= 10⁸|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: costs = [1,3,2,4,1], coins = 7
// Output: 4
//
// The boy can buy ice cream bars at indices 0,1,2,4 for a total price of 1 + 3
// + 2 + 1 = 7.

LEETCODE_SOLUTION_UNITTEST(1833, MaximumIceCreamBars, example_1) {
  auto        solution = MakeSolution();
  vector<int> costs    = {1, 3, 2, 4, 1};
  int         coins    = 7;
  int         expect   = 4;
  int         actual   = solution->maxIceCream(costs, coins);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: costs = [10,6,8,7,7,8], coins = 5
// Output: 0
//
// The boy cannot afford any of the ice cream bars.

LEETCODE_SOLUTION_UNITTEST(1833, MaximumIceCreamBars, example_2) {
  auto        solution = MakeSolution();
  vector<int> costs    = {10, 6, 8, 7, 7, 8};
  int         coins    = 5;
  int         expect   = 0;
  int         actual   = solution->maxIceCream(costs, coins);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: costs = [1,6,3,1,2,5], coins = 20
// Output: 6
//
// The boy can buy all the ice cream bars for a total price of 1 + 6 + 3 + 1 + 2
// + 5 = 18.

LEETCODE_SOLUTION_UNITTEST(1833, MaximumIceCreamBars, example_3) {
  auto        solution = MakeSolution();
  vector<int> costs    = {1, 6, 3, 1, 2, 5};
  int         coins    = 20;
  int         expect   = 6;
  int         actual   = solution->maxIceCream(costs, coins);
  LCD_EXPECT_EQ(expect, actual);
}
