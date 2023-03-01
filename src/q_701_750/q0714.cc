// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Best Time to Buy and Sell Stock with Transaction Fee
//
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
//
// Question ID: 714
// Difficult  : Medium
// Solve Date : 2021/10/17 14:20

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |714. Best Time to Buy and Sell Stock with Transaction Fee|:
//
// You are given an array |prices| where |prices[i]| is the price of a given
// stock on the |iᵗʰ| day, and an integer |fee| representing a transaction fee.
// Find the maximum profit you can achieve. You may complete as many
// transactions as you like, but you need to pay the transaction fee for each
// transaction. Note: You may not engage in multiple transactions simultaneously
// (i.e., you must sell the stock before you buy again).  
//

LEETCODE_BEGIN_RESOLVING(714, BestTimeToBuyAndSellStockWithTransactionFee,
                         Solution);

class Solution {
public:
  int maxProfit(vector<int> &prices, int fee) {
    int res = 0, hold = -prices[0];
    for (int i = 1; i < prices.size(); ++i) {
      res  = max(res, hold + prices[i] - fee);
      hold = max(hold, res - prices[i]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= prices.length <= 5 * 10⁴|
// * |1 <= prices[i] < 5 * 10⁴|
// * |0 <= fee < 5 * 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: prices = [1,3,2,8,4,9], fee = 2
// Output: 8
//
// The maximum profit can be achieved by:
// - Buying at prices[0] = 1
// - Selling at prices[3] = 8
// - Buying at prices[4] = 4
// - Selling at prices[5] = 9
// The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.

LEETCODE_SOLUTION_UNITTEST(714, BestTimeToBuyAndSellStockWithTransactionFee,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> prices   = {1, 3, 2, 8, 4, 9};
  int         fee      = 2;
  int         expect   = 8;
  int         actual   = solution->maxProfit(prices, fee);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: prices = [1,3,7,5,10,3], fee = 3
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(714, BestTimeToBuyAndSellStockWithTransactionFee,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> prices   = {1, 3, 7, 5, 10, 3};
  int         fee      = 3;
  int         expect   = 6;
  int         actual   = solution->maxProfit(prices, fee);
  LCD_EXPECT_EQ(expect, actual);
}
