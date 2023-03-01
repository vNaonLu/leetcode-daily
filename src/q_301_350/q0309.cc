// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Best Time to Buy and Sell Stock with Cooldown
//
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
//
// Question ID: 309
// Difficult  : Medium
// Solve Date : 2021/10/15 10:08

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |309. Best Time to Buy and Sell Stock with Cooldown|:
//
// You are given an array |prices| where |prices[i]| is the price of a given
// stock on the |iᵗʰ| day. Find the maximum profit you can achieve. You may
// complete as many transactions as you like (i.e., buy one and sell one share
// of the stock multiple times) with the following restrictions:
//
//  • After you sell your stock, you cannot buy stock on the next day (i.e.,
//  cooldown one day).
// Note: You may not engage in multiple transactions simultaneously (i.e., you
// must sell the stock before you buy again).  
//

LEETCODE_BEGIN_RESOLVING(309, BestTimeToBuyAndSellStockWithCooldown, Solution);

class Solution {
public:
  int maxProfit(vector<int> &prices) {
    int rest = 0, hold = numeric_limits<int>::min(),
        sold = numeric_limits<int>::min();
    for (const auto &x : prices) {
      int before = sold;
      sold       = hold + x;
      hold       = max(hold, rest - x);
      rest       = max(rest, before);
    }
    return max(rest, sold);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= prices.length <= 5000|
// * |0 <= prices[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: prices = [1,2,3,0,2]
// Output: 3
//
// transactions = [buy, sell, cooldown, buy, sell]

LEETCODE_SOLUTION_UNITTEST(309, BestTimeToBuyAndSellStockWithCooldown,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> prices   = {1, 2, 3, 0, 2};
  int         expect   = 3;
  int         actual   = solution->maxProfit(prices);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: prices = [1]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(309, BestTimeToBuyAndSellStockWithCooldown,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> prices   = {1};
  int         expect   = 0;
  int         actual   = solution->maxProfit(prices);
  LCD_EXPECT_EQ(expect, actual);
}
