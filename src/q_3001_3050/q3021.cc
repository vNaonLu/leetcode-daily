// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Alice and Bob Playing Flower Game
//
// https://leetcode.com/problems/alice-and-bob-playing-flower-game/
//
// Question ID: 3021
// Difficult  : Medium
// Solve Date : 2025/08/29 22:19

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3021. Alice and Bob Playing Flower Game|:
//
// Alice and Bob are playing a turn-based game on a field, with two lanes of
// flowers between them. There are |x| flowers in the first lane between Alice
// and Bob, and |y| flowers in the second lane between them.
// ![img](https://assets.leetcode.com/uploads/2025/08/27/3021.png)
// The game proceeds as follows:
//
//  1. Alice takes the first turn.
//
//  2. In each turn, a player must choose either one of the lane and pick one
//  flower from that side.
//
//  3. At the end of the turn, if there are no flowers left at all, the current
//  player captures their opponent and wins the game.
// Given two integers, |n| and |m|, the task is to compute the number of
// possible pairs |(x, y)| that satisfy the conditions:
//
//  • Alice must win the game according to the described rules.
//
//  • The number of flowers |x| in the first lane must be in the range |[1,n]|.
//
//  • The number of flowers |y| in the second lane must be in the range |[1,m]|.
// Return the number of possible pairs |(x, y)| that satisfy the conditions
// mentioned in the statement.
//
//

LEETCODE_BEGIN_RESOLVING(3021, AliceAndBobPlayingFlowerGame, Solution);

class Solution {
public:
  long long flowerGame(int n, int m) { return 1ll * n * m / 2; }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n, m <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, m = 2
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3021, AliceAndBobPlayingFlowerGame, example_1) {
  auto      solution = MakeSolution();
  int       n        = 3;
  int       m        = 2;
  long long expect   = 3;
  long long actual   = solution->flowerGame(n, m);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1, m = 1
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3021, AliceAndBobPlayingFlowerGame, example_2) {
  auto      solution = MakeSolution();
  int       n        = 1;
  int       m        = 1;
  long long expect   = 0;
  long long actual   = solution->flowerGame(n, m);
  LCD_EXPECT_EQ(expect, actual);
}
