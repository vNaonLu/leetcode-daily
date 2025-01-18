// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Cost to Make at Least One Valid Path in a Grid
//
// https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/
//
// Question ID: 1368
// Difficult  : Hard
// Solve Date : 2025/01/18 10:53

#include <deque>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1368. Minimum Cost to Make at Least One Valid Path in a
// Grid|:
//
// Given an |m x n| grid. Each cell of the grid has a sign pointing to the next
// cell you should visit if you are currently in this cell. The sign of
// |grid[i][j]| can be:
//
//  • |1| which means go to the cell to the right. (i.e go from |grid[i][j]| to
//  |grid[i][j + 1]|)
//
//  • |2| which means go to the cell to the left. (i.e go from |grid[i][j]| to
//  |grid[i][j - 1]|)
//
//  • |3| which means go to the lower cell. (i.e go from |grid[i][j]| to |grid[i
//  + 1][j]|)
//
//  • |4| which means go to the upper cell. (i.e go from |grid[i][j]| to |grid[i
//  - 1][j]|)
// Notice that there could be some signs on the cells of the grid that point
// outside the grid. You will initially start at the upper left cell |(0, 0)|. A
// valid path in the grid is a path that starts from the upper left cell |(0,
// 0)| and ends at the bottom-right cell |(m - 1, n - 1)| following the signs on
// the grid. The valid path does not have to be the shortest. You can modify the
// sign on a cell with |cost = 1|. You can modify the sign on a cell one time
// only. Return the minimum cost to make the grid have at least one valid path.
//
//

LEETCODE_BEGIN_RESOLVING(1368, MinimumCostToMakeAtLeastOneValidPathInAGrid,
                         Solution);

class Solution {
public:
  // Direction vectors: right, left, down, up (matching grid values 1, 2, 3,
  // 4)
  vector<vector<int>> dirs = {
      { 0,  1},
      { 0, -1},
      { 1,  0},
      {-1,  0}
  };

  int minCost(vector<vector<int>> &grid) {
    int numRows = grid.size(), numCols = grid[0].size();

    // Track minimum cost to reach each cell
    vector<vector<int>> minCost(
        numRows, vector<int>(numCols, numeric_limits<int>::max()));

    // Use deque for 0-1 BFS - add zero cost moves to front, cost=1 to back
    deque<pair<int, int>> deque;
    deque.push_front({0, 0});
    minCost[0][0] = 0;

    while (!deque.empty()) {
      auto [row, col] = deque.front();
      deque.pop_front();

      // Try all four directions
      for (int dir = 0; dir < 4; dir++) {
        int newRow = row + dirs[dir][0];
        int newCol = col + dirs[dir][1];
        int cost   = (grid[row][col] != (dir + 1)) ? 1 : 0;

        // If position is valid and we found a better path
        if (isValid(newRow, newCol, numRows, numCols) &&
            minCost[row][col] + cost < minCost[newRow][newCol]) {
          minCost[newRow][newCol] = minCost[row][col] + cost;

          // Add to back if cost=1, front if cost=0
          if (cost == 1) {
            deque.push_back({newRow, newCol});
          } else {
            deque.push_front({newRow, newCol});
          }
        }
      }
    }

    return minCost[numRows - 1][numCols - 1];
  }

private:
  // Check if coordinates are within grid bounds
  bool isValid(int row, int col, int numRows, int numCols) {
    return row >= 0 && row < numRows && col >= 0 && col < numCols;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 100|
// * |1 <= grid[i][j] <= 4|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1368, MinimumCostToMakeAtLeastOneValidPathInAGrid,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1, 1, 1},
      {2, 2, 2, 2},
      {1, 1, 1, 1},
      {2, 2, 2, 2}
  };
  int expect = 3;
  int actual = solution->minCost(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,1,3],[3,2,2],[1,1,4]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1368, MinimumCostToMakeAtLeastOneValidPathInAGrid,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1, 3},
      {3, 2, 2},
      {1, 1, 4}
  };
  int expect = 0;
  int actual = solution->minCost(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,2],[4,3]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1368, MinimumCostToMakeAtLeastOneValidPathInAGrid,
                           example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2},
      {4, 3}
  };
  int expect = 1;
  int actual = solution->minCost(grid);
  LCD_EXPECT_EQ(expect, actual);
}
