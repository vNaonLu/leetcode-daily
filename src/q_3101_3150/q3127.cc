// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Make a Square with the Same Color
//
// https://leetcode.com/problems/make-a-square-with-the-same-color/
//
// Question ID: 3127
// Difficult  : Easy
// Solve Date : 2024/05/04 14:14

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3127. Make a Square with the Same Color|:
//
// You are given a 2D matrix |grid| of size |3 x 3| consisting only of
// characters |'B'| and |'W'|. Character |'W'| represents the white color, and
// character |'B'| represents the black color. Your task is to change the color
// of at most one cell so that the matrix has a |2 x 2| square where all cells
// are of the same color. Return |true| if it is possible to create a |2 x 2|
// square of the same color, otherwise, return |false|.
//
// .grid-container {
//   display: grid;
//   grid-template-columns: 30px 30px 30px;
//   padding: 10px;
// }
// .grid-item {
//   background-color: black;
//   border: 1px solid gray;
//   height: 30px;
//   font-size: 30px;
//   text-align: center;
// }
// .grid-item-white {
//   background-color: white;
// }
//

LEETCODE_BEGIN_RESOLVING(3127, MakeASquareWithTheSameColor, Solution);

class Solution {
public:
  bool canMakeSquare(vector<vector<char>> &grid) {
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        int black = 0;
        if (grid[i][j] == 'B') {
          ++black;
        }
        if (grid[i][j + 1] == 'B') {
          ++black;
        }
        if (grid[i + 1][j] == 'B') {
          ++black;
        }
        if (grid[i + 1][j + 1] == 'B') {
          ++black;
        }
        if (black == 1 || black == 3 || black == 4 || black == 0) {
          return true;
        }
      }
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |grid.length == 3|
// * |grid[i].length == 3|
// * |grid[i][j]| is either |'W'| or |'B'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [["B","W","B"],["B","W","W"],["B","W","B"]]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3127, MakeASquareWithTheSameColor, example_1) {
  auto                 solution = MakeSolution();
  vector<vector<char>> grid     = {
      {'B', 'W', 'B'},
      {'B', 'W', 'W'},
      {'B', 'W', 'B'}
  };
  bool expect = true;
  bool actual = solution->canMakeSquare(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [["B","W","B"],["W","B","W"],["B","W","B"]]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3127, MakeASquareWithTheSameColor, example_2) {
  auto                 solution = MakeSolution();
  vector<vector<char>> grid     = {
      {'B', 'W', 'B'},
      {'W', 'B', 'W'},
      {'B', 'W', 'B'}
  };
  bool expect = false;
  bool actual = solution->canMakeSquare(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [["B","W","B"],["B","W","W"],["B","W","W"]]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3127, MakeASquareWithTheSameColor, example_3) {
  auto                 solution = MakeSolution();
  vector<vector<char>> grid     = {
      {'B', 'W', 'B'},
      {'B', 'W', 'W'},
      {'B', 'W', 'W'}
  };
  bool expect = true;
  bool actual = solution->canMakeSquare(grid);
  LCD_EXPECT_EQ(expect, actual);
}
