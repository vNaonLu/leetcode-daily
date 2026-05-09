// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Cyclically Rotating a Grid
//
// https://leetcode.com/problems/cyclically-rotating-a-grid/
//
// Question ID: 1914
// Difficult  : Medium
// Solve Date : 2026/05/09 10:51

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1914. Cyclically Rotating a Grid|:
//
// You are given an |m x n| integer matrix |grid|​​​, where |m| and |n|
// are both even integers, and an integer |k|.
//
// The matrix is composed of several layers, which is shown in the below image,
// where each color is its own layer:
//
// ![img](https://assets.leetcode.com/uploads/2021/06/10/ringofgrid.png)
//
// A cyclic rotation of the matrix is done by cyclically rotating each layer in
// the matrix. To cyclically rotate a layer once, each element in the layer will
// take the place of the adjacent element in the counter-clockwise direction. An
// example rotation is shown below:
// ![img](https://assets.leetcode.com/uploads/2021/06/22/explanation_grid.jpg)
// Return the matrix after applying |k| cyclic rotations to it.
//
//
//

LEETCODE_BEGIN_RESOLVING(1914, CyclicallyRotatingAGrid, Solution);

class Solution {
public:
  vector<vector<int>> rotateGrid(vector<vector<int>> &grid, int k) {
    int m = grid.size(), n = grid[0].size();
    int layers = min(m, n) / 2;

    for (int l = 0; l < layers; l++) {
      vector<int> vals;
      int         top = l, left = l;
      int         bottom = m - l - 1, right = n - l - 1;

      for (int j = left; j < right; j++) {
        vals.push_back(grid[top][j]);
      }
      for (int i = top; i < bottom; i++) {
        vals.push_back(grid[i][right]);
      }
      for (int j = right; j > left; j--) {
        vals.push_back(grid[bottom][j]);
      }
      for (int i = bottom; i > top; i--) {
        vals.push_back(grid[i][left]);
      }

      int len   = vals.size();
      int shift = k % len;
      rotate(vals.begin(), vals.begin() + shift, vals.end());

      int idx = 0;
      for (int j = left; j < right; j++) {
        grid[top][j] = vals[idx++];
      }
      for (int i = top; i < bottom; i++) {
        grid[i][right] = vals[idx++];
      }
      for (int j = right; j > left; j--) {
        grid[bottom][j] = vals[idx++];
      }
      for (int i = bottom; i > top; i--) {
        grid[i][left] = vals[idx++];
      }
    }
    return grid;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |2 <= m, n <= 50|
// * Both |m| and |n| are even integers.
// * |1 <= grid[i][j] <=^{ }5000|
// * |1 <= k <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[40,10],[30,20]], k = 1
// Output: [[10,20],[40,30]]
//

LEETCODE_SOLUTION_UNITTEST(1914, CyclicallyRotatingAGrid, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {40, 10},
      {30, 20}
  };
  int                 k      = 1;
  vector<vector<int>> expect = {
      {10, 20},
      {40, 30}
  };
  vector<vector<int>> actual = solution->rotateGrid(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]], k = 2
// Output: [[3,4,8,12],[2,11,10,16],[1,7,6,15],[5,9,13,14]]
//

LEETCODE_SOLUTION_UNITTEST(1914, CyclicallyRotatingAGrid, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      { 1,  2,  3,  4},
      { 5,  6,  7,  8},
      { 9, 10, 11, 12},
      {13, 14, 15, 16}
  };
  int                 k      = 2;
  vector<vector<int>> expect = {
      {3,  4,  8, 12},
      {2, 11, 10, 16},
      {1,  7,  6, 15},
      {5,  9, 13, 14}
  };
  vector<vector<int>> actual = solution->rotateGrid(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}
