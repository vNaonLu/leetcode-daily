// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Cells with Odd Values in a Matrix
//
// https://leetcode.com/problems/cells-with-odd-values-in-a-matrix/
//
// Question ID: 1252
// Difficult  : Easy
// Solve Date : 2022/11/29 18:27

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1252. Cells with Odd Values in a Matrix|:
//
// There is an |m x n| matrix that is initialized to all |0|'s. There is also a
// 2D array |indices| where each |indices[i] = [rᵢ, cᵢ]| represents a 0-indexed
// location to perform some increment operations on the matrix. For each
// location |indices[i]|, do both of the following:
//
//  1. Increment all the cells on row |rᵢ|.
//
//  2. Increment all the cells on column |cᵢ|.
// Given |m|, |n|, and |indices|, return the number of odd-valued cells in the
// matrix after applying the increment to all locations in |indices|.
//

LEETCODE_BEGIN_RESOLVING(1252, CellsWithOddValuesInAMatrix, Solution);

class Solution {
public:
  int oddCells(int m, int n, vector<vector<int>> &indices) {
    auto inc_row = vector<int>(m, 0);
    auto inc_col = vector<int>(n, 0);
    for (auto &v : indices) {
      ++inc_row[v[0]];
      ++inc_col[v[1]];
    }
    auto row_odd =
        count_if(inc_row.begin(), inc_row.end(), [](auto x) { return x & 1; });
    auto col_odd =
        count_if(inc_col.begin(), inc_col.end(), [](auto x) { return x & 1; });
    return row_odd * (n - col_odd) + col_odd * (m - row_odd);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= m, n <= 50|
// * |1 <= indices.length <= 100|
// * |0 <= rᵢ < m|
// * |0 <= cᵢ < n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: m = 2, n = 3, indices = [[0,1],[1,1]]
// Output: 6
//
// Initial matrix = [[0,0,0],[0,0,0]].
// After applying first increment it becomes [[1,2,1],[0,1,0]].
// The final matrix is [[1,3,1],[1,3,1]], which contains 6 odd numbers.

LEETCODE_SOLUTION_UNITTEST(1252, CellsWithOddValuesInAMatrix, example_1) {
  auto                solution = MakeSolution();
  int                 m        = 2;
  int                 n        = 3;
  vector<vector<int>> indices  = {
      {0, 1},
      {1, 1}
  };
  int expect = 6;
  int actual = solution->oddCells(m, n, indices);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: m = 2, n = 2, indices = [[1,1],[0,0]]
// Output: 0
//
// Final matrix = [[2,2],[2,2]]. There are no odd numbers in the final matrix.

LEETCODE_SOLUTION_UNITTEST(1252, CellsWithOddValuesInAMatrix, example_2) {
  auto                solution = MakeSolution();
  int                 m        = 2;
  int                 n        = 2;
  vector<vector<int>> indices  = {
      {1, 1},
      {0, 0}
  };
  int expect = 0;
  int actual = solution->oddCells(m, n, indices);
  LCD_EXPECT_EQ(expect, actual);
}
