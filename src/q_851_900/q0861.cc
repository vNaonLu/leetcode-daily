// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Score After Flipping Matrix
//
// https://leetcode.com/problems/score-after-flipping-matrix/
//
// Question ID: 861
// Difficult  : Medium
// Solve Date : 2024/05/13 19:41

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |861. Score After Flipping Matrix|:
//
// You are given an |m x n| binary matrix |grid|.
// A move consists of choosing any row or column and toggling each value in that
// row or column (i.e., changing all |0|'s to |1|'s, and all |1|'s to |0|'s).
// Every row of the matrix is interpreted as a binary number, and the score of
// the matrix is the sum of these numbers. Return the highest possible score
// after making any number of moves (including zero moves).
//
//

LEETCODE_BEGIN_RESOLVING(861, ScoreAfterFlippingMatrix, Solution);

class Solution {
public:
  int matrixScore(vector<vector<int>> &grid) {
    int m   = grid.size();
    int n   = grid[0].size();
    int res = (1 << (n - 1)) * m;
    for (int j = 1; j < n; ++j) {
      int val = 1 << (n - 1 - j);
      int set = 0;
      for (int i = 0; i < m; ++i) {
        if (grid[i][j] == grid[i][0]) {
          ++set;
        }
      }

      res += max(set, m - set) * val;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 20|
// * |grid[i][j]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
// Output: 39
//

LEETCODE_SOLUTION_UNITTEST(861, ScoreAfterFlippingMatrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 0, 1, 1},
      {1, 0, 1, 0},
      {1, 1, 0, 0}
  };
  int expect = 39;
  int actual = solution->matrixScore(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[0]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(861, ScoreAfterFlippingMatrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {{0}};
  int                 expect   = 1;
  int                 actual   = solution->matrixScore(grid);
  LCD_EXPECT_EQ(expect, actual);
}
