// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Winner on a Tic Tac Toe Game
//
// https://leetcode.com/problems/find-winner-on-a-tic-tac-toe-game/
//
// Question ID: 1275
// Difficult  : Easy
// Solve Date : 2021/09/20 08:00

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1275. Find Winner on a Tic Tac Toe Game|:
//
// Tic-tac-toe is played by two players |A| and |B| on a |3 x 3| grid. The rules
// of Tic-Tac-Toe are:
//
//  • Players take turns placing characters into empty squares |' '|.
//
//  • The first player |A| always places |'X'| characters, while the second
//  player |B| always places |'O'| characters.
//
//  • |'X'| and |'O'| characters are always placed into empty squares, never on
//  filled ones.
//
//  • The game ends when there are three of the same (non-empty) character
//  filling any row, column, or diagonal.
//
//  • The game also ends if all squares are non-empty.
//
//  • No more moves can be played if the game is over.
// Given a 2D integer array |moves| where |moves[i] = [rowᵢ, colᵢ]| indicates
// that the |iᵗʰ| move will be played on |grid[rowᵢ][colᵢ]|. return the winner
// of the game if it exists ( |A| or |B|). In case the game ends in a draw
// return |"Draw"|. If there are still movements to play return |"Pending"|. You
// can assume that |moves| is valid (i.e., it follows the rules of Tic-Tac-Toe),
// the grid is initially empty, and |A| will play first.  
//

LEETCODE_BEGIN_RESOLVING(1275, FindWinnerOnATicTacToeGame, Solution);

class Solution {
private:
  bool winner(const vector<vector<int>> &b, const int &r, const int &c) {
    if (b[r][0] == b[r][1] && b[r][1] == b[r][2])
      return true;
    if (b[0][c] == b[1][c] && b[1][c] == b[2][c])
      return true;
    if (c + r == 2 && b[2][0] == b[1][1] && b[1][1] == b[0][2])
      return true;
    if (c == r && b[0][0] == b[1][1] && b[1][1] == b[2][2])
      return true;
    return false;
  }

public:
  string tictactoe(vector<vector<int>> &moves) {
    vector<vector<int>> board(3, vector<int>(3, 0));
    int                 val = 1;
    for (int i = 0; i < moves.size(); ++i) {
      board[moves[i][0]][moves[i][1]] = val;
      if (winner(board, moves[i][0], moves[i][1])) {
        return val == 1 ? "A" : "B";
      }
      val *= -1;
    }
    return moves.size() == 9 ? "Draw" : "Pending";
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= moves.length <= 9|
// * |moves[i].length == 2|
// * |0 <= rowᵢ, colᵢ <= 2|
// * There are no repeated elements on |moves|.
// * |moves| follow the rules of tic tac toe.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: moves = [[0,0],[2,0],[1,1],[2,1],[2,2]]
// Output: "A"
//
// A wins, they always play first.

LEETCODE_SOLUTION_UNITTEST(1275, FindWinnerOnATicTacToeGame, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> moves    = {
      {0, 0},
      {2, 0},
      {1, 1},
      {2, 1},
      {2, 2}
  };
  string expect = "A";
  string actual = solution->tictactoe(moves);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: moves = [[0,0],[1,1],[0,1],[0,2],[1,0],[2,0]]
// Output: "B"
//
// B wins.

LEETCODE_SOLUTION_UNITTEST(1275, FindWinnerOnATicTacToeGame, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> moves    = {
      {0, 0},
      {1, 1},
      {0, 1},
      {0, 2},
      {1, 0},
      {2, 0}
  };
  string expect = "B";
  string actual = solution->tictactoe(moves);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: moves = [[0,0],[1,1],[2,0],[1,0],[1,2],[2,1],[0,1],[0,2],[2,2]]
// Output: "Draw"
//
// The game ends in a draw since there are no moves to make.

LEETCODE_SOLUTION_UNITTEST(1275, FindWinnerOnATicTacToeGame, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> moves    = {
      {0, 0},
      {1, 1},
      {2, 0},
      {1, 0},
      {1, 2},
      {2, 1},
      {0, 1},
      {0, 2},
      {2, 2}
  };
  string expect = "Draw";
  string actual = solution->tictactoe(moves);
  LCD_EXPECT_EQ(expect, actual);
}
