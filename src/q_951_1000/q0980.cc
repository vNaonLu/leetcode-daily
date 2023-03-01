// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Unique Paths III
//
// https://leetcode.com/problems/unique-paths-iii/
//
// Question ID: 980
// Difficult  : Hard
// Solve Date : 2021/11/02 18:23

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |980. Unique Paths III|:
//
// You are given an |m x n| integer array |grid| where |grid[i][j]| could be:
//
//  • |1| representing the starting square. There is exactly one starting
//  square.
//
//  • |2| representing the ending square. There is exactly one ending square.
//
//  • |0| representing empty squares we can walk over.
//
//  • |-1| representing obstacles that we cannot walk over.
// Return the number of 4-directional walks from the starting square to the
// ending square, that walk over every non-obstacle square exactly once.  
//

LEETCODE_BEGIN_RESOLVING(980, UniquePathsIII, Solution);

class Solution {
private:
  int  res   = 0;
  int  empty = 1;
  int  m, n;
  void helper(vector<vector<int>> &grid, int i, int j, int cnt = 0) {
    if (i < 0 || i >= m || j < 0 || j >= n)
      return;
    if (grid[i][j] == -1)
      return;
    if (grid[i][j] == 2) {
      if (cnt == empty)
        ++res;
      return;
    }
    ++cnt;
    grid[i][j] = -1;
    helper(grid, i + 1, j, cnt);
    helper(grid, i, j + 1, cnt);
    helper(grid, i - 1, j, cnt);
    helper(grid, i, j - 1, cnt);
    grid[i][j] = 0;
  }

public:
  int uniquePathsIII(vector<vector<int>> &grid) {
    m      = grid.size();
    n      = grid[0].size();
    int si = -1, sj = -1;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) {
          si = i;
          sj = j;
        } else if (grid[i][j] == 0) {
          ++empty;
        }
      }
    }
    helper(grid, si, sj);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 20|
// * |1 <= m * n <= 20|
// * |-1 <= grid[i][j] <= 2|
// * There is exactly one starting cell and one ending cell.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
// Output: 2
//
// We have the following two paths:
// 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
// 2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)

LEETCODE_SOLUTION_UNITTEST(980, UniquePathsIII, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0, 0,  0},
      {0, 0, 0,  0},
      {0, 0, 2, -1}
  };
  int expect = 2;
  int actual = solution->uniquePathsIII(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
// Output: 4
//
// We have the following four paths:
// 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
// 2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
// 3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
// 4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)

LEETCODE_SOLUTION_UNITTEST(980, UniquePathsIII, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 2}
  };
  int expect = 4;
  int actual = solution->uniquePathsIII(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[0,1],[2,0]]
// Output: 0
//
// There is no path that walks over every empty square exactly once.
// Note that the starting and ending square can be anywhere in the grid.

LEETCODE_SOLUTION_UNITTEST(980, UniquePathsIII, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 1},
      {2, 0}
  };
  int expect = 0;
  int actual = solution->uniquePathsIII(grid);
  LCD_EXPECT_EQ(expect, actual);
}
