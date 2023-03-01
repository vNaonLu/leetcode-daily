// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Winner of the Circular Game
//
// https://leetcode.com/problems/find-the-winner-of-the-circular-game/
//
// Question ID: 1823
// Difficult  : Medium
// Solve Date : 2021/10/02 15:06

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1823. Find the Winner of the Circular Game|:
//
// There are |n| friends that are playing a game. The friends are sitting in a
// circle and are numbered from |1| to |n| in clockwise order. More formally,
// moving clockwise from the |iᵗʰ| friend brings you to the |(i+1)ᵗʰ| friend for
// |1 <= i < n|, and moving clockwise from the |nᵗʰ| friend brings you to the
// |1ˢᵗ| friend. The rules of the game are as follows:
//
//  1. Start at the |1ˢᵗ| friend.
//
//  2. Count the next |k| friends in the clockwise direction including the
//  friend you started at. The counting wraps around the circle and may count
//  some friends more than once.
//
//  3. The last friend you counted leaves the circle and loses the game.
//
//  4. If there is still more than one friend in the circle, go back to step |2|
//  starting from the friend immediately clockwise of the friend who just lost
//  and repeat.
//
//  5. Else, the last friend in the circle wins the game.
// Given the number of friends, |n|, and an integer |k|, return the winner of
// the game.  
//

LEETCODE_BEGIN_RESOLVING(1823, FindTheWinnerOfTheCircularGame, Solution);

class Solution {
public:
  int findTheWinner(int n, int k) {
    if (n == 1)
      return 1;
    return (findTheWinner(n - 1, k) + k - 1) % n + 1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= k <= n <= 500|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, k = 2
// Output: 3
//
// Here are the steps of the game:
// 1) Start at friend 1.
// 2) Count 2 friends clockwise, which are friends 1 and 2.
// 3) Friend 2 leaves the circle. Next start is friend 3.
// 4) Count 2 friends clockwise, which are friends 3 and 4.
// 5) Friend 4 leaves the circle. Next start is friend 5.
// 6) Count 2 friends clockwise, which are friends 5 and 1.
// 7) Friend 1 leaves the circle. Next start is friend 3.
// 8) Count 2 friends clockwise, which are friends 3 and 5.
// 9) Friend 5 leaves the circle. Only friend 3 is left, so they are the winner.

LEETCODE_SOLUTION_UNITTEST(1823, FindTheWinnerOfTheCircularGame, example_1) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  k        = 2;
  int  expect   = 3;
  int  actual   = solution->findTheWinner(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 6, k = 5
// Output: 1
//
// The friends leave in this order: 5, 4, 6, 2, 3. The winner is friend 1.

LEETCODE_SOLUTION_UNITTEST(1823, FindTheWinnerOfTheCircularGame, example_2) {
  auto solution = MakeSolution();
  int  n        = 6;
  int  k        = 5;
  int  expect   = 1;
  int  actual   = solution->findTheWinner(n, k);
  LCD_EXPECT_EQ(expect, actual);
}
