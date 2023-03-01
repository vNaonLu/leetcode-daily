// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Best Time to Buy and Sell Stock III
//
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
//
// Question ID: 123
// Difficult  : Hard
// Solve Date : 2021/10/16 13:13

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |123. Best Time to Buy and Sell Stock III|:
//
// You are given an array |prices| where |prices[i]| is the price of a given
// stock on the |iᵗʰ| day. Find the maximum profit you can achieve. You may
// complete at most two transactions. Note: You may not engage in multiple
// transactions simultaneously (i.e., you must sell the stock before you buy
// again).  
//

LEETCODE_BEGIN_RESOLVING(123, BestTimeToBuyAndSellStockIII, Solution);

class Solution {
public:
  int maxProfit(vector<int> &prices) {
    if (prices.size() == 0)
      return 0;
    int         n = prices.size();
    vector<int> left(n, 0), right(n, 0);
    int         lmin = prices[0], rmax = prices[n - 1];
    for (int i = 1; i < n; ++i) {
      left[i] = max(left[i - 1], prices[i] - lmin);
      lmin    = min(prices[i], lmin);
    }
    for (int i = n - 2; i >= 0; --i) {
      right[i] = max(right[i + 1], rmax - prices[i]);
      rmax     = max(prices[i], rmax);
    }
    int res = right[0];
    for (int i = 1; i < n; ++i) {
      res = max(res, right[i] + left[i - 1]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= prices.length <= 10⁵|
// * |0 <= prices[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: prices = [3,3,5,0,0,3,1,4]
// Output: 6
//
// Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
// Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1
// = 3.

LEETCODE_SOLUTION_UNITTEST(123, BestTimeToBuyAndSellStockIII, example_1) {
  auto        solution = MakeSolution();
  vector<int> prices   = {3, 3, 5, 0, 0, 3, 1, 4};
  int         expect   = 6;
  int         actual   = solution->maxProfit(prices);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: prices = [1,2,3,4,5]
// Output: 4
//
// Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
// Note that you cannot buy on day 1, buy on day 2 and sell them later, as you
// are engaging multiple transactions at the same time. You must sell before
// buying again.

LEETCODE_SOLUTION_UNITTEST(123, BestTimeToBuyAndSellStockIII, example_2) {
  auto        solution = MakeSolution();
  vector<int> prices   = {1, 2, 3, 4, 5};
  int         expect   = 4;
  int         actual   = solution->maxProfit(prices);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: prices = [7,6,4,3,1]
// Output: 0
//
// In this case, no transaction is done, i.e. max profit = 0.

LEETCODE_SOLUTION_UNITTEST(123, BestTimeToBuyAndSellStockIII, example_3) {
  auto        solution = MakeSolution();
  vector<int> prices   = {7, 6, 4, 3, 1};
  int         expect   = 0;
  int         actual   = solution->maxProfit(prices);
  LCD_EXPECT_EQ(expect, actual);
}
