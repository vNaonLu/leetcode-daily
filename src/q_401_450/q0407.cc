// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Trapping Rain Water II
//
// https://leetcode.com/problems/trapping-rain-water-ii/
//
// Question ID: 407
// Difficult  : Hard
// Solve Date : 2025/10/03 19:48

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |407. Trapping Rain Water II|:
//
// Given an |m x n| integer matrix |heightMap| representing the height of each
// unit cell in a 2D elevation map, return the volume of water it can trap after
// raining.
//
//

LEETCODE_BEGIN_RESOLVING(407, TrappingRainWaterII, Solution);

class Solution {
public:
  int trapRainWater(vector<vector<int>> &heightMap) {
    int dRow[4] = {0, 0, -1, 1};
    int dCol[4] = {-1, 1, 0, 0};

    int numOfRows = heightMap.size();
    int numOfCols = heightMap[0].size();

    vector<vector<bool>> visited(numOfRows, vector<bool>(numOfCols, false));

    priority_queue<Cell> boundary;

    for (int i = 0; i < numOfRows; i++) {
      boundary.push(Cell(heightMap[i][0], i, 0));
      boundary.push(Cell(heightMap[i][numOfCols - 1], i, numOfCols - 1));
      visited[i][0] = visited[i][numOfCols - 1] = true;
    }

    for (int i = 0; i < numOfCols; i++) {
      boundary.push(Cell(heightMap[0][i], 0, i));
      boundary.push(Cell(heightMap[numOfRows - 1][i], numOfRows - 1, i));
      visited[0][i] = visited[numOfRows - 1][i] = true;
    }

    int totalWaterVolume = 0;

    while (!boundary.empty()) {
      Cell currentCell = boundary.top();
      boundary.pop();

      int currentRow        = currentCell.row;
      int currentCol        = currentCell.col;
      int minBoundaryHeight = currentCell.height;

      for (int direction = 0; direction < 4; direction++) {
        int neighborRow = currentRow + dRow[direction];
        int neighborCol = currentCol + dCol[direction];

        if (isValidCell(neighborRow, neighborCol, numOfRows, numOfCols) &&
            !visited[neighborRow][neighborCol]) {
          int neighborHeight = heightMap[neighborRow][neighborCol];

          if (neighborHeight < minBoundaryHeight) {
            totalWaterVolume += minBoundaryHeight - neighborHeight;
          }

          boundary.push(Cell(max(neighborHeight, minBoundaryHeight),
                             neighborRow, neighborCol));
          visited[neighborRow][neighborCol] = true;
        }
      }
    }

    return totalWaterVolume;
  }

private:
  class Cell {
  public:
    int height;
    int row;
    int col;

    Cell(int height, int row, int col) : height(height), row(row), col(col) {}

    bool operator<(const Cell &other) const { return height >= other.height; }
  };

  bool isValidCell(int row, int col, int numOfRows, int numOfCols) {
    return row >= 0 && col >= 0 && row < numOfRows && col < numOfCols;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == heightMap.length|
// * |n == heightMap[i].length|
// * |1 <= m, n <= 200|
// * |0 <= heightMap[i][j] <= 2 * 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(407, TrappingRainWaterII, example_1) {
  auto                solution  = MakeSolution();
  vector<vector<int>> heightMap = {
      {1, 4, 3, 1, 3, 2},
      {3, 2, 1, 3, 2, 4},
      {2, 3, 3, 2, 3, 1}
  };
  int expect = 4;
  int actual = solution->trapRainWater(heightMap);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: heightMap =
//  [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
// Output: 10
//

LEETCODE_SOLUTION_UNITTEST(407, TrappingRainWaterII, example_2) {
  auto                solution  = MakeSolution();
  vector<vector<int>> heightMap = {
      {3, 3, 3, 3, 3},
      {3, 2, 2, 2, 3},
      {3, 2, 1, 2, 3},
      {3, 2, 2, 2, 3},
      {3, 3, 3, 3, 3}
  };
  int expect = 10;
  int actual = solution->trapRainWater(heightMap);
  LCD_EXPECT_EQ(expect, actual);
}
