// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Transpose Matrix
//
// https://leetcode.com/problems/transpose-matrix/
//
// Question ID: 867
// Difficult  : Easy
// Solve Date : 2022/06/02 18:21

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |867. Transpose Matrix|:
//
// Given a 2D integer array |matrix|, return the transpose of |matrix|.
// The transpose of a matrix is the matrix flipped over its main diagonal,
// switching the matrix's row and column indices.
// ![img](https://assets.leetcode.com/uploads/2021/02/10/hint_transpose.png)
//

LEETCODE_BEGIN_RESOLVING(867, TransposeMatrix, Solution);

class Solution {
public:
  vector<vector<int>> transpose(vector<vector<int>> &matrix) {
    vector<vector<int>> res(matrix[0].size(), vector<int>(matrix.size()));

    for (int i = 0; i < matrix.size(); ++i) {
      for (int j = 0; j < matrix[i].size(); ++j) {
        res[j][i] = matrix[i][j];
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == matrix.length|
// * |n == matrix[i].length|
// * |1 <= m, n <= 1000|
// * |1 <= m * n <= 10⁵|
// * |-10⁹ <= matrix[i][j] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [[1,4,7],[2,5,8],[3,6,9]]
//

LEETCODE_SOLUTION_UNITTEST(867, TransposeMatrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };
  vector<vector<int>> expect = {
      {1, 4, 7},
      {2, 5, 8},
      {3, 6, 9}
  };
  vector<vector<int>> actual = solution->transpose(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [[1,2,3],[4,5,6]]
// Output: [[1,4],[2,5],[3,6]]
//

LEETCODE_SOLUTION_UNITTEST(867, TransposeMatrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {1, 2, 3},
      {4, 5, 6}
  };
  vector<vector<int>> expect = {
      {1, 4},
      {2, 5},
      {3, 6}
  };
  vector<vector<int>> actual = solution->transpose(matrix);
  LCD_EXPECT_EQ(expect, actual);
}
