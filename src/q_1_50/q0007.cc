// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reverse Integer
//
// https://leetcode.com/problems/reverse-integer/
//
// Question ID: 7
// Difficult  : Medium
// Solve Date : 2021/10/05 01:21

#include <iosfwd>
#include <limits>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |7. Reverse Integer|:
//
// Given a signed 32-bit integer |x|, return |x| with its digits reversed. If
// reversing |x| causes the value to go outside the signed 32-bit integer range
// |[-2³¹, 2³¹ - 1]|, then return |0|. Assume the environment does not allow you
// to store 64-bit integers (signed or unsigned).  
//

LEETCODE_BEGIN_RESOLVING(7, ReverseInteger, Solution);

class Solution {
public:
  int reverse(int x) {
    int       sign = x < 0 ? -1 : 1;
    long long res  = 0;
    x              = abs(x);
    while (x > 0) {
      res = res * 10 + x % 10;
      x /= 10;
    }
    res *= sign;
    return res > numeric_limits<int>::max()   ? 0
           : res < numeric_limits<int>::min() ? 0
                                              : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |-2³¹ <= x <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: x = 123
// Output: 321
//

LEETCODE_SOLUTION_UNITTEST(7, ReverseInteger, example_1) {
  auto solution = MakeSolution();
  int  x        = 123;
  int  expect   = 321;
  int  actual   = solution->reverse(x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: x = -123
// Output: -321
//

LEETCODE_SOLUTION_UNITTEST(7, ReverseInteger, example_2) {
  auto solution = MakeSolution();
  int  x        = -123;
  int  expect   = -321;
  int  actual   = solution->reverse(x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: x = 120
// Output: 21
//

LEETCODE_SOLUTION_UNITTEST(7, ReverseInteger, example_3) {
  auto solution = MakeSolution();
  int  x        = 120;
  int  expect   = 21;
  int  actual   = solution->reverse(x);
  LCD_EXPECT_EQ(expect, actual);
}
