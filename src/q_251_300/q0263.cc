// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Ugly Number
//
// https://leetcode.com/problems/ugly-number/
//
// Question ID: 263
// Difficult  : Easy
// Solve Date : 2021/11/25 18:02

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |263. Ugly Number|:
//
// An ugly number is a positive integer whose prime factors are limited to |2|,
// |3|, and |5|. Given an integer |n|, return |true| if |n| is an ugly number.  
//

LEETCODE_BEGIN_RESOLVING(263, UglyNumber, Solution);

class Solution {
public:
  bool isUgly(int n) {
    if (n == 0)
      return false;
    if (n == 1)
      return true;
    while (n % 2 == 0)
      n /= 2;
    while (n % 3 == 0)
      n /= 3;
    while (n % 5 == 0)
      n /= 5;
    return n == 1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |-2³¹ <= n <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 6
// Output: true
//
// 6 = 2 × 3

LEETCODE_SOLUTION_UNITTEST(263, UglyNumber, example_1) {
  auto solution = MakeSolution();
  int  n        = 6;
  bool expect   = true;
  bool actual   = solution->isUgly(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: true
//
// 1 has no prime factors, therefore all of its prime factors are limited to 2,
// 3, and 5.

LEETCODE_SOLUTION_UNITTEST(263, UglyNumber, example_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  bool expect   = true;
  bool actual   = solution->isUgly(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 14
// Output: false
//
// 14 is not ugly since it includes the prime factor 7.

LEETCODE_SOLUTION_UNITTEST(263, UglyNumber, example_3) {
  auto solution = MakeSolution();
  int  n        = 14;
  bool expect   = false;
  bool actual   = solution->isUgly(n);
  LCD_EXPECT_EQ(expect, actual);
}
