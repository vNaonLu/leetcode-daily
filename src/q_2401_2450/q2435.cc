// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Paths in Matrix Whose Sum Is Divisible by K
//
// https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/
//
// Question ID: 2435
// Difficult  : Hard
// Solve Date : 2025/11/26 22:20

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2435. Paths in Matrix Whose Sum Is Divisible by K|:
//
// You are given a 0-indexed |m x n| integer matrix |grid| and an integer |k|.
// You are currently at position |(0, 0)| and you want to reach position |(m -
// 1, n - 1)| moving only down or right. Return the number of paths where the
// sum of the elements on the path is divisible by |k|. Since the answer may be
// very large, return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(2435, PathsInMatrixWhoseSumIsDivisibleByK, Solution);

class Solution {
public:
  int rec(int i, int j, int sum, vector<vector<int>> &grid, int &k,
          vector<vector<vector<int>>> &dp) {
    int n = grid.size(), m = grid[0].size();

    if (i == n - 1 && j == m - 1)
      return sum % k == 0 ? 1 : 0;

    if (dp[i][j][sum] != -1)
      return dp[i][j][sum];

    int right = 0, down = 0;

    if (j + 1 < m)
      right = rec(i, j + 1, (sum + grid[i][j + 1]) % k, grid, k, dp);

    if (i + 1 < n)
      down = rec(i + 1, j, (sum + grid[i + 1][j]) % k, grid, k, dp);

    return dp[i][j][sum] = (right + down) % 1000000007;
  }

  int numberOfPaths(vector<vector<int>> &grid, int k) {
    int n = grid.size(), m = grid[0].size();

    if (k == 1) {
      vector<vector<int>> ways(n, vector<int>(m, 1));
      for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
          ways[i][j] = (ways[i - 1][j] + ways[i][j - 1]) % 1000000007;
      return ways[n - 1][m - 1];
    }

    vector<vector<vector<int>>> dp(n,
                                   vector<vector<int>>(m, vector<int>(k, -1)));

    return rec(0, 0, (grid[0][0]) % k, grid, k, dp);
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 5 * 10⁴|
// * |1 <= m * n <= 5 * 10⁴|
// * |0 <= grid[i][j] <= 100|
// * |1 <= k <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[5,2,4],[3,0,5],[0,7,2]], k = 3
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2435, PathsInMatrixWhoseSumIsDivisibleByK,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {5, 2, 4},
      {3, 0, 5},
      {0, 7, 2}
  };
  int k      = 3;
  int expect = 2;
  int actual = solution->numberOfPaths(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[0,0]], k = 5
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2435, PathsInMatrixWhoseSumIsDivisibleByK,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 0}
  };
  int k      = 5;
  int expect = 1;
  int actual = solution->numberOfPaths(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[7,3,4,9],[2,3,6,2],[2,3,7,0]], k = 1
// Output: 10
//

LEETCODE_SOLUTION_UNITTEST(2435, PathsInMatrixWhoseSumIsDivisibleByK,
                           example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {7, 3, 4, 9},
      {2, 3, 6, 2},
      {2, 3, 7, 0}
  };
  int k      = 1;
  int expect = 10;
  int actual = solution->numberOfPaths(grid, k);
  LCD_EXPECT_EQ(expect, actual);
}
