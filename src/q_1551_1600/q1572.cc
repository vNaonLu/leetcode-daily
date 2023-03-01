// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Matrix Diagonal Sum
//
// https://leetcode.com/problems/matrix-diagonal-sum/
//
// Question ID: 1572
// Difficult  : Easy
// Solve Date : 2022/04/20 18:07

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1572. Matrix Diagonal Sum|:
//
// Given a square matrix  |mat|, return the sum of the matrix diagonals.
// Only include the sum of all the elements on the primary diagonal and all the
// elements on the secondary diagonal that are not part of the primary diagonal.
//  
//

LEETCODE_BEGIN_RESOLVING(1572, MatrixDiagonalSum, Solution);

class Solution {
public:
  int diagonalSum(vector<vector<int>> &mat) {
    int n = mat.size(), res = 0;

    for (int i = 0; i < n; ++i) {
      res += mat[i][i] + mat[n - 1 - i][i];
    }

    if (n & 1) {
      res -= mat[n / 2][n / 2];
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == mat.length == mat[i].length|
// * |1 <= n <= 100|
// * |1 <= mat[i][j] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mat = [[1,2,3],
//   [4,5,6],
//   [7,8,9]]
// Output: 25
//
// Diagonals sum: 1 + 5 + 9 + 3 + 7 = 25
// Notice that element mat[1][1] = 5 is counted only once.

LEETCODE_SOLUTION_UNITTEST(1572, MatrixDiagonalSum, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };
  int expect = 25;
  int actual = solution->diagonalSum(mat);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mat = [[1,1,1,1],
//   [1,1,1,1],
//   [1,1,1,1],
//   [1,1,1,1]]
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(1572, MatrixDiagonalSum, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 1, 1, 1},
      {1, 1, 1, 1},
      {1, 1, 1, 1},
      {1, 1, 1, 1}
  };
  int expect = 8;
  int actual = solution->diagonalSum(mat);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: mat = [[5]]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(1572, MatrixDiagonalSum, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {{5}};
  int                 expect   = 5;
  int                 actual   = solution->diagonalSum(mat);
  LCD_EXPECT_EQ(expect, actual);
}
