// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Time to Visit a Cell In a Grid
//
// https://leetcode.com/problems/minimum-time-to-visit-a-cell-in-a-grid/
//
// Question ID: 2577
// Difficult  : Hard
// Solve Date : 2024/11/29 22:55

#include <iosfwd>
#include <queue>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2577. Minimum Time to Visit a Cell In a Grid|:
//
// You are given a |m x n| matrix |grid| consisting of non-negative integers
// where |grid[row][col]| represents the minimum time required to be able to
// visit the cell |(row, col)|, which means you can visit the cell |(row, col)|
// only when the time you visit it is greater than or equal to |grid[row][col]|.
// You are standing in the top-left cell of the matrix in the |0ᵗʰ| second, and
// you must move to any adjacent cell in the four directions: up, down, left,
// and right. Each move you make takes 1 second. Return the minimum time
// required in which you can visit the bottom-right cell of the matrix. If you
// cannot visit the bottom-right cell, then return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(2577, MinimumTimeToVisitACellInAGrid, Solution);

class Solution {
public:
  int minimumTime(vector<vector<int>> &grid) {
    if (min(grid[0][1], grid[1][0]) > 1) {
      return -1;
    }

    int m = grid.size();
    int n = grid[0].size();
    priority_queue<vector<int>, vector<vector<int>>, greater<>> min_heap;
    min_heap.push({0, 0, 0});
    set<pair<int, int>> visit;
    while (!min_heap.empty()) {
      auto curr = std::move(min_heap.top());
      min_heap.pop();

      int t = curr[0];
      int r = curr[1];
      int c = curr[2];

      if (r == m - 1 && c == n - 1) {
        return t;
      }

      vector<int> dir = {1, 0, -1, 0, 1};
      for (int i = 0; i < dir.size() - 1; ++i) {
        int dr = dir[i];
        int dc = dir[i + 1];

        int nr = r + dr;
        int nc = c + dc;

        if (nr < 0 || nc < 0 || nr == m || nc == n || visit.count({nr, nc})) {
          continue;
        }

        int wait   = (abs(grid[nr][nc] - t) % 2 == 0) ? 1 : 0;
        int n_time = max(grid[nr][nc] + wait, t + 1);
        min_heap.push({n_time, nr, nc});
        visit.insert({nr, nc});
      }
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |2 <= m, n <= 1000|
// * |4 <= m * n <= 10⁵|
// * |0 <= grid[i][j] <= 10⁵|
// * |grid[0][0] == 0|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0,1,3,2],[5,1,2,5],[4,3,8,6]]
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(2577, MinimumTimeToVisitACellInAGrid, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1, 3, 2},
      {5, 1, 2, 5},
      {4, 3, 8, 6}
  };
  int expect = 7;
  int actual = solution->minimumTime(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[0,2,4],[3,2,1],[1,0,4]]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2577, MinimumTimeToVisitACellInAGrid, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 2, 4},
      {3, 2, 1},
      {1, 0, 4}
  };
  int expect = -1;
  int actual = solution->minimumTime(grid);
  LCD_EXPECT_EQ(expect, actual);
}
