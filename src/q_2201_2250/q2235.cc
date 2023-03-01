// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Add Two Integers
//
// https://leetcode.com/problems/add-two-integers/
//
// Question ID: 2235
// Difficult  : Easy
// Solve Date : 2023/01/16 16:02

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2235. Add Two Integers|:
//
// Given two integers |num1| and |num2|, return the sum of the two integers.
//

LEETCODE_BEGIN_RESOLVING(2235, AddTwoIntegers, Solution);

class Solution {
public:
  int sum(int num1, int num2) { return num1 + num2; }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |-100 <= num1, num2 <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num1 = 12, num2 = 5
// Output: 17
//
// num1 is 12, num2 is 5, and their sum is 12 + 5 = 17, so 17 is returned.

LEETCODE_SOLUTION_UNITTEST(2235, AddTwoIntegers, example_1) {
  auto solution = MakeSolution();
  int  num1     = 12;
  int  num2     = 5;
  int  expect   = 17;
  int  actual   = solution->sum(num1, num2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num1 = -10, num2 = 4
// Output: -6
//
// num1 + num2 = -6, so -6 is returned.

LEETCODE_SOLUTION_UNITTEST(2235, AddTwoIntegers, example_2) {
  auto solution = MakeSolution();
  int  num1     = -10;
  int  num2     = 4;
  int  expect   = -6;
  int  actual   = solution->sum(num1, num2);
  LCD_EXPECT_EQ(expect, actual);
}
