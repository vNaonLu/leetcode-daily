// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Enclaves
//
// https://leetcode.com/problems/number-of-enclaves/
//
// Question ID: 1020
// Difficult  : Medium
// Solve Date : 2022/02/08 18:33

#include <iosfwd>
#include <stack>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1020. Number of Enclaves|:
//
// You are given an |m x n| binary matrix |grid|, where |0| represents a sea
// cell and |1| represents a land cell. A move consists of walking from one land
// cell to another adjacent (4-directionally) land cell or walking off the
// boundary of the |grid|. Return the number of land cells in |grid| for which
// we cannot walk off the boundary of the grid in any number of moves.  
//

LEETCODE_BEGIN_RESOLVING(1020, NumberOfEnclaves, Solution);

class Solution {
private:
  int               m, n;
  const vector<int> dir = {1, 0, 0, 1, -1, 0, 0, -1};
  bool              isBound(int row, int col) {
    return row == 0 || row == m - 1 || col == 0 || col == n - 1;
  }
  bool isValid(int row, int col) {
    return row >= 0 && row <= m - 1 && col >= 0 && col <= n - 1;
  }
  int walkOff(vector<vector<int>> &grid, int row, int col) {
    stack<pair<int, int>> stk;
    stk.emplace(row, col);
    grid[row][col] = 0;
    int  land_cnt  = 0;
    bool bound     = false;
    while (!stk.empty()) {
      auto [px, py] = stk.top();
      stk.pop();
      ++land_cnt;
      if (isBound(px, py))
        bound = true;
      for (int i = 0; i < dir.size();) {
        int x = px + dir[i++], y = py + dir[i++];
        if (isValid(x, y) && grid[x][y] == 1) {
          grid[x][y] = 0;
          stk.emplace(x, y);
        }
      }
    }
    return bound ? 0 : land_cnt;
  }

public:
  int numEnclaves(vector<vector<int>> &grid) {
    m       = grid.size();
    n       = grid[0].size();
    int res = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) {
          res += walkOff(grid, i, j);
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
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 500|
// * |grid[i][j]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
// Output: 3
//
// There are three 1s that are enclosed by 0s, and one 1 that is not enclosed
// because its on the boundary.

LEETCODE_SOLUTION_UNITTEST(1020, NumberOfEnclaves, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 0, 0, 0},
      {1, 0, 1, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0}
  };
  int expect = 3;
  int actual = solution->numEnclaves(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
// Output: 0
//
// All 1s are either on the boundary or can reach the boundary.

LEETCODE_SOLUTION_UNITTEST(1020, NumberOfEnclaves, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 0}
  };
  int expect = 0;
  int actual = solution->numEnclaves(grid);
  LCD_EXPECT_EQ(expect, actual);
}
