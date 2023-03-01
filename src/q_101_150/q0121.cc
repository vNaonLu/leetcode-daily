// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Best Time to Buy and Sell Stock
//
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
//
// Question ID: 121
// Difficult  : Easy
// Solve Date : 2021/09/07 08:00

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |121. Best Time to Buy and Sell Stock|:
//
// You are given an array |prices| where |prices[i]| is the price of a given
// stock on the |iᵗʰ| day. You want to maximize your profit by choosing a single
// day to buy one stock and choosing a different day in the future to sell that
// stock. Return the maximum profit you can achieve from this transaction. If
// you cannot achieve any profit, return |0|.  
//

LEETCODE_BEGIN_RESOLVING(121, BestTimetoBuyandSellStock, Solution);

class Solution {
public:
  int maxProfit(vector<int> &prices) {
    int res    = 0;
    int lowest = numeric_limits<int>::max();
    for (auto p : prices) {
      lowest = min(lowest, p);
      res    = max(res, p - lowest);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= prices.length <= 10⁵|
// * |0 <= prices[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: prices = [7,1,5,3,6,4]
// Output: 5
//
// Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
// Note that buying on day 2 and selling on day 1 is not allowed because you
// must buy before you sell.

LEETCODE_SOLUTION_UNITTEST(121, BestTimetoBuyandSellStock, example_1) {
  auto        solution = MakeSolution();
  vector<int> prices   = {7, 1, 5, 3, 6, 4};
  int         expect   = 5;
  int         actual   = solution->maxProfit(prices);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: prices = [7,6,4,3,1]
// Output: 0
//
// In this case, no transactions are done and the max profit = 0.

LEETCODE_SOLUTION_UNITTEST(121, BestTimetoBuyandSellStock, example_2) {
  auto        solution = MakeSolution();
  vector<int> prices   = {7, 6, 4, 3, 1};
  int         expect   = 0;
  int         actual   = solution->maxProfit(prices);
  EXPECT_EQ(expect, actual);
}
