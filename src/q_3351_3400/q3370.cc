// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Smallest Number With All Set Bits
//
// https://leetcode.com/problems/smallest-number-with-all-set-bits/
//
// Question ID: 3370
// Difficult  : Easy
// Solve Date : 2024/12/16 21:37

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3370. Smallest Number With All Set Bits|:
//
// You are given a positive number |n|.
// Return the smallest number |x| greater than or equal to |n|, such that the
// binary representation of |x| contains only set bits
//
//

LEETCODE_BEGIN_RESOLVING(3370, SmallestNumberWithAllSetBits, Solution);

class Solution {
public:
  int smallestNumber(int n) {
    int res = 0;
    while (n) {
      res = res << 1 | 1;
      n >>= 1;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(3370, SmallestNumberWithAllSetBits, example_1) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  expect   = 7;
  int  actual   = solution->smallestNumber(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 10
// Output: 15
//

LEETCODE_SOLUTION_UNITTEST(3370, SmallestNumberWithAllSetBits, example_2) {
  auto solution = MakeSolution();
  int  n        = 10;
  int  expect   = 15;
  int  actual   = solution->smallestNumber(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 3
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3370, SmallestNumberWithAllSetBits, example_3) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  expect   = 3;
  int  actual   = solution->smallestNumber(n);
  LCD_EXPECT_EQ(expect, actual);
}
