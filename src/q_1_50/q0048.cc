// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Rotate Image
//
// https://leetcode.com/problems/rotate-image/
//
// Question ID: 48
// Difficult  : Medium
// Solve Date : 2021/09/21 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |48. Rotate Image|:
//
// You are given an |n x n| 2D |matrix| representing an image, rotate the image
// by 90 degrees (clockwise). You have to rotate the image in-place, which means
// you have to modify the input 2D matrix directly. DO NOT allocate another 2D
// matrix and do the rotation.  
//

LEETCODE_BEGIN_RESOLVING(48, RotateImage, Solution);

class Solution {
public:
  void rotate(vector<vector<int>> &matrix) {
    auto n   = (int)matrix.size();
    auto res = vector<vector<int>>(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        res[j][n - i - 1] = matrix[i][j];
      }
    }
    matrix = move(res);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == matrix.length == matrix[i].length|
// * |1 <= n <= 20|
// * |-1000 <= matrix[i][j] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [[7,4,1],[8,5,2],[9,6,3]]
//

LEETCODE_SOLUTION_UNITTEST(48, RotateImage, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };
  vector<vector<int>> expect = {
      {7, 4, 1},
      {8, 5, 2},
      {9, 6, 3}
  };
  solution->rotate(matrix);
  LCD_EXPECT_EQ(expect, matrix);
}

// [Example #2]
//  Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
// Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
//

LEETCODE_SOLUTION_UNITTEST(48, RotateImage, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      { 5,  1,  9, 11},
      { 2,  4,  8, 10},
      {13,  3,  6,  7},
      {15, 14, 12, 16}
  };
  vector<vector<int>> expect = {
      {15, 13,  2,  5},
      {14,  3,  4,  1},
      {12,  6,  8,  9},
      {16,  7, 10, 11}
  };
  solution->rotate(matrix);
  LCD_EXPECT_EQ(expect, matrix);
}
