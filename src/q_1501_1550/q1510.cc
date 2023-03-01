// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Stone Game IV
//
// https://leetcode.com/problems/stone-game-iv/
//
// Question ID: 1510
// Difficult  : Hard
// Solve Date : 2022/01/22 13:57

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1510. Stone Game IV|:
//
// Alice and Bob take turns playing a game, with Alice starting first.
// Initially, there are |n| stones in a pile. On each player's turn, that player
// makes a move consisting of removing any non-zero square number of stones in
// the pile. Also, if a player cannot make a move, he/she loses the game. Given
// a positive integer |n|, return |true| if and only if Alice wins the game
// otherwise return |false|, assuming both players play optimally.  
//

LEETCODE_BEGIN_RESOLVING(1510, StoneGameIV, Solution);

class Solution {
public:
  bool winnerSquareGame(int n) {
    vector<bool> dp(n + 1, false);
    for (int i = 0; i <= n; ++i) {
      if (dp[i])
        continue;
      for (int k = 1; i + k * k <= n; ++k) {
        dp[i + k * k] = true;
      }
    }
    return dp.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1
// Output: true
//
// Alice can remove 1 stone winning the game because Bob doesn't have any moves.

LEETCODE_SOLUTION_UNITTEST(1510, StoneGameIV, example_1) {
  auto solution = MakeSolution();
  int  n        = 1;
  bool expect   = true;
  bool actual   = solution->winnerSquareGame(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2
// Output: false
//
// Alice can only remove 1 stone, after that Bob removes the last one winning
// the game (2 -> 1 -> 0).

LEETCODE_SOLUTION_UNITTEST(1510, StoneGameIV, example_2) {
  auto solution = MakeSolution();
  int  n        = 2;
  bool expect   = false;
  bool actual   = solution->winnerSquareGame(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 4
// Output: true
//
// n is already a perfect square, Alice can win with one move, removing 4 stones
// (4 -> 0).

LEETCODE_SOLUTION_UNITTEST(1510, StoneGameIV, example_3) {
  auto solution = MakeSolution();
  int  n        = 4;
  bool expect   = true;
  bool actual   = solution->winnerSquareGame(n);
  LCD_EXPECT_EQ(expect, actual);
}
