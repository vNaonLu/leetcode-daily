// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Detect Cycles in 2D Grid
//
// https://leetcode.com/problems/detect-cycles-in-2d-grid/
//
// Question ID: 1559
// Difficult  : Medium
// Solve Date : 2021/10/19 12:05

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1559. Detect Cycles in 2D Grid|:
//
// Given a 2D array of characters |grid| of size |m x n|, you need to find if
// there exists any cycle consisting of the same value in |grid|. A cycle is a
// path of length 4 or more in the grid that starts and ends at the same cell.
// From a given cell, you can move to one of the cells adjacent to it - in one
// of the four directions (up, down, left, or right), if it has the same value
// of the current cell. Also, you cannot move to the cell that you visited in
// your last move. For example, the cycle |(1, 1) -> (1, 2) -> (1, 1)| is
// invalid because from |(1, 2)| we visited |(1, 1)| which was the last visited
// cell. Return |true| if any cycle of the same value exists in |grid|,
// otherwise, return |false|.  
//

LEETCODE_BEGIN_RESOLVING(1559, DetectCyclesIn2DGrid, Solution);

class Solution {
private:
  char                 processing = '.';
  char                 found      = ' ';
  vector<int>          direct     = {1, 0, 0, 1, -1, 0, 0, -1};
  vector<vector<char>> g;
  int                  m, n;
  bool dfs(char target, int i, int j, int prev_i = -1, int prev_j = -1) {
    if (i < 0 || i >= m || j < 0 || j >= n || g[i][j] == found)
      return false;
    if (g[i][j] == processing)
      return true;
    if (g[i][j] != target)
      return false;
    bool res = false;
    g[i][j]  = processing;
    if (i + 1 != prev_i)
      res |= dfs(target, i + 1, j, i, j);
    if (i - 1 != prev_i)
      res |= dfs(target, i - 1, j, i, j);
    if (j + 1 != prev_j)
      res |= dfs(target, i, j + 1, i, j);
    if (j - 1 != prev_j)
      res |= dfs(target, i, j - 1, i, j);
    g[i][j] = found;
    return res;
  }

public:
  bool containsCycle(vector<vector<char>> &grid) {
    m = grid.size();
    n = grid[0].size();
    g = grid;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (dfs(g[i][j], i, j))
          return true;
      }
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 500|
// * |grid| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid =
//  [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
// Output: true
//
// There are two valid cycles shown in different colors in the image below:
// ![img](https://assets.leetcode.com/uploads/2020/07/15/11.png)

LEETCODE_SOLUTION_UNITTEST(1559, DetectCyclesIn2DGrid, example_1) {
  auto                 solution = MakeSolution();
  vector<vector<char>> grid     = {
      {'a', 'a', 'a', 'a'},
      {'a', 'b', 'b', 'a'},
      {'a', 'b', 'b', 'a'},
      {'a', 'a', 'a', 'a'}
  };
  bool expect = true;
  bool actual = solution->containsCycle(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid =
//  [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
// Output: true
//
// There is only one valid cycle highlighted in the image below:
// ![img](https://assets.leetcode.com/uploads/2020/07/15/2.png)

LEETCODE_SOLUTION_UNITTEST(1559, DetectCyclesIn2DGrid, example_2) {
  auto                 solution = MakeSolution();
  vector<vector<char>> grid     = {
      {'c', 'c', 'c', 'a'},
      {'c', 'd', 'c', 'c'},
      {'c', 'c', 'e', 'c'},
      {'f', 'c', 'c', 'c'}
  };
  bool expect = true;
  bool actual = solution->containsCycle(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [["a","b","b"],["b","z","b"],["b","b","a"]]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1559, DetectCyclesIn2DGrid, example_3) {
  auto                 solution = MakeSolution();
  vector<vector<char>> grid     = {
      {'a', 'b', 'b'},
      {'b', 'z', 'b'},
      {'b', 'b', 'a'}
  };
  bool expect = false;
  bool actual = solution->containsCycle(grid);
  LCD_EXPECT_EQ(expect, actual);
}
