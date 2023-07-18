// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Surface Area of 3D Shapes
//
// https://leetcode.com/problems/surface-area-of-3d-shapes/
//
// Question ID: 892
// Difficult  : Easy
// Solve Date : 2023/07/18 21:18

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |892. Surface Area of 3D Shapes|:
//
// You are given an |n x n| |grid| where you have placed some |1 x 1 x 1| cubes.
// Each value |v = grid[i][j]| represents a tower of |v| cubes placed on top of
// cell |(i, j)|. After placing these cubes, you have decided to glue any
// directly adjacent cubes to each other, forming several irregular 3D shapes.
// Return the total surface area of the resulting shapes.
// Note: The bottom face of each shape counts toward its surface area.
//
//

LEETCODE_BEGIN_RESOLVING(892, SurfaceAreaOf3DShapes, Solution);

class Solution {
public:
  int surfaceArea(vector<vector<int>> &grid) {
    int res = 0;
    int n   = grid.size();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] > 0) {
          res += 2; // up and down
        }
        if (i == 0) {
          res += grid[i][j];
        }
        if (j == 0) {
          res += grid[i][j];
        }
        if (i == n - 1) {
          res += grid[i][j];
        }
        if (j == n - 1) {
          res += grid[i][j];
        }
        if (i < n - 1 && grid[i + 1][j] != grid[i][j]) {
          res += abs(grid[i + 1][j] - grid[i][j]);
        }
        if (j < n - 1 && grid[i][j + 1] != grid[i][j]) {
          res += abs(grid[i][j + 1] - grid[i][j]);
        }
      }
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
// Output: 34
//

LEETCODE_SOLUTION_UNITTEST(892, SurfaceAreaOf3DShapes, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2},
      {3, 4}
  };
  int expect = 34;
  int actual = solution->surfaceArea(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
// Output: 32
//

LEETCODE_SOLUTION_UNITTEST(892, SurfaceAreaOf3DShapes, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1, 1},
      {1, 0, 1},
      {1, 1, 1}
  };
  int expect = 32;
  int actual = solution->surfaceArea(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[2,2,2],[2,1,2],[2,2,2]]
// Output: 46
//

LEETCODE_SOLUTION_UNITTEST(892, SurfaceAreaOf3DShapes, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {2, 2, 2},
      {2, 1, 2},
      {2, 2, 2}
  };
  int expect = 46;
  int actual = solution->surfaceArea(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [[1]]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(892, SurfaceAreaOf3DShapes, extra_testcase_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {{1}};
  int                 expect   = 6;
  int                 actual   = solution->surfaceArea(grid);
  LCD_EXPECT_EQ(expect, actual);
}
