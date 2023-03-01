// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Complement of Base 10 Integer
//
// https://leetcode.com/problems/complement-of-base-10-integer/
//
// Question ID: 1009
// Difficult  : Easy
// Solve Date : 2022/01/04 18:15

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1009. Complement of Base 10 Integer|:
//
// The complement of an integer is the integer you get when you flip all the
// |0|'s to |1|'s and all the |1|'s to |0|'s in its binary representation.
//
//  • For example, The integer |5| is |"101"| in binary and its complement is
//  |"010"| which is the integer |2|.
// Given an integer |n|, return its complement.
//  
//

LEETCODE_BEGIN_RESOLVING(1009, ComplementOfBase10Integer, Solution);

class Solution {
public:
  int bitwiseComplement(int n) {
    if (n == 0)
      return 1;
    unsigned mask = ~0;
    while (mask & n)
      mask <<= 1;
    return ~n ^ mask;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= n < 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5
// Output: 2
//
// 5 is "101" in binary, with complement "010" in binary, which is 2 in base-10.

LEETCODE_SOLUTION_UNITTEST(1009, ComplementOfBase10Integer, example_1) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  expect   = 2;
  int  actual   = solution->bitwiseComplement(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 7
// Output: 0
//
// 7 is "111" in binary, with complement "000" in binary, which is 0 in base-10.

LEETCODE_SOLUTION_UNITTEST(1009, ComplementOfBase10Integer, example_2) {
  auto solution = MakeSolution();
  int  n        = 7;
  int  expect   = 0;
  int  actual   = solution->bitwiseComplement(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 10
// Output: 5
//
// 10 is "1010" in binary, with complement "0101" in binary, which is 5 in
// base-10.

LEETCODE_SOLUTION_UNITTEST(1009, ComplementOfBase10Integer, example_3) {
  auto solution = MakeSolution();
  int  n        = 10;
  int  expect   = 5;
  int  actual   = solution->bitwiseComplement(n);
  LCD_EXPECT_EQ(expect, actual);
}
