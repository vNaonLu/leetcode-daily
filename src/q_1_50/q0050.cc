// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Pow(x, n)
//
// https://leetcode.com/problems/powx-n/
//
// Question ID: 50
// Difficult  : Medium
// Solve Date : 2021/11/28 14:29

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |50. Pow(x, n)|:
//
// Implement [pow(x, n)], which calculates |x| raised to the power |n| (i.e.,
// |xⁿ|).  
//

LEETCODE_BEGIN_RESOLVING(50, PowXN, Solution);

class Solution {
public:
  double myPow(double x, int n) {
    double    res = 1.0;
    long long y   = n;
    while (abs(n)) {
      if (abs(n) % 2)
        res = res * x;
      x = x * x;
      n = abs(n) / 2;
    }
    if (y < 0)
      res = (double)(1.0) / (double)(res);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |-100.0 < x < 100.0|
// * |-2³¹ <= n <= 2³¹-1|
// * |n| is an integer.
// * |-10⁴ <= xⁿ <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: x = 2.00000, n = 10
// Output: 1024.00000
//

LEETCODE_SOLUTION_UNITTEST(50, PowXN, example_1) {
  auto   solution = MakeSolution();
  double x        = 2.00000;
  int    n        = 10;
  double expect   = 1024.00000;
  double actual   = solution->myPow(x, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: x = 2.10000, n = 3
// Output: 9.26100
//

LEETCODE_SOLUTION_UNITTEST(50, PowXN, example_2) {
  auto   solution = MakeSolution();
  double x        = 2.10000;
  int    n        = 3;
  double expect   = 9.26100;
  double actual   = solution->myPow(x, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: x = 2.00000, n = -2
// Output: 0.25000
//
// 2⁻² = 1/2² = 1/4 = 0.25

LEETCODE_SOLUTION_UNITTEST(50, PowXN, example_3) {
  auto   solution = MakeSolution();
  double x        = 2.00000;
  int    n        = -2;
  double expect   = 0.25000;
  double actual   = solution->myPow(x, n);
  LCD_EXPECT_EQ(expect, actual);
}
