// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Where Will the Ball Fall
//
// https://leetcode.com/problems/where-will-the-ball-fall/
//
// Question ID: 1706
// Difficult  : Medium
// Solve Date : 2022/09/08 17:53

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1706. Where Will the Ball Fall|:
//
// You have a 2-D |grid| of size |m x n| representing a box, and you have |n|
// balls. The box is open on the top and bottom sides. Each cell in the box has
// a diagonal board spanning two corners of the cell that can redirect a ball to
// the right or to the left.
//
//  • A board that redirects the ball to the right spans the top-left corner to
//  the bottom-right corner and is represented in the grid as |1|.
//
//  • A board that redirects the ball to the left spans the top-right corner to
//  the bottom-left corner and is represented in the grid as |-1|.
// We drop one ball at the top of each column of the box. Each ball can get
// stuck in the box or fall out of the bottom. A ball gets stuck if it hits a
// "V" shaped pattern between two boards or if a board redirects the ball into
// either wall of the box. Return an array |answer| of size |n| where
// |answer[i]| is the column that the ball falls out of at the bottom after
// dropping the ball from the |iᵗʰ| column at the top, or |-1| if the ball gets
// stuck in the box.
//

LEETCODE_BEGIN_RESOLVING(1706, WhereWillTheBallFall, Solution);

class Solution {
public:
  vector<int> findBall(vector<vector<int>> &grid) {
    auto m   = grid.size();
    auto n   = grid.front().size();
    auto res = vector<int>(n, -1);
    auto beg = res.begin();
    while (beg != res.end()) {
      auto col = distance(res.begin(), beg);
      auto row = 0;
      while (row < m) {
        auto next_col = col + grid[row][col];
        if (next_col >= 0 && next_col < n &&
            grid[row][col] * grid[row][next_col] == 1) {
          col = next_col;
          ++row;
        } else {
          break;
        }
      }
      *beg++ = row == m ? col : -1;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 100|
// * |grid[i][j]| is |1| or |-1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid =
//  [[1,1,1,-1,-1],[1,1,1,-1,-1],[-1,-1,-1,1,1],[1,1,1,1,-1],[-1,-1,-1,-1,-1]]
// Output: [1,-1,-1,-1,-1]
//
// This example is shown in the photo.
// Ball b0 is dropped at column 0 and falls out of the box at column 1.
// Ball b1 is dropped at column 1 and will get stuck in the box between column 2
// and 3 and row 1. Ball b2 is dropped at column 2 and will get stuck on the box
// between column 2 and 3 and row 0. Ball b3 is dropped at column 3 and will get
// stuck on the box between column 2 and 3 and row 0. Ball b4 is dropped at
// column 4 and will get stuck on the box between column 2 and 3 and row 1.

LEETCODE_SOLUTION_UNITTEST(1706, WhereWillTheBallFall, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      { 1,  1,  1, -1, -1},
      { 1,  1,  1, -1, -1},
      {-1, -1, -1,  1,  1},
      { 1,  1,  1,  1, -1},
      {-1, -1, -1, -1, -1}
  };
  vector<int> expect = {1, -1, -1, -1, -1};
  vector<int> actual = solution->findBall(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[-1]]
// Output: [-1]
//
// The ball gets stuck against the left wall.

LEETCODE_SOLUTION_UNITTEST(1706, WhereWillTheBallFall, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {{-1}};
  vector<int>         expect   = {-1};
  vector<int>         actual   = solution->findBall(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid =
//  [[1,1,1,1,1,1],[-1,-1,-1,-1,-1,-1],[1,1,1,1,1,1],[-1,-1,-1,-1,-1,-1]]
// Output: [0,1,2,3,4,-1]
//

LEETCODE_SOLUTION_UNITTEST(1706, WhereWillTheBallFall, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      { 1,  1,  1,  1,  1,  1},
      {-1, -1, -1, -1, -1, -1},
      { 1,  1,  1,  1,  1,  1},
      {-1, -1, -1, -1, -1, -1}
  };
  vector<int> expect = {0, 1, 2, 3, 4, -1};
  vector<int> actual = solution->findBall(grid);
  LCD_EXPECT_EQ(expect, actual);
}
