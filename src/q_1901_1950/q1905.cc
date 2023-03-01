// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Sub Islands
//
// https://leetcode.com/problems/count-sub-islands/
//
// Question ID: 1905
// Difficult  : Medium
// Solve Date : 2022/03/12 14:08

#include <array>
#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1905. Count Sub Islands|:
//
// You are given two |m x n| binary matrices |grid1| and |grid2| containing only
// |0|'s (representing water) and |1|'s (representing land). An island is a
// group of |1|'s connected 4-directionally (horizontal or vertical). Any cells
// outside of the grid are considered water cells. An island in |grid2| is
// considered a sub-island if there is an island in |grid1| that contains all
// the cells that make up this island in |grid2|. Return the number of islands
// in |grid2| that are considered sub-islands.  
//

LEETCODE_BEGIN_RESOLVING(1905, CountSubIslands, Solution);

class Solution {
private:
  vector<vector<int>> g1, g2;
  int                 m, n;
  array<int, 8>       dir = {1, 0, 0, 1, -1, 0, 0, -1};
  inline bool         is_valid(int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n;
  }
  inline bool helper(int i, int j) {
    queue<pair<int, int>> q;
    bool                  res = true;
    q.emplace(i, j);
    while (!q.empty()) {
      auto [x, y] = q.front();
      q.pop();
      for (int i = 0; i < dir.size(); ++i) {
        auto dx = x + dir[i], dy = y + dir[++i];
        if (is_valid(dx, dy) && g2[dx][dy] == 1) {
          res &= g1[dx][dy] == 1;
          g2[dx][dy] = 0;
          q.emplace(dx, dy);
        }
      }
    }

    return res;
  }

public:
  int countSubIslands(vector<vector<int>> &grid1, vector<vector<int>> &grid2) {
    int res = 0;
    m       = grid1.size();
    n       = grid1[0].size();
    g1      = move(grid1);
    g2      = move(grid2);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (g2[i][j] == 1) {
          g2[i][j] = 0;
          if (helper(i, j) && g1[i][j] == 1) {
            ++res;
          }
        }
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == grid1.length == grid2.length|
// * |n == grid1[i].length == grid2[i].length|
// * |1 <= m, n <= 500|
// * |grid1[i][j]| and |grid2[i][j]| are either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid1 =
//  [[1,1,1,0,0],[0,1,1,1,1],[0,0,0,0,0],[1,0,0,0,0],[1,1,0,1,1]], grid2 =
//  [[1,1,1,0,0],[0,0,1,1,1],[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0]]
// Output: 3
//
// In the picture above, the grid on the left is grid1 and the grid on the right
// is grid2. The 1s colored red in grid2 are those considered to be part of a
// sub-island. There are three sub-islands.

LEETCODE_SOLUTION_UNITTEST(1905, CountSubIslands, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid1    = {
      {1, 1, 1, 0, 0},
      {0, 1, 1, 1, 1},
      {0, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 1, 0, 1, 1}
  };
  vector<vector<int>> grid2 = {
      {1, 1, 1, 0, 0},
      {0, 0, 1, 1, 1},
      {0, 1, 0, 0, 0},
      {1, 0, 1, 1, 0},
      {0, 1, 0, 1, 0}
  };
  int expect = 3;
  int actual = solution->countSubIslands(grid1, grid2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid1 =
//  [[1,0,1,0,1],[1,1,1,1,1],[0,0,0,0,0],[1,1,1,1,1],[1,0,1,0,1]], grid2 =
//  [[0,0,0,0,0],[1,1,1,1,1],[0,1,0,1,0],[0,1,0,1,0],[1,0,0,0,1]]
// Output: 2
//
// In the picture above, the grid on the left is grid1 and the grid on the right
// is grid2. The 1s colored red in grid2 are those considered to be part of a
// sub-island. There are two sub-islands.

LEETCODE_SOLUTION_UNITTEST(1905, CountSubIslands, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid1    = {
      {1, 0, 1, 0, 1},
      {1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1},
      {1, 0, 1, 0, 1}
  };
  vector<vector<int>> grid2 = {
      {0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1},
      {0, 1, 0, 1, 0},
      {0, 1, 0, 1, 0},
      {1, 0, 0, 0, 1}
  };
  int expect = 2;
  int actual = solution->countSubIslands(grid1, grid2);
  LCD_EXPECT_EQ(expect, actual);
}
