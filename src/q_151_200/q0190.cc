// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reverse Bits
//
// https://leetcode.com/problems/reverse-bits/
//
// Question ID: 190
// Difficult  : Easy
// Solve Date : 2021/09/18 08:00

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |190. Reverse Bits|:
//
// Reverse bits of a given 32 bits unsigned integer.
// Note:
//
//  • Note that in some languages, such as Java, there is no unsigned integer
//  type. In this case, both input and output will be given as a signed integer
//  type. They should not affect your implementation, as the integer's internal
//  binary representation is the same, whether it is signed or unsigned.
//

LEETCODE_BEGIN_RESOLVING(190, ReverseBits, Solution);

class Solution {
public:
  uint32_t reverseBits(uint32_t n) {
    uint32_t res = 0;
    for (int i = 0; i < 32; ++i) {
      res = (res << 1) + (n & 1);
      n >>= 1;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The input must be a binary string of length |32|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 00000010100101000001111010011100
// Output: 964176192 (00111001011110000010100101000000)
//
// The input binary string 00000010100101000001111010011100 represents the
// unsigned integer 43261596, so return 964176192 which its binary
// representation is 00111001011110000010100101000000.

LEETCODE_SOLUTION_UNITTEST(190, ReverseBits, example_1) {
  auto     solution = MakeSolution();
  uint32_t n        = 0b00000010100101000001111010011100;
  uint32_t expect   = 964176192;
  uint32_t actual   = solution->reverseBits(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 11111111111111111111111111111101
// Output: 3221225471 (10111111111111111111111111111111)
//
// The input binary string 11111111111111111111111111111101 represents the
// unsigned integer 4294967293, so return 3221225471 which its binary
// representation is 10111111111111111111111111111111.

LEETCODE_SOLUTION_UNITTEST(190, ReverseBits, example_2) {
  auto     solution = MakeSolution();
  uint32_t n        = 0b11111111111111111111111111111101;
  uint32_t expect   = 3221225471;
  uint32_t actual   = solution->reverseBits(n);
  LCD_EXPECT_EQ(expect, actual);
}
