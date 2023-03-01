// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Common Factors
//
// https://leetcode.com/problems/number-of-common-factors/
//
// Question ID: 2427
// Difficult  : Easy
// Solve Date : 2023/02/02 19:03

#include <iosfwd>
#include <numeric>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2427. Number of Common Factors|:
//
// Given two positive integers |a| and |b|, return the number of common factors
// of |a| and |b|. An integer |x| is a common factor of |a| and |b| if |x|
// divides both |a| and |b|.
//

LEETCODE_BEGIN_RESOLVING(2427, NumberOfCommonFactors, Solution);

class Solution {
public:
  int commonFactors(int a, int b) {
    auto x   = gcd(a, b);
    int  res = 0;
    for (int i = 1; i <= x; ++i) {
      if (x % i == 0) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= a, b <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: a = 12, b = 6
// Output: 4
//
// The common factors of 12 and 6 are 1, 2, 3, 6.

LEETCODE_SOLUTION_UNITTEST(2427, NumberOfCommonFactors, example_1) {
  auto solution = MakeSolution();
  int  a        = 12;
  int  b        = 6;
  int  expect   = 4;
  int  actual   = solution->commonFactors(a, b);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: a = 25, b = 30
// Output: 2
//
// The common factors of 25 and 30 are 1, 5.

LEETCODE_SOLUTION_UNITTEST(2427, NumberOfCommonFactors, example_2) {
  auto solution = MakeSolution();
  int  a        = 25;
  int  b        = 30;
  int  expect   = 2;
  int  actual   = solution->commonFactors(a, b);
  LCD_EXPECT_EQ(expect, actual);
}
