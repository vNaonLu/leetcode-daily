// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Rotting Oranges
//
// https://leetcode.com/problems/rotting-oranges/
//
// Question ID: 994
// Difficult  : Medium
// Solve Date : 2021/09/13 08:00

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |994. Rotting Oranges|:
//
// You are given an |m x n| |grid| where each cell can have one of three values:
//
//  • |0| representing an empty cell,
//
//  • |1| representing a fresh orange, or
//
//  • |2| representing a rotten orange.
// Every minute, any fresh orange that is 4-directionally adjacent to a rotten
// orange becomes rotten. Return the minimum number of minutes that must elapse
// until no cell has a fresh orange. If this is impossible, return |-1|.  
//

LEETCODE_BEGIN_RESOLVING(994, RottingOranges, Solution);

class Solution {
private:
  vector<int> direct = {1, 0, 0, 1, -1, 0, 0, -1};

public:
  int orangesRotting(vector<vector<int>> &grid) {
    queue<pair<int, int>> rot;
    int                   m = grid.size(), n = grid[0].size();
    int                   fresh_count = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 2)
          rot.emplace(i, j);
        else if (grid[i][j] == 1)
          ++fresh_count;
      }
    }
    int res       = 0;
    int rot_count = 0;
    while (!rot.empty()) {
      int rot_size = rot.size();
      while (rot_size-- > 0) {
        auto current = rot.front();
        rot.pop();
        for (int i = 0; i < direct.size(); ++i) {
          int x = current.first + direct[i];
          int y = current.second + direct[++i];
          if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 1) {
            ++rot_count;
            grid[x][y] = 2;
            rot.emplace(x, y);
          }
        }
      }
      ++res;
    }
    return fresh_count == 0 ? 0 : rot_count == fresh_count ? res - 1 : -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 10|
// * |grid[i][j]| is |0|, |1|, or |2|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(994, RottingOranges, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {2, 1, 1},
      {1, 1, 0},
      {0, 1, 1}
  };
  int expect = 4;
  int actual = solution->orangesRotting(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
// Output: -1
//
// The orange in the bottom left corner (row 2, column 0) is never rotten,
// because rotting only happens 4-directionally.

LEETCODE_SOLUTION_UNITTEST(994, RottingOranges, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {2, 1, 1},
      {0, 1, 1},
      {1, 0, 1}
  };
  int expect = -1;
  int actual = solution->orangesRotting(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[0,2]]
// Output: 0
//
// Since there are already no fresh oranges at minute 0, the answer is just 0.

LEETCODE_SOLUTION_UNITTEST(994, RottingOranges, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 2}
  };
  int expect = 0;
  int actual = solution->orangesRotting(grid);
  LCD_EXPECT_EQ(expect, actual);
}
