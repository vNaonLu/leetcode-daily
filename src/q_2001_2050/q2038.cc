// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove Colored Pieces if Both Neighbors are the Same Color
//
// https://leetcode.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/
//
// Question ID: 2038
// Difficult  : Medium
// Solve Date : 2023/10/02 21:07

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2038. Remove Colored Pieces if Both Neighbors are the Same
// Color|:
//
// There are |n| pieces arranged in a line, and each piece is colored either by
// |'A'| or by |'B'|. You are given a string |colors| of length |n| where
// |colors[i]| is the color of the |iᵗʰ| piece. Alice and Bob are playing a game
// where they take alternating turns removing pieces from the line. In this
// game, Alice moves first.
//
//  • Alice is only allowed to remove a piece colored |'A'| if both its
//  neighbors are also colored |'A'|. She is not allowed to remove pieces that
//  are colored |'B'|.
//
//  • Bob is only allowed to remove a piece colored |'B'| if both its neighbors
//  are also colored |'B'|. He is not allowed to remove pieces that are colored
//  |'A'|.
//
//  • Alice and Bob cannot remove pieces from the edge of the line.
//
//  • If a player cannot make a move on their turn, that player loses and the
//  other player wins.
// Assuming Alice and Bob play optimally, return |true| if Alice wins, or return
// |false| if Bob wins.
//
//

LEETCODE_BEGIN_RESOLVING(2038,
                         RemoveColoredPiecesIfBothNeighborsAreTheSameColor,
                         Solution);

class Solution {
public:
  bool winnerOfGame(string colors) {
    int c1 = 0;
    int c2 = 0;
    for (int i = 1; i < colors.size() - 1; ++i) {
      if (colors[i] == 'A' && colors[i - 1] == 'A' && colors[i + 1] == 'A') {
        ++c1;
      } else if (colors[i] == 'B' && colors[i - 1] == 'B' &&
                 colors[i + 1] == 'B') {
        ++c2;
      }
    }
    return c1 > c2;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= colors.length <= 10⁵|
// * |colors| consists of only the letters |'A'| and |'B'|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: colors = "AAABABB"
// Output: true
//
// AAABABB -> AABABB
// Alice moves first.
// She removes the second 'A' from the left since that is the only 'A' whose
// neighbors are both 'A'. Now it's Bob's turn. Bob cannot make a move on his
// turn since there are no 'B's whose neighbors are both 'B'. Thus, Alice wins,
// so return true.

LEETCODE_SOLUTION_UNITTEST(2038,
                           RemoveColoredPiecesIfBothNeighborsAreTheSameColor,
                           example_1) {
  auto   solution = MakeSolution();
  string colors   = "AAABABB";
  bool   expect   = true;
  bool   actual   = solution->winnerOfGame(colors);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: colors = "AA"
// Output: false
//
// Alice has her turn first.
// There are only two 'A's and both are on the edge of the line, so she cannot
// move on her turn. Thus, Bob wins, so return false.

LEETCODE_SOLUTION_UNITTEST(2038,
                           RemoveColoredPiecesIfBothNeighborsAreTheSameColor,
                           example_2) {
  auto   solution = MakeSolution();
  string colors   = "AA";
  bool   expect   = false;
  bool   actual   = solution->winnerOfGame(colors);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: colors = "ABBBBBBBAAA"
// Output: false
//
// ABBBBBBBAAA -> ABBBBBBBAA
// Alice moves first.
// Her only option is to remove the second to last 'A' from the right.
// ABBBBBBBAA -> ABBBBBBAA
// Next is Bob's turn.
// He has many options for which 'B' piece to remove. He can pick any.
// On Alice's second turn, she has no more pieces that she can remove.
// Thus, Bob wins, so return false.

LEETCODE_SOLUTION_UNITTEST(2038,
                           RemoveColoredPiecesIfBothNeighborsAreTheSameColor,
                           example_3) {
  auto   solution = MakeSolution();
  string colors   = "ABBBBBBBAAA";
  bool   expect   = false;
  bool   actual   = solution->winnerOfGame(colors);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "AAABABB"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(2038,
                           RemoveColoredPiecesIfBothNeighborsAreTheSameColor,
                           extra_testcase_1) {
  auto   solution = MakeSolution();
  string colors   = "AAABABB";
  bool   expect   = true;
  bool   actual   = solution->winnerOfGame(colors);
  LCD_EXPECT_EQ(expect, actual);
}
