// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shortest Bridge
//
// https://leetcode.com/problems/shortest-bridge/
//
// Question ID: 934
// Difficult  : Medium
// Solve Date : 2022/03/15 18:19

#include <array>
#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |934. Shortest Bridge|:
//
// You are given an |n x n| binary matrix |grid| where |1| represents land and
// |0| represents water. An island is a 4-directionally connected group of |1|'s
// not connected to any other |1|'s. There are exactly two islands in |grid|.
// You may change |0|'s to |1|'s to connect the two islands to form one island.
// Return the smallest number of |0|'s you must flip to connect the two islands.
//  
//

LEETCODE_BEGIN_RESOLVING(934, ShortestBridge, Solution);

class Solution {
private:
  int                            n;
  constexpr static array<int, 8> dir = {1, 0, 0, 1, -1, 0, 0, -1};

  inline pair<int, int> find_land(vector<vector<int>> &grid) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) {
          grid[i][j] = 2;
          return make_pair(i, j);
        }
      }
    }
    return make_pair(-1, -1);
  }

  inline void find_land(vector<vector<int>> &grid, queue<pair<int, int>> &q) {
    queue<pair<int, int>> tmp;
    tmp.emplace(find_land(grid));
    q.emplace(tmp.front());

    grid[tmp.front().first][tmp.front().second] = 2;

    while (!tmp.empty()) {
      auto [x, y] = tmp.front();
      tmp.pop();

      for (int i = 0; i < dir.size(); ++i) {
        int dx = x + dir[i], dy = y + dir[++i];

        if (is_valid(dx, dy) && grid[dx][dy] == 1) {
          grid[dx][dy] = 2;
          tmp.emplace(dx, dy);
          q.emplace(dx, dy);
        }
      }
    }
  }

  inline bool is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
  }

public:
  int shortestBridge(vector<vector<int>> &grid) {
    n                         = grid.size();
    int                   res = 0;
    queue<pair<int, int>> q;
    find_land(grid, q);

    while (!q.empty()) {
      queue<pair<int, int>> temp = move(q);

      while (!temp.empty()) {
        auto [x, y] = temp.front();
        temp.pop();

        for (int i = 0; i < dir.size(); ++i) {
          int dx = x + dir[i], dy = y + dir[++i];

          if (is_valid(dx, dy)) {
            if (grid[dx][dy] == 1) {
              return res;
            } else if (grid[dx][dy] == 0) {
              grid[dx][dy] = 2;
              q.emplace(dx, dy);
            }
          }
        }
      }

      ++res;
    }

    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == grid.length == grid[i].length|
// * |2 <= n <= 100|
// * |grid[i][j]| is either |0| or |1|.
// * There are exactly two islands in |grid|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0,1],[1,0]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(934, ShortestBridge, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1},
      {1, 0}
  };
  int expect = 1;
  int actual = solution->shortestBridge(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[0,1,0],[0,0,0],[0,0,1]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(934, ShortestBridge, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1, 0},
      {0, 0, 0},
      {0, 0, 1}
  };
  int expect = 2;
  int actual = solution->shortestBridge(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(934, ShortestBridge, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1, 1, 1, 1},
      {1, 0, 0, 0, 1},
      {1, 0, 1, 0, 1},
      {1, 0, 0, 0, 1},
      {1, 1, 1, 1, 1}
  };
  int expect = 1;
  int actual = solution->shortestBridge(grid);
  LCD_EXPECT_EQ(expect, actual);
}
