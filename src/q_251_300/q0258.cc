// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Add Digits
//
// https://leetcode.com/problems/add-digits/
//
// Question ID: 258
// Difficult  : Easy
// Solve Date : 2021/11/23 18:50

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |258. Add Digits|:
//
// Given an integer |num|, repeatedly add all its digits until the result has
// only one digit, and return it.  
//

LEETCODE_BEGIN_RESOLVING(258, AddDigits, Solution);

class Solution {
public:
  int addDigits(int num) { return num == 0 ? 0 : 1 + (num - 1) % 9; }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= num <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 38
// Output: 2
//
// The process is
// 38 --> 3 + 8 --> 11
// 11 --> 1 + 1 --> 2
// Since 2 has only one digit, return it.

LEETCODE_SOLUTION_UNITTEST(258, AddDigits, example_1) {
  auto solution = MakeSolution();
  int  num      = 38;
  int  expect   = 2;
  int  actual   = solution->addDigits(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 0
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(258, AddDigits, example_2) {
  auto solution = MakeSolution();
  int  num      = 0;
  int  expect   = 0;
  int  actual   = solution->addDigits(num);
  LCD_EXPECT_EQ(expect, actual);
}
