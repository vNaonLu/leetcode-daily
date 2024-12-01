// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Stone Removal Game
//
// https://leetcode.com/problems/stone-removal-game/
//
// Question ID: 3360
// Difficult  : Easy
// Solve Date : 2024/12/01 10:18

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3360. Stone Removal Game|:
//
// Alice and Bob are playing a game where they take turns removing stones from a
// pile, with Alice going first.
//
//  • Alice starts by removing exactly 10 stones on her first turn.
//
//  • For each subsequent turn, each player removes exactly 1 fewer stone than
//  the previous opponent.
// The player who cannot make a move loses the game.
// Given a positive integer |n|, return |true| if Alice wins the game and
// |false| otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(3360, StoneRemovalGame, Solution);

class Solution {
public:
  bool canAliceWin(int n) {
    int d = 10;
    while (n >= d) {
      n -= d--;
    }
    return d & 1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 12
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3360, StoneRemovalGame, example_1) {
  auto solution = MakeSolution();
  int  n        = 12;
  bool expect   = true;
  bool actual   = solution->canAliceWin(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3360, StoneRemovalGame, example_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  bool expect   = false;
  bool actual   = solution->canAliceWin(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 11
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3360, StoneRemovalGame, extra_testcase_1) {
  auto solution = MakeSolution();
  int  n        = 11;
  bool expect   = true;
  bool actual   = solution->canAliceWin(n);
  LCD_EXPECT_EQ(expect, actual);
}
