// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Increasing Paths in a Grid
//
// https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/
//
// Question ID: 2328
// Difficult  : Hard
// Solve Date : 2023/06/18 14:58

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2328. Number of Increasing Paths in a Grid|:
//
// You are given an |m x n| integer matrix |grid|, where you can move from a
// cell to any adjacent cell in all |4| directions. Return the number of
// strictly increasing paths in the grid such that you can start from any cell
// and end at any cell. Since the answer may be very large, return it modulo
// |10⁹ + 7|. Two paths are considered different if they do not have exactly the
// same sequence of visited cells.
//
//

LEETCODE_BEGIN_RESOLVING(2328, NumberOfIncreasingPathsInAGrid, Solution);

class Solution {
public:
  int countPaths(vector<vector<int>> &grid) {
    vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(), -1));
    int64_t             res = 0;
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid[0].size(); ++j) {
        res = (res + dfs(i, j, grid, dp)) % kMod;
      }
    }
    return res;
  }

private:
  constexpr static int kMod = 1e9 + 7;
  const vector<int>    dir  = {1, 0, 0, 1, -1, 0, 0, -1};

  bool isValid(vector<vector<int>> &grid, int i, int j) {
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) {
      return false;
    }
    return true;
  }

  int dfs(int r, int c, vector<vector<int>> &grid, vector<vector<int>> &dp) {
    if (dp[r][c] != -1) {
      return dp[r][c];
    }
    int res = 1;
    for (int i = 0; i < dir.size(); ++i) {
      int dr = r + dir[i++];
      int dc = c + dir[i];
      if (isValid(grid, dr, dc) && grid[dr][dc] > grid[r][c]) {
        res = (res + dfs(dr, dc, grid, dp)) % kMod;
      }
    }
    return dp[r][c] = res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 1000|
// * |1 <= m * n <= 10⁵|
// * |1 <= grid[i][j] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,1],[3,4]]
// Output: 8
//
// The strictly increasing paths are:
// - Paths with length 1: [1], [1], [3], [4].
// - Paths with length 2: [1 -> 3], [1 -> 4], [3 -> 4].
// - Paths with length 3: [1 -> 3 -> 4].
// The total number of paths is 4 + 3 + 1 = 8.

LEETCODE_SOLUTION_UNITTEST(2328, NumberOfIncreasingPathsInAGrid, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1},
      {3, 4}
  };
  int expect = 8;
  int actual = solution->countPaths(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1],[2]]
// Output: 3
//
// The strictly increasing paths are:
// - Paths with length 1: [1], [2].
// - Paths with length 2: [1 -> 2].
// The total number of paths is 2 + 1 = 3.

LEETCODE_SOLUTION_UNITTEST(2328, NumberOfIncreasingPathsInAGrid, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {{1}, {2}};
  int                 expect   = 3;
  int                 actual   = solution->countPaths(grid);
  LCD_EXPECT_EQ(expect, actual);
}
