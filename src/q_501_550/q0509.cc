// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Fibonacci Number
//
// https://leetcode.com/problems/fibonacci-number/
//
// Question ID: 509
// Difficult  : Easy
// Solve Date : 2021/10/10 13:37

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |509. Fibonacci Number|:
//
// The Fibonacci numbers, commonly denoted |F(n)| form a sequence, called the
// Fibonacci sequence, such that each number is the sum of the two preceding
// ones, starting from |0| and |1|. That is, F(0) = 0, F(1) = 1 F(n) = F(n - 1)
// + F(n - 2), for n > 1. Given |n|, calculate |F(n)|.  
//

LEETCODE_BEGIN_RESOLVING(509, FibonacciNumber, Solution);

class Solution {
public:
  int fib(int n) {
    if (n == 0)
      return 0;
    if (n == 1)
      return 1;
    int frs = 0, scd = 1;
    for (int i = 2; i < n; ++i) {
      scd += frs;
      frs = scd - frs;
    }
    return frs + scd;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= n <= 30|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2
// Output: 1
//
// F(2) = F(1) + F(0) = 1 + 0 = 1.

LEETCODE_SOLUTION_UNITTEST(509, FibonacciNumber, example_1) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  expect   = 1;
  int  actual   = solution->fib(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3
// Output: 2
//
// F(3) = F(2) + F(1) = 1 + 1 = 2.

LEETCODE_SOLUTION_UNITTEST(509, FibonacciNumber, example_2) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  expect   = 2;
  int  actual   = solution->fib(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 4
// Output: 3
//
// F(4) = F(3) + F(2) = 2 + 1 = 3.

LEETCODE_SOLUTION_UNITTEST(509, FibonacciNumber, example_3) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  expect   = 3;
  int  actual   = solution->fib(n);
  LCD_EXPECT_EQ(expect, actual);
}
