// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Map of Highest Peak
//
// https://leetcode.com/problems/map-of-highest-peak/
//
// Question ID: 1765
// Difficult  : Medium
// Solve Date : 2025/01/22 19:26

#include <array>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1765. Map of Highest Peak|:
//
// You are given an integer matrix |isWater| of size |m x n| that represents a
// map of land and water cells.
//
//  • If |isWater[i][j] == 0|, cell |(i, j)| is a land cell.
//
//  • If |isWater[i][j] == 1|, cell |(i, j)| is a water cell.
// You must assign each cell a height in a way that follows these rules:
//
//  • The height of each cell must be non-negative.
//
//  • If the cell is a water cell, its height must be |0|.
//
//  • Any two adjacent cells must have an absolute height difference of at most
//  |1|. A cell is adjacent to another cell if the former is directly north,
//  east, south, or west of the latter (i.e., their sides are touching).
// Find an assignment of heights such that the maximum height in the matrix is
// maximized. Return an integer matrix |height| of size |m x n| where
// |height[i][j]| is cell |(i, j)|'s height. If there are multiple solutions,
// return any of them.
//
//

LEETCODE_BEGIN_RESOLVING(1765, MapOfHighestPeak, Solution);

class Solution {
public:
  vector<vector<int>> highestPeak(vector<vector<int>> &isWater) {
    constexpr array<int, 5> kDir = {0, 1, 0, -1, 0};
    int                     m    = isWater.size();
    int                     n    = isWater[0].size();
    vector<vector<int>>     res(m, vector<int>(n, -1));
    vector<pair<int, int>>  pos;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (isWater[i][j] == 1) {
          res[i][j] = 0;
          pos.emplace_back(i, j);
        }
      }
    }
    while (!pos.empty()) {
      auto tmp = std::move(pos);
      for (auto [x, y] : tmp) {
        for (int i = 0; i < kDir.size() - 1; ++i) {
          int dx = x + kDir[i];
          int dy = y + kDir[i + 1];

          if (dx < 0 || dx >= m) {
            continue;
          }
          if (dy < 0 || dy >= n) {
            continue;
          }
          if (res[dx][dy] != -1) {
            continue;
          }

          res[dx][dy] = res[x][y] + 1;
          pos.emplace_back(dx, dy);
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == isWater.length|
// * |n == isWater[i].length|
// * |1 <= m, n <= 1000|
// * |isWater[i][j]| is |0| or |1|.
// * There is at least one water cell.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: isWater = [[0,1],[0,0]]
// Output: [[1,0],[2,1]]
//

LEETCODE_SOLUTION_UNITTEST(1765, MapOfHighestPeak, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> isWater  = {
      {0, 1},
      {0, 0}
  };
  vector<vector<int>> expect = {
      {1, 0},
      {2, 1}
  };
  vector<vector<int>> actual = solution->highestPeak(isWater);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: isWater = [[0,0,1],[1,0,0],[0,0,0]]
// Output: [[1,1,0],[0,1,1],[1,2,2]]
//

LEETCODE_SOLUTION_UNITTEST(1765, MapOfHighestPeak, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> isWater  = {
      {0, 0, 1},
      {1, 0, 0},
      {0, 0, 0}
  };
  vector<vector<int>> expect = {
      {1, 1, 0},
      {0, 1, 1},
      {1, 2, 2}
  };
  vector<vector<int>> actual = solution->highestPeak(isWater);
  LCD_EXPECT_EQ(expect, actual);
}
