// Copyright 2023 Naon Lu
//
// This file describes the solution of
// A Number After a Double Reversal
//
// https://leetcode.com/problems/a-number-after-a-double-reversal/
//
// Question ID: 2119
// Difficult  : Easy
// Solve Date : 2023/10/03 19:05

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2119. A Number After a Double Reversal|:
//
// Reversing an integer means to reverse all its digits.
//
//  • For example, reversing |2021| gives |1202|. Reversing |12300| gives |321|
//  as the leading zeros are not retained.
// Given an integer |num|, reverse |num| to get |reversed1|, then reverse
// |reversed1| to get |reversed2|. Return |true| if |reversed2| equals |num|.
// Otherwise return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(2119, ANumberAfterADoubleReversal, Solution);

class Solution {
public:
  bool isSameAfterReversals(int num) { return num == 0 || num % 10; }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |0 <= num <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 526
// Output: true
//
// Reverse num to get 625, then reverse 625 to get 526, which equals num.

LEETCODE_SOLUTION_UNITTEST(2119, ANumberAfterADoubleReversal, example_1) {
  auto solution = MakeSolution();
  int  num      = 526;
  bool expect   = true;
  bool actual   = solution->isSameAfterReversals(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 1800
// Output: false
//
// Reverse num to get 81, then reverse 81 to get 18, which does not equal num.

LEETCODE_SOLUTION_UNITTEST(2119, ANumberAfterADoubleReversal, example_2) {
  auto solution = MakeSolution();
  int  num      = 1800;
  bool expect   = false;
  bool actual   = solution->isSameAfterReversals(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: num = 0
// Output: true
//
// Reverse num to get 0, then reverse 0 to get 0, which equals num.

LEETCODE_SOLUTION_UNITTEST(2119, ANumberAfterADoubleReversal, example_3) {
  auto solution = MakeSolution();
  int  num      = 0;
  bool expect   = true;
  bool actual   = solution->isSameAfterReversals(num);
  LCD_EXPECT_EQ(expect, actual);
}
