// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Water and Jug Problem
//
// https://leetcode.com/problems/water-and-jug-problem/
//
// Question ID: 365
// Difficult  : Medium
// Solve Date : 2022/03/20 14:14

#include <iosfwd>
#include <queue>
#include <set>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |365. Water and Jug Problem|:
//
// You are given two jugs with capacities |jug1Capacity| and |jug2Capacity|
// liters. There is an infinite amount of water supply available. Determine
// whether it is possible to measure exactly |targetCapacity| liters using these
// two jugs. If |targetCapacity| liters of water are measurable, you must have
// |targetCapacity| liters of water contained within one or both buckets by the
// end. Operations allowed:
//
//  • Fill any of the jugs with water.
//
//  • Empty any of the jugs.
//
//  • Pour water from one jug into another till the other jug is completely
//  full, or the first jug itself is empty.
//  
//

LEETCODE_BEGIN_RESOLVING(365, WaterAndJugProblem, Solution);

class Solution {
public:
  bool canMeasureWater(int jug1Capacity, int jug2Capacity, int targetCapacity) {
    unordered_set<int> visit;
    queue<int>         step;
    vector<int>        dir = {jug1Capacity, -jug1Capacity, jug2Capacity,
                              -jug2Capacity};

    step.emplace(0);
    visit.emplace(0);

    while (!step.empty()) {
      int water = step.front();
      step.pop();

      for (auto &p : dir) {
        int x = water + p;

        if (x < 0 || x > jug1Capacity + jug2Capacity)
          continue;

        if (x == targetCapacity)
          return true;

        if (visit.emplace(x).second) {
          step.emplace(x);
        }
      }
    }

    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= jug1Capacity, jug2Capacity, targetCapacity <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: jug1Capacity = 3, jug2Capacity = 5, targetCapacity = 4
// Output: true
//
// The famous [Die Hard] example

LEETCODE_SOLUTION_UNITTEST(365, WaterAndJugProblem, example_1) {
  auto solution       = MakeSolution();
  int  jug1Capacity   = 3;
  int  jug2Capacity   = 5;
  int  targetCapacity = 4;
  bool expect         = true;
  bool actual =
      solution->canMeasureWater(jug1Capacity, jug2Capacity, targetCapacity);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: jug1Capacity = 2, jug2Capacity = 6, targetCapacity = 5
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(365, WaterAndJugProblem, example_2) {
  auto solution       = MakeSolution();
  int  jug1Capacity   = 2;
  int  jug2Capacity   = 6;
  int  targetCapacity = 5;
  bool expect         = false;
  bool actual =
      solution->canMeasureWater(jug1Capacity, jug2Capacity, targetCapacity);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: jug1Capacity = 1, jug2Capacity = 2, targetCapacity = 3
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(365, WaterAndJugProblem, example_3) {
  auto solution       = MakeSolution();
  int  jug1Capacity   = 1;
  int  jug2Capacity   = 2;
  int  targetCapacity = 3;
  bool expect         = true;
  bool actual =
      solution->canMeasureWater(jug1Capacity, jug2Capacity, targetCapacity);
  LCD_EXPECT_EQ(expect, actual);
}
