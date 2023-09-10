// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Determine Color of a Chessboard Square
//
// https://leetcode.com/problems/determine-color-of-a-chessboard-square/
//
// Question ID: 1812
// Difficult  : Easy
// Solve Date : 2023/09/10 13:51

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1812. Determine Color of a Chessboard Square|:
//
// You are given |coordinates|, a string that represents the coordinates of a
// square of the chessboard. Below is a chessboard for your reference.
// ![img](https://assets.leetcode.com/uploads/2021/02/19/screenshot-2021-02-20-at-22159-pm.png)
// Return |true| if the square is white, and |false| if the square is black.
// The coordinate will always represent a valid chessboard square. The
// coordinate will always have the letter first, and the number second.
//
//

LEETCODE_BEGIN_RESOLVING(1812, DetermineColorOfAChessboardSquare, Solution);

class Solution {
public:
  bool squareIsWhite(string coordinates) {
    int c = coordinates[0] - 'a';
    int r = coordinates[1] - '1';
    return ((c & 1) == 0) ^ ((r & 1) == 0);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |coordinates.length == 2|
// * |'a' <= coordinates[0] <= 'h'|
// * |'1' <= coordinates[1] <= '8'|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: coordinates = "a1"
// Output: false
//
// From the chessboard above, the square with coordinates "a1" is black, so
// return false.

LEETCODE_SOLUTION_UNITTEST(1812, DetermineColorOfAChessboardSquare, example_1) {
  auto   solution    = MakeSolution();
  string coordinates = "a1";
  bool   expect      = false;
  bool   actual      = solution->squareIsWhite(coordinates);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: coordinates = "h3"
// Output: true
//
// From the chessboard above, the square with coordinates "h3" is white, so
// return true.

LEETCODE_SOLUTION_UNITTEST(1812, DetermineColorOfAChessboardSquare, example_2) {
  auto   solution    = MakeSolution();
  string coordinates = "h3";
  bool   expect      = true;
  bool   actual      = solution->squareIsWhite(coordinates);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: coordinates = "c7"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1812, DetermineColorOfAChessboardSquare, example_3) {
  auto   solution    = MakeSolution();
  string coordinates = "c7";
  bool   expect      = false;
  bool   actual      = solution->squareIsWhite(coordinates);
  LCD_EXPECT_EQ(expect, actual);
}
