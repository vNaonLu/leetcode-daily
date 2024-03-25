// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Battleships in a Board
//
// https://leetcode.com/problems/battleships-in-a-board/
//
// Question ID: 419
// Difficult  : Medium
// Solve Date : 2024/03/25 19:38

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |419. Battleships in a Board|:
//
// Given an |m x n| matrix |board| where each cell is a battleship |'X'| or
// empty |'.'|, return the number of the battleships on |board|. Battleships can
// only be placed horizontally or vertically on |board|. In other words, they
// can only be made of the shape |1 x k| ( |1| row, |k| columns) or |k x 1| (
// |k| rows, |1| column), where |k| can be of any size. At least one horizontal
// or vertical cell separates between two battleships (i.e., there are no
// adjacent battleships).
//
//

LEETCODE_BEGIN_RESOLVING(419, BattleshipsInABoard, Solution);

class Solution {
public:
  int countBattleships(vector<vector<char>> &board) {
    int m   = board.size();
    int n   = board[0].size();
    int res = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if ('X' == board[i][j]) {
          dfs(&board, i, j);
          ++res;
        }
      }
    }
    return res;
  }

private:
  void dfs(vector<vector<char>> *grid, int i, int j) {
    int m = grid->size();
    int n = (*grid)[0].size();
    if (i < 0 || j < 0 || i >= m || j >= n || (*grid)[i][j] != 'X') {
      return;
    }
    (*grid)[i][j] = 'Y';
    dfs(grid, i + 1, j);
    dfs(grid, i, j + 1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == board.length|
// * |n == board[i].length|
// * |1 <= m, n <= 200|
// * |board[i][j]| is either |'.'| or |'X'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: board = [["X",".",".","X"],[".",".",".","X"],[".",".",".","X"]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(419, BattleshipsInABoard, example_1) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {
      {'X', '.', '.', 'X'},
      {'.', '.', '.', 'X'},
      {'.', '.', '.', 'X'}
  };
  int expect = 2;
  int actual = solution->countBattleships(board);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: board = [["."]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(419, BattleshipsInABoard, example_2) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {{'.'}};
  int                  expect   = 0;
  int                  actual   = solution->countBattleships(board);
  LCD_EXPECT_EQ(expect, actual);
}
