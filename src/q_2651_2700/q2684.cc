// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Number of Moves in a Grid
//
// https://leetcode.com/problems/maximum-number-of-moves-in-a-grid/
//
// Question ID: 2684
// Difficult  : Medium
// Solve Date : 2024/10/29 19:24

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2684. Maximum Number of Moves in a Grid|:
//
// You are given a 0-indexed |m x n| matrix |grid| consisting of positive
// integers. You can start at any cell in the first column of the matrix, and
// traverse the grid in the following way:
//
//  • From a cell |(row, col)|, you can move to any of the cells: |(row - 1, col
//  + 1)|, |(row, col + 1)| and |(row + 1, col + 1)| such that the value of the
//  cell you move to, should be strictly bigger than the value of the current
//  cell.
// Return the maximum number of moves that you can perform.
//
//

LEETCODE_BEGIN_RESOLVING(2684, MaximumNumberOfMovesInAGrid, Solution);

class Solution {
public:
  int maxMoves(vector<vector<int>> &grid) {
    int                 m = grid.size();
    int                 n = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, -1));
    int                 res = 0;
    for (int i = 0; i < m; ++i) {
      if (res == n) {
        break;
      }
      res = max(res, f(i, 0, -1, grid, &dp));
    }
    return res - 1;
  }

private:
  int f(int i, int j, int prev, vector<vector<int>> const &grid,
        vector<vector<int>> *dp) {
    if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size()) {
      return 0;
    }
    int x = grid[i][j];
    if (x <= prev) {
      return 0;
    }

    if ((*dp)[i][j] != -1) {
      return (*dp)[i][j];
    }

    int res = 1 + f(i - 1, j + 1, x, grid, dp);
    for (int k = i; k <= i + 1; ++k) {
      if (res == grid[0].size() - j) {
        break;
      }
      res = max(res, 1 + f(k, j + 1, x, grid, dp));
    }
    return (*dp)[i][j] = res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |2 <= m, n <= 1000|
// * |4 <= m * n <= 10⁵|
// * |1 <= grid[i][j] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2684, MaximumNumberOfMovesInAGrid, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      { 2, 4,  3,  5},
      { 5, 4,  9,  3},
      { 3, 4,  2, 11},
      {10, 9, 13, 15}
  };
  int expect = 3;
  int actual = solution->maxMoves(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[3,2,4],[2,1,9],[1,1,7]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2684, MaximumNumberOfMovesInAGrid, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {3, 2, 4},
      {2, 1, 9},
      {1, 1, 7}
  };
  int expect = 0;
  int actual = solution->maxMoves(grid);
  LCD_EXPECT_EQ(expect, actual);
}
