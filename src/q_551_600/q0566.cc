// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reshape the Matrix
//
// https://leetcode.com/problems/reshape-the-matrix/
//
// Question ID: 566
// Difficult  : Easy
// Solve Date : 2021/09/08 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |566. Reshape the Matrix|:
//
// In MATLAB, there is a handy function called |reshape| which can reshape an |m
// x n| matrix into a new one with a different size |r x c| keeping its original
// data. You are given an |m x n| matrix |mat| and two integers |r| and |c|
// representing the number of rows and the number of columns of the wanted
// reshaped matrix. The reshaped matrix should be filled with all the elements
// of the original matrix in the same row-traversing order as they were. If the
// |reshape| operation with given parameters is possible and legal, output the
// new reshaped matrix; Otherwise, output the original matrix.  
//

LEETCODE_BEGIN_RESOLVING(566, ReshapetheMatrix, Solution);

class Solution {
public:
  vector<vector<int>> matrixReshape(vector<vector<int>> &mat, int r, int c) {
    int m = mat.size(), n = mat[0].size();
    if (m * n != r * c) {
      return mat;
    } else {
      vector<vector<int>> res(r, vector<int>(c));
      for (int i = 0; i < m * n; ++i) {
        res[i / c][i % c] = mat[i / n][i % n];
      }
      return res;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == mat.length|
// * |n == mat[i].length|
// * |1 <= m, n <= 100|
// * |-1000 <= mat[i][j] <= 1000|
// * |1 <= r, c <= 300|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mat = [[1,2],[3,4]], r = 1, c = 4
// Output: [[1,2,3,4]]
//

LEETCODE_SOLUTION_UNITTEST(566, ReshapetheMatrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 2},
      {3, 4}
  };
  int                 r      = 1;
  int                 c      = 4;
  vector<vector<int>> expect = {
      {1, 2, 3, 4}
  };
  vector<vector<int>> actual = solution->matrixReshape(mat, r, c);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mat = [[1,2],[3,4]], r = 2, c = 4
// Output: [[1,2],[3,4]]
//

LEETCODE_SOLUTION_UNITTEST(566, ReshapetheMatrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 2},
      {3, 4}
  };
  int                 r      = 2;
  int                 c      = 4;
  vector<vector<int>> expect = {
      {1, 2},
      {3, 4}
  };
  vector<vector<int>> actual = solution->matrixReshape(mat, r, c);
  EXPECT_EQ(expect, actual);
}
