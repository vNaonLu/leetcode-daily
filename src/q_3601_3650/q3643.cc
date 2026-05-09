// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Flip Square Submatrix Vertically
//
// https://leetcode.com/problems/flip-square-submatrix-vertically/
//
// Question ID: 3643
// Difficult  : Easy
// Solve Date : 2026/03/21 15:47

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3643. Flip Square Submatrix Vertically|:
//
//

LEETCODE_BEGIN_RESOLVING(3643, FlipSquareSubmatrixVertically, Solution);

class Solution {
public:
  vector<vector<int>> reverseSubmatrix(vector<vector<int>> &grid, int x, int y,
                                       int k) {
    for (int i = 0; i < k / 2; ++i) {
      for (int j = 0; j < k; ++j) {
        swap(grid[x + i][y + j], grid[x + k - 1 - i][y + j]);
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
// * |1 <= m, n <= 50|
// * |1 <= grid[i][j] <= 100|
// * |0 <= x < m|
// * |0 <= y < n|
// * |1 <= k <= min(m - x, n - y)|
///////////////////////////////////////////////////////////////////////////////

LEETCODE_SOLUTION_UNITTEST(3643, FlipSquareSubmatrixVertically, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      { 1,  2,  3,  4},
      { 5,  6,  7,  8},
      { 9, 10, 11, 12},
      {13, 14, 15, 16}
  };
  int                 x      = 1;
  int                 y      = 0;
  int                 k      = 3;
  vector<vector<int>> expect = {
      { 1,  2,  3,  4},
      {13, 14, 15,  8},
      { 9, 10, 11, 12},
      { 5,  6,  7, 16}
  };
  vector<vector<int>> actual = solution->reverseSubmatrix(grid, x, y, k);
  LCD_EXPECT_EQ(expect, actual);
}

LEETCODE_SOLUTION_UNITTEST(3643, FlipSquareSubmatrixVertically, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {3, 4, 2, 3},
      {2, 3, 4, 2},
  };
  int                 x      = 0;
  int                 y      = 2;
  int                 k      = 2;
  vector<vector<int>> expect = {
      {3, 4, 4, 2},
      {2, 3, 2, 3}
  };
  vector<vector<int>> actual = solution->reverseSubmatrix(grid, x, y, k);
  LCD_EXPECT_EQ(expect, actual);
}
