// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Numbers with Unique Digits
//
// https://leetcode.com/problems/count-numbers-with-unique-digits/
//
// Question ID: 357
// Difficult  : Medium
// Solve Date : 2022/11/15 18:58

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |357. Count Numbers with Unique Digits|:
//
// Given an integer |n|, return the count of all numbers with unique digits,
// |x|, where |0 <= x < 10ⁿ|.
//

LEETCODE_BEGIN_RESOLVING(357, CountNumbersWithUniqueDigits, Solution);

class Solution {
public:
  int countNumbersWithUniqueDigits(int n) {
    if (n == 0) {
      return 1;
    } else if (n == 1) {
      return 10;
    } else if (n == 2) {
      return 91;
    } else {
      auto res = (int)91;
      auto dgt = (int)81;
      for (int i = 3; i <= n; ++i) {
        res += (dgt *= (10 - i + 1));
      }
      return res;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= n <= 8|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2
// Output: 91
//
// The answer should be the total numbers in the range of 0 ≤ x < 100, excluding
// 11,22,33,44,55,66,77,88,99

LEETCODE_SOLUTION_UNITTEST(357, CountNumbersWithUniqueDigits, example_1) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  expect   = 91;
  int  actual   = solution->countNumbersWithUniqueDigits(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 0
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(357, CountNumbersWithUniqueDigits, example_2) {
  auto solution = MakeSolution();
  int  n        = 0;
  int  expect   = 1;
  int  actual   = solution->countNumbersWithUniqueDigits(n);
  LCD_EXPECT_EQ(expect, actual);
}
