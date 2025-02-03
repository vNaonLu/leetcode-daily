// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Number of Fish in a Grid
//
// https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/
//
// Question ID: 2658
// Difficult  : Medium
// Solve Date : 2025/01/28 10:43

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2658. Maximum Number of Fish in a Grid|:
//
// You are given a 0-indexed 2D matrix |grid| of size |m x n|, where |(r, c)|
// represents:
//
//  • A land cell if |grid[r][c] = 0|, or
//
//  • A water cell containing |grid[r][c]| fish, if |grid[r][c] > 0|.
// A fisher can start at any water cell |(r, c)| and can do the following
// operations any number of times:
//
//  • Catch all the fish at cell |(r, c)|, or
//
//  • Move to any adjacent water cell.
// Return the maximum number of fish the fisher can catch if he chooses his
// starting cell optimally, or |0| if no water cell exists. An adjacent cell of
// the cell |(r, c)|, is one of the cells |(r, c + 1)|, |(r, c - 1)|, |(r + 1,
// c)| or |(r - 1, c)| if it exists.
//
//

LEETCODE_BEGIN_RESOLVING(2658, MaximumNumberOfFishInAGrid, Solution);

class Solution {
public:
  int findMaxFish(vector<vector<int>> &grid) {
    int                  m   = grid.size();
    int                  n   = grid[0].size();
    int                  res = 0;
    vector<vector<bool>> vis(m, vector<bool>(n, false));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] > 0 && !vis[i][j]) {
          res = max(res, calc(grid, &vis, i, j));
        }
      }
    }
    return res;
  }

private:
  int calc(vector<vector<int>> const &grid, vector<vector<bool>> *vis, int r,
           int c) {
    if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size() ||
        grid[r][c] == 0 || (*vis)[r][c]) {
      return 0;
    }

    (*vis)[r][c] = true;
    return grid[r][c] + calc(grid, vis, r, c + 1) + calc(grid, vis, r, c - 1) +
           calc(grid, vis, r + 1, c) + calc(grid, vis, r - 1, c);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 10|
// * |0 <= grid[i][j] <= 10|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0,2,1,0],[4,0,0,3],[1,0,0,4],[0,3,2,0]]
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(2658, MaximumNumberOfFishInAGrid, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 2, 1, 0},
      {4, 0, 0, 3},
      {1, 0, 0, 4},
      {0, 3, 2, 0}
  };
  int expect = 7;
  int actual = solution->findMaxFish(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,1]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2658, MaximumNumberOfFishInAGrid, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 1}
  };
  int expect = 1;
  int actual = solution->findMaxFish(grid);
  LCD_EXPECT_EQ(expect, actual);
}
