// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Angle Between Hands of a Clock
//
// https://leetcode.com/problems/angle-between-hands-of-a-clock/
//
// Question ID: 1344
// Difficult  : Medium
// Solve Date : 2022/03/02 18:33

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1344. Angle Between Hands of a Clock|:
//
// Given two numbers, |hour| and |minutes|, return the smaller angle (in
// degrees) formed between the |hour| and the |minute| hand. Answers within
// |10⁻⁵| of the actual value will be accepted as correct.  
//

LEETCODE_BEGIN_RESOLVING(1344, AngleBetweenHandsOfAClock, Solution);

class Solution {
public:
  double angleClock(int hour, int minutes) {
    if (hour == 12)
      hour = 0;

    double hour_d = (hour * 30.) + (minutes / 2.), min_d = minutes * 6.;

    return hour_d > min_d ? min(hour_d - min_d, 360 - hour_d + min_d)
                          : min(min_d - hour_d, 360 - min_d + hour_d);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= hour <= 12|
// * |0 <= minutes <= 59|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: hour = 12, minutes = 30
// Output: 165
//

LEETCODE_SOLUTION_UNITTEST(1344, AngleBetweenHandsOfAClock, example_1) {
  auto   solution = MakeSolution();
  int    hour     = 12;
  int    minutes  = 30;
  double expect   = 165;
  double actual   = solution->angleClock(hour, minutes);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: hour = 3, minutes = 30
// Output: 75
//

LEETCODE_SOLUTION_UNITTEST(1344, AngleBetweenHandsOfAClock, example_2) {
  auto   solution = MakeSolution();
  int    hour     = 3;
  int    minutes  = 30;
  double expect   = 75;
  double actual   = solution->angleClock(hour, minutes);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: hour = 3, minutes = 15
// Output: 7.5
//

LEETCODE_SOLUTION_UNITTEST(1344, AngleBetweenHandsOfAClock, example_3) {
  auto   solution = MakeSolution();
  int    hour     = 3;
  int    minutes  = 15;
  double expect   = 7.5;
  double actual   = solution->angleClock(hour, minutes);
  LCD_EXPECT_EQ(expect, actual);
}
