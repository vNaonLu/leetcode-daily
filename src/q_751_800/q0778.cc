// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Swim in Rising Water
//
// https://leetcode.com/problems/swim-in-rising-water/
//
// Question ID: 778
// Difficult  : Hard
// Solve Date : 2025/10/06 14:19

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |778. Swim in Rising Water|:
//
// You are given an |n x n| integer matrix |grid| where each value |grid[i][j]|
// represents the elevation at that point |(i, j)|. It starts raining, and water
// gradually rises over time. At time |t|, the water level is |t|, meaning any
// cell with elevation less than equal to |t| is submerged or reachable. You can
// swim from a square to another 4-directionally adjacent square if and only if
// the elevation of both squares individually are at most |t|. You can swim
// infinite distances in zero time. Of course, you must stay within the
// boundaries of the grid during your swim. Return the minimum time until you
// can reach the bottom right square |(n - 1, n - 1)| if you start at the top
// left square |(0, 0)|.
//
//

LEETCODE_BEGIN_RESOLVING(778, SwimInRisingWater, Solution);

class Solution {
public:
  int swimInWater(vector<vector<int>> &grid) {
    int                    m = grid.size(), n = grid[0].size();
    vector<pair<int, int>> directions = {
        { 0,  1},
        { 1,  0},
        { 0, -1},
        {-1,  0}
    };

    auto dfs = [&](int r, int c, int mid, vector<vector<bool>> &seen,
                   auto &dfs_ref) -> bool {
      if (r == m - 1 && c == n - 1)
        return true;
      seen[r][c] = true;

      for (auto [dr, dc] : directions) {
        int nr = r + dr, nc = c + dc;
        if (nr >= 0 && nr < m && nc >= 0 && nc < n && !seen[nr][nc]) {
          if (grid[nr][nc] <= mid) {
            if (dfs_ref(nr, nc, mid, seen, dfs_ref))
              return true;
          }
        }
      }
      return false;
    };

    auto possible = [&](int mid) {
      if (grid[0][0] > mid)
        return false;
      vector<vector<bool>> seen(m, vector<bool>(n, false));
      return dfs(0, 0, mid, seen, dfs);
    };

    int lo = grid[0][0], hi = 0;
    for (auto &row : grid)
      for (int val : row)
        hi = max(hi, val);

    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (possible(mid))
        hi = mid;
      else
        lo = mid + 1;
    }
    return lo;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == grid.length|
// * |n == grid[i].length|
// * |1 <= n <= 50|
// * |0 <= grid[i][j] < n²|
// * Each value |grid[i][j]| is unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0,2],[1,3]]
// Output: 3
// Explanation:
// At time 0, you are in grid location (0, 0).
// You cannot go anywhere else because 4-directionally adjacent neighbors have a
// higher elevation than t = 0. You cannot reach point (1, 1) until time 3. When
// the depth of water is 3, we can swim anywhere inside the grid.
//

LEETCODE_SOLUTION_UNITTEST(778, SwimInRisingWater, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 2},
      {1, 3}
  };
  int expect = 3;
  int actual = solution->swimInWater(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid =
//  [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
// Output: 16
//

LEETCODE_SOLUTION_UNITTEST(778, SwimInRisingWater, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      { 0,  1,  2,  3,  4},
      {24, 23, 22, 21,  5},
      {12, 13, 14, 15, 16},
      {11, 17, 18, 19, 20},
      {10,  9,  8,  7,  6}
  };
  int expect = 16;
  int actual = solution->swimInWater(grid);
  LCD_EXPECT_EQ(expect, actual);
}
