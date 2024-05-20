// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Check if Grid Satisfies Conditions
//
// https://leetcode.com/problems/check-if-grid-satisfies-conditions/
//
// Question ID: 3142
// Difficult  : Easy
// Solve Date : 2024/05/20 21:17

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3142. Check if Grid Satisfies Conditions|:
//
// You are given a 2D matrix |grid| of size |m x n|. You need to check if each
// cell |grid[i][j]| is:
//
//  • Equal to the cell below it, i.e. |grid[i][j] == grid[i + 1][j]| (if it
//  exists).
//
//  • Different from the cell to its right, i.e. |grid[i][j] != grid[i][j + 1]|
//  (if it exists).
// Return |true| if all the cells satisfy these conditions, otherwise, return
// |false|.
//
//

LEETCODE_BEGIN_RESOLVING(3142, CheckIfGridSatisfiesConditions, Solution);

class Solution {
public:
  bool satisfiesConditions(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (j > 0 && grid[i][j - 1] == grid[i][j]) {
          return false;
        }

        if (i > 0 && grid[i - 1][j] != grid[i][j]) {
          return false;
        }
      }
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n, m <= 10|
// * |0 <= grid[i][j] <= 9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,0,2],[1,0,2]]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3142, CheckIfGridSatisfiesConditions, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0, 2},
      {1, 0, 2}
  };
  bool expect = true;
  bool actual = solution->satisfiesConditions(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,1,1],[0,0,0]]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3142, CheckIfGridSatisfiesConditions, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1, 1},
      {0, 0, 0}
  };
  bool expect = false;
  bool actual = solution->satisfiesConditions(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1],[2],[3]]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3142, CheckIfGridSatisfiesConditions, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {{1}, {2}, {3}};
  bool                expect   = false;
  bool                actual   = solution->satisfiesConditions(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [[1,1,6,1,4,6,3,1,0,7]]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3142, CheckIfGridSatisfiesConditions,
                           extra_testcase_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 1, 6, 1, 4, 6, 3, 1, 0, 7}
  };
  bool expect = false;
  bool actual = solution->satisfiesConditions(grid);
  LCD_EXPECT_EQ(expect, actual);
}
