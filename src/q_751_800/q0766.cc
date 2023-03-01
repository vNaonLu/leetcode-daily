// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Toeplitz Matrix
//
// https://leetcode.com/problems/toeplitz-matrix/
//
// Question ID: 766
// Difficult  : Easy
// Solve Date : 2022/10/31 12:37

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |766. Toeplitz Matrix|:
//
// Given an |m x n| |matrix|, return |true|if the matrix is Toeplitz. Otherwise,
// return |false|. A matrix is Toeplitz if every diagonal from top-left to
// bottom-right has the same elements.
//

LEETCODE_BEGIN_RESOLVING(766, ToeplitzMatrix, Solution);

class Solution {
public:
  bool isToeplitzMatrix(vector<vector<int>> &matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
      for (int j = 0; j < matrix.front().size(); ++j) {
        if (i > 0 && j > 0 && matrix[i - 1][j - 1] != matrix[i][j]) {
          return 0;
        }
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == matrix.length|
// * |n == matrix[i].length|
// * |1 <= m, n <= 20|
// * |0 <= matrix[i][j] <= 99|
// * What if the |matrix| is stored on disk, and the memory is limited such that
// you can only load at most one row of the matrix into the memory at once?
// * What if the |matrix| is so large that you can only load up a partial row
// into the memory at once?
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
// Output: true
//
// In the above grid, thediagonals are:
// "[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]".
// In each diagonal all elements are the same, so the answer is True.

LEETCODE_SOLUTION_UNITTEST(766, ToeplitzMatrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {1, 2, 3, 4},
      {5, 1, 2, 3},
      {9, 5, 1, 2}
  };
  bool expect = true;
  bool actual = solution->isToeplitzMatrix(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [[1,2],[2,2]]
// Output: false
//
// The diagonal "[1, 2]" has different elements.

LEETCODE_SOLUTION_UNITTEST(766, ToeplitzMatrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {1, 2},
      {2, 2}
  };
  bool expect = false;
  bool actual = solution->isToeplitzMatrix(matrix);
  LCD_EXPECT_EQ(expect, actual);
}
