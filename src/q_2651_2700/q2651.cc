// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Calculate Delayed Arrival Time
//
// https://leetcode.com/problems/calculate-delayed-arrival-time/
//
// Question ID: 2651
// Difficult  : Easy
// Solve Date : 2023/05/08 15:43

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2651. Calculate Delayed Arrival Time|:
//
// You are given a positive integer |arrivalTime| denoting the arrival time of a
// train in hours, and another positive integer |delayedTime| denoting the
// amount of delay in hours. Return the time when the train will arrive at the
// station. Note that the time in this problem is in 24-hours format.
//
//

LEETCODE_BEGIN_RESOLVING(2651, CalculateDelayedArrivalTime, Solution);

class Solution {
public:
  int findDelayedArrivalTime(int arrivalTime, int delayedTime) {
    return (arrivalTime + delayedTime) % 24;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arrivaltime < 24|
// * |1 <= delayedTime <= 24|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arrivalTime = 15, delayedTime = 5
// Output: 20
//
// Arrival time of the train was 15:00 hours. It is delayed by 5 hours. Now it
// will reach at 15+5 = 20 (20:00 hours).

LEETCODE_SOLUTION_UNITTEST(2651, CalculateDelayedArrivalTime, example_1) {
  auto solution    = MakeSolution();
  int  arrivalTime = 15;
  int  delayedTime = 5;
  int  expect      = 20;
  int  actual      = solution->findDelayedArrivalTime(arrivalTime, delayedTime);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arrivalTime = 13, delayedTime = 11
// Output: 0
//
// Arrival time of the train was 13:00 hours. It is delayed by 11 hours. Now it
// will reach at 13+11=24 (Which is denoted by 00:00 in 24 hours format so
// return 0).

LEETCODE_SOLUTION_UNITTEST(2651, CalculateDelayedArrivalTime, example_2) {
  auto solution    = MakeSolution();
  int  arrivalTime = 13;
  int  delayedTime = 11;
  int  expect      = 0;
  int  actual      = solution->findDelayedArrivalTime(arrivalTime, delayedTime);
  LCD_EXPECT_EQ(expect, actual);
}
