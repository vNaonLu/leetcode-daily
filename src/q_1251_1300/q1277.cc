// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Count Square Submatrices with All Ones
//
// https://leetcode.com/problems/count-square-submatrices-with-all-ones/
//
// Question ID: 1277
// Difficult  : Medium
// Solve Date : 2024/10/27 13:47

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1277. Count Square Submatrices with All Ones|:
//
// Given a |m * n| matrix of ones and zeros, return how many square submatrices
// have all ones.
//
//

LEETCODE_BEGIN_RESOLVING(1277, CountSquareSubmatricesWithAllOnes, Solution);

class Solution {
public:
  int countSquares(vector<vector<int>> &matrix) {
    int                 m = matrix.size();
    int                 n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n));
    int                 res = 0;
    for (int i = 0; i < m; ++i) {
      dp[i][0] = matrix[i][0];
      res += dp[i][0];
    }
    for (int j = 1; j < n; ++j) {
      dp[0][j] = matrix[0][j];
      res += dp[0][j];
    }
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        if (matrix[i][j] == 1) {
          dp[i][j] = 1 + min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]});
        }
        res += dp[i][j];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 300|
// * |1 <= arr[0].length <= 300|
// * |0 <= arr[i][j] <= 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix =
// [
//   [0,1,1,1],
//   [1,1,1,1],
//   [0,1,1,1]
// ]
// Output: 15
//

LEETCODE_SOLUTION_UNITTEST(1277, CountSquareSubmatricesWithAllOnes, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {0, 1, 1, 1},
      {1, 1, 1, 1},
      {0, 1, 1, 1}
  };
  int expect = 15;
  int actual = solution->countSquares(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix =
// [
//  [1,0,1],
//  [1,1,0],
//  [1,1,0]
// ]
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(1277, CountSquareSubmatricesWithAllOnes, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {1, 0, 1},
      {1, 1, 0},
      {1, 1, 0}
  };
  int expect = 7;
  int actual = solution->countSquares(matrix);
  LCD_EXPECT_EQ(expect, actual);
}
