// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Check if Two Chessboard Squares Have the Same Color
//
// https://leetcode.com/problems/check-if-two-chessboard-squares-have-the-same-color/
//
// Question ID: 3274
// Difficult  : Easy
// Solve Date : 2024/09/07 16:13

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3274. Check if Two Chessboard Squares Have the Same Color|:
//
// You are given two strings, |coordinate1| and |coordinate2|, representing the
// coordinates of a square on an |8 x 8| chessboard. Below is the chessboard for
// reference.
// ![img](https://assets.leetcode.com/uploads/2024/07/17/screenshot-2021-02-20-at-22159-pm.png)
// Return |true| if these two squares have the same color and |false| otherwise.
// The coordinate will always represent a valid chessboard square. The
// coordinate will always have the letter first (indicating its column), and the
// number second (indicating its row).
//
//

LEETCODE_BEGIN_RESOLVING(3274, CheckIfTwoChessboardSquaresHaveTheSameColor,
                         Solution);

class Solution {
public:
  bool checkTwoChessboards(string coordinate1, string coordinate2) {
    auto cord1 = (coordinate1[0] - 'a') + (coordinate1[1] - '1');
    auto cord2 = (coordinate2[0] - 'a') + (coordinate2[1] - '1');
    return (cord1 & 1) == (cord2 & 1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |coordinate1.length == coordinate2.length == 2|
// * |'a' <= coordinate1[0], coordinate2[0] <= 'h'|
// * |'1' <= coordinate1[1], coordinate2[1] <= '8'|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: coordinate1 = "a1", coordinate2 = "c3"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3274, CheckIfTwoChessboardSquaresHaveTheSameColor,
                           example_1) {
  auto   solution    = MakeSolution();
  string coordinate1 = "a1";
  string coordinate2 = "c3";
  bool   expect      = true;
  bool   actual      = solution->checkTwoChessboards(coordinate1, coordinate2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: coordinate1 = "a1", coordinate2 = "h3"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3274, CheckIfTwoChessboardSquaresHaveTheSameColor,
                           example_2) {
  auto   solution    = MakeSolution();
  string coordinate1 = "a1";
  string coordinate2 = "h3";
  bool   expect      = false;
  bool   actual      = solution->checkTwoChessboards(coordinate1, coordinate2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "a7"
// "a6"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3274, CheckIfTwoChessboardSquaresHaveTheSameColor,
                           extra_testcase_1) {
  auto   solution    = MakeSolution();
  string coordinate1 = "a7";
  string coordinate2 = "a6";
  bool   expect      = false;
  bool   actual      = solution->checkTwoChessboards(coordinate1, coordinate2);
  LCD_EXPECT_EQ(expect, actual);
}
