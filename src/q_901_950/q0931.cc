// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Falling Path Sum
//
// https://leetcode.com/problems/minimum-falling-path-sum/
//
// Question ID: 931
// Difficult  : Medium
// Solve Date : 2021/10/22 13:55

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |931. Minimum Falling Path Sum|:
//
// Given an |n x n| array of integers |matrix|, return the minimum sum of any
// falling path through |matrix|. A falling path starts at any element in the
// first row and chooses the element in the next row that is either directly
// below or diagonally left/right. Specifically, the next element from position
// |(row, col)| will be |(row + 1, col - 1)|, |(row + 1, col)|, or |(row + 1,
// col + 1)|.  
//

LEETCODE_BEGIN_RESOLVING(931, MinimumFallingPathSum, Solution);

class Solution {
private:
  vector<vector<int>> dp;
  int                 helper(const vector<vector<int>> &m, int col, int row) {
    if (row >= m.size())
      return 0;
    if (dp[row][col] == numeric_limits<int>::max()) {
      if (col == 0) {
        dp[row][col] = m[row][col] + min(helper(m, col, row + 1),
                                                         helper(m, col + 1, row + 1));
      } else if (col == m.size() - 1) {
        dp[row][col] = m[row][col] + min(helper(m, col - 1, row + 1),
                                                         helper(m, col, row + 1));
      } else {
        dp[row][col] = m[row][col] + min({helper(m, col - 1, row + 1),
                                                          helper(m, col, row + 1),
                                                          helper(m, col + 1, row + 1)});
      }
    }
    return dp[row][col];
  }

public:
  int minFallingPathSum(vector<vector<int>> &matrix) {
    dp.resize(matrix.size(),
              vector<int>(matrix.size(), numeric_limits<int>::max()));
    int res = numeric_limits<int>::max();
    for (int i = 0; i < matrix.size(); ++i) {
      res = min(res, helper(matrix, i, 0));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == matrix.length == matrix[i].length|
// * |1 <= n <= 100|
// * |-100 <= matrix[i][j] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
// Output: 13
//
// There are two falling paths with a minimum sum as shown.

LEETCODE_SOLUTION_UNITTEST(931, MinimumFallingPathSum, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {2, 1, 3},
      {6, 5, 4},
      {7, 8, 9}
  };
  int expect = 13;
  int actual = solution->minFallingPathSum(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [[-19,57],[-40,-5]]
// Output: -59
//
// The falling path with a minimum sum is shown.

LEETCODE_SOLUTION_UNITTEST(931, MinimumFallingPathSum, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {-19, 57},
      {-40, -5}
  };
  int expect = -59;
  int actual = solution->minFallingPathSum(matrix);
  LCD_EXPECT_EQ(expect, actual);
}
