// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Smallest Divisible Digit Product I
//
// https://leetcode.com/problems/smallest-divisible-digit-product-i/
//
// Question ID: 3345
// Difficult  : Easy
// Solve Date : 2024/11/15 20:53

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3345. Smallest Divisible Digit Product I|:
//
// You are given two integers |n| and |t|. Return the smallest number greater
// than or equal to |n| such that the product of its digits is divisible by |t|.
//
//

LEETCODE_BEGIN_RESOLVING(3345, SmallestDivisibleDigitProductI, Solution);

class Solution {
public:
  int smallestNumber(int n, int t) {
    while (product(n) % t != 0) {
      ++n;
    }
    return n;
  }

private:
  int product(int n) {
    int p = 1;
    while (n > 0) {
      p *= n % 10;
      n /= 10;
    }
    return p;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 100|
// * |1 <= t <= 10|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 10, t = 2
// Output: 10
//

LEETCODE_SOLUTION_UNITTEST(3345, SmallestDivisibleDigitProductI, example_1) {
  auto solution = MakeSolution();
  int  n        = 10;
  int  t        = 2;
  int  expect   = 10;
  int  actual   = solution->smallestNumber(n, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 15, t = 3
// Output: 16
//

LEETCODE_SOLUTION_UNITTEST(3345, SmallestDivisibleDigitProductI, example_2) {
  auto solution = MakeSolution();
  int  n        = 15;
  int  t        = 3;
  int  expect   = 16;
  int  actual   = solution->smallestNumber(n, t);
  LCD_EXPECT_EQ(expect, actual);
}
