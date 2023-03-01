// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximal Square
//
// https://leetcode.com/problems/maximal-square/
//
// Question ID: 221
// Difficult  : Medium
// Solve Date : 2021/10/25 14:23

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |221. Maximal Square|:
//
// Given an |m x n| binary |matrix| filled with |0|'s and |1|'s, find the
// largest square containing only |1|'s and return its area.  
//

LEETCODE_BEGIN_RESOLVING(221, MaximalSquare, Solution);

class Solution {
public:
  int maximalSquare(vector<vector<char>> &matrix) {
    int                 m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    int                 res = 0;
    for (int i = 0; i < m; ++i) {
      dp[i][0] = matrix[i][0] == '1' ? 1 : 0;
      res      = max(res, dp[i][0]);
    }
    for (int i = 0; i < n; ++i) {
      dp[0][i] = matrix[0][i] == '1' ? 1 : 0;
      res      = max(res, dp[0][i]);
    }
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        if (matrix[i][j] == '1') {
          dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
          res      = max(res, dp[i][j]);
        }
      }
    }
    return res * res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == matrix.length|
// * |n == matrix[i].length|
// * |1 <= m, n <= 300|
// * |matrix[i][j]| is |'0'| or |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix =
//  [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(221, MaximalSquare, example_1) {
  auto                 solution = MakeSolution();
  vector<vector<char>> matrix   = {
      {'1', '0', '1', '0', '0'},
      {'1', '0', '1', '1', '1'},
      {'1', '1', '1', '1', '1'},
      {'1', '0', '0', '1', '0'}
  };
  int expect = 4;
  int actual = solution->maximalSquare(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [["0","1"],["1","0"]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(221, MaximalSquare, example_2) {
  auto                 solution = MakeSolution();
  vector<vector<char>> matrix   = {
      {'0', '1'},
      {'1', '0'}
  };
  int expect = 1;
  int actual = solution->maximalSquare(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: matrix = [["0"]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(221, MaximalSquare, example_3) {
  auto                 solution = MakeSolution();
  vector<vector<char>> matrix   = {{'0'}};
  int                  expect   = 0;
  int                  actual   = solution->maximalSquare(matrix);
  LCD_EXPECT_EQ(expect, actual);
}
