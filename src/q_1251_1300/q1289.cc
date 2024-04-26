// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Falling Path Sum II
//
// https://leetcode.com/problems/minimum-falling-path-sum-ii/
//
// Question ID: 1289
// Difficult  : Hard
// Solve Date : 2024/04/26 19:41

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1289. Minimum Falling Path Sum II|:
//
// Given an |n x n| integer matrix |grid|, return the minimum sum of a falling
// path with non-zero shifts. A falling path with non-zero shifts is a choice of
// exactly one element from each row of |grid| such that no two elements chosen
// in adjacent rows are in the same column.
//
//

LEETCODE_BEGIN_RESOLVING(1289, MinimumFallingPathSumII, Solution);

class Solution {
public:
  int minFallingPathSum(vector<vector<int>> &grid) {
    int                 n   = grid.size();
    int                 res = numeric_limits<int>::max();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    for (int j = 0; j < n; ++j) {
      dp[0][j] = grid[0][j];
    }

    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int tmp = numeric_limits<int>::max();

        for (int k = 0; k < n; ++k) {
          if (k != j) {
            tmp = min(tmp, grid[i][j] + dp[i - 1][k]);
          }
          dp[i][j] = tmp;
        }
      }
    }

    for (int j = 0; j < n; ++j) {
      res = min(res, dp[n - 1][j]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == grid.length == grid[i].length|
// * |1 <= n <= 200|
// * |-99 <= grid[i][j] <= 99|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
// Output: 13
//

LEETCODE_SOLUTION_UNITTEST(1289, MinimumFallingPathSumII, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };
  int expect = 13;
  int actual = solution->minFallingPathSum(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[7]]
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(1289, MinimumFallingPathSumII, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {{7}};
  int                 expect   = 7;
  int                 actual   = solution->minFallingPathSum(grid);
  LCD_EXPECT_EQ(expect, actual);
}
