// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of 1 Bits
//
// https://leetcode.com/problems/number-of-1-bits/
//
// Question ID: 191
// Difficult  : Easy
// Solve Date : 2021/09/17 08:00

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |191. Number of 1 Bits|:
//
// Write a function that takes the binary representation of an unsigned integer
// and returns the number of '1' bits it has (also known as the [Hamming
// weight]). Note:
//
//  • Note that in some languages, such as Java, there is no unsigned integer
//  type. In this case, the input will be given as a signed integer type. It
//  should not affect your implementation, as the integer's internal binary
//  representation is the same, whether it is signed or unsigned.
//

LEETCODE_BEGIN_RESOLVING(191, NumberOf1Bits, Solution);

class Solution {
public:
  int hammingWeight(uint32_t n) {
    int res = 0;
    while (n != 0) {
      n &= n - 1;
      ++res;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The input must be a binary string of length |32|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 00000000000000000000000000001011
// Output: 3
//
// The input binary string 00000000000000000000000000001011 has a total of three
// '1' bits.

LEETCODE_SOLUTION_UNITTEST(191, NumberOf1Bits, example_1) {
  auto     solution = MakeSolution();
  uint32_t n        = 0b00000000000000000000000000001011;
  int      expect   = 3;
  int      actual   = solution->hammingWeight(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 00000000000000000000000010000000
// Output: 1
//
// The input binary string 00000000000000000000000010000000 has a total of one
// '1' bit.

LEETCODE_SOLUTION_UNITTEST(191, NumberOf1Bits, example_2) {
  auto     solution = MakeSolution();
  uint32_t n        = 0b00000000000000000000000010000000;
  int      expect   = 1;
  int      actual   = solution->hammingWeight(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 11111111111111111111111111111101
// Output: 31
//
// The input binary string 11111111111111111111111111111101 has a total of
// thirty one '1' bits.

LEETCODE_SOLUTION_UNITTEST(191, NumberOf1Bits, example_3) {
  auto     solution = MakeSolution();
  uint32_t n        = 0b11111111111111111111111111111101;
  int      expect   = 31;
  int      actual   = solution->hammingWeight(n);
  LCD_EXPECT_EQ(expect, actual);
}
