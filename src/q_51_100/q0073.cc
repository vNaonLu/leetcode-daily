// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Set Matrix Zeroes
//
// https://leetcode.com/problems/set-matrix-zeroes/
//
// Question ID: 73
// Difficult  : Medium
// Solve Date : 2022/08/29 22:06

#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |73. Set Matrix Zeroes|:
//
// Given an |m x n| integer matrix |matrix|, if an element is |0|, set its
// entire row and column to |0|'s. You must do it [in place].
//

LEETCODE_BEGIN_RESOLVING(73, SetMatrixZeroes, Solution);

class Solution {
public:
  void setZeroes(vector<vector<int>> &matrix) {
    auto m         = (int)matrix.size();
    auto n         = (int)matrix.front().size();
    auto zero_cols = unordered_set<int>();
    auto zero_rows = unordered_set<int>();
    /// keep the columns and rows which contain zero.
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (matrix[i][j] == 0) {
          zero_cols.emplace(j);
          zero_rows.emplace(i);
        }
      }
    }
    /// deal with columns
    for (auto x : zero_cols) {
      for (int i = 0; i < m; ++i) {
        matrix[i][x] = 0;
      }
    }
    /// deal with rows
    for (auto x : zero_rows) {
      for (int i = 0; i < n; ++i) {
        matrix[x][i] = 0;
      }
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == matrix.length|
// * |n == matrix[0].length|
// * |1 <= m, n <= 200|
// * |-2³¹ <= matrix[i][j] <= 2³¹ - 1|
// * A straightforward solution using |O(mn)| space is probably a bad idea.
// * A simple improvement uses |O(m + n)| space, but still not the best
// solution.
// * Could you devise a constant space solution?
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
// Output: [[1,0,1],[0,0,0],[1,0,1]]
//

LEETCODE_SOLUTION_UNITTEST(73, SetMatrixZeroes, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {1, 1, 1},
      {1, 0, 1},
      {1, 1, 1}
  };
  vector<vector<int>> expect = {
      {1, 0, 1},
      {0, 0, 0},
      {1, 0, 1}
  };
  solution->setZeroes(matrix);
  LCD_EXPECT_EQ(expect, matrix);
}

// [Example #2]
//  Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
// Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
//

LEETCODE_SOLUTION_UNITTEST(73, SetMatrixZeroes, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {0, 1, 2, 0},
      {3, 4, 5, 2},
      {1, 3, 1, 5}
  };
  vector<vector<int>> expect = {
      {0, 0, 0, 0},
      {0, 4, 5, 0},
      {0, 3, 1, 0}
  };
  solution->setZeroes(matrix);
  LCD_EXPECT_EQ(expect, matrix);
}
