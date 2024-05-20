// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Path with Maximum Gold
//
// https://leetcode.com/problems/path-with-maximum-gold/
//
// Question ID: 1219
// Difficult  : Medium
// Solve Date : 2024/05/14 23:28

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1219. Path with Maximum Gold|:
//
// In a gold mine |grid| of size |m x n|, each cell in this mine has an integer
// representing the amount of gold in that cell, |0| if it is empty. Return the
// maximum amount of gold you can collect under the conditions:
//
//  • Every time you are located in a cell you will collect all the gold in that
//  cell.
//
//  • From your position, you can walk one step to the left, right, up, or down.
//
//  • You can't visit the same cell more than once.
//
//  • Never visit a cell with |0| gold.
//
//  • You can start and stop collecting gold from any position in the grid that
//  has some gold.
//
//

LEETCODE_BEGIN_RESOLVING(1219, PathWithMaximumGold, Solution);

class Solution {
public:
  int getMaximumGold(vector<vector<int>> &grid) {
    int res = 0;
    int m   = grid.size();
    int n   = grid[0].size();

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] != 0) {
          res = max(res, dfs(&grid, i, j, m, n));
        }
      }
    }

    return res;
  }

private:
  int dfs(vector<vector<int>> *grid, int x, int y, int m, int n) {
    if (x < 0 || x >= m || y < 0 || y >= n || (*grid)[x][y] == 0) {
      return 0;
    }

    static vector<int> const dir  = {1, 0, -1, 0, 0, -1, 0, 1};
    int                      curr = (*grid)[x][y];
    (*grid)[x][y]                 = 0;
    int local                     = curr;

    for (int i = 0; i < dir.size();) {
      int dx = x + dir[i++];
      int dy = y + dir[i++];
      local  = max(local, curr + dfs(grid, dx, dy, m, n));
    }

    (*grid)[x][y] = curr;
    return local;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 15|
// * |0 <= grid[i][j] <= 100|
// * There are at most 25 cells containing gold.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
// Output: 24
//

LEETCODE_SOLUTION_UNITTEST(1219, PathWithMaximumGold, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 6, 0},
      {5, 8, 7},
      {0, 9, 0}
  };
  int expect = 24;
  int actual = solution->getMaximumGold(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
// Output: 28
//

LEETCODE_SOLUTION_UNITTEST(1219, PathWithMaximumGold, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0,  7},
      {2, 0,  6},
      {3, 4,  5},
      {0, 3,  0},
      {9, 0, 20}
  };
  int expect = 28;
  int actual = solution->getMaximumGold(grid);
  LCD_EXPECT_EQ(expect, actual);
}
