// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Unique Paths
//
// https://leetcode.com/problems/unique-paths/
//
// Question ID: 62
// Difficult  : Medium
// Solve Date : 2021/10/01 11:51

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |62. Unique Paths|:
//
// There is a robot on an |m x n| grid. The robot is initially located at the
// top-left corner (i.e., |grid[0][0]|). The robot tries to move to the
// bottom-right corner (i.e., |grid[m - 1][n - 1]|). The robot can only move
// either down or right at any point in time. Given the two integers |m| and
// |n|, return the number of possible unique paths that the robot can take to
// reach the bottom-right corner. The test cases are generated so that the
// answer will be less than or equal to |2 * 10⁹|.  
//

LEETCODE_BEGIN_RESOLVING(62, UniquePaths, Solution);

class Solution {
public:
  int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; ++i)
      dp[i][0] = 1;
    for (int i = 0; i < n; ++i)
      dp[0][i] = 1;
    for (int i = 1; i < m; ++i)
      for (int j = 1; j < n; ++j)
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    return dp.back().back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= m, n <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: m = 3, n = 7
// Output: 28
//

LEETCODE_SOLUTION_UNITTEST(62, UniquePaths, example_1) {
  auto solution = MakeSolution();
  int  m        = 3;
  int  n        = 7;
  int  expect   = 28;
  int  actual   = solution->uniquePaths(m, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: m = 3, n = 2
// Output: 3
//
// From the top-left corner, there are a total of 3 ways to reach the
// bottom-right corner:
// 1. Right -> Down -> Down
// 2. Down -> Down -> Right
// 3. Down -> Right -> Down

LEETCODE_SOLUTION_UNITTEST(62, UniquePaths, example_2) {
  auto solution = MakeSolution();
  int  m        = 3;
  int  n        = 2;
  int  expect   = 3;
  int  actual   = solution->uniquePaths(m, n);
  LCD_EXPECT_EQ(expect, actual);
}
