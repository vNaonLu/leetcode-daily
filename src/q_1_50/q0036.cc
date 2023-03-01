// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Valid Sudoku
//
// https://leetcode.com/problems/valid-sudoku/
//
// Question ID: 36
// Difficult  : Medium
// Solve Date : 2021/09/09 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |36. Valid Sudoku|:
//
// Determine if a  |9 x 9| Sudoku board is valid. Only the filled cells need to
// be validated according to the following rules:
//
//  1. Each row must contain the digits  |1-9| without repetition.
//
//  2. Each column must contain the digits  |1-9| without repetition.
//
//  3. Each of the nine  |3 x 3| sub-boxes of the grid must contain the digits 
//  |1-9| without repetition.
// Note:
//
//  • A Sudoku board (partially filled) could be valid but is not necessarily
//  solvable.
//
//  • Only the filled cells need to be validated according to the
//  mentioned rules.
//  
//

LEETCODE_BEGIN_RESOLVING(36, ValidSudoku, Solution);

class Solution {
public:
  bool isValidSudoku(vector<vector<char>> &board) {
    return helper(board, 0, 0);
  }

private:
  bool helper(vector<vector<char>> &b, int c, int r) {
    if (r > 8)
      return true;
    if (c > 8)
      return helper(b, 0, r + 1);
    if (b[r][c] != '.') {
      char current = b[r][c];
      for (int i = 0; i < 9; ++i) {
        if (i == c)
          continue;
        if (b[r][i] == current)
          return false;
      }
      for (int i = 0; i < 9; ++i) {
        if (i == r)
          continue;
        if (b[i][c] == current)
          return false;
      }
      int block_col = c / 3 * 3, block_row = r / 3 * 3;
      for (int i = block_row; i < block_row + 3; ++i) {
        for (int j = block_col; j < block_col + 3; ++j) {
          if (i == r && j == c)
            continue;
          if (b[i][j] == current)
            return false;
        }
      }
    }
    return helper(b, c + 1, r);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |board.length == 9|
// * |board[i].length == 9|
// * |board[i][j]| is a digit |1-9| or |'.'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: board =
// [["5","3",".",".","7",".",".",".","."]
// ,["6",".",".","1","9","5",".",".","."]
// ,[".","9","8",".",".",".",".","6","."]
// ,["8",".",".",".","6",".",".",".","3"]
// ,["4",".",".","8",".","3",".",".","1"]
// ,["7",".",".",".","2",".",".",".","6"]
// ,[".","6",".",".",".",".","2","8","."]
// ,[".",".",".","4","1","9",".",".","5"]
// ,[".",".",".",".","8",".",".","7","9"]]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(36, ValidSudoku, example_1) {
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
  bool expect = true;
  bool actual = solution->isValidSudoku(board);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: board =
// [["8","3",".",".","7",".",".",".","."]
// ,["6",".",".","1","9","5",".",".","."]
// ,[".","9","8",".",".",".",".","6","."]
// ,["8",".",".",".","6",".",".",".","3"]
// ,["4",".",".","8",".","3",".",".","1"]
// ,["7",".",".",".","2",".",".",".","6"]
// ,[".","6",".",".",".",".","2","8","."]
// ,[".",".",".","4","1","9",".",".","5"]
// ,[".",".",".",".","8",".",".","7","9"]]
// Output: false
//
// Same as Example 1, except with the 5 in the top left corner being modified
// to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.

LEETCODE_SOLUTION_UNITTEST(36, ValidSudoku, example_2) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {
      {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
  };
  bool expect = false;
  bool actual = solution->isValidSudoku(board);
  EXPECT_EQ(expect, actual);
}
