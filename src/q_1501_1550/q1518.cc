// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Water Bottles
//
// https://leetcode.com/problems/water-bottles/
//
// Question ID: 1518
// Difficult  : Easy
// Solve Date : 2023/08/23 20:18

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1518. Water Bottles|:
//
// There are |numBottles| water bottles that are initially full of water. You
// can exchange |numExchange| empty water bottles from the market with one full
// water bottle. The operation of drinking a full water bottle turns it into an
// empty bottle. Given the two integers |numBottles| and |numExchange|, return
// the maximum number of water bottles you can drink.
//
//

LEETCODE_BEGIN_RESOLVING(1518, WaterBottles, Solution);

class Solution {
public:
  int numWaterBottles(int numBottles, int numExchange) {
    int res = numBottles;
    while (numBottles >= numExchange) {
      int ex   = numBottles / numExchange;
      int left = numBottles % numExchange;
      res += ex;
      numBottles = ex + left;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= numBottles <= 100|
// * |2 <= numExchange <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: numBottles = 9, numExchange = 3
// Output: 13
//
// You can exchange 3 empty bottles to get 1 full water bottle.
// Number of water bottles you can drink: 9 + 3 + 1 = 13.

LEETCODE_SOLUTION_UNITTEST(1518, WaterBottles, example_1) {
  auto solution    = MakeSolution();
  int  numBottles  = 9;
  int  numExchange = 3;
  int  expect      = 13;
  int  actual      = solution->numWaterBottles(numBottles, numExchange);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: numBottles = 15, numExchange = 4
// Output: 19
//
// You can exchange 4 empty bottles to get 1 full water bottle.
// Number of water bottles you can drink: 15 + 3 + 1 = 19.

LEETCODE_SOLUTION_UNITTEST(1518, WaterBottles, example_2) {
  auto solution    = MakeSolution();
  int  numBottles  = 15;
  int  numExchange = 4;
  int  expect      = 19;
  int  actual      = solution->numWaterBottles(numBottles, numExchange);
  LCD_EXPECT_EQ(expect, actual);
}
