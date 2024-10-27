// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Coloring A Border
//
// https://leetcode.com/problems/coloring-a-border/
//
// Question ID: 1034
// Difficult  : Medium
// Solve Date : 2024/10/08 21:58

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1034. Coloring A Border|:
//
// You are given an |m x n| integer matrix |grid|, and three integers |row|,
// |col|, and |color|. Each value in the grid represents the color of the grid
// square at that location. Two squares are called adjacent if they are next to
// each other in any of the 4 directions. Two squares belong to the same
// connected component if they have the same color and they are adjacent. The
// border of a connected component is all the squares in the connected component
// that are either adjacent to (at least) a square not in the component, or on
// the boundary of the grid (the first or last row or column). You should color
// the border of the connected component that contains the square
// |grid[row][col]| with |color|. Return the final grid.
//
//

LEETCODE_BEGIN_RESOLVING(1034, ColoringABorder, Solution);

class Solution {
public:
  vector<vector<int>> colorBorder(vector<vector<int>> &grid, int row, int col,
                                  int color) {
    if (grid[row][col] == color) {
      return grid;
    }

    int                 m = grid.size();
    int                 n = grid[0].size();
    vector<vector<int>> vis(m, vector<int>(n, 0));
    dfs(&grid, &vis, grid[row][col], color, row, col);
    return grid;
  }

private:
  void dfs(vector<vector<int>> *grid, vector<vector<int>> *vis, int cur,
           int color, int i, int j) {
    if (i < 0 || i >= grid->size() || j < 0 || j >= (*grid)[0].size() ||
        (*grid)[i][j] != cur || (*vis)[i][j]) {
      return;
    }

    (*vis)[i][j] = 1;

    vector<int> dir{-1, 0, 1, 0, -1};
    for (int k = 0; k < 4; ++k) {
      int x = i + dir[k];
      int y = j + dir[k + 1];
      if (x < 0 || x >= grid->size() || y < 0 || y >= (*grid)[0].size() ||
          ((*grid)[x][y] != cur && !(*vis)[x][y])) {
        (*grid)[i][j] = color;
      }

      dfs(grid, vis, cur, color, x, y);
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 50|
// * |1 <= grid[i][j], color <= 1000|
// * |0 <= row < m|
// * |0 <= col < n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,1],[1,2]], row = 0, col = 0, color = 3
// Output: [[3,3],[3,2]]
//

LEETCODE_SOLUTION_UNITTEST(1034, ColoringABorder, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1},
      {1, 2}
  };
  int                 row    = 0;
  int                 col    = 0;
  int                 color  = 3;
  vector<vector<int>> expect = {
      {3, 3},
      {3, 2}
  };
  vector<vector<int>> actual = solution->colorBorder(grid, row, col, color);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,2,2],[2,3,2]], row = 0, col = 1, color = 3
// Output: [[1,3,3],[2,3,3]]
//

LEETCODE_SOLUTION_UNITTEST(1034, ColoringABorder, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2, 2},
      {2, 3, 2}
  };
  int                 row    = 0;
  int                 col    = 1;
  int                 color  = 3;
  vector<vector<int>> expect = {
      {1, 3, 3},
      {2, 3, 3}
  };
  vector<vector<int>> actual = solution->colorBorder(grid, row, col, color);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,1,1],[1,1,1],[1,1,1]], row = 1, col = 1, color = 2
// Output: [[2,2,2],[2,1,2],[2,2,2]]
//

LEETCODE_SOLUTION_UNITTEST(1034, ColoringABorder, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1, 1},
      {1, 1, 1},
      {1, 1, 1}
  };
  int                 row    = 1;
  int                 col    = 1;
  int                 color  = 2;
  vector<vector<int>> expect = {
      {2, 2, 2},
      {2, 1, 2},
      {2, 2, 2}
  };
  vector<vector<int>> actual = solution->colorBorder(grid, row, col, color);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [[1,2,1,2,1,2],[2,2,2,2,1,2],[1,2,2,2,1,2]]
// 1
// 3
// 1
// Output: [[1,1,1,1,1,2],[1,2,1,1,1,2],[1,1,1,1,1,2]]
//

LEETCODE_SOLUTION_UNITTEST(1034, ColoringABorder, extra_testcase_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2, 1, 2, 1, 2},
      {2, 2, 2, 2, 1, 2},
      {1, 2, 2, 2, 1, 2}
  };
  int                 row    = 1;
  int                 col    = 3;
  int                 color  = 1;
  vector<vector<int>> expect = {
      {1, 1, 1, 1, 1, 2},
      {1, 2, 1, 1, 1, 2},
      {1, 1, 1, 1, 1, 2}
  };
  vector<vector<int>> actual = solution->colorBorder(grid, row, col, color);
  LCD_EXPECT_EQ(expect, actual);
}
