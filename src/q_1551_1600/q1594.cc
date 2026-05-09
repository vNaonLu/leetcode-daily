// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Maximum Non Negative Product in a Matrix
//
// https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/
//
// Question ID: 1594
// Difficult  : Medium
// Solve Date : 2026/03/23 19:01

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1594. Maximum Non Negative Product in a Matrix|:
//
// You are given a |m x n| matrix |grid|. Initially, you are located at the
// top-left corner |(0, 0)|, and in each step, you can only move right or down
// in the matrix. Among all possible paths starting from the top-left corner
// |(0, 0)| and ending in the bottom-right corner |(m - 1, n - 1)|, find the
// path with the maximum non-negative product. The product of a path is the
// product of all integers in the grid cells visited along the path. Return the
// maximum non-negative product modulo |10⁹ + 7|. If the maximum product is
// negative, return |-1|. Notice that the modulo is performed after getting the
// maximum product.
//
//

LEETCODE_BEGIN_RESOLVING(1594, MaximumNonNegativeProductInAMatrix, Solution);

// 2D array optimized for space
class Solution {
public:
  int maxProductPath(vector<vector<int>> &grid) {
    const int r = grid.size(), c = grid[0].size(), MOD = 1e9 + 7;
    dp        = vector<vector<int64_t>>(15, vector<int64_t>(2));
    int64_t p = dp[0][0] = dp[0][1] = grid[0][0];
    for (int j = 1; j < c; j++) {
      p *= grid[0][j];
      dp[j][0] = dp[j][1] = p;
    }
    p = grid[0][0];
    for (int i = 1; i < r; i++) {
      p *= grid[i][0];
      dp[0][0] = dp[0][1] = p;
      for (int j = 1; j < c; j++) {
        const int x             = grid[i][j];
        tie(dp[j][0], dp[j][1]) = minmax(
            {x * dp[j - 1][0], x * dp[j - 1][1], x * dp[j][0], x * dp[j][1]});
      }
    }
    int64_t res = dp[c - 1][1];
    return res < 0 ? -1 : res % MOD;
  }

private:
  vector<vector<int64_t>> dp;
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 15|
// * |-4 <= grid[i][j] <= 4|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[-1,-2,-3],[-2,-3,-3],[-3,-3,-2]]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(1594, MaximumNonNegativeProductInAMatrix,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {-1, -2, -3},
      {-2, -3, -3},
      {-3, -3, -2}
  };
  int expect = -1;
  int actual = solution->maxProductPath(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,-2,1],[1,-2,1],[3,-4,1]]
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(1594, MaximumNonNegativeProductInAMatrix,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, -2, 1},
      {1, -2, 1},
      {3, -4, 1}
  };
  int expect = 8;
  int actual = solution->maxProductPath(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,3],[0,-4]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1594, MaximumNonNegativeProductInAMatrix,
                           example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1,  3},
      {0, -4}
  };
  int expect = 0;
  int actual = solution->maxProductPath(grid);
  LCD_EXPECT_EQ(expect, actual);
}
