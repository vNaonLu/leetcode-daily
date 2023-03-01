// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sum of Digits in Base K
//
// https://leetcode.com/problems/sum-of-digits-in-base-k/
//
// Question ID: 1837
// Difficult  : Easy
// Solve Date : 2022/12/20 18:35

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1837. Sum of Digits in Base K|:
//
// Given an integer |n| (in base |10|) and a base |k|, return the sum of the
// digits of |n| after converting |n| from base |10| to base |k|. After
// converting, each digit should be interpreted as a base |10| number, and the
// sum should be returned in base |10|.
//

LEETCODE_BEGIN_RESOLVING(1837, SumOfDigitsInBaseK, Solution);

class Solution {
public:
  int sumBase(int n, int k) {
    auto res = (int)0;
    while (n) {
      res += n % k;
      n /= k;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 100|
// * |2 <= k <= 10|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 34, k = 6
// Output: 9
//
// 34 (base 10) expressed in base 6 is 54. 5 + 4 = 9.

LEETCODE_SOLUTION_UNITTEST(1837, SumOfDigitsInBaseK, example_1) {
  auto solution = MakeSolution();
  int  n        = 34;
  int  k        = 6;
  int  expect   = 9;
  int  actual   = solution->sumBase(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 10, k = 10
// Output: 1
//
// n is already in base 10. 1 + 0 = 1.

LEETCODE_SOLUTION_UNITTEST(1837, SumOfDigitsInBaseK, example_2) {
  auto solution = MakeSolution();
  int  n        = 10;
  int  k        = 10;
  int  expect   = 1;
  int  actual   = solution->sumBase(n, k);
  LCD_EXPECT_EQ(expect, actual);
}
