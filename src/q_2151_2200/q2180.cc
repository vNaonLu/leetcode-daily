// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Integers With Even Digit Sum
//
// https://leetcode.com/problems/count-integers-with-even-digit-sum/
//
// Question ID: 2180
// Difficult  : Easy
// Solve Date : 2022/03/16 18:36

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2180. Count Integers With Even Digit Sum|:
//
// Given a positive integer |num|, return the number of positive integers less
// than or equal to |num| whose digit sums are even. The digit sum of a positive
// integer is the sum of all its digits.  
//

LEETCODE_BEGIN_RESOLVING(2180, CountIntegersWithEvenDigitSum, Solution);

class Solution {
public:
  int countEven(int num) {
    int adjust =
        (num / 1000 + num % 1000 / 100 + num % 100 / 10 + num % 10) % 2;
    return (num - adjust) / 2;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= num <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 4
// Output: 2
//
// The only integers less than or equal to 4 whose digit sums are even are 2
// and 4.

LEETCODE_SOLUTION_UNITTEST(2180, CountIntegersWithEvenDigitSum, example_1) {
  auto solution = MakeSolution();
  int  num      = 4;
  int  expect   = 2;
  int  actual   = solution->countEven(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 30
// Output: 14
//
// The 14 integers less than or equal to 30 whose digit sums are even are
// 2, 4, 6, 8, 11, 13, 15, 17, 19, 20, 22, 24, 26, and 28.

LEETCODE_SOLUTION_UNITTEST(2180, CountIntegersWithEvenDigitSum, example_2) {
  auto solution = MakeSolution();
  int  num      = 30;
  int  expect   = 14;
  int  actual   = solution->countEven(num);
  LCD_EXPECT_EQ(expect, actual);
}
