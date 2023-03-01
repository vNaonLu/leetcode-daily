// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Matrix Block Sum
//
// https://leetcode.com/problems/matrix-block-sum/
//
// Question ID: 1314
// Difficult  : Medium
// Solve Date : 2021/10/23 09:56

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1314. Matrix Block Sum|:
//
// Given a |m x n| matrix |mat| and an integer |k|, return a matrix |answer|
// where each |answer[i][j]| is the sum of all elements |mat[r][c]| for:
//
//  • |i - k <= r <= i + k,|
//
//  • |j - k <= c <= j + k|, and
//
//  • |(r, c)| is a valid position in the matrix.
//  
//

LEETCODE_BEGIN_RESOLVING(1314, MatrixBlockSum, Solution);

class Solution {
public:
  vector<vector<int>> matrixBlockSum(vector<vector<int>> &mat, int k) {
    int                 m = mat.size(), n = mat[0].size();
    vector<vector<int>> res(m, vector<int>(n, 0));
    for (int i = 0; i < m; ++i)
      for (int j = 1; j < n; ++j)
        mat[i][j] += mat[i][j - 1];
    for (int i = 0; i < m; ++i) {
      int max_row = min(m - 1, i + k), min_row = max(0, i - k);
      for (int j = 0; j < n; ++j) {
        int max_col = min(n - 1, j + k), min_col = max(0, j - k);
        for (int k = min_row; k <= max_row; ++k)
          res[i][j] += mat[k][max_col];
        if (min_col > 0)
          for (int k = min_row; k <= max_row; ++k)
            res[i][j] -= mat[k][min_col - 1];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == mat.length|
// * |n == mat[i].length|
// * |1 <= m, n, k <= 100|
// * |1 <= mat[i][j] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 1
// Output: [[12,21,16],[27,45,33],[24,39,28]]
//

LEETCODE_SOLUTION_UNITTEST(1314, MatrixBlockSum, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };
  int                 k      = 1;
  vector<vector<int>> expect = {
      {12, 21, 16},
      {27, 45, 33},
      {24, 39, 28}
  };
  vector<vector<int>> actual = solution->matrixBlockSum(mat, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 2
// Output: [[45,45,45],[45,45,45],[45,45,45]]
//

LEETCODE_SOLUTION_UNITTEST(1314, MatrixBlockSum, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };
  int                 k      = 2;
  vector<vector<int>> expect = {
      {45, 45, 45},
      {45, 45, 45},
      {45, 45, 45}
  };
  vector<vector<int>> actual = solution->matrixBlockSum(mat, k);
  LCD_EXPECT_EQ(expect, actual);
}
