// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Coin Change
//
// https://leetcode.com/problems/coin-change/
//
// Question ID: 322
// Difficult  : Medium
// Solve Date : 2021/10/06 13:01

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |322. Coin Change|:
//
// You are given an integer array |coins| representing coins of different
// denominations and an integer |amount| representing a total amount of money.
// Return the fewest number of coins that you need to make up that amount. If
// that amount of money cannot be made up by any combination of the coins,
// return |-1|. You may assume that you have an infinite number of each kind of
// coin.  
//

LEETCODE_BEGIN_RESOLVING(322, CoinChange, Solution);

class Solution {
public:
  int coinChange(vector<int> &coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for (const auto &c : coins) {
      for (int x = c; x < dp.size(); ++x) {
        dp[x] = min(dp[x], 1 + dp[x - c]);
      }
    }
    return dp.back() == amount + 1 ? -1 : dp.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= coins.length <= 12|
// * |1 <= coins[i] <= 2³¹ - 1|
// * |0 <= amount <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: coins = [1,2,5], amount = 11
// Output: 3
//
// 11 = 5 + 5 + 1

LEETCODE_SOLUTION_UNITTEST(322, CoinChange, example_1) {
  auto        solution = MakeSolution();
  vector<int> coins    = {1, 2, 5};
  int         amount   = 11;
  int         expect   = 3;
  int         actual   = solution->coinChange(coins, amount);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: coins = [2], amount = 3
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(322, CoinChange, example_2) {
  auto        solution = MakeSolution();
  vector<int> coins    = {2};
  int         amount   = 3;
  int         expect   = -1;
  int         actual   = solution->coinChange(coins, amount);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: coins = [1], amount = 0
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(322, CoinChange, example_3) {
  auto        solution = MakeSolution();
  vector<int> coins    = {1};
  int         amount   = 0;
  int         expect   = 0;
  int         actual   = solution->coinChange(coins, amount);
  LCD_EXPECT_EQ(expect, actual);
}
