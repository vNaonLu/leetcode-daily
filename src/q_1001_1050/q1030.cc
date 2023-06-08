// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Matrix Cells in Distance Order
//
// https://leetcode.com/problems/matrix-cells-in-distance-order/
//
// Question ID: 1030
// Difficult  : Easy
// Solve Date : 2023/06/08 18:47

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1030. Matrix Cells in Distance Order|:
//
// You are given four integers |row|, |cols|, |rCenter|, and |cCenter|. There is
// a |rows x cols| matrix and you are on the cell with the coordinates
// |(rCenter, cCenter)|. Return the coordinates of all cells in the matrix,
// sorted by their distance from |(rCenter, cCenter)| from the smallest distance
// to the largest distance. You may return the answer in any order that
// satisfies this condition. The distance between two cells |(r₁, c₁)| and |(r₂,
// c₂)| is ||r₁ - r₂| + |c₁ - c₂||.
//
//

LEETCODE_BEGIN_RESOLVING(1030, MatrixCellsInDistanceOrder, Solution);

class Solution {
public:
  vector<vector<int>> allCellsDistOrder(int rows, int cols, int rCenter,
                                        int cCenter) {
    vector<vector<int>> res;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        res.emplace_back(vector<int>{i, j});
      }
    }
    sort(res.begin(), res.end(), [&](vector<int> &a, vector<int> &b) {
      return (abs(a[0] - rCenter) + abs(a[1] - cCenter)) <
             (abs(b[0] - rCenter) + abs(b[1] - cCenter));
    });
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= rows, cols <= 100|
// * |0 <= rCenter < rows|
// * |0 <= cCenter < cols|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: rows = 1, cols = 2, rCenter = 0, cCenter = 0
// Output: [[0,0],[0,1]]
//
// The distances from (0, 0) to other cells are: [0,1]

LEETCODE_SOLUTION_UNITTEST(1030, MatrixCellsInDistanceOrder, example_1) {
  auto                solution = MakeSolution();
  int                 rows     = 1;
  int                 cols     = 2;
  int                 rCenter  = 0;
  int                 cCenter  = 0;
  vector<vector<int>> expect   = {
      {0, 0},
      {0, 1}
  };
  vector<vector<int>> actual =
      solution->allCellsDistOrder(rows, cols, rCenter, cCenter);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: rows = 2, cols = 2, rCenter = 0, cCenter = 1
// Output: [[0,1],[0,0],[1,1],[1,0]]
//
// The distances from (0, 1) to other cells are: [0,1,1,2]
// The answer [[0,1],[1,1],[0,0],[1,0]] would also be accepted as correct.

LEETCODE_SOLUTION_UNITTEST(1030, MatrixCellsInDistanceOrder, example_2) {
  auto                solution = MakeSolution();
  int                 rows     = 2;
  int                 cols     = 2;
  int                 rCenter  = 0;
  int                 cCenter  = 1;
  vector<vector<int>> expect   = {
      {0, 1},
      {0, 0},
      {1, 1},
      {1, 0}
  };
  vector<vector<int>> actual =
      solution->allCellsDistOrder(rows, cols, rCenter, cCenter);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: rows = 2, cols = 3, rCenter = 1, cCenter = 2
// Output: [[1,2],[0,2],[1,1],[0,1],[1,0],[0,0]]
//
// The distances from (1, 2) to other cells are: [0,1,1,2,2,3]
// There are other answers that would also be accepted as correct, such as
// [[1,2],[1,1],[0,2],[1,0],[0,1],[0,0]].

LEETCODE_SOLUTION_UNITTEST(1030, MatrixCellsInDistanceOrder, example_3) {
  auto                solution = MakeSolution();
  int                 rows     = 2;
  int                 cols     = 3;
  int                 rCenter  = 1;
  int                 cCenter  = 2;
  vector<vector<int>> expect   = {
      {1, 2},
      {0, 2},
      {1, 1},
      {0, 1},
      {1, 0},
      {0, 0}
  };
  vector<vector<int>> actual =
      solution->allCellsDistOrder(rows, cols, rCenter, cCenter);
  EXPECT_ANYORDER_EQ(expect, actual);
}
