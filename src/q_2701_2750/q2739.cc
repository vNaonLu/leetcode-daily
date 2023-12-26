// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Total Distance Traveled
//
// https://leetcode.com/problems/total-distance-traveled/
//
// Question ID: 2739
// Difficult  : Easy
// Solve Date : 2023/12/22 20:13

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2739. Total Distance Traveled|:
//
// A truck has two fuel tanks. You are given two integers, |mainTank|
// representing the fuel present in the main tank in liters and |additionalTank|
// representing the fuel present in the additional tank in liters. The truck has
// a mileage of |10| km per liter. Whenever |5| liters of fuel get used up in
// the main tank, if the additional tank has at least |1| liters of fuel, |1|
// liters of fuel will be transferred from the additional tank to the main tank.
// Return the maximum distance which can be traveled.
// Note: Injection from the additional tank is not continuous. It happens
// suddenly and immediately for every 5 liters consumed.
//
//

LEETCODE_BEGIN_RESOLVING(2739, TotalDistanceTraveled, Solution);

class Solution {
public:
  int distanceTraveled(int mainTank, int additionalTank) {
    int res = 0;
    while (mainTank) {
      if (mainTank / 5) {
        if (additionalTank > 0) {
          ++mainTank;
          --additionalTank;
        }
        res += 5;
        mainTank -= 5;
      } else {
        res += mainTank;
        break;
      }
    }
    return 10 * res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= mainTank, additionalTank <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mainTank = 5, additionalTank = 10
// Output: 60
//
// After spending 5 litre of fuel, fuel remaining is (5 - 5 + 1) = 1 litre and
// distance traveled is 50km. After spending another 1 litre of fuel, no fuel
// gets injected in the main tank and the main tank becomes empty. Total
// distance traveled is 60km.

LEETCODE_SOLUTION_UNITTEST(2739, TotalDistanceTraveled, example_1) {
  auto solution       = MakeSolution();
  int  mainTank       = 5;
  int  additionalTank = 10;
  int  expect         = 60;
  int  actual         = solution->distanceTraveled(mainTank, additionalTank);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mainTank = 1, additionalTank = 2
// Output: 10
//
// After spending 1 litre of fuel, the main tank becomes empty.
// Total distance traveled is 10km.

LEETCODE_SOLUTION_UNITTEST(2739, TotalDistanceTraveled, example_2) {
  auto solution       = MakeSolution();
  int  mainTank       = 1;
  int  additionalTank = 2;
  int  expect         = 10;
  int  actual         = solution->distanceTraveled(mainTank, additionalTank);
  LCD_EXPECT_EQ(expect, actual);
}
