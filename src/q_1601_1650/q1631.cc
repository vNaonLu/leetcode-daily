// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Path With Minimum Effort
//
// https://leetcode.com/problems/path-with-minimum-effort/
//
// Question ID: 1631
// Difficult  : Medium
// Solve Date : 2022/04/28 18:28

#include <array>
#include <iosfwd>
#include <limits>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1631. Path With Minimum Effort|:
//
// You are a hiker preparing for an upcoming hike. You are given |heights|, a 2D
// array of size |rows x columns|, where |heights[row][col]| represents the
// height of cell |(row, col)|. You are situated in the top-left cell, |(0, 0)|,
// and you hope to travel to the bottom-right cell, |(rows-1, columns-1)|
// (i.e., 0-indexed). You can move up, down, left, or right, and you wish to
// find a route that requires the minimum effort.
//
// A route's effort is the maximum absolute difference in heights between two
// consecutive cells of the route.
//
// Return the minimum effort required to travel from the top-left cell to the
// bottom-right cell.
//
//  
//

LEETCODE_BEGIN_RESOLVING(1631, PathWithMinimumEffort, Solution);

class Solution {
private:
  typedef pair<int, int>           pos_t;
  int                              m, n;
  constexpr static array<pos_t, 4> dir{
      {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}
  };

  bool is_valid(int x, int y) { return x >= 0 && x < m && y >= 0 && y < n; }

public:
  int minimumEffortPath(vector<vector<int>> &heights) {
    priority_queue<pair<int, pos_t>, vector<pair<int, pos_t>>,
                   greater<pair<int, pos_t>>>
        pq;
    m = heights.size();
    n = heights[0].size();

    vector<vector<int>> dist(m, vector<int>(n, numeric_limits<int>::max()));
    dist[0][0] = 0;

    pq.emplace(0, make_pair(0, 0));
    while (!pq.empty()) {
      auto [d, coord] = pq.top();
      auto &[x, y]    = coord;
      pq.pop();

      if (dist[x][y] < d) {
        continue;
      }

      if (x == m - 1 && y == n - 1) {
        return d;
      }

      for (auto &[dx, dy] : dir) {
        auto nx = x + dx, ny = y + dy;

        if (is_valid(nx, ny)) {
          auto nd = max(abs(heights[x][y] - heights[nx][ny]), d);
          if (dist[nx][ny] > nd) {
            dist[nx][ny] = nd;
            pq.emplace(nd, make_pair(nx, ny));
          }
        }
      }
    }

    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |rows == heights.length|
// * |columns == heights[i].length|
// * |1 <= rows, columns <= 100|
// * |1 <= heights[i][j] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
// Output: 2
//
// The route of [1,3,5,3,5] has a maximum absolute difference of 2 in
// consecutive cells. This is better than the route of [1,2,2,2,5], where the
// maximum absolute difference is 3.

LEETCODE_SOLUTION_UNITTEST(1631, PathWithMinimumEffort, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> heights  = {
      {1, 2, 2},
      {3, 8, 2},
      {5, 3, 5}
  };
  int expect = 2;
  int actual = solution->minimumEffortPath(heights);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
// Output: 1
//
// The route of [1,2,3,4,5] has a maximum absolute difference of 1 in
// consecutive cells, which is better than route [1,3,5,3,5].

LEETCODE_SOLUTION_UNITTEST(1631, PathWithMinimumEffort, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> heights  = {
      {1, 2, 3},
      {3, 8, 4},
      {5, 3, 5}
  };
  int expect = 1;
  int actual = solution->minimumEffortPath(heights);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: heights =
//  [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
// Output: 0
//
// This route does not require any effort.

LEETCODE_SOLUTION_UNITTEST(1631, PathWithMinimumEffort, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> heights  = {
      {1, 2, 1, 1, 1},
      {1, 2, 1, 2, 1},
      {1, 2, 1, 2, 1},
      {1, 2, 1, 2, 1},
      {1, 1, 1, 2, 1}
  };
  int expect = 0;
  int actual = solution->minimumEffortPath(heights);
  LCD_EXPECT_EQ(expect, actual);
}
