// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check if Matrix Is X-Matrix
//
// https://leetcode.com/problems/check-if-matrix-is-x-matrix/
//
// Question ID: 2319
// Difficult  : Easy
// Solve Date : 2023/01/17 21:30

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2319. Check if Matrix Is X-Matrix|:
//
// A square matrix is said to be an X-Matrix if both of the following conditions
// hold:
//
//  1. All the elements in the diagonals of the matrix are non-zero.
//
//  2. All other elements are 0.
// Given a 2D integer array |grid| of size |n x n| representing a square matrix,
// return |true| if |grid| is an X-Matrix. Otherwise, return |false|.
//

LEETCODE_BEGIN_RESOLVING(2319, CheckIfMatrixIsXMatrix, Solution);

class Solution {
public:
  bool checkXMatrix(vector<vector<int>> &grid) {
    int n = grid.size();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == j || i + j == n - 1) {
          if (grid[i][j] == 0) {
            return false;
          }
        } else if (grid[i][j] != 0) {
          return false;
        }
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == grid.length == grid[i].length|
// * |3 <= n <= 100|
// * |0 <= grid[i][j] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[2,0,0,1],[0,3,1,0],[0,5,2,0],[4,0,0,2]]
// Output: true
//
// Refer to the diagram above.
// An X-Matrix should have the green elements (diagonals) be non-zero and the
// red elements be 0. Thus, grid is an X-Matrix.

LEETCODE_SOLUTION_UNITTEST(2319, CheckIfMatrixIsXMatrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {2, 0, 0, 1},
      {0, 3, 1, 0},
      {0, 5, 2, 0},
      {4, 0, 0, 2}
  };
  bool expect = true;
  bool actual = solution->checkXMatrix(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[5,7,0],[0,3,1],[0,5,0]]
// Output: false
//
// Refer to the diagram above.
// An X-Matrix should have the green elements (diagonals) be non-zero and the
// red elements be 0. Thus, grid is not an X-Matrix.

LEETCODE_SOLUTION_UNITTEST(2319, CheckIfMatrixIsXMatrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {5, 7, 0},
      {0, 3, 1},
      {0, 5, 0}
  };
  bool expect = false;
  bool actual = solution->checkXMatrix(grid);
  LCD_EXPECT_EQ(expect, actual);
}
