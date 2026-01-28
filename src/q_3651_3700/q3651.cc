// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimum Cost Path with Teleportations
//
// https://leetcode.com/problems/minimum-cost-path-with-teleportations/
//
// Question ID: 3651
// Difficult  : Hard
// Solve Date : 2026/01/28 18:46

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3651. Minimum Cost Path with Teleportations|:
//
// You are given a |m x n| 2D integer array |grid| and an integer |k|. You start
// at the top-left cell |(0, 0)| and your goal is to reach the bottom‐right cell
// |(m - 1, n - 1)|. There are two types of moves available:
//
//  •
// 	Normal move: You can move right or down from your current cell |(i, j)|,
// i.e. you can move to |(i, j + 1)| (right) or |(i + 1, j)| (down). The cost is
// the value of the destination cell.
//
//
//  •
// 	Teleportation: You can teleport from any cell |(i, j)|, to any cell |(x,
// y)| such that |grid[x][y] <= grid[i][j]|; the cost of this move is 0. You may
// teleport at most |k| times.
//
// Return the minimum total cost to reach cell |(m - 1, n - 1)| from |(0, 0)|.
//
//

LEETCODE_BEGIN_RESOLVING(3651, MinimumCostPathWithTeleportations, Solution);

class Solution {
public:
  int minCost(vector<vector<int>> &grid, int k) {
    int                            m       = grid.size();
    int                            n       = grid[0].size();
    const int                      INF     = 1e9;
    const int                      MAX_VAL = 10000;
    vector<vector<pair<int, int>>> val_to_coords(MAX_VAL + 1);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        val_to_coords[grid[i][j]].push_back({i, j});
      }
    }
    vector<vector<vector<int>>> dist(
        k + 1, vector<vector<int>>(m, vector<int>(n, INF)));

    dist[0][0][0] = 0;

    for (int t = 0; t <= k; ++t) {
      priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
          if (dist[t][i][j] != INF) {
            pq.push({dist[t][i][j], i * n + j});
          }
        }
      }

      while (!pq.empty()) {
        auto [d, pos] = pq.top();
        pq.pop();

        int r = pos / n;
        int c = pos % n;
        if (d > dist[t][r][c])
          continue;

        int dr[2] = {0, 1};
        int dc[2] = {1, 0};

        for (int i = 0; i < 2; ++i) {
          int nr = r + dr[i];
          int nc = c + dc[i];
          if (nr < m && nc < n) {
            if (dist[t][nr][nc] > d + grid[nr][nc]) {
              dist[t][nr][nc] = d + grid[nr][nc];
              pq.push({dist[t][nr][nc], nr * n + nc});
            }
          }
        }
      }
      if (t < k) {
        vector<int> min_cost_at_val(MAX_VAL + 1, INF);
        for (int i = 0; i < m; ++i) {
          for (int j = 0; j < n; ++j) {
            min_cost_at_val[grid[i][j]] =
                min(min_cost_at_val[grid[i][j]], dist[t][i][j]);
          }
        }

        vector<int> suffix_min(MAX_VAL + 2, INF);
        for (int v = MAX_VAL; v >= 0; --v) {
          suffix_min[v] = min(suffix_min[v + 1], min_cost_at_val[v]);
        }

        for (int v = 0; v <= MAX_VAL; ++v) {
          if (suffix_min[v] == INF)
            continue;
          for (auto &[r, c] : val_to_coords[v]) {
            dist[t + 1][r][c] = min(dist[t + 1][r][c], suffix_min[v]);
          }
        }
      }
    }

    int ans = INF;
    for (int t = 0; t <= k; ++t) {
      ans = min(ans, dist[t][m - 1][n - 1]);
    }

    return ans >= INF ? -1 : ans;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= m, n <= 80|
// * |m == grid.length|
// * |n == grid[i].length|
// * |0 <= grid[i][j] <= 10⁴|
// * |0 <= k <= 10|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,3,3],[2,5,4],[4,3,5]], k = 2
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(3651, MinimumCostPathWithTeleportations, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 3, 3},
      {2, 5, 4},
      {4, 3, 5}
  };
  int k      = 2;
  int expect = 7;
  int actual = solution->minCost(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,2],[2,3],[3,4]], k = 1
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(3651, MinimumCostPathWithTeleportations, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2},
      {2, 3},
      {3, 4}
  };
  int k      = 1;
  int expect = 9;
  int actual = solution->minCost(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}
