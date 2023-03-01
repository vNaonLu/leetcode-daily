// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number Complement
//
// https://leetcode.com/problems/number-complement/
//
// Question ID: 476
// Difficult  : Easy
// Solve Date : 2021/12/27 18:26

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |476. Number Complement|:
//
// The complement of an integer is the integer you get when you flip all the
// |0|'s to |1|'s and all the |1|'s to |0|'s in its binary representation.
//
//  • For example, The integer |5| is |"101"| in binary and its complement is
//  |"010"| which is the integer |2|.
// Given an integer |num|, return its complement.
//  
//

LEETCODE_BEGIN_RESOLVING(476, NumberComplement, Solution);

class Solution {
public:
  int findComplement(int num) {
    unsigned mask = ~0;
    while (mask & num)
      mask <<= 1;
    return ~num ^ mask;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= num < 2³¹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 5
// Output: 2
//
// The binary representation of 5 is 101 (no leading zero bits), and its
// complement is 010. So you need to output 2.

LEETCODE_SOLUTION_UNITTEST(476, NumberComplement, example_1) {
  auto solution = MakeSolution();
  int  num      = 5;
  int  expect   = 2;
  int  actual   = solution->findComplement(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 1
// Output: 0
//
// The binary representation of 1 is 1 (no leading zero bits), and its
// complement is 0. So you need to output 0.

LEETCODE_SOLUTION_UNITTEST(476, NumberComplement, example_2) {
  auto solution = MakeSolution();
  int  num      = 1;
  int  expect   = 0;
  int  actual   = solution->findComplement(num);
  LCD_EXPECT_EQ(expect, actual);
}
