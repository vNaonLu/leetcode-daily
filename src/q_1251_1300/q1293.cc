// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shortest Path in a Grid with Obstacles Elimination
//
// https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/
//
// Question ID: 1293
// Difficult  : Hard
// Solve Date : 2021/09/25 15:43

#include <iosfwd>
#include <limits>
#include <map>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1293. Shortest Path in a Grid with Obstacles Elimination|:
//
// You are given an |m x n| integer matrix |grid| where each cell is either |0|
// (empty) or |1| (obstacle). You can move up, down, left, or right from and to
// an empty cell in one step. Return the minimum number of steps to walk from
// the upper left corner |(0, 0)| to the lower right corner |(m - 1, n - 1)|
// given that you can eliminate at most |k| obstacles. If it is not possible to
// find such walk return |-1|.  
//

LEETCODE_BEGIN_RESOLVING(1293, ShortestPathInAGridWithObstaclesElimination,
                         Solution);

class Solution {
private:
  vector<int> direct = {1, 0, 0, 1, -1, 0, 0, -1};

public:
  int shortestPath(vector<vector<int>> &grid, int k) {
    int                 m = grid.size(), n = grid[0].size();
    vector<vector<int>> eliminated_map(
        m, vector<int>(n, numeric_limits<int>::max()));
    queue<pair<int, int>> q;
    q.push({0, 0});
    eliminated_map[0][0] = grid[0][0];
    int dist             = 0;
    while (!q.empty()) {
      int level_size = q.size() + 1;
      while (--level_size) {
        auto cp = q.front();
        q.pop();
        if (cp.first == m - 1 && cp.second == n - 1)
          return dist;
        for (int i = 0; i < direct.size(); ++i) {
          int dx = cp.first + direct[i++];
          int dy = cp.second + direct[i];
          if (dx >= 0 && dx < m && dy >= 0 && dy < n &&
              eliminated_map[cp.first][cp.second] + grid[dx][dy] <= k &&
              eliminated_map[cp.first][cp.second] + grid[dx][dy] <
                  eliminated_map[dx][dy]) {
            eliminated_map[dx][dy] =
                eliminated_map[cp.first][cp.second] + grid[dx][dy];
            q.emplace(dx, dy);
          }
        }
      }
      ++dist;
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 40|
// * |1 <= k <= m * n|
// * |grid[i][j]| is either |0| or |1|.
// * |grid[0][0] == grid[m - 1][n - 1] == 0|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0,0,0],[1,1,0],[0,0,0],[0,1,1],[0,0,0]], k = 1
// Output: 6
//
// The shortest path without eliminating any obstacle is 10.
// The shortest path with one obstacle elimination at position (3,2) is 6. Such
// path is (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).

LEETCODE_SOLUTION_UNITTEST(1293, ShortestPathInAGridWithObstaclesElimination,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 0, 0},
      {1, 1, 0},
      {0, 0, 0},
      {0, 1, 1},
      {0, 0, 0}
  };
  int k      = 1;
  int expect = 6;
  int actual = solution->shortestPath(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[0,1,1],[1,1,1],[1,0,0]], k = 1
// Output: -1
//
// We need to eliminate at least two obstacles to find such a walk.

LEETCODE_SOLUTION_UNITTEST(1293, ShortestPathInAGridWithObstaclesElimination,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1, 1},
      {1, 1, 1},
      {1, 0, 0}
  };
  int k      = 1;
  int expect = -1;
  int actual = solution->shortestPath(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}
