// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Magic Squares In Grid
//
// https://leetcode.com/problems/magic-squares-in-grid/
//
// Question ID: 840
// Difficult  : Medium
// Solve Date : 2022/02/09 19:10

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |840. Magic Squares In Grid|:
//
// A |3 x 3| magic square is a |3 x 3| grid filled with distinct numbers from
// |1| to |9| such that each row, column, and both diagonals all have the same
// sum. Given a |row x col|  |grid| of integers, how many |3 x 3| "magic square"
// subgrids are there?  (Each subgrid is contiguous).  
//

LEETCODE_BEGIN_RESOLVING(840, MagicSquaresInGrid, Solution);

class Solution {
private:
  int  m, n;
  bool checkDistinct(vector<vector<int>> &grid, int row, int col) noexcept {
    vector<bool> exist(10, false);
    for (int i = row; i < row + 3; ++i) {
      for (int j = col; j < col + 3; ++j) {
        auto x = grid[i][j];
        if (x == 0 || x > 9 || exist[x])
          return false;
        exist[x] = true;
      }
    }
    return true;
  }
  bool checkSum(vector<vector<int>> &grid, int row, int col) noexcept {
    int sum = grid[row][col] + grid[row][col + 1] + grid[row][col + 2];
    /// check rows
    for (int i = row + 1; i < row + 3; ++i) {
      if (sum != grid[i][col] + grid[i][col + 1] + grid[i][col + 2])
        return false;
    }
    /// check cols
    for (int i = col; i < col + 3; ++i) {
      if (sum != grid[row][i] + grid[row + 1][i] + grid[row + 2][i])
        return false;
    }
    /// check diagnal
    if (sum != grid[row][col] + grid[row + 1][col + 1] + grid[row + 2][col + 2])
      return false;
    if (sum != grid[row + 2][col] + grid[row + 1][col + 1] + grid[row][col + 2])
      return false;
    return true;
  }

public:
  int numMagicSquaresInside(vector<vector<int>> &grid) {
    m       = grid.size();
    n       = grid[0].size();
    int res = 0;
    for (int i = 0; i < m - 2; ++i) {
      for (int j = 0; j < n - 2; ++j) {
        if (checkDistinct(grid, i, j) && checkSum(grid, i, j))
          ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |row == grid.length|
// * |col == grid[i].length|
// * |1 <= row, col <= 10|
// * |0 <= grid[i][j] <= 15|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[4,3,8,4],[9,5,1,9],[2,7,6,2]]
// Output: 1
//
// The following subgrid is a 3 x 3 magic square:
// ![img](https://assets.leetcode.com/uploads/2020/09/11/magic_valid.jpg)
// while this one is not:
// ![img](https://assets.leetcode.com/uploads/2020/09/11/magic_invalid.jpg)
// In total, there is only one magic square inside the given grid.

LEETCODE_SOLUTION_UNITTEST(840, MagicSquaresInGrid, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {4, 3, 8, 4},
      {9, 5, 1, 9},
      {2, 7, 6, 2}
  };
  int expect = 1;
  int actual = solution->numMagicSquaresInside(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[8]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(840, MagicSquaresInGrid, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {{8}};
  int                 expect   = 0;
  int                 actual   = solution->numMagicSquaresInside(grid);
  LCD_EXPECT_EQ(expect, actual);
}
