// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Island Perimeter
//
// https://leetcode.com/problems/island-perimeter/
//
// Question ID: 463
// Difficult  : Easy
// Solve Date : 2021/10/04 11:24

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |463. Island Perimeter|:
//
// You are given |row x col| |grid| representing a map where |grid[i][j] = 1|
// represents land and |grid[i][j] = 0| represents water. Grid cells are
// connected horizontally/vertically (not diagonally). The |grid| is completely
// surrounded by water, and there is exactly one island (i.e., one or more
// connected land cells). The island doesn't have "lakes", meaning the water
// inside isn't connected to the water around the island. One cell is a square
// with side length 1. The grid is rectangular, width and height don't exceed
// 100. Determine the perimeter of the island.  
//

LEETCODE_BEGIN_RESOLVING(463, IslandPerimeter, Solution);

class Solution {
private:
  int         m      = 0;
  int         n      = 0;
  vector<int> direct = {1, 0, 0, 1, -1, 0, 0, -1};
  int         helper(vector<vector<int>> &grid, int r, int c) {
    int                   res = 0;
    queue<pair<int, int>> q;
    q.push(make_pair(r, c));
    grid[r][c] = 2;
    while (!q.empty()) {
      auto top = q.front();
      q.pop();
      for (int i = 0; i < direct.size(); ++i) {
        int x = top.first + direct[i];
        int y = top.second + direct[++i];
        if (x >= 0 && x < m && y >= 0 && y < n) {
          if (grid[x][y] == 1) {
            q.push(make_pair(x, y));
            grid[x][y] = 2;
          } else if (grid[x][y] == 0) {
            ++res;
          }
        } else {
          ++res;
        }
      }
    }
    return res;
  }

public:
  int islandPerimeter(vector<vector<int>> &grid) {
    m = grid.size();
    n = grid[0].size();
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) {
          return helper(grid, i, j);
        }
      }
    }
    return 0;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |row == grid.length|
// * |col == grid[i].length|
// * |1 <= row, col <= 100|
// * |grid[i][j]| is |0| or |1|.
// * There is exactly one island in |grid|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
// Output: 16
//
// The perimeter is the 16 yellow stripes in the image above.

LEETCODE_SOLUTION_UNITTEST(463, IslandPerimeter, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1, 0, 0},
      {1, 1, 1, 0},
      {0, 1, 0, 0},
      {1, 1, 0, 0}
  };
  int expect = 16;
  int actual = solution->islandPerimeter(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(463, IslandPerimeter, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {{1}};
  int                 expect   = 4;
  int                 actual   = solution->islandPerimeter(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,0]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(463, IslandPerimeter, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0}
  };
  int expect = 4;
  int actual = solution->islandPerimeter(grid);
  LCD_EXPECT_EQ(expect, actual);
}
