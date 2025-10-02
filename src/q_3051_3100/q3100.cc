// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Water Bottles II
//
// https://leetcode.com/problems/water-bottles-ii/
//
// Question ID: 3100
// Difficult  : Medium
// Solve Date : 2025/10/02 18:36

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3100. Water Bottles II|:
//
// You are given two integers |numBottles| and |numExchange|.
// |numBottles| represents the number of full water bottles that you initially
// have. In one operation, you can perform one of the following operations:
//
//  • Drink any number of full water bottles turning them into empty bottles.
//
//  • Exchange |numExchange| empty bottles with one full water bottle. Then,
//  increase |numExchange| by one.
// Note that you cannot exchange multiple batches of empty bottles for the same
// value of |numExchange|. For example, if |numBottles == 3| and |numExchange ==
// 1|, you cannot exchange |3| empty water bottles for |3| full bottles. Return
// the maximum number of water bottles you can drink.
//
//

LEETCODE_BEGIN_RESOLVING(3100, WaterBottlesII, Solution);

class Solution {
public:
  int maxBottlesDrunk(int numBottles, int numExchange) {
    int res   = numBottles;
    int empty = numBottles;
    while (empty >= numExchange) {
      ++res;
      empty = empty - numExchange + 1;
      ++numExchange;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= numBottles <= 100 |
// * |1 <= numExchange <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: numBottles = 13, numExchange = 6
// Output: 15
//

LEETCODE_SOLUTION_UNITTEST(3100, WaterBottlesII, example_1) {
  auto solution    = MakeSolution();
  int  numBottles  = 13;
  int  numExchange = 6;
  int  expect      = 15;
  int  actual      = solution->maxBottlesDrunk(numBottles, numExchange);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: numBottles = 10, numExchange = 3
// Output: 13
//

LEETCODE_SOLUTION_UNITTEST(3100, WaterBottlesII, example_2) {
  auto solution    = MakeSolution();
  int  numBottles  = 10;
  int  numExchange = 3;
  int  expect      = 13;
  int  actual      = solution->maxBottlesDrunk(numBottles, numExchange);
  LCD_EXPECT_EQ(expect, actual);
}
