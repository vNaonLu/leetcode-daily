// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Nim Game
//
// https://leetcode.com/problems/nim-game/
//
// Question ID: 292
// Difficult  : Easy
// Solve Date : 2022/08/13 12:42

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |292. Nim Game|:
//
// You are playing the following Nim Game with your friend:
//
//  • Initially, there is a heap of stones on the table.
//
//  • You and your friend will alternate taking turns, and you go first.
//
//  • On each turn, the person whose turn it is will remove 1 to 3 stones from
//  the heap.
//
//  • The one who removes the last stone is the winner.
// Given |n|, the number of stones in the heap, return |true| if you can win the
// game assuming both you and your friend play optimally, otherwise return
// |false|.
//

LEETCODE_BEGIN_RESOLVING(292, NimGame, Solution);

class Solution {
public:
  bool canWinNim(int n) { return n & 3; }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4
// Output: false
//
// These are the possible outcomes:
// 1. You remove 1 stone. Your friend removes 3 stones, including the last
// stone. Your friend wins.
// 2. You remove 2 stones. Your friend removes 2 stones, including the last
// stone. Your friend wins.
// 3. You remove 3 stones. Your friend removes the last stone. Your friend wins.
// In all outcomes, your friend wins.

LEETCODE_SOLUTION_UNITTEST(292, NimGame, example_1) {
  auto solution = MakeSolution();
  int  n        = 4;
  bool expect   = false;
  bool actual   = solution->canWinNim(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(292, NimGame, example_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  bool expect   = true;
  bool actual   = solution->canWinNim(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 2
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(292, NimGame, example_3) {
  auto solution = MakeSolution();
  int  n        = 2;
  bool expect   = true;
  bool actual   = solution->canWinNim(n);
  LCD_EXPECT_EQ(expect, actual);
}
