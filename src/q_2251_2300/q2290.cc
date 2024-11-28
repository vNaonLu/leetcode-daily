// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Obstacle Removal to Reach Corner
//
// https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/
//
// Question ID: 2290
// Difficult  : Hard
// Solve Date : 2024/11/28 22:12

#include <deque>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2290. Minimum Obstacle Removal to Reach Corner|:
//
// You are given a 0-indexed 2D integer array |grid| of size |m x n|. Each cell
// has one of two values:
//
//  • |0| represents an empty cell,
//
//  • |1| represents an obstacle that may be removed.
// You can move up, down, left, or right from and to an empty cell.
// Return the minimum number of obstacles to remove so you can move from the
// upper left corner |(0, 0)| to the lower right corner |(m - 1, n - 1)|.
//
//

LEETCODE_BEGIN_RESOLVING(2290, MinimumObstacleRemovalToReachCorner, Solution);

class Solution {
public:
  int minimumObstacles(vector<vector<int>> &grid) {
    int                   m = grid.size();
    int                   n = grid[0].size();
    vector<int>           dist(m * n, numeric_limits<int>::max());
    deque<pair<int, int>> q;
    dist[0] = 0;
    q.emplace_back(0, 0);
    while (!q.empty()) {
      auto [d1, idx] = q.front();
      q.pop_front();

      int i = idx / n;
      int j = idx % n;

      if (i == m - 1 && j == n - 1) {
        return d1;
      }

      for (int a = 0; a < 4; ++a) {
        int r = i + kDir[a];
        int c = j + kDir[a + 1];
        if (r < 0 || r >= m || c < 0 || c >= n) {
          continue;
        }

        int d2   = d1 + grid[r][c];
        int idx2 = r * n + c;
        if (d2 < dist[idx2]) {
          dist[idx2] = d2;

          if (grid[r][c] == 0) {
            q.emplace_front(d2, idx2);
          } else {
            q.emplace_back(d2, idx2);
          }
        }
      }
    }
    return -1;
  }

private:
  vector<int> const kDir{0, 1, 0, -1, 0};
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 10⁵|
// * |2 <= m * n <= 10⁵|
// * |grid[i][j]| is either |0| or |1|.
// * |grid[0][0] == grid[m - 1][n - 1] == 0|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0,1,1],[1,1,0],[1,1,0]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2290, MinimumObstacleRemovalToReachCorner,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1, 1},
      {1, 1, 0},
      {1, 1, 0}
  };
  int expect = 2;
  int actual = solution->minimumObstacles(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2290, MinimumObstacleRemovalToReachCorner,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1, 0, 0, 0},
      {0, 1, 0, 1, 0},
      {0, 0, 0, 1, 0}
  };
  int expect = 0;
  int actual = solution->minimumObstacles(grid);
  LCD_EXPECT_EQ(expect, actual);
}
