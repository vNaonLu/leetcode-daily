// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Closed Islands
//
// https://leetcode.com/problems/number-of-closed-islands/
//
// Question ID: 1254
// Difficult  : Medium
// Solve Date : 2021/11/04 18:09

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1254. Number of Closed Islands|:
//
// Given a 2D  |grid| consists of |0s| (land) and |1s| (water).  An island is a
// maximal 4-directionally connected group of |0s| and a closed island is an
// island totally (all left, top, right, bottom) surrounded by |1s.| Return the
// number of closed islands.  
//

LEETCODE_BEGIN_RESOLVING(1254, NumberOfClosedIslands, Solution);

class Solution {
private:
  vector<int> direct = {0, 1, 1, 0, 0, -1, -1, 0};

public:
  int closedIsland(vector<vector<int>> &grid) {
    int m = grid.size(), n = grid[0].size();
    int res = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 0) {
          bool                  surround = true;
          queue<pair<int, int>> q;
          grid[i][j] = 1;
          q.emplace(i, j);
          while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            for (int d = 0; d < direct.size(); ++d) {
              int x = cur.first + direct[d];
              int y = cur.second + direct[++d];
              if (x < 0 || x >= m || y < 0 || y >= n) {
                surround = false;
                continue;
              }
              if (grid[x][y] == 0) {
                grid[x][y] = 1;
                q.emplace(x, y);
              }
            }
          }
          if (surround)
            ++res;
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
// * |1 <= grid.length, grid[0].length <= 100|
// * |0 <= grid[i][j] <=1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid =
//  [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
// Output: 2
//
// Islands in gray are closed because they are completely surrounded by water
// (group of 1s).

LEETCODE_SOLUTION_UNITTEST(1254, NumberOfClosedIslands, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1, 1, 1, 1, 1, 1, 0},
      {1, 0, 0, 0, 0, 1, 1, 0},
      {1, 0, 1, 0, 1, 1, 1, 0},
      {1, 0, 0, 0, 0, 1, 0, 1},
      {1, 1, 1, 1, 1, 1, 1, 0}
  };
  int expect = 2;
  int actual = solution->closedIsland(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1254, NumberOfClosedIslands, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 0, 1, 0, 0},
      {0, 1, 0, 1, 0},
      {0, 1, 1, 1, 0}
  };
  int expect = 1;
  int actual = solution->closedIsland(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,1,1,1,1,1,1],
//   [1,0,0,0,0,0,1],
//   [1,0,1,1,1,0,1],
//   [1,0,1,0,1,0,1],
//   [1,0,1,1,1,0,1],
//   [1,0,0,0,0,0,1],
//  [1,1,1,1,1,1,1]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1254, NumberOfClosedIslands, example_3) {
  GTEST_SKIP() << "Unittest Not Implemented";
}
