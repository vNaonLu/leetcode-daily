// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minesweeper
//
// https://leetcode.com/problems/minesweeper/
//
// Question ID: 529
// Difficult  : Medium
// Solve Date : 2024/06/20 21:04

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |529. Minesweeper|:
//
// Let's play the minesweeper game ([Wikipedia], [online game])!
// You are given an |m x n| char matrix |board| representing the game board
// where:
//
//  • |'M'| represents an unrevealed mine,
//
//  • |'E'| represents an unrevealed empty square,
//
//  • |'B'| represents a revealed blank square that has no adjacent mines (i.e.,
//  above, below, left, right, and all 4 diagonals),
//
//  • digit ( |'1'| to |'8'|) represents how many mines are adjacent to this
//  revealed square, and
//
//  • |'X'| represents a revealed mine.
// You are also given an integer array |click| where |click = [clickᵣ,
// click_{c}]| represents the next click position among all the unrevealed
// squares ( |'M'| or |'E'|). Return the board after revealing this position
// according to the following rules:
//
//  1. If a mine |'M'| is revealed, then the game is over. You should change it
//  to |'X'|.
//
//  2. If an empty square |'E'| with no adjacent mines is revealed, then change
//  it to a revealed blank |'B'| and all of its adjacent unrevealed squares
//  should be revealed recursively.
//
//  3. If an empty square |'E'| with at least one adjacent mine is revealed,
//  then change it to a digit ( |'1'| to |'8'|) representing the number of
//  adjacent mines.
//
//  4. Return the board when no more squares will be revealed.
//
//

LEETCODE_BEGIN_RESOLVING(529, Minesweeper, Solution);

class Solution {
public:
  vector<vector<char>> updateBoard(vector<vector<char>> &board,
                                   vector<int>          &click) {
    int m = board.size();
    int n = board[0].size();

    if (board[click[0]][click[1]] == 'M') {
      board[click[0]][click[1]] = 'X';
      return board;
    }

    queue<pair<int, int>> pos;
    pos.emplace(click[0], click[1]);
    board[click[0]][click[1]] = 'B';

    while (!pos.empty()) {
      auto [x, y] = pos.front();
      pos.pop();

      int mine = 0;
      for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
          if (i < 0 || i >= m || j < 0 || j >= n) {
            continue;
          }

          if (board[i][j] == 'M') {
            ++mine;
          }
        }
      }

      if (mine > 0) {
        board[x][y] = '0' + mine;
      } else {
        for (int i = x - 1; i <= x + 1; ++i) {
          for (int j = y - 1; j <= y + 1; ++j) {
            if (i < 0 || i >= m || j < 0 || j >= n) {
              continue;
            }

            if (board[i][j] == 'E') {
              board[i][j] = 'B';
              pos.emplace(i, j);
            }
          }
        }
      }
    }
    return board;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == board.length|
// * |n == board[i].length|
// * |1 <= m, n <= 50|
// * |board[i][j]| is either |'M'|, |'E'|, |'B'|, or a digit from |'1'| to
// |'8'|.
// * |click.length == 2|
// * |0 <= clickᵣ < m|
// * |0 <= click_{c} < n|
// * |board[clickᵣ][click_{c}]| is either |'M'| or |'E'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: board =
//  [["E","E","E","E","E"],["E","E","M","E","E"],["E","E","E","E","E"],["E","E","E","E","E"]],
//  click = [3,0]
// Output:
// [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]
//

LEETCODE_SOLUTION_UNITTEST(529, Minesweeper, example_1) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {
      {'E', 'E', 'E', 'E', 'E'},
      {'E', 'E', 'M', 'E', 'E'},
      {'E', 'E', 'E', 'E', 'E'},
      {'E', 'E', 'E', 'E', 'E'}
  };
  vector<int>          click  = {3, 0};
  vector<vector<char>> expect = {
      {'B', '1', 'E', '1', 'B'},
      {'B', '1', 'M', '1', 'B'},
      {'B', '1', '1', '1', 'B'},
      {'B', 'B', 'B', 'B', 'B'}
  };
  vector<vector<char>> actual = solution->updateBoard(board, click);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: board =
//  [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]],
//  click = [1,2]
// Output:
// [["B","1","E","1","B"],["B","1","X","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]
//

LEETCODE_SOLUTION_UNITTEST(529, Minesweeper, example_2) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {
      {'B', '1', 'E', '1', 'B'},
      {'B', '1', 'M', '1', 'B'},
      {'B', '1', '1', '1', 'B'},
      {'B', 'B', 'B', 'B', 'B'}
  };
  vector<int>          click  = {1, 2};
  vector<vector<char>> expect = {
      {'B', '1', 'E', '1', 'B'},
      {'B', '1', 'X', '1', 'B'},
      {'B', '1', '1', '1', 'B'},
      {'B', 'B', 'B', 'B', 'B'}
  };
  vector<vector<char>> actual = solution->updateBoard(board, click);
  LCD_EXPECT_EQ(expect, actual);
}
