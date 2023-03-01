// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Best Time to Buy and Sell Stock IV
//
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
//
// Question ID: 188
// Difficult  : Hard
// Solve Date : 2022/09/10 20:38

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |188. Best Time to Buy and Sell Stock IV|:
//
// You are given an integer array |prices| where |prices[i]| is the price of a
// given stock on the |iᵗʰ| day, and an integer |k|. Find the maximum profit you
// can achieve. You may complete at most |k| transactions. Note: You may not
// engage in multiple transactions simultaneously (i.e., you must sell the stock
// before you buy again).
//

LEETCODE_BEGIN_RESOLVING(188, BestTimeToBuyAndSellStockIV, Solution);

class Solution {
private:
  int maxProfit(vector<int> &prices) {
    auto res = (int)0;
    auto beg = prices.begin();
    while (beg != prices.end() && beg + 1 != prices.end()) {
      res += max(0, *(beg + 1) - *beg);
      ++beg;
    }
    return res;
  }

public:
  int maxProfit(int k, vector<int> &prices) {
    if (k >= prices.size() / 2) {
      return maxProfit(prices);
    } else {
      auto buys  = vector<int>(k + 1, numeric_limits<int>::min());
      auto sells = vector<int>(k + 1, 0);
      for (auto p : prices) {
        for (int i = 1; i <= k; ++i) {
          buys[i]  = max(sells[i - 1] - p, buys[i]);
          sells[i] = max(sells[i], buys[i] + p);
        }
      }
      return sells.back();
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= k <= 100|
// * |1 <= prices.length <= 1000|
// * |0 <= prices[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: k = 2, prices = [2,4,1]
// Output: 2
//
// Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.

LEETCODE_SOLUTION_UNITTEST(188, BestTimeToBuyAndSellStockIV, example_1) {
  auto        solution = MakeSolution();
  int         k        = 2;
  vector<int> prices   = {2, 4, 1};
  int         expect   = 2;
  int         actual   = solution->maxProfit(k, prices);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: k = 2, prices = [3,2,6,5,0,3]
// Output: 7
//
// Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4.
// Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0
// = 3.

LEETCODE_SOLUTION_UNITTEST(188, BestTimeToBuyAndSellStockIV, example_2) {
  auto        solution = MakeSolution();
  int         k        = 2;
  vector<int> prices   = {3, 2, 6, 5, 0, 3};
  int         expect   = 7;
  int         actual   = solution->maxProfit(k, prices);
  LCD_EXPECT_EQ(expect, actual);
}
