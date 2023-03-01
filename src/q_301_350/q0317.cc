// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shortest Distance from All Buildings
//
// https://leetcode.com/problems/shortest-distance-from-all-buildings/
//
// Question ID: 317
// Difficult  : Hard
// Solve Date : 2022/08/24 18:00

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |317. Shortest Distance from All Buildings|:
//
// This question is marked as premium question.

LEETCODE_BEGIN_RESOLVING(317, ShortestDistanceFromAllBuildings, Solution);

class Solution {
public:
  int getSum(int a, int b) {
    while (b != 0) {
      auto carry = a & b;
      a ^= b;
      b = (uint32_t)carry << 1;
    }
    return a;
  }
};

LEETCODE_END_RESOLVING(Solution);

LEETCODE_SOLUTION_UNITTEST(317, ShortestDistanceFromAllBuildings, example_1) {
  auto solution = MakeSolution();
  int  a        = 1;
  int  b        = 2;
  bool exp      = 3;
  bool act      = solution->getSum(a, b);
  LCD_EXPECT_EQ(act, exp);
}

LEETCODE_SOLUTION_UNITTEST(317, ShortestDistanceFromAllBuildings, example_2) {
  auto solution = MakeSolution();
  int  a        = 2;
  int  b        = 3;
  bool exp      = 5;
  bool act      = solution->getSum(a, b);
  LCD_EXPECT_EQ(act, exp);
}
