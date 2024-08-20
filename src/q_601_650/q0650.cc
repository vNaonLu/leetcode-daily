// Copyright 2024 Naon Lu
//
// This file describes the solution of
// 2 Keys Keyboard
//
// https://leetcode.com/problems/2-keys-keyboard/
//
// Question ID: 650
// Difficult  : Medium
// Solve Date : 2024/08/19 19:15

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |650. 2 Keys Keyboard|:
//
// There is only one character |'A'| on the screen of a notepad. You can perform
// one of two operations on this notepad for each step:
//
//  • Copy All: You can copy all the characters present on the screen (a partial
//  copy is not allowed).
//
//  • Paste: You can paste the characters which are copied last time.
// Given an integer |n|, return the minimum number of operations to get the
// character |'A'| exactly |n| times on the screen.
//
//

LEETCODE_BEGIN_RESOLVING(650, 2KeysKeyboard, Solution);

class Solution {
public:
  int minSteps(int n) {
    if (1 == n) {
      return 0;
    }

    int res    = 0;
    int factor = 2;
    while (n > 1) {
      while (n % factor == 0) {
        res += factor;
        n /= factor;
      }
      ++factor;
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
//  Input: n = 3
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(650, 2KeysKeyboard, example_1) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  expect   = 3;
  int  actual   = solution->minSteps(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(650, 2KeysKeyboard, example_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 0;
  int  actual   = solution->minSteps(n);
  LCD_EXPECT_EQ(expect, actual);
}
