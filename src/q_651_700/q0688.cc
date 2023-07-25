// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Knight Probability in Chessboard
//
// https://leetcode.com/problems/knight-probability-in-chessboard/
//
// Question ID: 688
// Difficult  : Medium
// Solve Date : 2023/07/22 15:25

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |688. Knight Probability in Chessboard|:
//
// On an |n x n| chessboard, a knight starts at the cell |(row, column)| and
// attempts to make exactly |k| moves. The rows and columns are 0-indexed, so
// the top-left cell is |(0, 0)|, and the bottom-right cell is |(n - 1, n - 1)|.
// A chess knight has eight possible moves it can make, as illustrated below.
// Each move is two cells in a cardinal direction, then one cell in an
// orthogonal direction.
// ![img](https://assets.leetcode.com/uploads/2018/10/12/knight.png)
// Each time the knight is to move, it chooses one of eight possible moves
// uniformly at random (even if the piece would go off the chessboard) and moves
// there. The knight continues moving until it has made exactly |k| moves or has
// moved off the chessboard. Return the probability that the knight remains on
// the board after it has stopped moving.
//
//

LEETCODE_BEGIN_RESOLVING(688, KnightProbabilityInChessboard, Solution);

class Solution {
public:
  double knightProbability(int n, int k, int row, int column) {
    vector<vector<vector<double>>> dp(
        n, vector<vector<double>>(n, vector<double>(k + 1, 0.0)));
    return dfs(row, column, k, n, &dp);
  }

private:
  const vector<pair<int, int>> kDir = {
      { 2,  1},
      { 1,  2},
      {-1,  2},
      {-2,  1},
      {-2, -1},
      {-1, -2},
      { 1, -2},
      { 2, -1}
  };

  double dfs(int i, int j, int k, int n, vector<vector<vector<double>>> *dp) {
    if (i < 0 || j < 0 || i >= n || j >= n) {
      return 0;
    }
    if (k == 0) {
      return 1;
    }
    if ((*dp)[i][j][k] != 0) {
      return (*dp)[i][j][k];
    }

    double res = 0.0;
    for (auto [dx, dy] : kDir) {
      int x = i + dx;
      int y = j + dy;
      res += dfs(x, y, k - 1, n, dp);
    }
    return (*dp)[i][j][k] += (res / 8.0);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 25|
// * |0 <= k <= 100|
// * |0 <= row, column <= n - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, k = 2, row = 0, column = 0
// Output: 0.06250
//
// There are two moves (to (1,2), (2,1)) that will keep the knight on the board.
// From each of those positions, there are also two moves that will keep the
// knight on the board. The total probability the knight stays on the board is
// 0.0625.

LEETCODE_SOLUTION_UNITTEST(688, KnightProbabilityInChessboard, example_1) {
  auto   solution = MakeSolution();
  int    n        = 3;
  int    k        = 2;
  int    row      = 0;
  int    column   = 0;
  double expect   = 0.06250;
  double actual   = solution->knightProbability(n, k, row, column);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1, k = 0, row = 0, column = 0
// Output: 1.00000
//

LEETCODE_SOLUTION_UNITTEST(688, KnightProbabilityInChessboard, example_2) {
  auto   solution = MakeSolution();
  int    n        = 1;
  int    k        = 0;
  int    row      = 0;
  int    column   = 0;
  double expect   = 1.00000;
  double actual   = solution->knightProbability(n, k, row, column);
  LCD_EXPECT_EQ(expect, actual);
}
