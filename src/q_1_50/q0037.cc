// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sudoku Solver
//
// https://leetcode.com/problems/sudoku-solver/
//
// Question ID: 37
// Difficult  : Hard
// Solve Date : 2021/10/04 23:01

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |37. Sudoku Solver|:
//
// Write a program to solve a Sudoku puzzle by filling the empty cells.
// A sudoku solution must satisfy all of the following rules:
//
//  1. Each of the digits |1-9| must occur exactly once in each row.
//
//  2. Each of the digits |1-9| must occur exactly once in each column.
//
//  3. Each of the digits |1-9| must occur exactly once in each of the 9 |3x3|
//  sub-boxes of the grid.
// The |'.'| character indicates empty cells.
//  
//

LEETCODE_BEGIN_RESOLVING(37, SudokuSolver, Solution);

class Solution {
private:
  bool valid(vector<vector<char>> &b, int r, int c) {
    char keep = b[r][c];
    for (int i = 0; i < 9; ++i) {
      if (b[i][c] == keep && i != r)
        return false;
      if (b[r][i] == keep && i != c)
        return false;
    }
    int row_block = r / 3 * 3;
    int col_block = c / 3 * 3;
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (row_block + i == r && col_block + j == c)
          continue;
        if (b[row_block + i][col_block + j] == keep)
          return false;
      }
    }
    return true;
  }
  bool helper(vector<vector<char>> &b, int r = 0, int c = 0) {
    if (c == 9)
      return helper(b, r + 1, 0);
    else if (r == 9)
      return true;
    if (b[r][c] != '.')
      return helper(b, r, c + 1);
    for (char i = '1'; i <= '9'; ++i) {
      b[r][c] = i;
      if (valid(b, r, c) && helper(b, r, c + 1))
        return true;
    }
    b[r][c] = '.';
    return false;
  }

public:
  void solveSudoku(vector<vector<char>> &board) { helper(board); }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |board.length == 9|
// * |board[i].length == 9|
// * |board[i][j]| is a digit or |'.'|.
// * It is guaranteed that the input board has only one solution.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: board =
//  [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
// Output:
// [["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]
//
//  The input board is shown above and the only valid solution is shown below:
// ![img](https://upload.wikimedia.org/wikipedia/commons/thumb/3/31/Sudoku-by-L2G-20050714_solution.svg/250px-Sudoku-by-L2G-20050714_solution.svg.png)

LEETCODE_SOLUTION_UNITTEST(37, SudokuSolver, example_1) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {
      {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
  };
  vector<vector<char>> expect = {
      {'5', '3', '4', '6', '7', '8', '9', '1', '2'},
      {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
      {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
      {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
      {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
      {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
      {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
      {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
      {'3', '4', '5', '2', '8', '6', '1', '7', '9'}
  };
  solution->solveSudoku(board);
  LCD_EXPECT_EQ(expect, board);
}
