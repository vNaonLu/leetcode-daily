// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Search a 2D Matrix II
//
// https://leetcode.com/problems/search-a-2d-matrix-ii/
//
// Question ID: 240
// Difficult  : Medium
// Solve Date : 2021/09/22 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |240. Search a 2D Matrix II|:
//
// Write an efficient algorithm that searches for a value |target| in an |m x n|
// integer matrix |matrix|. This matrix has the following properties:
//
//  • Integers in each row are sorted in ascending from left to right.
//
//  • Integers in each column are sorted in ascending from top to bottom.
//  
//

LEETCODE_BEGIN_RESOLVING(240, SearchA2DMatrixII, Solution);

class Solution {
public:
  bool searchMatrix(vector<vector<int>> &matrix, int target) {
    int r = 0, c = matrix[0].size() - 1;
    while (r < matrix.size() && c >= 0) {
      if (matrix[r][c] == target)
        return true;
      else if (matrix[r][c] > target)
        --c;
      else
        ++r;
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == matrix.length|
// * |n == matrix[i].length|
// * |1 <= n, m <= 300|
// * |-10⁹ <= matrix[i][j] <= 10⁹|
// * All the integers in each row are sorted in ascending order.
// * All the integers in each column are sorted in ascending order.
// * |-10⁹ <= target <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix =
//  [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]],
//  target = 5
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(240, SearchA2DMatrixII, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      { 1,  4,  7, 11, 15},
      { 2,  5,  8, 12, 19},
      { 3,  6,  9, 16, 22},
      {10, 13, 14, 17, 24},
      {18, 21, 23, 26, 30}
  };
  int  target = 5;
  bool expect = true;
  bool actual = solution->searchMatrix(matrix, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix =
//  [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]],
//  target = 20
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(240, SearchA2DMatrixII, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      { 1,  4,  7, 11, 15},
      { 2,  5,  8, 12, 19},
      { 3,  6,  9, 16, 22},
      {10, 13, 14, 17, 24},
      {18, 21, 23, 26, 30}
  };
  int  target = 20;
  bool expect = false;
  bool actual = solution->searchMatrix(matrix, target);
  LCD_EXPECT_EQ(expect, actual);
}
