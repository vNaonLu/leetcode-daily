// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Spiral Matrix
//
// https://leetcode.com/problems/spiral-matrix/
//
// Question ID: 54
// Difficult  : Medium
// Solve Date : 2021/09/16 08:00

#include <array>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |54. Spiral Matrix|:
//
// Given an |m x n| |matrix|, return all elements of the |matrix| in spiral
// order.  
//

LEETCODE_BEGIN_RESOLVING(54, SpiralMatrix, Solution);

class Solution {
private:
  inline constexpr static array<pair<int, int>, 4> dir = {
      make_pair(0, 1), make_pair(-1, 0), make_pair(0, -1), make_pair(1, 0)};

public:
  vector<int> spiralOrder(vector<vector<int>> &matrix) {
    auto m       = matrix.size();
    auto n       = matrix.front().size();
    auto res     = vector<int>(m * n, 0);
    auto step    = 0;
    auto curr    = make_pair(0, 0);
    auto beg     = res.begin();
    *beg++       = matrix[0][0];
    matrix[0][0] = -101;
    while (beg != res.end()) {
      auto &[x, y]   = curr;
      auto &[dx, dy] = dir[step & 3];

      if (x + dx >= 0 && x + dx < m && y + dy >= 0 && y + dy < n &&
          matrix[x + dx][y + dy] != -101) {
        x += dx;
        y += dy;
        *beg++       = matrix[x][y];
        matrix[x][y] = -101;
      } else {
        ++step;
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
// * |1 <= m, n <= 10|
// * |-100 <= matrix[i][j] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,2,3,6,9,8,7,4,5]
//

LEETCODE_SOLUTION_UNITTEST(54, SpiralMatrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };
  vector<int> expect = {1, 2, 3, 6, 9, 8, 7, 4, 5};
  vector<int> actual = solution->spiralOrder(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
// Output: [1,2,3,4,8,12,11,10,9,5,6,7]
//

LEETCODE_SOLUTION_UNITTEST(54, SpiralMatrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {1,  2,  3,  4},
      {5,  6,  7,  8},
      {9, 10, 11, 12}
  };
  vector<int> expect = {1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7};
  vector<int> actual = solution->spiralOrder(matrix);
  LCD_EXPECT_EQ(expect, actual);
}
