// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Projection Area of 3D Shapes
//
// https://leetcode.com/problems/projection-area-of-3d-shapes/
//
// Question ID: 883
// Difficult  : Easy
// Solve Date : 2023/07/17 16:36

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |883. Projection Area of 3D Shapes|:
//
// You are given an |n x n| |grid| where we place some |1 x 1 x 1| cubes that
// are axis-aligned with the |x|, |y|, and |z| axes. Each value |v = grid[i][j]|
// represents a tower of |v| cubes placed on top of the cell |(i, j)|. We view
// the projection of these cubes onto the |xy|, |yz|, and |zx| planes. A
// projection is like a shadow, that maps our 3-dimensional figure to a
// 2-dimensional plane. We are viewing the "shadow" when looking at the cubes
// from the top, the front, and the side. Return the total area of all three
// projections.
//
//

LEETCODE_BEGIN_RESOLVING(883, ProjectionAreaOf3DShapes, Solution);

class Solution {
public:
  int projectionArea(vector<vector<int>> &grid) {
    int res = 0;
    int n   = grid.size();
    for (int i = 0; i < n; ++i) {
      int x = 0;
      int y = 0;
      int z = 0;
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] > 0) {
          ++x;
        }
        y = max(y, grid[i][j]);
        z = max(z, grid[j][i]);
      }
      res += x + y + z;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == grid.length == grid[i].length|
// * |1 <= n <= 50|
// * |0 <= grid[i][j] <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,2],[3,4]]
// Output: 17
//
// Here are the three projections ("shadows") of the shape made with each
// axis-aligned plane.

LEETCODE_SOLUTION_UNITTEST(883, ProjectionAreaOf3DShapes, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2},
      {3, 4}
  };
  int expect = 17;
  int actual = solution->projectionArea(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[2]]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(883, ProjectionAreaOf3DShapes, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {{2}};
  int                 expect   = 5;
  int                 actual   = solution->projectionArea(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,0],[0,2]]
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(883, ProjectionAreaOf3DShapes, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0},
      {0, 2}
  };
  int expect = 8;
  int actual = solution->projectionArea(grid);
  LCD_EXPECT_EQ(expect, actual);
}
