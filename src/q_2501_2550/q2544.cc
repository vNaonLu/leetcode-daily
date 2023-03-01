// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Alternating Digit Sum
//
// https://leetcode.com/problems/alternating-digit-sum/
//
// Question ID: 2544
// Difficult  : Easy
// Solve Date : 2023/02/06 16:42

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2544. Alternating Digit Sum|:
//
// You are given a positive integer |n|. Each digit of |n| has a sign according
// to the following rules:
//
//  • The most significant digit is assigned a positive sign.
//
//  • Each other digit has an opposite sign to its adjacent digits.
// Return the sum of all digits with their corresponding sign.
//

LEETCODE_BEGIN_RESOLVING(2544, AlternatingDigitSum, Solution);

class Solution {
public:
  int alternateDigitSum(int n) {
    int res    = 0;
    int sign   = 1;
    int length = 0;
    while (n > 0) {
      res += (n % 10) * sign;
      sign *= -1;
      ++length;
      n /= 10;
    }
    return length & 1 ? res : -res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 521
// Output: 4
//
// (+5) + (-2) + (+1) = 4.

LEETCODE_SOLUTION_UNITTEST(2544, AlternatingDigitSum, example_1) {
  auto solution = MakeSolution();
  int  n        = 521;
  int  expect   = 4;
  int  actual   = solution->alternateDigitSum(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 111
// Output: 1
//
// (+1) + (-1) + (+1) = 1.

LEETCODE_SOLUTION_UNITTEST(2544, AlternatingDigitSum, example_2) {
  auto solution = MakeSolution();
  int  n        = 111;
  int  expect   = 1;
  int  actual   = solution->alternateDigitSum(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 886996
// Output: 0
//
// (+8) + (-8) + (+6) + (-9) + (+9) + (-6) = 0.

LEETCODE_SOLUTION_UNITTEST(2544, AlternatingDigitSum, example_3) {
  auto solution = MakeSolution();
  int  n        = 886996;
  int  expect   = 0;
  int  actual   = solution->alternateDigitSum(n);
  LCD_EXPECT_EQ(expect, actual);
}
