// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Paint House III
//
// https://leetcode.com/problems/paint-house-iii/
//
// Question ID: 1473
// Difficult  : Hard
// Solve Date : 2022/07/08 18:21

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1473. Paint House III|:
//
// There is a row of |m| houses in a small city, each house must be painted with
// one of the |n| colors (labeled from |1| to |n|), some houses that have been
// painted last summer should not be painted again. A neighborhood is a maximal
// group of continuous houses that are painted with the same color.
//
//  • For example: |houses = [1,2,2,3,3,2,1,1]| contains |5| neighborhoods
//  |[{1}, {2,2}, {3,3}, {2}, {1,1}]|.
// Given an array |houses|, an |m x n| matrix |cost| and an integer |target|
// where:
//
//  • |houses[i]|: is the color of the house |i|, and |0| if the house is not
//  painted yet.
//
//  • |cost[i][j]|: is the cost of paint the house |i| with the color |j + 1|.
// Return the minimum cost of painting all the remaining houses in such a way
// that there are exactly |target| neighborhoods. If it is not possible, return
// |-1|.
//

LEETCODE_BEGIN_RESOLVING(1473, PaintHouseIII, Solution);

class Solution {
private:
  inline static constexpr int kMaxCost = 1e6 + 1;

public:
  int minCost(vector<int> &houses, vector<vector<int>> &cost, int m, int n,
              int target) {
    vector<vector<vector<int>>> dp(
        m, vector<vector<int>>(target + 1, vector<int>(n, kMaxCost)));

    for (int color = 1; color <= n; ++color) {
      if (houses[0] == color) {
        dp[0][1][color - 1] = 0;
      } else if (!houses[0]) {
        dp[0][1][color - 1] = cost[0][color - 1];
      }
    }

    for (int house = 1; house < m; ++house) {
      for (int neigh = 1; neigh <= min(target, house + 1); ++neigh) {
        for (int color = 1; color <= n; ++color) {
          if (houses[house] && color != houses[house]) {
            continue;
          }

          int local = kMaxCost;
          for (int prevColor = 1; prevColor <= n; prevColor++) {
            if (prevColor != color) {
              local = min(local, dp[house - 1][neigh - 1][prevColor - 1]);
            } else {
              local = min(local, dp[house - 1][neigh][color - 1]);
            }
          }
          int curr_cost = houses[house] ? 0 : cost[house][color - 1];
          dp[house][neigh][color - 1] = local + curr_cost;
        }
      }
    }

    int res = kMaxCost;
    for (int color = 1; color <= n; color++) {
      res = min(res, dp[m - 1][target][color - 1]);
    }

    return res == kMaxCost ? -1 : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == houses.length == cost.length|
// * |n == cost[i].length|
// * |1 <= m <= 100|
// * |1 <= n <= 20|
// * |1 <= target <= m|
// * |0 <= houses[i] <= n|
// * |1 <= cost[i][j] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m =
//  5, n = 2, target = 3
// Output: 9
//
// Paint houses of this way [1,2,2,1,1]
// This array contains target = 3 neighborhoods, [{1}, {2,2}, {1,1}].
// Cost of paint all houses (1 + 1 + 1 + 1 + 5) = 9.

LEETCODE_SOLUTION_UNITTEST(1473, PaintHouseIII, example_1) {
  auto                solution = MakeSolution();
  vector<int>         houses   = {0, 0, 0, 0, 0};
  vector<vector<int>> cost     = {
      { 1, 10},
      {10,  1},
      {10,  1},
      { 1, 10},
      { 5,  1}
  };
  int m      = 5;
  int n      = 2;
  int target = 3;
  int expect = 9;
  int actual = solution->minCost(houses, cost, m, n, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: houses = [0,2,1,2,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m =
//  5, n = 2, target = 3
// Output: 11
//
// Some houses are already painted, Paint the houses of this way [2,2,1,2,2]
// This array contains target = 3 neighborhoods, [{2,2}, {1}, {2,2}].
// Cost of paint the first and last house (10 + 1) = 11.

LEETCODE_SOLUTION_UNITTEST(1473, PaintHouseIII, example_2) {
  auto                solution = MakeSolution();
  vector<int>         houses   = {0, 2, 1, 2, 0};
  vector<vector<int>> cost     = {
      { 1, 10},
      {10,  1},
      {10,  1},
      { 1, 10},
      { 5,  1}
  };
  int m      = 5;
  int n      = 2;
  int target = 3;
  int expect = 11;
  int actual = solution->minCost(houses, cost, m, n, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: houses = [3,1,2,3], cost = [[1,1,1],[1,1,1],[1,1,1],[1,1,1]], m = 4,
//  n = 3, target = 3
// Output: -1
//
// Houses are already painted with a total of 4 neighborhoods [{3},{1},{2},{3}]
// different of target = 3.

LEETCODE_SOLUTION_UNITTEST(1473, PaintHouseIII, example_3) {
  auto                solution = MakeSolution();
  vector<int>         houses   = {3, 1, 2, 3};
  vector<vector<int>> cost     = {
      {1, 1, 1},
      {1, 1, 1},
      {1, 1, 1},
      {1, 1, 1}
  };
  int m      = 4;
  int n      = 3;
  int target = 3;
  int expect = -1;
  int actual = solution->minCost(houses, cost, m, n, target);
  LCD_EXPECT_EQ(expect, actual);
}
