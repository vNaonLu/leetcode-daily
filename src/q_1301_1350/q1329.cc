// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sort the Matrix Diagonally
//
// https://leetcode.com/problems/sort-the-matrix-diagonally/
//
// Question ID: 1329
// Difficult  : Medium
// Solve Date : 2022/08/28 15:01

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1329. Sort the Matrix Diagonally|:
//
// A matrix diagonal is a diagonal line of cells starting from some cell in
// either the topmost row or leftmost column and going in the bottom-right
// direction until reaching the matrix's end. For example, the matrix diagonal
// starting from |mat[2][0]|, where |mat| is a |6 x 3| matrix, includes cells
// |mat[2][0]|, |mat[3][1]|, and |mat[4][2]|. Given an |m x n| matrix |mat| of
// integers, sort each matrix diagonal in ascending order and return the
// resulting matrix.
//

LEETCODE_BEGIN_RESOLVING(1329, SortTheMatrixDiagonally, Solution);

class Solution {
public:
  vector<vector<int>> diagonalSort(vector<vector<int>> &mat) {
    int m = mat.size();
    int n = mat.front().size();
    /// sort rows
    for (int i = m - 1; i >= 0; --i) {
      vector<int> tmp;
      int         x = i;
      int         y = 0;
      while (x < m && y < n) {
        tmp.emplace_back(mat[x++][y++]);
      }
      sort(tmp.begin(), tmp.end());
      /// store back
      auto beg = tmp.begin();
      x        = i;
      y        = 0;
      while (beg != tmp.end()) {
        mat[x++][y++] = *beg++;
      }
    }
    /// sort cols
    for (int i = 1; i < n; ++i) {
      vector<int> tmp;
      int         x = 0;
      int         y = i;
      while (x < m && y < n) {
        tmp.emplace_back(mat[x++][y++]);
      }
      sort(tmp.begin(), tmp.end());
      /// store back
      auto beg = tmp.begin();
      x        = 0;
      y        = i;
      while (beg != tmp.end()) {
        mat[x++][y++] = *beg++;
      }
    }
    return mat;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == mat.length|
// * |n == mat[i].length|
// * |1 <= m, n <= 100|
// * |1 <= mat[i][j] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mat = [[3,3,1,1],[2,2,1,2],[1,1,1,2]]
// Output: [[1,1,1,1],[1,2,2,2],[1,2,3,3]]
//

LEETCODE_SOLUTION_UNITTEST(1329, SortTheMatrixDiagonally, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {3, 3, 1, 1},
      {2, 2, 1, 2},
      {1, 1, 1, 2}
  };
  vector<vector<int>> expect = {
      {1, 1, 1, 1},
      {1, 2, 2, 2},
      {1, 2, 3, 3}
  };
  vector<vector<int>> actual = solution->diagonalSort(mat);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mat =
//  [[11,25,66,1,69,7],[23,55,17,45,15,52],[75,31,36,44,58,8],[22,27,33,25,68,4],[84,28,14,11,5,50]]
// Output:
// [[5,17,4,1,52,7],[11,11,25,45,8,69],[14,23,25,44,58,15],[22,27,31,36,50,66],[84,28,75,33,55,68]]
//

LEETCODE_SOLUTION_UNITTEST(1329, SortTheMatrixDiagonally, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {11, 25, 66,  1, 69,  7},
      {23, 55, 17, 45, 15, 52},
      {75, 31, 36, 44, 58,  8},
      {22, 27, 33, 25, 68,  4},
      {84, 28, 14, 11,  5, 50}
  };
  vector<vector<int>> expect = {
      { 5, 17,  4,  1, 52,  7},
      {11, 11, 25, 45,  8, 69},
      {14, 23, 25, 44, 58, 15},
      {22, 27, 31, 36, 50, 66},
      {84, 28, 75, 33, 55, 68}
  };
  vector<vector<int>> actual = solution->diagonalSort(mat);
  LCD_EXPECT_EQ(expect, actual);
}
