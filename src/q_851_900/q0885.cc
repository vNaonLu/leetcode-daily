// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Spiral Matrix III
//
// https://leetcode.com/problems/spiral-matrix-iii/
//
// Question ID: 885
// Difficult  : Medium
// Solve Date : 2024/08/08 21:11

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |885. Spiral Matrix III|:
//
// You start at the cell |(rStart, cStart)| of an |rows x cols| grid facing
// east. The northwest corner is at the first row and column in the grid, and
// the southeast corner is at the last row and column. You will walk in a
// clockwise spiral shape to visit every position in this grid. Whenever you
// move outside the grid's boundary, we continue our walk outside the grid (but
// may return to the grid boundary later.). Eventually, we reach all |rows *
// cols| spaces of the grid. Return an array of coordinates representing the
// positions of the grid in the order you visited them.
//
//

LEETCODE_BEGIN_RESOLVING(885, SpiralMatrixIII, Solution);

class Solution {
public:
  vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart,
                                      int cStart) {
    vector<vector<int>> res;
    vector<vector<int>> dir{
        { 0,  1},
        { 1,  0},
        { 0, -1},
        {-1,  0}
    };
    vector<int> limit{1, 1, 2, 2};
    int         cur = 0;
    while (res.size() < (rows * cols)) {
      vector<int> d = dir[cur];
      int         l = 0;
      while (l < limit[cur]) {
        if (rStart < rows && rStart >= 0 && cStart < cols && cStart >= 0) {
          res.push_back({rStart, cStart});
        }
        rStart += d[0];
        cStart += d[1];
        ++l;
      }
      limit[cur] += 2;
      ++cur;
      cur = cur % 4;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= rows, cols <= 100|
// * |0 <= rStart < rows|
// * |0 <= cStart < cols|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: rows = 1, cols = 4, rStart = 0, cStart = 0
// Output: [[0,0],[0,1],[0,2],[0,3]]
//

LEETCODE_SOLUTION_UNITTEST(885, SpiralMatrixIII, example_1) {
  auto                solution = MakeSolution();
  int                 rows     = 1;
  int                 cols     = 4;
  int                 rStart   = 0;
  int                 cStart   = 0;
  vector<vector<int>> expect   = {
      {0, 0},
      {0, 1},
      {0, 2},
      {0, 3}
  };
  vector<vector<int>> actual =
      solution->spiralMatrixIII(rows, cols, rStart, cStart);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: rows = 5, cols = 6, rStart = 1, cStart = 4
// Output:
// [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]
//

LEETCODE_SOLUTION_UNITTEST(885, SpiralMatrixIII, example_2) {
  auto                solution = MakeSolution();
  int                 rows     = 5;
  int                 cols     = 6;
  int                 rStart   = 1;
  int                 cStart   = 4;
  vector<vector<int>> expect   = {
      {1, 4},
      {1, 5},
      {2, 5},
      {2, 4},
      {2, 3},
      {1, 3},
      {0, 3},
      {0, 4},
      {0, 5},
      {3, 5},
      {3, 4},
      {3, 3},
      {3, 2},
      {2, 2},
      {1, 2},
      {0, 2},
      {4, 5},
      {4, 4},
      {4, 3},
      {4, 2},
      {4, 1},
      {3, 1},
      {2, 1},
      {1, 1},
      {0, 1},
      {4, 0},
      {3, 0},
      {2, 0},
      {1, 0},
      {0, 0}
  };
  vector<vector<int>> actual =
      solution->spiralMatrixIII(rows, cols, rStart, cStart);
  LCD_EXPECT_EQ(expect, actual);
}
