// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Out of Boundary Paths
//
// https://leetcode.com/problems/out-of-boundary-paths/
//
// Question ID: 576
// Difficult  : Medium
// Solve Date : 2022/07/16 14:38

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |576. Out of Boundary Paths|:
//
// There is an |m x n| grid with a ball. The ball is initially at the position
// |[startRow, startColumn]|. You are allowed to move the ball to one of the
// four adjacent cells in the grid (possibly out of the grid crossing the grid
// boundary). You can apply at most |maxMove| moves to the ball. Given the five
// integers |m|, |n|, |maxMove|, |startRow|, |startColumn|, return the number of
// paths to move the ball out of the grid boundary. Since the answer can be very
// large, return it modulo |10⁹ + 7|.
//

LEETCODE_BEGIN_RESOLVING(576, OutOfBoundaryPaths, Solution);

class Solution {
private:
  constexpr static int kMod = 1e9 + 7;

public:
  int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
    int                  res = 0;
    vector<vector<long>> dp(m, vector<long>(n, 0));
    dp[startRow][startColumn] = 1;
    for (int step = 0; step < maxMove; ++step) {
      vector<vector<long>> tmp(m, vector<long>(n));

      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
          if (i == m - 1) {
            res += dp[i][j];
            res %= kMod;
          }
          if (j == n - 1) {
            res += dp[i][j];
            res %= kMod;
          }
          if (i == 0) {
            res += dp[i][j];
            res %= kMod;
          }
          if (j == 0) {
            res += dp[i][j];
            res %= kMod;
          }

          tmp[i][j] = (i > 0 ? dp[i - 1][j] : 0) +
                      (i < m - 1 ? dp[i + 1][j] : 0) % kMod;
          tmp[i][j] += (j > 0 ? dp[i][j - 1] : 0) +
                       (j < n - 1 ? dp[i][j + 1] : 0) % kMod;
          tmp[i][j] %= kMod;
        }
      }

      dp = move(tmp);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= m, n <= 50|
// * |0 <= maxMove <= 50|
// * |0 <= startRow < m|
// * |0 <= startColumn < n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(576, OutOfBoundaryPaths, example_1) {
  auto solution    = MakeSolution();
  int  m           = 2;
  int  n           = 2;
  int  maxMove     = 2;
  int  startRow    = 0;
  int  startColumn = 0;
  int  expect      = 6;
  int  actual      = solution->findPaths(m, n, maxMove, startRow, startColumn);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
// Output: 12
//

LEETCODE_SOLUTION_UNITTEST(576, OutOfBoundaryPaths, example_2) {
  auto solution    = MakeSolution();
  int  m           = 1;
  int  n           = 3;
  int  maxMove     = 3;
  int  startRow    = 0;
  int  startColumn = 1;
  int  expect      = 12;
  int  actual      = solution->findPaths(m, n, maxMove, startRow, startColumn);
  LCD_EXPECT_EQ(expect, actual);
}
