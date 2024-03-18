// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Elimination Game
//
// https://leetcode.com/problems/elimination-game/
//
// Question ID: 390
// Difficult  : Medium
// Solve Date : 2024/03/18 21:17

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |390. Elimination Game|:
//
// You have a list |arr| of all integers in the range |[1, n]| sorted in a
// strictly increasing order. Apply the following algorithm on |arr|:
//
//  • Starting from left to right, remove the first number and every other
//  number afterward until you reach the end of the list.
//
//  • Repeat the previous step again, but this time from right to left, remove
//  the rightmost number and every other number from the remaining numbers.
//
//  • Keep repeating the steps again, alternating left to right and right to
//  left, until a single number remains.
// Given the integer |n|, return the last number that remains in |arr|.
//
//

LEETCODE_BEGIN_RESOLVING(390, EliminationGame, Solution);

class Solution {
public:
  int lastRemaining(int n) {
    if (n == 1) {
      return 1;
    }
    int  res    = 1;
    int  ord    = 1;
    int  remain = n;
    bool left   = false;
    while (remain > 1) {
      if (!left || remain & 1) {
        res = res + ord;
      }
      ord <<= 1;
      remain >>= 1;
      left = !left;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 9
// Output: 6
//
// arr = [1, 2, 3, 4, 5, 6, 7, 8, 9]
// arr = [2, 4, 6, 8]
// arr = [2, 6]
// arr = [6]

LEETCODE_SOLUTION_UNITTEST(390, EliminationGame, example_1) {
  auto solution = MakeSolution();
  int  n        = 9;
  int  expect   = 6;
  int  actual   = solution->lastRemaining(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(390, EliminationGame, example_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 1;
  int  actual   = solution->lastRemaining(n);
  LCD_EXPECT_EQ(expect, actual);
}
