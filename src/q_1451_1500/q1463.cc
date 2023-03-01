// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Cherry Pickup II
//
// https://leetcode.com/problems/cherry-pickup-ii/
//
// Question ID: 1463
// Difficult  : Hard
// Solve Date : 2022/01/08 13:55

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1463. Cherry Pickup II|:
//
// You are given a |rows x cols| matrix |grid| representing a field of cherries
// where |grid[i][j]| represents the number of cherries that you can collect
// from the |(i, j)| cell. You have two robots that can collect cherries for
// you:
//
//  • Robot #1 is located at the top-left corner |(0, 0)|, and
//
//  • Robot #2 is located at the top-right corner |(0, cols - 1)|.
// Return the maximum number of cherries collection using both robots by
// following the rules below:
//
//  • From a cell |(i, j)|, robots can move to cell |(i + 1, j - 1)|, |(i + 1,
//  j)|, or |(i + 1, j + 1)|.
//
//  • When any robot passes through a cell, It picks up all cherries, and the
//  cell becomes an empty cell.
//
//  • When both robots stay in the same cell, only one takes the cherries.
//
//  • Both robots cannot move outside of the grid at any moment.
//
//  • Both robots should reach the bottom row in |grid|.
//  
//

LEETCODE_BEGIN_RESOLVING(1463, CherryPickupII, Solution);

class Solution {
private:
  int                         m, n;
  vector<vector<int>>         grid;
  vector<vector<vector<int>>> dpcache;
  int                         dp(int row, int col1, int col2) {
    if (col1 < 0 || col1 >= n || col2 < 0 || col2 >= n)
      return 0;
    if (dpcache[row][col1][col2] != -1)
      return dpcache[row][col1][col2];
    int res = 0;
    res += grid[row][col1];
    if (col1 != col2)
      res += grid[row][col2];
    if (row != m - 1) {
      int max_value = std::numeric_limits<int>::min();
      for (int new_col1 = col1 - 1; new_col1 <= col1 + 1; ++new_col1)
        for (int new_col2 = col2 - 1; new_col2 <= col2 + 1; ++new_col2)
          max_value = max(max_value, dp(row + 1, new_col1, new_col2));
      res += max_value;
    }
    dpcache[row][col1][col2] = res;
    return res;
  }

public:
  int cherryPickup(vector<vector<int>> &grid) {
    this->grid = grid;
    m = grid.size(), n = grid[0].size();
    dpcache.clear();
    vector<vector<int>> tmp(n, vector<int>(n, -1));
    dpcache.resize(m, tmp);
    return dp(0, 0, n - 1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |rows == grid.length|
// * |cols == grid[i].length|
// * |2 <= rows, cols <= 70|
// * |0 <= grid[i][j] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
// Output: 24
//
// Path of robot #1 and #2 are described in color green and blue respectively.
// Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
// Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
// Total of cherries: 12 + 12 = 24.

LEETCODE_SOLUTION_UNITTEST(1463, CherryPickupII, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {3, 1, 1},
      {2, 5, 1},
      {1, 5, 5},
      {2, 1, 1}
  };
  int expect = 24;
  int actual = solution->cherryPickup(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid =
//  [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
// Output: 28
//
// Path of robot #1 and #2 are described in color green and blue respectively.
// Cherries taken by Robot #1, (1 + 9 + 5 + 2) = 17.
// Cherries taken by Robot #2, (1 + 3 + 4 + 3) = 11.
// Total of cherries: 17 + 11 = 28.

LEETCODE_SOLUTION_UNITTEST(1463, CherryPickupII, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 0, 0, 0, 0, 0, 1},
      {2, 0, 0, 0, 0, 3, 0},
      {2, 0, 9, 0, 0, 0, 0},
      {0, 3, 0, 5, 4, 0, 0},
      {1, 0, 2, 3, 0, 0, 6}
  };
  int expect = 28;
  int actual = solution->cherryPickup(grid);
  LCD_EXPECT_EQ(expect, actual);
}
