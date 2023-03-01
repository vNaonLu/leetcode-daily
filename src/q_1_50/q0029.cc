// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Divide Two Integers
//
// https://leetcode.com/problems/divide-two-integers/
//
// Question ID: 29
// Difficult  : Medium
// Solve Date : 2021/11/20 14:38

#include <iosfwd>
#include <limits>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |29. Divide Two Integers|:
//
// Given two integers |dividend| and |divisor|, divide two integers without
// using multiplication, division, and mod operator. The integer division should
// truncate toward zero, which means losing its fractional part. For example,
// |8.345| would be truncated to |8|, and |-2.7335| would be truncated to |-2|.
// Return the quotient after dividing |dividend| by |divisor|.
// Note: Assume we are dealing with an environment that could only store
// integers within the 32-bit signed integer range: |[−2³¹, 2³¹ − 1]|. For this
// problem, if the quotient is strictly greater than |2³¹ - 1|, then return |2³¹
// - 1|, and if the quotient is strictly less than |-2³¹|, then return |-2³¹|.  
//

LEETCODE_BEGIN_RESOLVING(29, DivideTwoIntegers, Solution);

class Solution {
public:
  int divide(int dividend, int divisor) {
    if (dividend == numeric_limits<int>::min() && divisor == -1)
      return numeric_limits<int>::max();
    long l_divisor, l_dividend, quotient = 0;
    l_divisor  = static_cast<long>(divisor);
    l_dividend = static_cast<long>(dividend);
    int sign =
        (l_dividend < 0 && l_divisor > 0) || (l_divisor < 0 && l_dividend > 0)
            ? -1
            : 1;
    l_dividend = abs(l_dividend);
    l_divisor  = abs(l_divisor);
    for (int shift_counter = 31; shift_counter >= 0; shift_counter--) {
      if ((l_divisor << shift_counter) <= l_dividend) {
        l_dividend -= l_divisor << shift_counter;
        quotient = quotient | static_cast<long>(1) << shift_counter;
      }
    }
    return sign * quotient;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |-2³¹ <= dividend, divisor <= 2³¹ - 1|
// * |divisor != 0|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: dividend = 10, divisor = 3
// Output: 3
//
// 10/3 = 3.33333.. which is truncated to 3.

LEETCODE_SOLUTION_UNITTEST(29, DivideTwoIntegers, example_1) {
  auto solution = MakeSolution();
  int  dividend = 10;
  int  divisor  = 3;
  int  expect   = 3;
  int  actual   = solution->divide(dividend, divisor);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: dividend = 7, divisor = -3
// Output: -2
//
// 7/-3 = -2.33333.. which is truncated to -2.

LEETCODE_SOLUTION_UNITTEST(29, DivideTwoIntegers, example_2) {
  auto solution = MakeSolution();
  int  dividend = 7;
  int  divisor  = -3;
  int  expect   = -2;
  int  actual   = solution->divide(dividend, divisor);
  LCD_EXPECT_EQ(expect, actual);
}
