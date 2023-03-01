// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Path Sum
//
// https://leetcode.com/problems/minimum-path-sum/
//
// Question ID: 64
// Difficult  : Medium
// Solve Date : 2021/10/25 14:22

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |64. Minimum Path Sum|:
//
// Given a |m x n| |grid| filled with non-negative numbers, find a path from top
// left to bottom right, which minimizes the sum of all numbers along its path.
// Note: You can only move either down or right at any point in time.
//  
//

LEETCODE_BEGIN_RESOLVING(64, MinimumPathSum, Solution);

class Solution {
public:
  int minPathSum(vector<vector<int>> &grid) {
    int m = grid.size(), n = grid[0].size();
    for (int i = m - 2; i >= 0; --i)
      grid[i][n - 1] += grid[i + 1].back();
    for (int i = n - 2; i >= 0; --i)
      grid[m - 1][i] += grid[m - 1][i + 1];
    for (int i = m - 2; i >= 0; --i) {
      for (int j = n - 2; j >= 0; --j) {
        grid[i][j] += min(grid[i + 1][j], grid[i][j + 1]);
      }
    }
    return grid.front().front();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 200|
// * |0 <= grid[i][j] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
// Output: 7
//
// Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.

LEETCODE_SOLUTION_UNITTEST(64, MinimumPathSum, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 3, 1},
      {1, 5, 1},
      {4, 2, 1}
  };
  int expect = 7;
  int actual = solution->minPathSum(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,2,3],[4,5,6]]
// Output: 12
//

LEETCODE_SOLUTION_UNITTEST(64, MinimumPathSum, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2, 3},
      {4, 5, 6}
  };
  int expect = 12;
  int actual = solution->minPathSum(grid);
  LCD_EXPECT_EQ(expect, actual);
}
