// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Number of Days to Disconnect Island
//
// https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/
//
// Question ID: 1568
// Difficult  : Hard
// Solve Date : 2024/08/11 13:14

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1568. Minimum Number of Days to Disconnect Island|:
//
// You are given an |m x n| binary grid |grid| where |1| represents land and |0|
// represents water. An island is a maximal 4-directionally (horizontal or
// vertical) connected group of |1|'s. The grid is said to be connected if we
// have exactly one island, otherwise is said disconnected. In one day, we are
// allowed to change any single land cell |(1)| into a water cell |(0)|. Return
// the minimum number of days to disconnect the grid.
//
//

LEETCODE_BEGIN_RESOLVING(1568, MinimumNumberOfDaysToDisconnectIsland, Solution);
class Solution {
public:
  int minDays(vector<vector<int>> &grid) {
    int rows = grid.size(), cols = grid[0].size();
    discoveryTime        = vector<vector<int>>(rows, vector<int>(cols, 0));
    lowestReachableTime  = vector<vector<int>>(rows, vector<int>(cols, 0));
    time                 = 1;
    hasArticulationPoint = false;
    totalLandCells       = 0;
    int islands          = 0;

    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < cols; col++) {
        if (grid[row][col] == 1 && discoveryTime[row][col] == 0) {
          islands++;
          if (islands > 1)
            return 0; // More than one island
          dfs(row, col, grid, -1, -1);
        }
      }
    }

    if (totalLandCells == 0)
      return 0; // No land
    if (totalLandCells == 1)
      return 1; // Only one land cell
    if (islands == 0)
      return 0; // No islands (should not happen if input is valid)
    return hasArticulationPoint ? 1 : 2;
  }

private:
  void dfs(int row, int col, vector<vector<int>> &grid, int parentRow,
           int parentCol) {
    discoveryTime[row][col]       = time;
    lowestReachableTime[row][col] = time;
    time++;
    totalLandCells++;
    int children = 0;

    for (const auto &direction : DIRECTIONS) {
      int newRow = row + direction.first;
      int newCol = col + direction.second;

      if (!isValidCell(newRow, newCol, grid)) {
        continue;
      }

      if (discoveryTime[newRow][newCol] == 0) {
        children++;
        dfs(newRow, newCol, grid, row, col);
        lowestReachableTime[row][col] = min(
            lowestReachableTime[row][col], lowestReachableTime[newRow][newCol]);

        if (lowestReachableTime[newRow][newCol] >= discoveryTime[row][col] &&
            parentRow != -1) {
          hasArticulationPoint = true;
        }
      } else if ((newRow != parentRow || newCol != parentCol) &&
                 discoveryTime[newRow][newCol] < discoveryTime[row][col]) {
        lowestReachableTime[row][col] =
            min(lowestReachableTime[row][col], discoveryTime[newRow][newCol]);
      }
    }

    if (parentRow == -1 && children > 1) {
      hasArticulationPoint = true;
    }
  }

  bool isValidCell(int row, int col, const vector<vector<int>> &grid) {
    return row >= 0 && col >= 0 && row < grid.size() && col < grid[0].size() &&
           grid[row][col] == 1;
  }

  int                          time;
  vector<vector<int>>          discoveryTime;
  vector<vector<int>>          lowestReachableTime;
  const vector<pair<int, int>> DIRECTIONS = {
      { 0,  1},
      { 1,  0},
      { 0, -1},
      {-1,  0}
  };
  bool hasArticulationPoint;
  int  totalLandCells;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 30|
// * |grid[i][j]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1568, MinimumNumberOfDaysToDisconnectIsland,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1, 1, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0}
  };
  int expect = 2;
  int actual = solution->minDays(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,1]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1568, MinimumNumberOfDaysToDisconnectIsland,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1}
  };
  int expect = 2;
  int actual = solution->minDays(grid);
  LCD_EXPECT_EQ(expect, actual);
}
