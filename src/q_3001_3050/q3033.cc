// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Modify the Matrix
//
// https://leetcode.com/problems/modify-the-matrix/
//
// Question ID: 3033
// Difficult  : Easy
// Solve Date : 2024/03/01 17:30

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3033. Modify the Matrix|:
//
// Given a 0-indexed |m x n| integer matrix |matrix|, create a new 0-indexed
// matrix called |answer|. Make |answer| equal to |matrix|, then replace each
// element with the value |-1| with the maximum element in its respective
// column. Return the matrix |answer|.
//
//

LEETCODE_BEGIN_RESOLVING(3033, ModifyTheMatrix, Solution);

class Solution {
public:
  vector<vector<int>> modifiedMatrix(vector<vector<int>> &matrix) {
    int                                   m = matrix.size();
    int                                   n = matrix[0].size();
    vector<vector<vector<int>::iterator>> repl(n);
    vector<int>                           mx(n, -1);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (matrix[i][j] == -1) {
          repl[j].emplace_back(matrix[i].begin() + j);
        } else {
          mx[j] = max(mx[j], matrix[i][j]);
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      for (auto x : repl[i]) {
        *x = mx[i];
      }
    }
    return matrix;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == matrix.length|
// * |n == matrix[i].length|
// * |2 <= m, n <= 50|
// * |-1 <= matrix[i][j] <= 100|
// * The input is generated such that each column contains at least one
// non-negative integer.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[1,2,-1],[4,-1,6],[7,8,9]]
// Output: [[1,2,9],[4,8,6],[7,8,9]]
//
// The diagram above shows the elements that are changed (in blue).
// - We replace the value in the cell [1][1] with the maximum value in the
// column 1, that is 8.
// - We replace the value in the cell [0][2] with the maximum value in the
// column 2, that is 9.

LEETCODE_SOLUTION_UNITTEST(3033, ModifyTheMatrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {1,  2, -1},
      {4, -1,  6},
      {7,  8,  9}
  };
  vector<vector<int>> expect = {
      {1, 2, 9},
      {4, 8, 6},
      {7, 8, 9}
  };
  vector<vector<int>> actual = solution->modifiedMatrix(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [[3,-1],[5,2]]
// Output: [[3,2],[5,2]]
//
// The diagram above shows the elements that are changed (in blue).

LEETCODE_SOLUTION_UNITTEST(3033, ModifyTheMatrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {3, -1},
      {5,  2}
  };
  vector<vector<int>> expect = {
      {3, 2},
      {5, 2}
  };
  vector<vector<int>> actual = solution->modifiedMatrix(matrix);
  LCD_EXPECT_EQ(expect, actual);
}
