// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Unique Paths II
//
// https://leetcode.com/problems/unique-paths-ii/
//
// Question ID: 63
// Difficult  : Medium
// Solve Date : 2021/10/24 22:07

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |63. Unique Paths II|:
//
// You are given an |m x n| integer array |grid|. There is a robot initially
// located at the top-left corner (i.e., |grid[0][0]|). The robot tries to move
// to the bottom-right corner (i.e., |grid[m - 1][n - 1]|). The robot can only
// move either down or right at any point in time. An obstacle and space are
// marked as |1| or |0| respectively in |grid|. A path that the robot takes
// cannot include any square that is an obstacle. Return the number of possible
// unique paths that the robot can take to reach the bottom-right corner. The
// testcases are generated so that the answer will be less than or equal to |2 *
// 10⁹|.  
//

LEETCODE_BEGIN_RESOLVING(63, UniquePathsII, Solution);

class Solution {
public:
  int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
    int                 m = obstacleGrid.size(), n = obstacleGrid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = obstacleGrid[0][0] == 1 ? 0 : 1;
    for (int i = 1; i < m; ++i)
      dp[i][0] = obstacleGrid[i][0] == 1 ? 0 : dp[i - 1][0];
    for (int j = 1; j < n; ++j)
      dp[0][j] = obstacleGrid[0][j] == 1 ? 0 : dp[0][j - 1];
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        if (obstacleGrid[i][j] == 1) {
          dp[i][j] = 0;
        } else {
          dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
      }
    }
    return dp.back().back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == obstacleGrid.length|
// * |n == obstacleGrid[i].length|
// * |1 <= m, n <= 100|
// * |obstacleGrid[i][j]| is |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
// Output: 2
//
// There is one obstacle in the middle of the 3x3 grid above.
// There are two ways to reach the bottom-right corner:
// 1. Right -> Right -> Down -> Down
// 2. Down -> Down -> Right -> Right

LEETCODE_SOLUTION_UNITTEST(63, UniquePathsII, example_1) {
  auto                solution     = MakeSolution();
  vector<vector<int>> obstacleGrid = {
      {0, 0, 0},
      {0, 1, 0},
      {0, 0, 0}
  };
  int expect = 2;
  int actual = solution->uniquePathsWithObstacles(obstacleGrid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: obstacleGrid = [[0,1],[0,0]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(63, UniquePathsII, example_2) {
  auto                solution     = MakeSolution();
  vector<vector<int>> obstacleGrid = {
      {0, 1},
      {0, 0}
  };
  int expect = 1;
  int actual = solution->uniquePathsWithObstacles(obstacleGrid);
  LCD_EXPECT_EQ(expect, actual);
}
