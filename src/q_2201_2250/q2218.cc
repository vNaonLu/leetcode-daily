// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Value of K Coins From Piles
//
// https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/
//
// Question ID: 2218
// Difficult  : Hard
// Solve Date : 2023/04/15 12:54

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2218. Maximum Value of K Coins From Piles|:
//
// There are |n| piles of coins on a table. Each pile consists of a positive
// number of coins of assorted denominations. In one move, you can choose any
// coin on top of any pile, remove it, and add it to your wallet. Given a list
// |piles|, where |piles[i]| is a list of integers denoting the composition of
// the |iᵗʰ| pile from top to bottom, and a positive integer |k|, return the
// maximum total value of coins you can have in your wallet if you choose
// exactly |k| coins optimally.
//
//

LEETCODE_BEGIN_RESOLVING(2218, MaximumValueOfKCoinsFromPiles, Solution);

class Solution {
public:
  int maxValueOfCoins(vector<vector<int>> &piles, int k) {
    int                 n = piles.size();
    vector<vector<int>> pre(n);
    vector<vector<int>> dp(n + 2, vector<int>(k + 2, -1));
    for (int i = 0; i < n; ++i) {
      int sum = 0;
      for (auto x : piles[i]) {
        pre[i].emplace_back(sum);
        sum += x;
      }
      pre[i].emplace_back(sum);
    }
    return solve(pre, 0, k, dp);
  }

private:
  int solve(vector<vector<int>> &pp, int cur, int k, vector<vector<int>> &dp) {
    if (cur >= pp.size()) {
      return 0;
    }

    if (dp[cur][k] == -1) {
      int mx = 0;
      for (int i = 0; i < pp[cur].size(); ++i) {
        if (k - i >= 0) {
          mx = max(mx, pp[cur][i] + solve(pp, cur + 1, k - i, dp));
        }
      }
      dp[cur][k] = mx;
    }
    return dp[cur][k];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == piles.length|
// * |1 <= n <= 1000|
// * |1 <= piles[i][j] <= 10⁵|
// * |1 <= k <= sum(piles[i].length) <= 2000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: piles = [[1,100,3],[7,8,9]], k = 2
// Output: 101
//
// The above diagram shows the different ways we can choose k coins.
// The maximum total we can obtain is 101.

LEETCODE_SOLUTION_UNITTEST(2218, MaximumValueOfKCoinsFromPiles, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> piles    = {
      {1, 100, 3},
      {7,   8, 9}
  };
  int k      = 2;
  int expect = 101;
  int actual = solution->maxValueOfCoins(piles, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: piles = [[100],[100],[100],[100],[100],[100],[1,1,1,1,1,1,700]], k =
//  7
// Output: 706
// Explanation:
// The maximum total can be obtained if we choose all coins from the last pile.
//

LEETCODE_SOLUTION_UNITTEST(2218, MaximumValueOfKCoinsFromPiles, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> piles    = {
      {100},
      {100},
      {100},
      {100},
      {100},
      {100},
      {1, 1, 1, 1, 1, 1, 700}
  };
  int k      = 7;
  int expect = 706;
  int actual = solution->maxValueOfCoins(piles, k);
  LCD_EXPECT_EQ(expect, actual);
}
