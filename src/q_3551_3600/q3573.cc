// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Best Time to Buy and Sell Stock V
//
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-v/
//
// Question ID: 3573
// Difficult  : Medium
// Solve Date : 2025/12/17 19:11

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3573. Best Time to Buy and Sell Stock V|:
//
// You are given an integer array |prices| where |prices[i]| is the price of a
// stock in dollars on the |iᵗʰ| day, and an integer |k|. You are allowed to
// make at most |k| transactions, where each transaction can be either of the
// following:
//
//  •
// 	Normal transaction: Buy on day |i|, then sell on a later day |j| where
// |i < j|. You profit |prices[j] - prices[i]|.
//
//
//  •
// 	Short selling transaction: Sell on day |i|, then buy back on a later day
// |j| where |i < j|. You profit |prices[i] - prices[j]|.
//
// Note that you must complete each transaction before starting another.
// Additionally, you can't buy or sell on the same day you are selling or buying
// back as part of a previous transaction. Return the maximum total profit you
// can earn by making at most |k| transactions.
//
//

LEETCODE_BEGIN_RESOLVING(3573, BestTimeToBuyAndSellStockV, Solution);

class Solution {
public:
  long long maximumProfit(vector<int> &prices, int k) {
    const int     firstPrice = prices[0];
    vector<State> dp(k + 1, State(0, -firstPrice, firstPrice));
    const int     n = prices.size();

    for (int day = 1; day < n; day++) {
      const int currPrice = prices[day];
      for (int trans = k; trans > 0; trans--) {
        auto &[profit, buy, sell]  = dp[trans];
        const long long prevProfit = dp[trans - 1].maxProfit;
        profit = max(profit, max(buy + currPrice, sell - currPrice));
        buy    = max(buy, prevProfit - currPrice);
        sell   = max(sell, prevProfit + currPrice);
      }
    }

    return dp[k].maxProfit;
  }

private:
  struct State {
    long long maxProfit, buyHold, sellHold;
    State(long long p = 0, long long b = 0, long long s = 0)
        : maxProfit(p), buyHold(b), sellHold(s) {}
  };
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= prices.length <= 10³|
// * |1 <= prices[i] <= 10⁹|
// * |1 <= k <= prices.length / 2|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: prices = [1,7,9,8,2], k = 2
// Output: 14
//

LEETCODE_SOLUTION_UNITTEST(3573, BestTimeToBuyAndSellStockV, example_1) {
  auto        solution = MakeSolution();
  vector<int> prices   = {1, 7, 9, 8, 2};
  int         k        = 2;
  long long   expect   = 14;
  long long   actual   = solution->maximumProfit(prices, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: prices = [12,16,19,19,8,1,19,13,9], k = 3
// Output: 36
//

LEETCODE_SOLUTION_UNITTEST(3573, BestTimeToBuyAndSellStockV, example_2) {
  auto        solution = MakeSolution();
  vector<int> prices   = {12, 16, 19, 19, 8, 1, 19, 13, 9};
  int         k        = 3;
  long long   expect   = 36;
  long long   actual   = solution->maximumProfit(prices, k);
  LCD_EXPECT_EQ(expect, actual);
}
