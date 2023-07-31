// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Divisor Game
//
// https://leetcode.com/problems/divisor-game/
//
// Question ID: 1025
// Difficult  : Easy
// Solve Date : 2023/07/25 19:48

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1025. Divisor Game|:
//
// Alice and Bob take turns playing a game, with Alice starting first.
// Initially, there is a number |n| on the chalkboard. On each player's turn,
// that player makes a move consisting of:
//
//  • Choosing any |x| with |0 < x < n| and |n % x == 0|.
//
//  • Replacing the number |n| on the chalkboard with |n - x|.
// Also, if a player cannot make a move, they lose the game.
// Return |true| if and only if Alice wins the game, assuming both players play
// optimally.
//
//

LEETCODE_BEGIN_RESOLVING(1025, DivisorGame, Solution);

class Solution {
public:
  bool divisorGame(int n) {
    vector<int> dp(n + 1, -1);
    return helper(&dp, n);
  }

private:
  bool helper(vector<int> *dp, int i) {
    if (i == 1) {
      return false;
    }
    if ((*dp)[i] != -1) {
      return (*dp)[i];
    }
    bool res = false;
    for (int j = 1; j < i; ++j) {
      if (i % j == 0) {
        res |= !helper(dp, i - j);
      }
    }
    return (bool)((*dp)[i] = res);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2
// Output: true
//
// Alice chooses 1, and Bob has no more moves.

LEETCODE_SOLUTION_UNITTEST(1025, DivisorGame, example_1) {
  auto solution = MakeSolution();
  int  n        = 2;
  bool expect   = true;
  bool actual   = solution->divisorGame(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3
// Output: false
//
// Alice chooses 1, Bob chooses 1, and Alice has no more moves.

LEETCODE_SOLUTION_UNITTEST(1025, DivisorGame, example_2) {
  auto solution = MakeSolution();
  int  n        = 3;
  bool expect   = false;
  bool actual   = solution->divisorGame(n);
  LCD_EXPECT_EQ(expect, actual);
}
