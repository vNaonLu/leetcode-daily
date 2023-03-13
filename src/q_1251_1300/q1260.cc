// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shift 2D Grid
//
// https://leetcode.com/problems/shift-2d-grid/
//
// Question ID: 1260
// Difficult  : Easy
// Solve Date : 2022/04/11 18:21

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1260. Shift 2D Grid|:
//
// Given a 2D |grid| of size |m x n| and an integer |k|. You need to shift the
// |grid|  |k| times. In one shift operation:
//
//  • Element at |grid[i][j]| moves to |grid[i][j + 1]|.
//
//  • Element at |grid[i][n - 1]| moves to |grid[i + 1][0]|.
//
//  • Element at |grid[m - 1][n - 1]| moves to |grid[0][0]|.
// Return the 2D grid after applying shift operation |k| times.
//  
//

LEETCODE_BEGIN_RESOLVING(1260, Shift2DGrid, Solution);

class Solution {
public:
  vector<vector<int>> shiftGrid(vector<vector<int>> &grid, int k) {
    int                 m = grid.size(), n = grid[0].size();
    int                 prod = m * n;
    vector<vector<int>> res(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        int idx               = (i * n + j + k) % prod;
        res[idx / n][idx % n] = grid[i][j];
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m <= 50|
// * |1 <= n <= 50|
// * |-1000 <= grid[i][j] <= 1000|
// * |0 <= k <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: |grid| = [[1,2,3],[4,5,6],[7,8,9]], k = 1
// Output: [[9,1,2],[3,4,5],[6,7,8]]
//

LEETCODE_SOLUTION_UNITTEST(1260, Shift2DGrid, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };
  int                 k      = 1;
  vector<vector<int>> expect = {
      {9, 1, 2},
      {3, 4, 5},
      {6, 7, 8}
  };
  vector<vector<int>> actual = solution->shiftGrid(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: |grid| = [[3,8,1,9],[19,7,2,5],[4,6,11,10],[12,0,21,13]], k = 4
// Output: [[12,0,21,13],[3,8,1,9],[19,7,2,5],[4,6,11,10]]
//

LEETCODE_SOLUTION_UNITTEST(1260, Shift2DGrid, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      { 3, 8,  1,  9},
      {19, 7,  2,  5},
      { 4, 6, 11, 10},
      {12, 0, 21, 13}
  };
  int                 k      = 4;
  vector<vector<int>> expect = {
      {12, 0, 21, 13},
      { 3, 8,  1,  9},
      {19, 7,  2,  5},
      { 4, 6, 11, 10}
  };
  vector<vector<int>> actual = solution->shiftGrid(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: |grid| = [[1,2,3],[4,5,6],[7,8,9]], k = 9
// Output: [[1,2,3],[4,5,6],[7,8,9]]
//

LEETCODE_SOLUTION_UNITTEST(1260, Shift2DGrid, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };
  int                 k      = 9;
  vector<vector<int>> expect = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };
  vector<vector<int>> actual = solution->shiftGrid(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}
