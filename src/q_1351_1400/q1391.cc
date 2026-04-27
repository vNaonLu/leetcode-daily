// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Check if There is a Valid Path in a Grid
//
// https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/
//
// Question ID: 1391
// Difficult  : Medium
// Solve Date : 2026/04/27 18:39

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1391. Check if There is a Valid Path in a Grid|:
//
// You are given an |m x n| |grid|. Each cell of |grid| represents a street. The
// street of |grid[i][j]| can be:
//
//  • |1| which means a street connecting the left cell and the right cell.
//
//  • |2| which means a street connecting the upper cell and the lower cell.
//
//  • |3| which means a street connecting the left cell and the lower cell.
//
//  • |4| which means a street connecting the right cell and the lower cell.
//
//  • |5| which means a street connecting the left cell and the upper cell.
//
//  • |6| which means a street connecting the right cell and the upper cell.
// ![img](https://assets.leetcode.com/uploads/2020/03/05/main.png)
// You will initially start at the street of the upper-left cell |(0, 0)|. A
// valid path in the grid is a path that starts from the upper left cell |(0,
// 0)| and ends at the bottom-right cell |(m - 1, n - 1)|. The path should only
// follow the streets. Notice that you are not allowed to change any street.
// Return |true| if there is a valid path in the grid or |false| otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(1391, CheckIfThereIsAValidPathInAGrid, Solution);

class Solution {
public:
  bool hasValidPath(vector<vector<int>> &grid) {
    int m = grid.size(), n = grid[0].size();

    vector<vector<pair<int, int>>> dir = {
        {},
        {{0, -1}, {0, 1}},
        {{-1, 0}, {1, 0}},
        {{0, -1}, {1, 0}},
        {{0, 1}, {1, 0}},
        {{0, -1}, {-1, 0}},
        {{0, 1}, {-1, 0}}
    };

    queue<pair<int, int>> q;
    vector<vector<int>>   vis(m, vector<int>(n, 0));

    q.push({0, 0});
    vis[0][0] = 1;

    while (!q.empty()) {
      auto [r, c] = q.front();
      q.pop();

      if (r == m - 1 && c == n - 1)
        return true;

      for (auto [dr, dc] : dir[grid[r][c]]) {
        int nr = r + dr;
        int nc = c + dc;

        if (nr < 0 || nc < 0 || nr >= m || nc >= n || vis[nr][nc])
          continue;

        for (auto [bdr, bdc] : dir[grid[nr][nc]]) {
          if (nr + bdr == r && nc + bdc == c) {
            vis[nr][nc] = 1;
            q.push({nr, nc});
          }
        }
      }
    }

    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 300|
// * |1 <= grid[i][j] <= 6|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[2,4,3],[6,5,2]]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1391, CheckIfThereIsAValidPathInAGrid, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {2, 4, 3},
      {6, 5, 2}
  };
  bool expect = true;
  bool actual = solution->hasValidPath(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,2,1],[1,2,1]]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1391, CheckIfThereIsAValidPathInAGrid, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2, 1},
      {1, 2, 1}
  };
  bool expect = false;
  bool actual = solution->hasValidPath(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,1,2]]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1391, CheckIfThereIsAValidPathInAGrid, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1, 2}
  };
  bool expect = false;
  bool actual = solution->hasValidPath(grid);
  LCD_EXPECT_EQ(expect, actual);
}
