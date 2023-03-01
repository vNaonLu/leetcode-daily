// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Steps to Reduce a Number to Zero
//
// https://leetcode.com/problems/number-of-steps-to-reduce-a-number-to-zero/
//
// Question ID: 1342
// Difficult  : Easy
// Solve Date : 2022/05/27 18:13

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1342. Number of Steps to Reduce a Number to Zero|:
//
// Given an integer |num|, return the number of steps to reduce it to zero.
// In one step, if the current number is even, you have to divide it by |2|,
// otherwise, you have to subtract |1| from it.
//

LEETCODE_BEGIN_RESOLVING(1342, NumberOfStepsToReduceANumberToZero, Solution);

class Solution {
public:
  int numberOfSteps(int num) {
    int res = 0;
    while (num != 0) {
      if (num & 1) {
        --num;
      } else {
        num >>= 1;
      }
      ++res;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= num <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 14
// Output: 6
//
//
// Step 1) 14 is even; divide by 2 and obtain 7.
// Step 2) 7 is odd; subtract 1 and obtain 6.
// Step 3) 6 is even; divide by 2 and obtain 3.
// Step 4) 3 is odd; subtract 1 and obtain 2.
// Step 5) 2 is even; divide by 2 and obtain 1.
// Step 6) 1 is odd; subtract 1 and obtain 0.

LEETCODE_SOLUTION_UNITTEST(1342, NumberOfStepsToReduceANumberToZero,
                           example_1) {
  auto solution = MakeSolution();
  int  num      = 14;
  int  expect   = 6;
  int  actual   = solution->numberOfSteps(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 8
// Output: 4
//
//
// Step 1) 8 is even; divide by 2 and obtain 4.
// Step 2) 4 is even; divide by 2 and obtain 2.
// Step 3) 2 is even; divide by 2 and obtain 1.
// Step 4) 1 is odd; subtract 1 and obtain 0.

LEETCODE_SOLUTION_UNITTEST(1342, NumberOfStepsToReduceANumberToZero,
                           example_2) {
  auto solution = MakeSolution();
  int  num      = 8;
  int  expect   = 4;
  int  actual   = solution->numberOfSteps(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: num = 123
// Output: 12
//

LEETCODE_SOLUTION_UNITTEST(1342, NumberOfStepsToReduceANumberToZero,
                           example_3) {
  auto solution = MakeSolution();
  int  num      = 123;
  int  expect   = 12;
  int  actual   = solution->numberOfSteps(num);
  LCD_EXPECT_EQ(expect, actual);
}
