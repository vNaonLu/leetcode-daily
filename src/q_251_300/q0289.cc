// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Game of Life
//
// https://leetcode.com/problems/game-of-life/
//
// Question ID: 289
// Difficult  : Medium
// Solve Date : 2022/04/12 18:29

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |289. Game of Life|:
//
// According to [Wikipedia's article]: "The Game of Life, also known simply as
// Life, is a cellular automaton devised by the British mathematician John
// Horton Conway in 1970." The board is made up of an |m x n| grid of cells,
// where each cell has an initial state: live (represented by a |1|) or dead
// (represented by a |0|). Each cell interacts with its [eight neighbors]
// (horizontal, vertical, diagonal) using the following four rules (taken from
// the above Wikipedia article):
//
//  1. Any live cell with fewer than two live neighbors dies as if caused by
//  under-population.
//
//  2. Any live cell with two or three live neighbors lives on to the next
//  generation.
//
//  3. Any live cell with more than three live neighbors dies, as if by
//  over-population.
//
//  4. Any dead cell with exactly three live neighbors becomes a live cell, as
//  if by reproduction.
// The next state is created by applying the above rules simultaneously to every
// cell in the current state, where births and deaths occur simultaneously.
// Given the current state of the |m x n| grid |board|, return the next state.  
//

LEETCODE_BEGIN_RESOLVING(289, GameOfLife, Solution);

class Solution {
private:
  int         m, n;
  inline bool valid(int x, int y) { return x >= 0 && x < m && y >= 0 && y < n; }

  inline int count_neighbor(vector<vector<int>> &b, int x, int y) {
    int res = 0;
    res += valid(x - 1, y - 1) ? b[x - 1][y - 1] : 0;
    res += valid(x, y - 1) ? b[x][y - 1] : 0;
    res += valid(x + 1, y - 1) ? b[x + 1][y - 1] : 0;
    res += valid(x - 1, y) ? b[x - 1][y] : 0;
    res += valid(x + 1, y) ? b[x + 1][y] : 0;
    res += valid(x - 1, y + 1) ? b[x - 1][y + 1] : 0;
    res += valid(x, y + 1) ? b[x][y + 1] : 0;
    res += valid(x + 1, y + 1) ? b[x + 1][y + 1] : 0;

    return res;
  }

public:
  void gameOfLife(vector<vector<int>> &board) {
    m = board.size();
    n = board.front().size();
    vector<vector<int>> res(m, vector<int>(n));

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        int neighbor = count_neighbor(board, i, j);
        if (board[i][j] == 1) {
          res[i][j] = neighbor >= 2 && neighbor <= 3 ? 1 : 0;
        } else {
          res[i][j] = neighbor == 3 ? 1 : 0;
        }
      }
    }

    swap(board, res);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == board.length|
// * |n == board[i].length|
// * |1 <= m, n <= 25|
// * |board[i][j]| is |0| or |1|.
// * Could you solve it in-place? Remember that the board needs to be updated
// simultaneously: You cannot update some cells first and then use their updated
// values to update other cells.
// * In this question, we represent the board using a 2D array. In principle,
// the board is infinite, which would cause problems when the active area
// encroaches upon the border of the array (i.e., live cells reach the border).
// How would you address these problems?
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
// Output: [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
//

LEETCODE_SOLUTION_UNITTEST(289, GameOfLife, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> board    = {
      {0, 1, 0},
      {0, 0, 1},
      {1, 1, 1},
      {0, 0, 0}
  };
  vector<vector<int>> expect = {
      {0, 0, 0},
      {1, 0, 1},
      {0, 1, 1},
      {0, 1, 0}
  };
  solution->gameOfLife(board);
  LCD_EXPECT_EQ(expect, board);
}

// [Example #2]
//  Input: board = [[1,1],[1,0]]
// Output: [[1,1],[1,1]]
//

LEETCODE_SOLUTION_UNITTEST(289, GameOfLife, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> board    = {
      {1, 1},
      {1, 0}
  };
  vector<vector<int>> expect = {
      {1, 1},
      {1, 1}
  };
  solution->gameOfLife(board);
  LCD_EXPECT_EQ(expect, board);
}
