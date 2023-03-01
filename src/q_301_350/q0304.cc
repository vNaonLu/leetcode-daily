// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Range Sum Query 2D - Immutable
//
// https://leetcode.com/problems/range-sum-query-2d-immutable/
//
// Question ID: 304
// Difficult  : Medium
// Solve Date : 2021/10/23 09:57

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |304. Range Sum Query 2D - Immutable|:
//
// Given a 2D matrix |matrix|, handle multiple queries of the following type:
//
//  • Calculate the sum of the elements of |matrix| inside the rectangle defined
//  by its upper left corner |(row1, col1)| and lower right corner |(row2,
//  col2)|.
// Implement the |NumMatrix| class:
//
//  • |NumMatrix(int[][] matrix)| Initializes the object with the integer matrix
//  |matrix|.
//
//  • |int sumRegion(int row1, int col1, int row2, int col2)| Returns the sum of
//  the elements of |matrix| inside the rectangle defined by its upper left
//  corner |(row1, col1)| and lower right corner |(row2, col2)|.
// You must design an algorithm where |sumRegion| works on |O(1)| time
// complexity.  
//

LEETCODE_BEGIN_RESOLVING(304, RangeSumQuery2DImmutable, NumMatrix);

class NumMatrix {
private:
  int                 m;
  int                 n;
  vector<vector<int>> presum;

public:
  NumMatrix(vector<vector<int>> &matrix) {
    m      = matrix.size();
    n      = matrix.front().size();
    presum = matrix;
    for (int i = 0; i < m; ++i)
      for (int j = 1; j < n; ++j)
        presum[i][j] += presum[i][j - 1];
  }
  int sumRegion(int row1, int col1, int row2, int col2) {
    int res = 0;
    for (int i = row1; i <= row2; ++i) {
      if (col1 > 0) {
        res += presum[i][col2] - presum[i][col1 - 1];
      } else {
        res += presum[i][col2];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(NumMatrix);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == matrix.length|
// * |n == matrix[i].length|
// * |1 <= m, n <= 200|
// * |-10⁴ <= matrix[i][j] <= 10⁴|
// * |0 <= row1 <= row2 < m|
// * |0 <= col1 <= col2 < n|
// * At most |10⁴| calls will be made to |sumRegion|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["NumMatrix", "sumRegion", "sumRegion", "sumRegion"]
// [[[[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0,
// 3, 0, 5]]], [2, 1, 4, 3], [1, 1, 2, 2], [1, 2, 2, 4]] Output: [null, 8, 11,
// 12]
//
// NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2,
// 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]); numMatrix.sumRegion(2, 1, 4,
// 3); // return 8 (i.e sum of the red rectangle) numMatrix.sumRegion(1, 1, 2,
// 2); // return 11 (i.e sum of the green rectangle) numMatrix.sumRegion(1, 2,
// 2, 4); // return 12 (i.e sum of the blue rectangle)

LEETCODE_SOLUTION_UNITTEST(304, RangeSumQuery2DImmutable, example_1) {
  vector<vector<int>> s0_matrix = {
      {3, 0, 1, 4, 2},
      {5, 6, 3, 2, 1},
      {1, 2, 0, 1, 5},
      {4, 1, 0, 1, 7},
      {1, 0, 3, 0, 5}
  };
  auto num_matrix = MakeNumMatrix(s0_matrix);
  int  s1_row1    = 2;
  int  s1_col1    = 1;
  int  s1_row2    = 4;
  int  s1_col2    = 3;
  int  s1_expect  = 8;
  int  s1_actual  = num_matrix->sumRegion(s1_row1, s1_col1, s1_row2, s1_col2);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_row1   = 1;
  int s2_col1   = 1;
  int s2_row2   = 2;
  int s2_col2   = 2;
  int s2_expect = 11;
  int s2_actual = num_matrix->sumRegion(s2_row1, s2_col1, s2_row2, s2_col2);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_row1   = 1;
  int s3_col1   = 2;
  int s3_row2   = 2;
  int s3_col2   = 4;
  int s3_expect = 12;
  int s3_actual = num_matrix->sumRegion(s3_row1, s3_col1, s3_row2, s3_col2);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
}
