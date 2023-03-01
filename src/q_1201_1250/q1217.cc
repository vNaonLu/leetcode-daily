// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Cost to Move Chips to The Same Position
//
// https://leetcode.com/problems/minimum-cost-to-move-chips-to-the-same-position/
//
// Question ID: 1217
// Difficult  : Easy
// Solve Date : 2021/12/06 18:16

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1217. Minimum Cost to Move Chips to The Same Position|:
//
// We have |n| chips, where the position of the |iᵗʰ| chip is |position[i]|.
// We need to move all the chips to the same position. In one step, we can
// change the position of the |iᵗʰ| chip from |position[i]| to:
//
//  • |position[i] + 2| or |position[i] - 2| with |cost = 0|.
//
//  • |position[i] + 1| or |position[i] - 1| with |cost = 1|.
// Return the minimum cost needed to move all the chips to the same position.
//  
//

LEETCODE_BEGIN_RESOLVING(1217, MinimumCostToMoveChipsToTheSamePosition,
                         Solution);

class Solution {
public:
  int minCostToMoveChips(vector<int> &position) {
    int even = 0, odd = 0;
    for (const auto &x : position) {
      if (x & 1)
        ++odd;
      else
        ++even;
    }
    return min(odd, even);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= position.length <= 100|
// * |1 <= position[i] <= 10^9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: position = [1,2,3]
// Output: 1
//
// First step: Move the chip at position 3 to position 1 with cost = 0.
// Second step: Move the chip at position 2 to position 1 with cost = 1.
// Total cost is 1.

LEETCODE_SOLUTION_UNITTEST(1217, MinimumCostToMoveChipsToTheSamePosition,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> position = {1, 2, 3};
  int         expect   = 1;
  int         actual   = solution->minCostToMoveChips(position);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: position = [2,2,2,3,3]
// Output: 2
//
// We can move the two chips at position 3 to position 2. Each move has cost
// = 1. The total cost = 2.

LEETCODE_SOLUTION_UNITTEST(1217, MinimumCostToMoveChipsToTheSamePosition,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> position = {2, 2, 2, 3, 3};
  int         expect   = 2;
  int         actual   = solution->minCostToMoveChips(position);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: position = [1,1000000000]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1217, MinimumCostToMoveChipsToTheSamePosition,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> position = {1, 1000000000};
  int         expect   = 1;
  int         actual   = solution->minCostToMoveChips(position);
  LCD_EXPECT_EQ(expect, actual);
}
