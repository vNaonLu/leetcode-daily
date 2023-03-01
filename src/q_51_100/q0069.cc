// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sqrt(x)
//
// https://leetcode.com/problems/sqrtx/
//
// Question ID: 69
// Difficult  : Easy
// Solve Date : 2022/01/14 18:14

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |69. Sqrt(x)|:
//
// Given a non-negative integer |x|, return the square root of |x| rounded down
// to the nearest integer. The returned integer should be non-negative as well.
// You must not use any built-in exponent function or operator.
//
//  • For example, do not use |pow(x, 0.5)| in c++ or |x ** 0.5| in python.
//  
//

LEETCODE_BEGIN_RESOLVING(69, SqrtX, Solution);

class Solution {
public:
  int mySqrt(int x) {
    if (x <= 1)
      return x;
    int64_t l = 1, r = x;
    while (r - l > 1) {
      int64_t mid = l + (r - l) / 2;
      if (mid * mid < x) {
        l = mid;
      } else if (mid * mid > x) {
        r = mid - 1;
      } else
        return mid;
    }
    return r * r <= x ? r : l;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= x <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: x = 4
// Output: 2
//
// The square root of 4 is 2, so we return 2.

LEETCODE_SOLUTION_UNITTEST(69, SqrtX, example_1) {
  auto solution = MakeSolution();
  int  x        = 4;
  int  expect   = 2;
  int  actual   = solution->mySqrt(x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: x = 8
// Output: 2
//
// The square root of 8 is 2.82842..., and since we round it down to the nearest
// integer, 2 is returned.

LEETCODE_SOLUTION_UNITTEST(69, SqrtX, example_2) {
  auto solution = MakeSolution();
  int  x        = 8;
  int  expect   = 2;
  int  actual   = solution->mySqrt(x);
  LCD_EXPECT_EQ(expect, actual);
}
