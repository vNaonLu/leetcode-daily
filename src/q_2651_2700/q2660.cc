// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Determine the Winner of a Bowling Game
//
// https://leetcode.com/problems/determine-the-winner-of-a-bowling-game/
//
// Question ID: 2660
// Difficult  : Easy
// Solve Date : 2023/12/09 18:33

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2660. Determine the Winner of a Bowling Game|:
//
// You are given two 0-indexed integer arrays |player1| and |player2|, that
// represent the number of pins that player 1 and player 2 hit in a bowling
// game, respectively. The bowling game consists of |n| turns, and the number of
// pins in each turn is exactly |10|. Assume a player hit |xᵢ| pins in the |iᵗʰ|
// turn. The value of the |iᵗʰ| turn for the player is:
//
//  • |2xᵢ| if the player hit |10| pins in any of the previous two turns.
//
//  • Otherwise, It is |xᵢ|.
// The score of the player is the sum of the values of their |n| turns.
// Return
//
//  • |1| if the score of player 1 is more than the score of player 2,
//
//  • |2| if the score of player 2 is more than the score of player 1, and
//
//  • |0| in case of a draw.
//
//

LEETCODE_BEGIN_RESOLVING(2660, DetermineTheWinnerOfABowlingGame, Solution);

class Solution {
public:
  int isWinner(vector<int> &player1, vector<int> &player2) {
    int x1 = score(player1);
    int x2 = score(player2);
    return x1 == x2 ? 0 : x1 > x2 ? 1 : 2;
  }

private:
  int score(vector<int> const &v) {
    int res = 0;
    int mul = 0;

    for (auto x : v) {
      if (mul > 0) {
        res += 2 * x;
        --mul;
      } else {
        res += x;
      }

      if (x == 10) {
        mul = 2;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == player1.length == player2.length|
// * |1 <= n <= 1000|
// * |0 <= player1[i], player2[i] <= 10|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: player1 = [4,10,7,9], player2 = [6,5,2,3]
// Output: 1
//
// The score of player1 is 4 + 10 + 2*7 + 2*9 = 46.
// The score of player2 is 6 + 5 + 2 + 3 = 16.
// Score of player1 is more than the score of player2, so, player1 is the
// winner, and the answer is 1.

LEETCODE_SOLUTION_UNITTEST(2660, DetermineTheWinnerOfABowlingGame, example_1) {
  auto        solution = MakeSolution();
  vector<int> player1  = {4, 10, 7, 9};
  vector<int> player2  = {6, 5, 2, 3};
  int         expect   = 1;
  int         actual   = solution->isWinner(player1, player2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: player1 = [3,5,7,6], player2 = [8,10,10,2]
// Output: 2
//
// The score of player1 is 3 + 5 + 7 + 6 = 21.
// The score of player2 is 8 + 10 + 2*10 + 2*2 = 42.
// Score of player2 is more than the score of player1, so, player2 is the
// winner, and the answer is 2.

LEETCODE_SOLUTION_UNITTEST(2660, DetermineTheWinnerOfABowlingGame, example_2) {
  auto        solution = MakeSolution();
  vector<int> player1  = {3, 5, 7, 6};
  vector<int> player2  = {8, 10, 10, 2};
  int         expect   = 2;
  int         actual   = solution->isWinner(player1, player2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: player1 = [2,3], player2 = [4,1]
// Output: 0
//
// The score of player1 is 2 + 3 = 5
// The score of player2 is 4 + 1 = 5
// The score of player1 equals to the score of player2, so, there is a draw, and
// the answer is 0.

LEETCODE_SOLUTION_UNITTEST(2660, DetermineTheWinnerOfABowlingGame, example_3) {
  auto        solution = MakeSolution();
  vector<int> player1  = {2, 3};
  vector<int> player2  = {4, 1};
  int         expect   = 0;
  int         actual   = solution->isWinner(player1, player2);
  LCD_EXPECT_EQ(expect, actual);
}
