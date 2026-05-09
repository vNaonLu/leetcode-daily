// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Maximum Path Score in a Grid
//
// https://leetcode.com/problems/maximum-path-score-in-a-grid/
//
// Question ID: 3742
// Difficult  : Medium
// Solve Date : 2026/04/30 19:05

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3742. Maximum Path Score in a Grid|:
//
// You are given an |m x n| grid where each cell contains one of the values 0,
// 1, or 2. You are also given an integer |k|. You start from the top-left
// corner |(0, 0)| and want to reach the bottom-right corner |(m - 1, n - 1)| by
// moving only right or down. Each cell contributes a specific score and incurs
// an associated cost, according to their cell values:
//
//  • 0: adds 0 to your score and costs 0.
//
//  • 1: adds 1 to your score and costs 1.
//
//  • 2: adds 2 to your score and costs 1. ​​​​​​​
// Return the maximum score achievable without exceeding a total cost of |k|, or
// -1 if no valid path exists. Note: If you reach the last cell but the total
// cost exceeds |k|, the path is invalid.
//
//

LEETCODE_BEGIN_RESOLVING(3742, MaximumPathScoreInAGrid, Solution);

class Solution {
public:
  int maxPathScore(vector<vector<int>> &grid, int k) {
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<vector<int>>> dp(
        m, vector<vector<int>>(n, vector<int>(k + 1, -1)));

    dp[0][0][0] = 0;

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {

        for (int c = 0; c <= k; c++) {

          if (dp[i][j][c] == -1)
            continue;

          if (i + 1 < m) {
            int val  = grid[i + 1][j];
            int cost = (val == 0 ? 0 : 1);

            int nc = c + cost;
            if (nc <= k) {
              dp[i + 1][j][nc] = max(dp[i + 1][j][nc], dp[i][j][c] + val);
            }
          }

          if (j + 1 < n) {
            int val  = grid[i][j + 1];
            int cost = (val == 0 ? 0 : 1);

            int nc = c + cost;
            if (nc <= k) {
              dp[i][j + 1][nc] = max(dp[i][j + 1][nc], dp[i][j][c] + val);
            }
          }
        }
      }
    }

    int ans = -1;
    for (int c = 0; c <= k; c++) {
      ans = max(ans, dp[m - 1][n - 1][c]);
    }

    return ans;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= m, n <= 200|
// * |0 <= k <= 10³​​​​​​​|
// * |^{​​​​​​​}grid[0][0] == 0|
// * |0 <= grid[i][j] <= 2|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0, 1],[2, 0]], k = 1
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3742, MaximumPathScoreInAGrid, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1},
      {2, 0}
  };
  int k      = 1;
  int expect = 2;
  int actual = solution->maxPathScore(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[0, 1],[1, 2]], k = 1
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(3742, MaximumPathScoreInAGrid, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1},
      {1, 2}
  };
  int k      = 1;
  int expect = -1;
  int actual = solution->maxPathScore(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}
