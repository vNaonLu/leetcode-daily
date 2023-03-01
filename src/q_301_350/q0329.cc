// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Increasing Path in a Matrix
//
// https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
//
// Question ID: 329
// Difficult  : Hard
// Solve Date : 2022/05/19 18:17

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |329. Longest Increasing Path in a Matrix|:
//
// Given an |m x n| integers |matrix|, return the length of the longest
// increasing path in |matrix|. From each cell, you can either move in four
// directions: left, right, up, or down. You may not move diagonally or move
// outside the boundary (i.e., wrap-around is not allowed).
//

LEETCODE_BEGIN_RESOLVING(329, LongestIncreasingPathInAMatrix, Solution);

class Solution {
private:
  int m, n;

  bool valid(int x, int y) { return x >= 0 && x < m && y >= 0 && y < n; }

  int helper(vector<vector<int>> &mat, vector<vector<int>> &dp, int x, int y) {
    if (!valid(x, y))
      return 0;

    if (dp[x][y] != -1)
      return dp[x][y];

    int l1 = 0, l2 = 0, l3 = 0, l4 = 0;

    if (valid(x + 1, y) && mat[x + 1][y] > mat[x][y]) {
      l1 = helper(mat, dp, x + 1, y);
    }
    if (valid(x, y + 1) && mat[x][y + 1] > mat[x][y]) {
      l2 = helper(mat, dp, x, y + 1);
    }
    if (valid(x - 1, y) && mat[x - 1][y] > mat[x][y]) {
      l3 = helper(mat, dp, x - 1, y);
    }
    if (valid(x, y - 1) && mat[x][y - 1] > mat[x][y]) {
      l4 = helper(mat, dp, x, y - 1);
    }

    return dp[x][y] = 1 + max({l1, l2, l3, l4});
  }

public:
  int longestIncreasingPath(vector<vector<int>> &matrix) {
    m = matrix.size();
    n = matrix.front().size();
    vector<vector<int>> dp(m, vector<int>(n, -1));
    int                 res = 0;

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (dp[i][j] == -1) {
          res = max(res, helper(matrix, dp, i, j));
        }
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
// * |1 <= m, n <= 200|
// * |0 <= matrix[i][j] <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
// Output: 4
//
// The longest increasing path is |[1, 2, 6, 9]|.

LEETCODE_SOLUTION_UNITTEST(329, LongestIncreasingPathInAMatrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {9, 9, 4},
      {6, 6, 8},
      {2, 1, 1}
  };
  int expect = 4;
  int actual = solution->longestIncreasingPath(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
// Output: 4
//
// The longest increasing path is |[3, 4, 5, 6]|. Moving diagonally is not
// allowed.

LEETCODE_SOLUTION_UNITTEST(329, LongestIncreasingPathInAMatrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {3, 4, 5},
      {3, 2, 6},
      {2, 2, 1}
  };
  int expect = 4;
  int actual = solution->longestIncreasingPath(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: matrix = [[1]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(329, LongestIncreasingPathInAMatrix, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {{1}};
  int                 expect   = 1;
  int                 actual   = solution->longestIncreasingPath(matrix);
  LCD_EXPECT_EQ(expect, actual);
}
