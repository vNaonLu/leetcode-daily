// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Maximum Amount of Money Robot Can Earn
//
// https://leetcode.com/problems/maximum-amount-of-money-robot-can-earn/
//
// Question ID: 3418
// Difficult  : Medium
// Solve Date : 2026/04/02 14:30

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3418. Maximum Amount of Money Robot Can Earn|:
//
// You are given an |m x n| grid. A robot starts at the top-left corner of the
// grid |(0, 0)| and wants to reach the bottom-right corner |(m - 1, n - 1)|.
// The robot can move either right or down at any point in time. The grid
// contains a value |coins[i][j]| in each cell:
//
//  • If |coins[i][j] >= 0|, the robot gains that many coins.
//
//  • If |coins[i][j] < 0|, the robot encounters a robber, and the robber steals
//  the absolute value of |coins[i][j]| coins.
// The robot has a special ability to neutralize robbers in at most 2 cells on
// its path, preventing them from stealing coins in those cells. Note: The
// robot's total coins can be negative. Return the maximum profit the robot can
// gain on the route.
//
//

LEETCODE_BEGIN_RESOLVING(3418, MaximumAmountOfMoneyRobotCanEarn, Solution);

class Solution {
public:
  int maximumAmount(vector<vector<int>> &coins) {
    int    n = coins.size(), m = coins[0].size();
    vector dp(n, vector(m, vector<int>(3, -1e9)));
    dp[0][0][1] = dp[0][0][2] = 0, dp[0][0][0] = coins[0][0];

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        for (int k = 0; k < 3; k++) {
          if (i)
            dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k] + coins[i][j]);
          if (i && k)
            dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k - 1]);
          if (j)
            dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k] + coins[i][j]);
          if (j && k)
            dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k - 1]);
        }
    int ans = *max_element(dp[n - 1][m - 1].begin(), dp[n - 1][m - 1].end());
    return ans;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == coins.length|
// * |n == coins[i].length|
// * |1 <= m, n <= 500|
// * |-1000 <= coins[i][j] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: coins = [[0,1,-1],[1,-2,3],[2,-3,4]]
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(3418, MaximumAmountOfMoneyRobotCanEarn, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> coins    = {
      {0,  1, -1},
      {1, -2,  3},
      {2, -3,  4}
  };
  int expect = 8;
  int actual = solution->maximumAmount(coins);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: coins = [[10,10,10],[10,10,10]]
// Output: 40
//

LEETCODE_SOLUTION_UNITTEST(3418, MaximumAmountOfMoneyRobotCanEarn, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> coins    = {
      {10, 10, 10},
      {10, 10, 10}
  };
  int expect = 40;
  int actual = solution->maximumAmount(coins);
  LCD_EXPECT_EQ(expect, actual);
}
