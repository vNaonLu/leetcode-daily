// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Broken Calculator
//
// https://leetcode.com/problems/broken-calculator/
//
// Question ID: 991
// Difficult  : Medium
// Solve Date : 2022/03/23 18:27

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |991. Broken Calculator|:
//
// There is a broken calculator that has the integer |startValue| on its display
// initially. In one operation, you can:
//
//  • multiply the number on display by |2|, or
//
//  • subtract |1| from the number on display.
// Given two integers |startValue| and |target|, return the minimum number of
// operations needed to display |target| on the calculator.  
//

LEETCODE_BEGIN_RESOLVING(991, BrokenCalculator, Solution);

class Solution {
public:
  int brokenCalc(int startValue, int target) {
    int res = 0;

    while (target > startValue) {
      ++res;

      if (target % 2) {
        ++target;
      } else {
        target >>= 1;
      }
    }

    return res + startValue - target;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= startValue, target <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: startValue = 2, target = 3
// Output: 2
//
// Use double operation and then decrement operation {2 -> 4 -> 3}.

LEETCODE_SOLUTION_UNITTEST(991, BrokenCalculator, example_1) {
  auto solution   = MakeSolution();
  int  startValue = 2;
  int  target     = 3;
  int  expect     = 2;
  int  actual     = solution->brokenCalc(startValue, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: startValue = 5, target = 8
// Output: 2
//
// Use decrement and then double {5 -> 4 -> 8}.

LEETCODE_SOLUTION_UNITTEST(991, BrokenCalculator, example_2) {
  auto solution   = MakeSolution();
  int  startValue = 5;
  int  target     = 8;
  int  expect     = 2;
  int  actual     = solution->brokenCalc(startValue, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: startValue = 3, target = 10
// Output: 3
//
// Use double, decrement and double {3 -> 6 -> 5 -> 10}.

LEETCODE_SOLUTION_UNITTEST(991, BrokenCalculator, example_3) {
  auto solution   = MakeSolution();
  int  startValue = 3;
  int  target     = 10;
  int  expect     = 3;
  int  actual     = solution->brokenCalc(startValue, target);
  LCD_EXPECT_EQ(expect, actual);
}
