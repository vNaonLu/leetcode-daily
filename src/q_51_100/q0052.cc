// Copyright 2023 Naon Lu
//
// This file describes the solution of
// N-Queens II
//
// https://leetcode.com/problems/n-queens-ii/
//
// Question ID: 52
// Difficult  : Hard
// Solve Date : 2022/02/27 00:19

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |52. N-Queens II|:
//
// The n-queens puzzle is the problem of placing |n| queens on an |n x n|
// chessboard such that no two queens attack each other. Given an integer |n|,
// return the number of distinct solutions to the n-queens puzzle.  
//

LEETCODE_BEGIN_RESOLVING(52, NQueensII, Solution);

class Solution {
private:
  int         n, total;
  mutable int res;

  void solver(int col, int first, int second) const {
    if (col == total) {
      ++res;
      return;
    }

    int can = (~(col | first | second)) & total;
    while (can) {
      int t = can & (-can);
      solver(col | t, (first | t) >> 1, (second | t) << 1 & total);
      can &= ~t;
    }
  }

public:
  int totalNQueens(int n) {
    this->n = n;
    total   = (1 << n) - 1;
    res     = 0;
    solver(0, 0, 0);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4
// Output: 2
//
// There are two distinct solutions to the 4-queens puzzle as shown.

LEETCODE_SOLUTION_UNITTEST(52, NQueensII, example_1) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  expect   = 2;
  int  actual   = solution->totalNQueens(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(52, NQueensII, example_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 1;
  int  actual   = solution->totalNQueens(n);
  LCD_EXPECT_EQ(expect, actual);
}
