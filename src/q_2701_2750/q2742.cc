// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Painting the Walls
//
// https://leetcode.com/problems/painting-the-walls/
//
// Question ID: 2742
// Difficult  : Hard
// Solve Date : 2023/10/14 13:04

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2742. Painting the Walls|:
//
// You are given two 0-indexed integer arrays, |cost| and |time|, of size |n|
// representing the costs and the time taken to paint |n| different walls
// respectively. There are two painters available:
//
//  • A paid painter that paints the |iᵗʰ| wall in |time[i]| units of time and
//  takes |cost[i]| units of money.
//
//  • A free painter that paints any wall in |1| unit of time at a cost of |0|.
//  But the free painter can only be used if the paid painter is already
//  occupied.
// Return the minimum amount of money required to paint the |n| walls.
//
//

LEETCODE_BEGIN_RESOLVING(2742, PaintingTheWalls, Solution);

class Solution {
public:
  int paintWalls(vector<int> &cost, vector<int> &time) {
    int                 n = cost.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; ++i) {
      dp[n][i] = 1e9;
    }
    for (int i = n - 1; i >= 0; --i) {
      for (int remain = 1; remain <= n; ++remain) {
        int opt1      = cost[i] + dp[i + 1][max(0, remain - 1 - time[i])];
        int opt2      = dp[i + 1][remain];
        dp[i][remain] = min(opt1, opt2);
      }
    }
    return dp[0][n];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= cost.length <= 500|
// * |cost.length == time.length|
// * |1 <= cost[i] <= 10⁶|
// * |1 <= time[i] <= 500|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: cost = [1,2,3,2], time = [1,2,3,2]
// Output: 3
//
// The walls at index 0 and 1 will be painted by the paid painter, and it will
// take 3 units of time; meanwhile, the free painter will paint the walls at
// index 2 and 3, free of cost in 2 units of time. Thus, the total cost is 1 + 2
// = 3.

LEETCODE_SOLUTION_UNITTEST(2742, PaintingTheWalls, example_1) {
  auto        solution = MakeSolution();
  vector<int> cost     = {1, 2, 3, 2};
  vector<int> time     = {1, 2, 3, 2};
  int         expect   = 3;
  int         actual   = solution->paintWalls(cost, time);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: cost = [2,3,4,2], time = [1,1,1,1]
// Output: 4
//
// The walls at index 0 and 3 will be painted by the paid painter, and it will
// take 2 units of time; meanwhile, the free painter will paint the walls at
// index 1 and 2, free of cost in 2 units of time. Thus, the total cost is 2 + 2
// = 4.

LEETCODE_SOLUTION_UNITTEST(2742, PaintingTheWalls, example_2) {
  auto        solution = MakeSolution();
  vector<int> cost     = {2, 3, 4, 2};
  vector<int> time     = {1, 1, 1, 1};
  int         expect   = 4;
  int         actual   = solution->paintWalls(cost, time);
  LCD_EXPECT_EQ(expect, actual);
}
