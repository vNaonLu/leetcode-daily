// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Largest Magic Square
//
// https://leetcode.com/problems/largest-magic-square/
//
// Question ID: 1895
// Difficult  : Medium
// Solve Date : 2026/01/18 15:58

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1895. Largest Magic Square|:
//
// A |k x k| magic square is a |k x k| grid filled with integers such that every
// row sum, every column sum, and both diagonal sums are all equal. The integers
// in the magic square do not have to be distinct. Every |1 x 1| grid is
// trivially a magic square. Given an |m x n| integer |grid|, return the size
// (i.e., the side length |k|) of the largest magic square that can be found
// within this grid.
//
//

LEETCODE_BEGIN_RESOLVING(1895, LargestMagicSquare, Solution);

class Solution {
public:
  int largestMagicSquare(vector<vector<int>> &grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    int max = std::min(rows, cols);
    for (int size = max; size >= 2; size--) {
      for (int r = 0; r + size - 1 < rows; r++) {
        for (int c = 0; c + size - 1 < cols; c++) {
          if (isMagic(grid, r, c, size)) {
            return size;
          }
        }
      }
    }

    return 1;
  }

  bool isMagic(vector<vector<int>> &grid, int r, int c, int size) {
    int targetSum = 0;

    for (int j = 0; j < size; j++) {
      targetSum += grid[r][c + j];
    }

    int diag1 = 0, diag2 = 0;
    for (int i = 0; i < size; i++) {
      diag1 += grid[r + i][c + i];
      diag2 += grid[r + i][c + size - 1 - i];
    }
    if (diag1 != targetSum || diag2 != targetSum)
      return false;

    for (int i = 1; i < size; i++) {
      int sum = 0;
      for (int j = 0; j < size; j++) {
        sum += grid[r + i][c + j];
      }
      if (sum != targetSum)
        return false;
    }

    for (int j = 0; j < size; j++) {
      int sum = 0;
      for (int i = 0; i < size; i++) {
        sum += grid[r + i][c + j];
      }
      if (sum != targetSum)
        return false;
    }

    return true;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 50|
// * |1 <= grid[i][j] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1895, LargestMagicSquare, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {7, 1, 4, 5, 6},
      {2, 5, 1, 6, 4},
      {1, 5, 4, 3, 2},
      {1, 2, 7, 3, 4}
  };
  int expect = 3;
  int actual = solution->largestMagicSquare(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[5,1,3,1],[9,3,3,1],[1,3,3,8]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1895, LargestMagicSquare, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {5, 1, 3, 1},
      {9, 3, 3, 1},
      {1, 3, 3, 8}
  };
  int expect = 2;
  int actual = solution->largestMagicSquare(grid);
  LCD_EXPECT_EQ(expect, actual);
}
