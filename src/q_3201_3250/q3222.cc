// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the Winning Player in Coin Game
//
// https://leetcode.com/problems/find-the-winning-player-in-coin-game/
//
// Question ID: 3222
// Difficult  : Easy
// Solve Date : 2024/07/23 22:27

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3222. Find the Winning Player in Coin Game|:
//
// You are given two positive integers |x| and |y|, denoting the number of coins
// with values 75 and 10 respectively. Alice and Bob are playing a game. Each
// turn, starting with Alice, the player must pick up coins with a total value
// 115. If the player is unable to do so, they lose the game. Return the name of
// the player who wins the game if both players play optimally.
//
//

LEETCODE_BEGIN_RESOLVING(3222, FindTheWinningPlayerInCoinGame, Solution);

class Solution {
public:
  string losingPlayer(int x, int y) {
    bool alice_turn = min(x, y / 4) % 2 == 0;
    return alice_turn ? "Bob" : "Alice";
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= x, y <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: x = 2, y = 7
// Output: "Alice"
//

LEETCODE_SOLUTION_UNITTEST(3222, FindTheWinningPlayerInCoinGame, example_1) {
  auto   solution = MakeSolution();
  int    x        = 2;
  int    y        = 7;
  string expect   = "Alice";
  string actual   = solution->losingPlayer(x, y);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: x = 4, y = 11
// Output: "Bob"
//

LEETCODE_SOLUTION_UNITTEST(3222, FindTheWinningPlayerInCoinGame, example_2) {
  auto   solution = MakeSolution();
  int    x        = 4;
  int    y        = 11;
  string expect   = "Bob";
  string actual   = solution->losingPlayer(x, y);
  LCD_EXPECT_EQ(expect, actual);
}
