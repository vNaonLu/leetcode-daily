// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimize XOR
//
// https://leetcode.com/problems/minimize-xor/
//
// Question ID: 2429
// Difficult  : Medium
// Solve Date : 2025/01/15 19:35

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2429. Minimize XOR|:
//
// Given two positive integers |num1| and |num2|, find the positive integer |x|
// such that:
//
//  • |x| has the same number of set bits as |num2|, and
//
//  • The value |x XOR num1| is minimal.
// Note that |XOR| is the bitwise XOR operation.
// Return the integer |x|. The test cases are generated such that |x| is
// uniquely determined. The number of set bits of an integer is the number of
// |1|'s in its binary representation.
//
//

LEETCODE_BEGIN_RESOLVING(2429, MinimizeXOR, Solution);

class Solution {
public:
  int minimizeXor(int num1, int num2) {
    int a   = __builtin_popcount(num1);
    int b   = __builtin_popcount(num2);
    int res = num1;
    for (int i = 0; i < 32; ++i) {
      if (a > b && (1 << i) & num1) {
        res ^= 1 << i;
        --a;
      }
      if (a < b && !((1 << i) & num1)) {
        res ^= 1 << i;
        ++a;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= num1, num2 <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num1 = 3, num2 = 5
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2429, MinimizeXOR, example_1) {
  auto solution = MakeSolution();
  int  num1     = 3;
  int  num2     = 5;
  int  expect   = 3;
  int  actual   = solution->minimizeXor(num1, num2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num1 = 1, num2 = 12
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2429, MinimizeXOR, example_2) {
  auto solution = MakeSolution();
  int  num1     = 1;
  int  num2     = 12;
  int  expect   = 3;
  int  actual   = solution->minimizeXor(num1, num2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 25
// 72
// Output: 24
//

LEETCODE_SOLUTION_UNITTEST(2429, MinimizeXOR, extra_testcase_1) {
  auto solution = MakeSolution();
  int  num1     = 25;
  int  num2     = 72;
  int  expect   = 24;
  int  actual   = solution->minimizeXor(num1, num2);
  LCD_EXPECT_EQ(expect, actual);
}
