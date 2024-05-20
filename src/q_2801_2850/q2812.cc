// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the Safest Path in a Grid
//
// https://leetcode.com/problems/find-the-safest-path-in-a-grid/
//
// Question ID: 2812
// Difficult  : Medium
// Solve Date : 2024/05/15 22:59

#include <deque>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2812. Find the Safest Path in a Grid|:
//
// You are given a 0-indexed 2D matrix |grid| of size |n x n|, where |(r, c)|
// represents:
//
//  • A cell containing a thief if |grid[r][c] = 1|
//
//  • An empty cell if |grid[r][c] = 0|
// You are initially positioned at cell |(0, 0)|. In one move, you can move to
// any adjacent cell in the grid, including cells containing thieves. The
// safeness factor of a path on the grid is defined as the minimum manhattan
// distance from any cell in the path to any thief in the grid. Return the
// maximum safeness factor of all paths leading to cell |(n - 1, n - 1)|. An
// adjacent cell of cell |(r, c)|, is one of the cells |(r, c + 1)|, |(r, c -
// 1)|, |(r + 1, c)| and |(r - 1, c)| if it exists. The Manhattan distance
// between two cells |(a, b)| and |(x, y)| is equal to ||a - x| + |b - y||,
// where ||val|| denotes the absolute value of val.
//
//

LEETCODE_BEGIN_RESOLVING(2812, FindTheSafestPathInAGrid, Solution);

class Solution {
public:
  int maximumSafenessFactor(vector<vector<int>> &grid) {
    int                         n = grid.size();
    deque<tuple<int, int, int>> q;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j]) {
          q.emplace_back(i, j, 1);
        }
        --grid[i][j];
      }
    }

    while (!q.empty()) {
      auto [i, j, safety] = q.front();
      q.pop_front();
      vector<pair<int, int>> expand = {
          {i + 1,     j},
          {i - 1,     j},
          {    i, j + 1},
          {    i, j - 1}
      };

      for (auto [r, c] : expand) {
        if (!boundCheck(r, c, n) || grid[r][c] != -1) {
          continue;
        }
        grid[r][c] = safety;
        q.emplace_back(r, c, safety + 1);
      }
    }

    int res = grid[0][0];
    q.emplace_back(0, 0, grid[0][0]);
    while (!q.empty()) {
      auto [i, j, safety] = q.front();
      q.pop_front();

      res = min(res, safety);

      if (i == n - 1 && j == n - 1) {
        break;
      }

      vector<pair<int, int>> expand = {
          {i + 1,     j},
          {i - 1,     j},
          {    i, j + 1},
          {    i, j - 1}
      };

      for (auto [r, c] : expand) {
        if (!boundCheck(r, c, n) || grid[r][c] == -1) {
          continue;
        }
        int safety = grid[r][c];
        grid[r][c] = -1;
        if (safety < res) {
          q.emplace_back(r, c, safety);
        } else {
          q.emplace_front(r, c, safety);
        }
      }
    }
    return res;
  }

private:
  bool boundCheck(int r, int c, int n) {
    return r >= 0 && c >= 0 && r < n && c < n;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= grid.length == n <= 400|
// * |grid[i].length == n|
// * |grid[i][j]| is either |0| or |1|.
// * There is at least one thief in the |grid|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2812, FindTheSafestPathInAGrid, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0, 0},
      {0, 0, 0},
      {0, 0, 1}
  };
  int expect = 0;
  int actual = solution->maximumSafenessFactor(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[0,0,1],[0,0,0],[0,0,0]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2812, FindTheSafestPathInAGrid, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 0, 1},
      {0, 0, 0},
      {0, 0, 0}
  };
  int expect = 2;
  int actual = solution->maximumSafenessFactor(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2812, FindTheSafestPathInAGrid, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 0, 0, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {1, 0, 0, 0}
  };
  int expect = 2;
  int actual = solution->maximumSafenessFactor(grid);
  LCD_EXPECT_EQ(expect, actual);
}
