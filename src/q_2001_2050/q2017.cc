// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Grid Game
//
// https://leetcode.com/problems/grid-game/
//
// Question ID: 2017
// Difficult  : Medium
// Solve Date : 2025/01/21 20:42

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2017. Grid Game|:
//
// You are given a 0-indexed 2D array |grid| of size |2 x n|, where |grid[r][c]|
// represents the number of points at position |(r, c)| on the matrix. Two
// robots are playing a game on this matrix. Both robots initially start at |(0,
// 0)| and want to reach |(1, n-1)|. Each robot may only move to the right (
// |(r, c)| to |(r, c + 1)|) or down ( |(r, c)| to |(r + 1, c)|). At the start
// of the game, the first robot moves from |(0, 0)| to |(1, n-1)|, collecting
// all the points from the cells on its path. For all cells |(r, c)| traversed
// on the path, |grid[r][c]| is set to |0|. Then, the second robot moves from
// |(0, 0)| to |(1, n-1)|, collecting the points on its path. Note that their
// paths may intersect with one another. The first robot wants to minimize the
// number of points collected by the second robot. In contrast, the second robot
// wants to maximize the number of points it collects. If both robots play
// optimally, return the number of points collected by the second robot.
//
//

LEETCODE_BEGIN_RESOLVING(2017, GridGame, Solution);

class Solution {
public:
  long long gridGame(vector<vector<int>> &grid) {
    int64_t f   = accumulate(grid[0].begin(), grid[0].end(), 0ul);
    int64_t s   = 0;
    int64_t res = numeric_limits<int64_t>::max();
    for (int i = 0; i < grid[0].size(); ++i) {
      f -= grid[0][i];
      res = min(res, max(f, s));
      s += grid[1][i];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |grid.length == 2|
// * |n == grid[r].length|
// * |1 <= n <= 5 * 10⁴|
// * |1 <= grid[r][c] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[2,5,4],[1,5,1]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2017, GridGame, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {2, 5, 4},
      {1, 5, 1}
  };
  long long expect = 4;
  long long actual = solution->gridGame(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[3,3,1],[8,5,2]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2017, GridGame, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {3, 3, 1},
      {8, 5, 2}
  };
  long long expect = 4;
  long long actual = solution->gridGame(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[1,3,1,15],[1,3,3,1]]
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(2017, GridGame, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 3, 1, 15},
      {1, 3, 3,  1}
  };
  long long expect = 7;
  long long actual = solution->gridGame(grid);
  LCD_EXPECT_EQ(expect, actual);
}
