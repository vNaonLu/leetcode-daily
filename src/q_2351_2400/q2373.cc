// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Largest Local Values in a Matrix
//
// https://leetcode.com/problems/largest-local-values-in-a-matrix/
//
// Question ID: 2373
// Difficult  : Easy
// Solve Date : 2023/02/19 14:42

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2373. Largest Local Values in a Matrix|:
//
// You are given an |n x n| integer matrix |grid|.
// Generate an integer matrix |maxLocal| of size |(n - 2) x (n - 2)| such that:
//
//  • |maxLocal[i][j]| is equal to the largest value of the |3 x 3| matrix in
//  |grid| centered around row |i + 1| and column |j + 1|.
// In other words, we want to find the largest value in every contiguous |3 x 3|
// matrix in |grid|. Return the generated matrix.
//

LEETCODE_BEGIN_RESOLVING(2373, LargestLocalValuesInAMatrix, Solution);

class Solution {
private:
  int getMax(vector<vector<int>> &grid, int r, int c) {
    int res = grid[r][c];
    for (int i = r; i < r + 3; ++i) {
      for (int j = c; j < c + 3; ++j) {
        res = max(res, grid[i][j]);
      }
    }
    return res;
  }

public:
  vector<vector<int>> largestLocal(vector<vector<int>> &grid) {
    int                 n = grid.size();
    vector<vector<int>> res;
    for (int i = 0; i < n - 2; ++i) {
      res.emplace_back();
      for (int j = 0; j < n - 2; ++j) {
        res.back().emplace_back(getMax(grid, i, j));
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == grid.length == grid[i].length|
// * |3 <= n <= 100|
// * |1 <= grid[i][j] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[9,9,8,1],[5,6,2,6],[8,2,6,4],[6,2,2,2]]
// Output: [[9,9],[8,6]]
//
// The diagram above shows the original matrix and the generated matrix.
// Notice that each value in the generated matrix corresponds to the largest
// value of a contiguous 3 x 3 matrix in grid.

LEETCODE_SOLUTION_UNITTEST(2373, LargestLocalValuesInAMatrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {9, 9, 8, 1},
      {5, 6, 2, 6},
      {8, 2, 6, 4},
      {6, 2, 2, 2}
  };
  vector<vector<int>> expect = {
      {9, 9},
      {8, 6}
  };
  vector<vector<int>> actual = solution->largestLocal(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,1,1,1,1],[1,1,1,1,1],[1,1,2,1,1],[1,1,1,1,1],[1,1,1,1,1]]
// Output: [[2,2,2],[2,2,2],[2,2,2]]
//
// Notice that the 2 is contained within every contiguous 3 x 3 matrix in grid.

LEETCODE_SOLUTION_UNITTEST(2373, LargestLocalValuesInAMatrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1},
      {1, 1, 2, 1, 1},
      {1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1}
  };
  vector<vector<int>> expect = {
      {2, 2, 2},
      {2, 2, 2},
      {2, 2, 2}
  };
  vector<vector<int>> actual = solution->largestLocal(grid);
  LCD_EXPECT_EQ(expect, actual);
}
