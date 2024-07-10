// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Max Increase to Keep City Skyline
//
// https://leetcode.com/problems/max-increase-to-keep-city-skyline/
//
// Question ID: 807
// Difficult  : Medium
// Solve Date : 2024/07/08 14:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |807. Max Increase to Keep City Skyline|:
//
// There is a city composed of |n x n| blocks, where each block contains a
// single building shaped like a vertical square prism. You are given a
// 0-indexed |n x n| integer matrix |grid| where |grid[r][c]| represents the
// height of the building located in the block at row |r| and column |c|. A
// city's skyline is the outer contour formed by all the building when viewing
// the side of the city from a distance. The skyline from each cardinal
// direction north, east, south, and west may be different. We are allowed to
// increase the height of any number of buildings by any amount (the amount can
// be different per building). The height of a |0|-height building can also be
// increased. However, increasing the height of a building should not affect the
// city's skyline from any cardinal direction. Return the maximum total sum that
// the height of the buildings can be increased by without changing the city's
// skyline from any cardinal direction.
//
//

LEETCODE_BEGIN_RESOLVING(807, MaxIncreaseToKeepCitySkyline, Solution);

class Solution {
public:
  int maxIncreaseKeepingSkyline(vector<vector<int>> &grid) {
    int                    res = 0;
    int                    n   = grid.size();
    vector<pair<int, int>> v(n, {-1, -1});
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        v[i].first  = max(v[i].first, grid[i][j]);
        v[j].second = max(v[j].second, grid[i][j]);
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        res += min(v[i].first, v[j].second) - grid[i][j];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == grid.length|
// * |n == grid[r].length|
// * |2 <= n <= 50|
// * |0 <= grid[r][c] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[3,0,8,4],[2,4,5,7],[9,2,6,3],[0,3,1,0]]
// Output: 35
//

LEETCODE_SOLUTION_UNITTEST(807, MaxIncreaseToKeepCitySkyline, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {3, 0, 8, 4},
      {2, 4, 5, 7},
      {9, 2, 6, 3},
      {0, 3, 1, 0}
  };
  int expect = 35;
  int actual = solution->maxIncreaseKeepingSkyline(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[0,0,0],[0,0,0],[0,0,0]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(807, MaxIncreaseToKeepCitySkyline, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
  };
  int expect = 0;
  int actual = solution->maxIncreaseKeepingSkyline(grid);
  LCD_EXPECT_EQ(expect, actual);
}
