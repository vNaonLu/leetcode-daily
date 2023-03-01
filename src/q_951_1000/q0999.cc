// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Available Captures for Rook
//
// https://leetcode.com/problems/available-captures-for-rook/
//
// Question ID: 999
// Difficult  : Easy
// Solve Date : 2022/03/05 10:04

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |999. Available Captures for Rook|:
//
// On an |8 x 8| chessboard, there is exactly one white rook |'R'| and some
// number of white bishops |'B'|, black pawns |'p'|, and empty squares |'.'|.
// When the rook moves, it chooses one of four cardinal directions (north, east,
// south, or west), then moves in that direction until it chooses to stop,
// reaches the edge of the board, captures a black pawn, or is blocked by a
// white bishop. A rook is considered attacking a pawn if the rook can capture
// the pawn on the rook's turn. The number of available captures for the white
// rook is the number of pawns that the rook is attacking. Return the number of
// available captures for the white rook.  
//

LEETCODE_BEGIN_RESOLVING(999, AvailableCapturesForRook, Solution);

class Solution {
public:
  int numRookCaptures(vector<vector<char>> &board) {
    int            res = 0;
    pair<int, int> rock_pos;
    for (int i = 0; i < board.size(); ++i) {
      for (int j = 0; j < board.size(); ++j) {
        if (board[i][j] == 'R') {
          rock_pos = make_pair(i, j);
        }
      }
    }

    auto &[x, y] = rock_pos;
    int i        = x + 1;
    while (i < board.size()) {
      if (board[i][y] == '.') {
        ++i;
        continue;
      } else if (board[i][y] == 'p') {
        ++res;
      }
      break;
    }
    i = x - 1;
    while (i >= 0) {
      if (board[i][y] == '.') {
        --i;
        continue;
      } else if (board[i][y] == 'p') {
        ++res;
      }
      break;
    }
    i = y + 1;
    while (i < board.size()) {
      if (board[x][i] == '.') {
        ++i;
        continue;
      } else if (board[x][i] == 'p') {
        ++res;
      }
      break;
    }
    i = y - 1;
    while (i >= 0) {
      if (board[x][i] == '.') {
        --i;
        continue;
      } else if (board[x][i] == 'p') {
        ++res;
      }
      break;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |board.length == 8|
// * |board[i].length == 8|
// * |board[i][j]| is either |'R'|, |'.'|, |'B'|, or |'p'|
// * There is exactly one cell with |board[i][j] == 'R'|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: board =
//  [[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","R",".",".",".","p"],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
// Output: 3
//
// In this example, the rook is attacking all the pawns.

LEETCODE_SOLUTION_UNITTEST(999, AvailableCapturesForRook, example_1) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', 'p', '.', '.', '.', '.'},
      {'.', '.', '.', 'R', '.', '.', '.', 'p'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', 'p', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'}
  };
  int expect = 3;
  int actual = solution->numRookCaptures(board);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: board =
//  [[".",".",".",".",".",".",".","."],[".","p","p","p","p","p",".","."],[".","p","p","B","p","p",".","."],[".","p","B","R","B","p",".","."],[".","p","p","B","p","p",".","."],[".","p","p","p","p","p",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
// Output: 0
//
// The bishops are blocking the rook from attacking any of the pawns.

LEETCODE_SOLUTION_UNITTEST(999, AvailableCapturesForRook, example_2) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', 'p', 'p', 'p', 'p', 'p', '.', '.'},
      {'.', 'p', 'p', 'B', 'p', 'p', '.', '.'},
      {'.', 'p', 'B', 'R', 'B', 'p', '.', '.'},
      {'.', 'p', 'p', 'B', 'p', 'p', '.', '.'},
      {'.', 'p', 'p', 'p', 'p', 'p', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'}
  };
  int expect = 0;
  int actual = solution->numRookCaptures(board);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: board =
//  [[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","p",".",".",".","."],["p","p",".","R",".","p","B","."],[".",".",".",".",".",".",".","."],[".",".",".","B",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."]]
// Output: 3
//
// The rook is attacking the pawns at positions b5, d6, and f5.

LEETCODE_SOLUTION_UNITTEST(999, AvailableCapturesForRook, example_3) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', 'p', '.', '.', '.', '.'},
      {'.', '.', '.', 'p', '.', '.', '.', '.'},
      {'p', 'p', '.', 'R', '.', 'p', 'B', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', 'B', '.', '.', '.', '.'},
      {'.', '.', '.', 'p', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'}
  };
  int expect = 3;
  int actual = solution->numRookCaptures(board);
  LCD_EXPECT_EQ(expect, actual);
}
