// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Best Time to Buy and Sell Stock II
//
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
//
// Question ID: 122
// Difficult  : Medium
// Solve Date : 2021/10/16 13:35

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |122. Best Time to Buy and Sell Stock II|:
//
// You are given an integer array |prices| where |prices[i]| is the price of a
// given stock on the |iᵗʰ| day. On each day, you may decide to buy and/or sell
// the stock. You can only hold at most one share of the stock at any time.
// However, you can buy it then immediately sell it on the same day. Find and
// return the maximum profit you can achieve.  
//

LEETCODE_BEGIN_RESOLVING(122, BestTimeToBuyAndSellStockII, Solution);

class Solution {
public:
  int maxProfit(vector<int> &prices) {
    int res = 0;
    for (int i = 1; i < prices.size(); ++i)
      if (prices[i] > prices[i - 1])
        res += prices[i] - prices[i - 1];
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= prices.length <= 3 * 10⁴|
// * |0 <= prices[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: prices = [7,1,5,3,6,4]
// Output: 7
//
// Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
// Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3
// = 3. Total profit is 4 + 3 = 7.

LEETCODE_SOLUTION_UNITTEST(122, BestTimeToBuyAndSellStockII, example_1) {
  auto        solution = MakeSolution();
  vector<int> prices   = {7, 1, 5, 3, 6, 4};
  int         expect   = 7;
  int         actual   = solution->maxProfit(prices);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: prices = [1,2,3,4,5]
// Output: 4
//
// Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
// Total profit is 4.

LEETCODE_SOLUTION_UNITTEST(122, BestTimeToBuyAndSellStockII, example_2) {
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
// There is no way to make a positive profit, so we never buy the stock to
// achieve the maximum profit of 0.

LEETCODE_SOLUTION_UNITTEST(122, BestTimeToBuyAndSellStockII, example_3) {
  auto        solution = MakeSolution();
  vector<int> prices   = {7, 6, 4, 3, 1};
  int         expect   = 0;
  int         actual   = solution->maxProfit(prices);
  LCD_EXPECT_EQ(expect, actual);
}
