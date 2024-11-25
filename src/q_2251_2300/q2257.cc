// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Count Unguarded Cells in the Grid
//
// https://leetcode.com/problems/count-unguarded-cells-in-the-grid/
//
// Question ID: 2257
// Difficult  : Medium
// Solve Date : 2024/11/21 19:42

#include <iosfwd>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2257. Count Unguarded Cells in the Grid|:
//
// You are given two integers |m| and |n| representing a 0-indexed |m x n| grid.
// You are also given two 2D integer arrays |guards| and |walls| where
// |guards[i] = [rowᵢ, colᵢ]| and |walls[j] = [rowⱼ, colⱼ]| represent the
// positions of the |iᵗʰ| guard and |jᵗʰ| wall respectively. A guard can see
// every cell in the four cardinal directions (north, east, south, or west)
// starting from their position unless obstructed by a wall or another guard. A
// cell is guarded if there is at least one guard that can see it. Return the
// number of unoccupied cells that are not guarded.
//
//

LEETCODE_BEGIN_RESOLVING(2257, CountUnguardedCellsInTheGrid, Solution);

class Solution {
public:
  int countUnguarded(int m, int n, vector<vector<int>> &guards,
                     vector<vector<int>> &walls) {
    vector<vector<int>> g(m, vector<int>(n, 0));
    for (auto &v : walls) {
      g[v[0]][v[1]] = 2;
    }
    for (auto &v : guards) {
      g[v[0]][v[1]] = 2;
    }
    vector<int> dirs{-1, 0, 1, 0, -1};

    for (auto &v : guards) {
      for (int k = 0; k < 4; ++k) {
        int x  = v[0];
        int y  = v[1];
        int dx = dirs[k];
        int dy = dirs[k + 1];
        while (x + dx >= 0 && x + dx < m && y + dy >= 0 && y + dy < n &&
               g[x + dx][y + dy] < 2) {
          x += dx;
          y += dy;
          g[x][y] = 1;
        }
      }
    }

    int res = 0;
    for (int i = 0; i < m; ++i) {
      res += count(g[i].begin(), g[i].end(), 0);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= m, n <= 10⁵|
// * |2 <= m * n <= 10⁵|
// * |1 <= guards.length, walls.length <= 5 * 10⁴|
// * |2 <= guards.length + walls.length <= m * n|
// * |guards[i].length == walls[j].length == 2|
// * |0 <= rowᵢ, rowⱼ < m|
// * |0 <= colᵢ, colⱼ < n|
// * All the positions in |guards| and |walls| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: m = 4, n = 6, guards = [[0,0],[1,1],[2,3]], walls =
//  [[0,1],[2,2],[1,4]]
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(2257, CountUnguardedCellsInTheGrid, example_1) {
  auto                solution = MakeSolution();
  int                 m        = 4;
  int                 n        = 6;
  vector<vector<int>> guards   = {
      {0, 0},
      {1, 1},
      {2, 3}
  };
  vector<vector<int>> walls = {
      {0, 1},
      {2, 2},
      {1, 4}
  };
  int expect = 7;
  int actual = solution->countUnguarded(m, n, guards, walls);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: m = 3, n = 3, guards = [[1,1]], walls = [[0,1],[1,0],[2,1],[1,2]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2257, CountUnguardedCellsInTheGrid, example_2) {
  auto                solution = MakeSolution();
  int                 m        = 3;
  int                 n        = 3;
  vector<vector<int>> guards   = {
      {1, 1}
  };
  vector<vector<int>> walls = {
      {0, 1},
      {1, 0},
      {2, 1},
      {1, 2}
  };
  int expect = 4;
  int actual = solution->countUnguarded(m, n, guards, walls);
  LCD_EXPECT_EQ(expect, actual);
}
