// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Valid Tic-Tac-Toe State
//
// https://leetcode.com/problems/valid-tic-tac-toe-state/
//
// Question ID: 794
// Difficult  : Medium
// Solve Date : 2022/06/09 18:35

#include <array>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |794. Valid Tic-Tac-Toe State|:
//
// Given a Tic-Tac-Toe board as a string array |board|, return |true| if and
// only if it is possible to reach this board position during the course of a
// valid tic-tac-toe game. The board is a |3 x 3| array that consists of
// characters |' '|, |'X'|, and |'O'|. The |' '| character represents an empty
// square. Here are the rules of Tic-Tac-Toe:
//
//  • Players take turns placing characters into empty squares |' '|.
//
//  • The first player always places |'X'| characters, while the second player
//  always places |'O'| characters.
//
//  • |'X'| and |'O'| characters are always placed into empty squares, never
//  filled ones.
//
//  • The game ends when there are three of the same (non-empty) character
//  filling any row, column, or diagonal.
//
//  • The game also ends if all squares are non-empty.
//
//  • No more moves can be played if the game is over.
//

LEETCODE_BEGIN_RESOLVING(794, ValidTicTacToeState, Solution);

class Solution {
private:
  /**
   * 0 1 2
   * 3 4 5
   * 6 7 8
   */
  inline static constexpr array<array<int, 3>, 8> lines{
      array<int, 3>{0, 1, 2},
       array<int, 3>{3, 4, 5},
       array<int, 3>{6, 7, 8},
      array<int, 3>{0, 3, 6},
       array<int, 3>{1, 4, 7},
       array<int, 3>{2, 5, 8},
      array<int, 3>{0, 4, 8},
       array<int, 3>{2, 4, 6}
  };

  inline static constexpr array<pair<int, int>, 9> conv{
      pair<int, int>{0, 0},
       pair<int, int>{0, 1},
       pair<int, int>{0, 2},
      pair<int, int>{1, 0},
       pair<int, int>{1, 1},
       pair<int, int>{1, 2},
      pair<int, int>{2, 0},
       pair<int, int>{2, 1},
       pair<int, int>{2, 2},
  };

  bool is_winner(char c, vector<string> &b) {
    for (auto &l : lines) {
      auto &[x1, y1] = conv[l[0]];
      auto &[x2, y2] = conv[l[1]];
      auto &[x3, y3] = conv[l[2]];

      if (b[x1][y1] == c && b[x1][y1] == b[x2][y2] && b[x2][y2] == b[x3][y3]) {
        return true;
      }
    }

    return false;
  }

public:
  bool validTicTacToe(vector<string> &board) {
    int X_cnt = 0, O_cnt = 0;

    for (auto &s : board) {
      for (auto &c : s) {
        if (c == 'X') {
          ++X_cnt;
        } else if (c == 'O') {
          ++O_cnt;
        }
      }
    }

    if (X_cnt - O_cnt > 1 || X_cnt < O_cnt) {
      return false;
    } else if (is_winner('X', board) && X_cnt == O_cnt) {
      return false;
    } else if (is_winner('O', board) && O_cnt != X_cnt) {
      return false;
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |board.length == 3|
// * |board[i].length == 3|
// * |board[i][j]| is either |'X'|, |'O'|, or |' '|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: board = ["O "," "," "]
// Output: false
//
// The first player always plays "X".

LEETCODE_SOLUTION_UNITTEST(794, ValidTicTacToeState, example_1) {
  auto           solution = MakeSolution();
  vector<string> board    = {"O ", " ", " "};
  bool           expect   = false;
  bool           actual   = solution->validTicTacToe(board);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: board = ["XOX"," X "," "]
// Output: false
//
// Players take turns making moves.

LEETCODE_SOLUTION_UNITTEST(794, ValidTicTacToeState, example_2) {
  auto           solution = MakeSolution();
  vector<string> board    = {"XOX", " X ", " "};
  bool           expect   = false;
  bool           actual   = solution->validTicTacToe(board);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: board = ["XOX","O O","XOX"]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(794, ValidTicTacToeState, example_3) {
  auto           solution = MakeSolution();
  vector<string> board    = {"XOX", "O O", "XOX"};
  bool           expect   = true;
  bool           actual   = solution->validTicTacToe(board);
  LCD_EXPECT_EQ(expect, actual);
}
