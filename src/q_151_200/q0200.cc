// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Islands
//
// https://leetcode.com/problems/number-of-islands/
//
// Question ID: 200
// Difficult  : Medium
// Solve Date : 2021/09/24 15:43

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |200. Number of Islands|:
//
// Given an |m x n| 2D binary grid |grid| which represents a map of |'1'|s
// (land) and |'0'|s (water), return the number of islands. An island is
// surrounded by water and is formed by connecting adjacent lands horizontally
// or vertically. You may assume all four edges of the grid are all surrounded
// by water.  
//

LEETCODE_BEGIN_RESOLVING(200, NumberOfIslands, Solution);

class Solution {
private:
  vector<int> dir = {-1, 0, 1, 0, 0, 1, 0, -1};

public:
  int numIslands(vector<vector<char>> &grid) {
    int                   res = 0;
    int                   m = grid.size(), n = grid[0].size();
    queue<pair<int, int>> island;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == '1') {
          island.push({i, j});
          grid[i][j] = '0';
          while (!island.empty()) {
            auto &p = island.front();
            for (int k = 0; k < dir.size(); ++k) {
              int x = p.first + dir[k], y = p.second + dir[++k];
              if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == '1') {
                grid[x][y] = '0';
                island.emplace(x, y);
              }
            }
            island.pop();
          }
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
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 300|
// * |grid[i][j]| is |'0'| or |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [
//  ["1","1","1","1","0"],
//  ["1","1","0","1","0"],
//  ["1","1","0","0","0"],
//  ["0","0","0","0","0"]
// ]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(200, NumberOfIslands, example_1) {
  auto                 solution = MakeSolution();
  vector<vector<char>> grid     = {
      {'1', '1', '1', '1', '0'},
      {'1', '1', '0', '1', '0'},
      {'1', '1', '0', '0', '0'},
      {'0', '0', '0', '0', '0'}
  };
  int expect = 1;
  int actual = solution->numIslands(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [
//  ["1","1","0","0","0"],
//  ["1","1","0","0","0"],
//  ["0","0","1","0","0"],
//  ["0","0","0","1","1"]
// ]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(200, NumberOfIslands, example_2) {
  auto                 solution = MakeSolution();
  vector<vector<char>> grid     = {
      {'1', '1', '0', '0', '0'},
      {'1', '1', '0', '0', '0'},
      {'0', '0', '1', '0', '0'},
      {'0', '0', '0', '1', '1'}
  };
  int expect = 3;
  int actual = solution->numIslands(grid);
  LCD_EXPECT_EQ(expect, actual);
}
