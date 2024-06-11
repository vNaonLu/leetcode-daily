// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Reach a Number
//
// https://leetcode.com/problems/reach-a-number/
//
// Question ID: 754
// Difficult  : Medium
// Solve Date : 2024/06/09 13:52

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |754. Reach a Number|:
//
// You are standing at position |0| on an infinite number line. There is a
// destination at position |target|. You can make some number of moves
// |numMoves| so that:
//
//  • On each move, you can either go left or right.
//
//  • During the |iᵗʰ| move (starting from |i == 1| to |i == numMoves|), you
//  take |i| steps in the chosen direction.
// Given the integer |target|, return the minimum number of moves required
// (i.e., the minimum |numMoves|) to reach the destination.
//
//

LEETCODE_BEGIN_RESOLVING(754, ReachANumber, Solution);

class Solution {
public:
  int reachNumber(int target) {
    int nt  = abs(target);
    int res = 0;
    int pos = 0;
    while (pos < nt) {
      pos += ++res;
    }
    while ((pos - nt) & 1) {
      pos += ++res;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |-10⁹ <= target <= 10⁹|
// * |target != 0|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: target = 2
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(754, ReachANumber, example_1) {
  auto solution = MakeSolution();
  int  target   = 2;
  int  expect   = 3;
  int  actual   = solution->reachNumber(target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: target = 3
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(754, ReachANumber, example_2) {
  auto solution = MakeSolution();
  int  target   = 3;
  int  expect   = 2;
  int  actual   = solution->reachNumber(target);
  LCD_EXPECT_EQ(expect, actual);
}
