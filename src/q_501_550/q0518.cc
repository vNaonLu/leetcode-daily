// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Coin Change II
//
// https://leetcode.com/problems/coin-change-ii/
//
// Question ID: 518
// Difficult  : Medium
// Solve Date : 2021/10/29 12:56

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |518. Coin Change II|:
//
// You are given an integer array |coins| representing coins of different
// denominations and an integer |amount| representing a total amount of money.
// Return the number of combinations that make up that amount. If that amount of
// money cannot be made up by any combination of the coins, return |0|. You may
// assume that you have an infinite number of each kind of coin. The answer is
// guaranteed to fit into a signed 32-bit integer.  
//

LEETCODE_BEGIN_RESOLVING(518, CoinChangeII, Solution);

class Solution {
public:
  int change(int amount, vector<int> &coins) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    for (const auto &c : coins) {
      for (int x = c; x < dp.size(); ++x) {
        dp[x] += dp[x - c];
      }
    }
    return dp.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= coins.length <= 300|
// * |1 <= coins[i] <= 5000|
// * All the values of |coins| are unique.
// * |0 <= amount <= 5000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: amount = 5, coins = [1,2,5]
// Output: 4
//
// there are four ways to make up the amount:
// 5=5
// 5=2+2+1
// 5=2+1+1+1
// 5=1+1+1+1+1

LEETCODE_SOLUTION_UNITTEST(518, CoinChangeII, example_1) {
  auto        solution = MakeSolution();
  int         amount   = 5;
  vector<int> coins    = {1, 2, 5};
  int         expect   = 4;
  int         actual   = solution->change(amount, coins);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: amount = 3, coins = [2]
// Output: 0
//
// the amount of 3 cannot be made up just with coins of 2.

LEETCODE_SOLUTION_UNITTEST(518, CoinChangeII, example_2) {
  auto        solution = MakeSolution();
  int         amount   = 3;
  vector<int> coins    = {2};
  int         expect   = 0;
  int         actual   = solution->change(amount, coins);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: amount = 10, coins = [10]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(518, CoinChangeII, example_3) {
  auto        solution = MakeSolution();
  int         amount   = 10;
  vector<int> coins    = {10};
  int         expect   = 1;
  int         actual   = solution->change(amount, coins);
  LCD_EXPECT_EQ(expect, actual);
}
