// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Smallest Integer Divisible by K
//
// https://leetcode.com/problems/smallest-integer-divisible-by-k/
//
// Question ID: 1015
// Difficult  : Medium
// Solve Date : 2021/12/30 18:05

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1015. Smallest Integer Divisible by K|:
//
// Given a positive integer |k|, you need to find the length of the smallest
// positive integer |n| such that |n| is divisible by |k|, and |n| only contains
// the digit |1|. Return the length of |n|. If there is no such |n|, return -1.
// Note: |n| may not fit in a 64-bit signed integer.
//  
//

LEETCODE_BEGIN_RESOLVING(1015, SmallestIntegerDivisibleByK, Solution);

class Solution {
public:
  int smallestRepunitDivByK(int k) {
    int res = 0;
    for (int i = 1; i <= k; ++i) {
      res = (res * 10 + 1) % k;
      if (res == 0)
        return i;
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= k <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: k = 1
// Output: 1
//
// The smallest answer is n = 1, which has length 1.

LEETCODE_SOLUTION_UNITTEST(1015, SmallestIntegerDivisibleByK, example_1) {
  auto solution = MakeSolution();
  int  k        = 1;
  int  expect   = 1;
  int  actual   = solution->smallestRepunitDivByK(k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: k = 2
// Output: -1
//
// There is no such positive integer n divisible by 2.

LEETCODE_SOLUTION_UNITTEST(1015, SmallestIntegerDivisibleByK, example_2) {
  auto solution = MakeSolution();
  int  k        = 2;
  int  expect   = -1;
  int  actual   = solution->smallestRepunitDivByK(k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: k = 3
// Output: 3
//
// The smallest answer is n = 111, which has length 3.

LEETCODE_SOLUTION_UNITTEST(1015, SmallestIntegerDivisibleByK, example_3) {
  auto solution = MakeSolution();
  int  k        = 3;
  int  expect   = 3;
  int  actual   = solution->smallestRepunitDivByK(k);
  LCD_EXPECT_EQ(expect, actual);
}
