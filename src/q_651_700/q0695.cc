// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Max Area of Island
//
// https://leetcode.com/problems/max-area-of-island/
//
// Question ID: 695
// Difficult  : Medium
// Solve Date : 2021/09/11 08:00

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |695. Max Area of Island|:
//
// You are given an |m x n| binary matrix |grid|. An island is a group of |1|'s
// (representing land) connected 4-directionally (horizontal or vertical.) You
// may assume all four edges of the grid are surrounded by water. The area of an
// island is the number of cells with a value |1| in the island. Return the
// maximum area of an island in |grid|. If there is no island, return |0|.  
//

LEETCODE_BEGIN_RESOLVING(695, MaxAreaOfIsland, Solution);

class Solution {
private:
  int                    m, n;
  vector<pair<int, int>> dir = {
      { 1,  0},
      {-1,  0},
      { 0,  1},
      { 0, -1}
  };
  int findLand(vector<vector<int>> &grid, queue<pair<int, int>> q) {
    int res = 0;
    while (!q.empty()) {
      pair<int, int> p = q.front();
      q.pop();
      res++;
      for (int i = 0; i < 4; ++i) {
        pair<int, int> newp = {p.first + dir[i].first,
                               p.second + dir[i].second};
        if (newp.first >= 0 && newp.first < m && newp.second >= 0 &&
            newp.second < n && grid[newp.first][newp.second] != 0) {
          grid[newp.first][newp.second] = 0;
          q.push(newp);
        }
      }
    }
    return res;
  }

public:
  int maxAreaOfIsland(vector<vector<int>> &grid) {
    m       = grid.size();
    n       = grid[0].size();
    int res = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) {
          queue<pair<int, int>> q;
          q.push({i, j});
          grid[i][j] = 0;
          res        = max(res, findLand(grid, q));
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
// * |1 <= m, n <= 50|
// * |grid[i][j]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid =
//  [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
// Output: 6
//
// The answer is not 11, because the island must be connected 4-directionally.

LEETCODE_SOLUTION_UNITTEST(695, MaxAreaOfIsland, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
      {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
      {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}
  };
  int expect = 6;
  int actual = solution->maxAreaOfIsland(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[0,0,0,0,0,0,0,0]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(695, MaxAreaOfIsland, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 0, 0, 0, 0, 0, 0, 0}
  };
  int expect = 0;
  int actual = solution->maxAreaOfIsland(grid);
  LCD_EXPECT_EQ(expect, actual);
}
