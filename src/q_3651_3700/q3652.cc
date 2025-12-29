// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Best Time to Buy and Sell Stock using Strategy
//
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-using-strategy/
//
// Question ID: 3652
// Difficult  : Medium
// Solve Date : 2025/12/18 21:42

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3652. Best Time to Buy and Sell Stock using Strategy|:
//
// You are given two integer arrays |prices| and |strategy|, where:
//
//  • |prices[i]| is the price of a given stock on the |iᵗʰ| day.
//
//  • |strategy[i]| represents a trading action on the |iᵗʰ| day, where:
//
//
//    • |-1| indicates buying one unit of the stock.
//
//    • |0| indicates holding the stock.
//
//    • |1| indicates selling one unit of the stock.
//
//
// You are also given an even integer |k|, and may perform at most one
// modification to |strategy|. A modification consists of:
//
//  • Selecting exactly |k| consecutive elements in |strategy|.
//
//  • Set the first |k / 2| elements to |0| (hold).
//
//  • Set the last |k / 2| elements to |1| (sell).
// The profit is defined as the sum of |strategy[i] * prices[i]| across all
// days. Return the maximum possible profit you can achieve. Note: There are no
// constraints on budget or stock ownership, so all buy and sell operations are
// feasible regardless of past actions.
//
//

LEETCODE_BEGIN_RESOLVING(3652, BestTimeToBuyAndSellStockUsingStrategy,
                         Solution);

class Solution {
public:
  long long maxProfit(vector<int> &prices, vector<int> &strategy, int k) {
    int n = prices.size();

    long long         actualP = 0;
    vector<long long> profit(n);

    for (int i = 0; i < n; i++) {
      profit[i] = (long long)strategy[i] * prices[i];
      actualP += profit[i];
    }

    long long originalWindProfit = 0;
    long long modifiedWindProfit = 0;
    long long maxGain            = 0;

    int i = 0, j = 0;

    // sliding window
    while (j < n) {
      originalWindProfit += profit[j];

      // second half of the window contributes to modifiedWindProfit
      if (j - i + 1 > k / 2) {
        modifiedWindProfit += prices[j];
      }

      if (j - i + 1 > k) {
        originalWindProfit -= profit[i];
        modifiedWindProfit -= prices[i + k / 2];
        i++;
      }

      // evaluate window of size k
      if (j - i + 1 == k) {
        maxGain = max(maxGain, modifiedWindProfit - originalWindProfit);
      }

      j++;
    }

    return actualP + maxGain;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= prices.length == strategy.length <= 10⁵|
// * |1 <= prices[i] <= 10⁵|
// * |-1 <= strategy[i] <= 1|
// * |2 <= k <= prices.length|
// * |k| is even
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: prices = [4,2,8], strategy = [-1,0,1], k = 2
// Output: 10
//

LEETCODE_SOLUTION_UNITTEST(3652, BestTimeToBuyAndSellStockUsingStrategy,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> prices   = {4, 2, 8};
  vector<int> strategy = {-1, 0, 1};
  int         k        = 2;
  long long   expect   = 10;
  long long   actual   = solution->maxProfit(prices, strategy, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: prices = [5,4,3], strategy = [1,1,0], k = 2
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(3652, BestTimeToBuyAndSellStockUsingStrategy,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> prices   = {5, 4, 3};
  vector<int> strategy = {1, 1, 0};
  int         k        = 2;
  long long   expect   = 9;
  long long   actual   = solution->maxProfit(prices, strategy, k);
  LCD_EXPECT_EQ(expect, actual);
}
