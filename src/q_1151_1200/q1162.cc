// Copyright 2023 Naon Lu
//
// This file describes the solution of
// As Far from Land as Possible
//
// https://leetcode.com/problems/as-far-from-land-as-possible/
//
// Question ID: 1162
// Difficult  : Medium
// Solve Date : 2022/03/13 13:28

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1162. As Far from Land as Possible|:
//
// Given an |n x n| |grid| containing only values |0| and |1|, where  |0|
// represents water and |1| represents land, find a water cell such that its
// distance to the nearest land cell is maximized, and return the distance. If
// no land or water exists in the grid, return |-1|. The distance used in this
// problem is the Manhattan distance: the distance between two cells |(x0, y0)|
// and |(x1, y1)| is ||x0 - x1| + |y0 - y1||.  
//

LEETCODE_BEGIN_RESOLVING(1162, AsFarFromLandAsPossible, Solution);

class Solution {
public:
  int maxDistance(vector<vector<int>> &grid) {
    queue<pair<int, int>> land_pos;
    int                   m = grid.size(), n = grid[0].size();
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) {
          land_pos.emplace(i, j);
        }
      }
    }

    if (land_pos.empty() || land_pos.size() == m * n)
      return -1;
    int res = -1;

    while (!land_pos.empty()) {
      auto temp = move(land_pos);
      ++res;

      while (!temp.empty()) {
        auto [x, y] = temp.front();
        temp.pop();

        if (x + 1 < m && grid[x + 1][y] == 0) {
          land_pos.emplace(x + 1, y);
          grid[x + 1][y] = 1;
        }

        if (x - 1 >= 0 && grid[x - 1][y] == 0) {
          land_pos.emplace(x - 1, y);
          grid[x - 1][y] = 1;
        }

        if (y + 1 < n && grid[x][y + 1] == 0) {
          land_pos.emplace(x, y + 1);
          grid[x][y + 1] = 1;
        }

        if (y - 1 >= 0 && grid[x][y - 1] == 0) {
          land_pos.emplace(x, y - 1);
          grid[x][y - 1] = 1;
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
// * |n == grid.length|
// * |n == grid[i].length|
// * |1 <= n <= 100|
// * |grid[i][j]| is |0| or |1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,0,1],[0,0,0],[1,0,1]]
// Output: 2
//
// The cell (1, 1) is as far as possible from all the land with distance 2.

LEETCODE_SOLUTION_UNITTEST(1162, AsFarFromLandAsPossible, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0, 1},
      {0, 0, 0},
      {1, 0, 1}
  };
  int expect = 2;
  int actual = solution->maxDistance(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,0,0],[0,0,0],[0,0,0]]
// Output: 4
//
// The cell (2, 2) is as far as possible from all the land with distance 4.

LEETCODE_SOLUTION_UNITTEST(1162, AsFarFromLandAsPossible, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
  };
  int expect = 4;
  int actual = solution->maxDistance(grid);
  LCD_EXPECT_EQ(expect, actual);
}
