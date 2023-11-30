// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum One Bit Operations to Make Integers Zero
//
// https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/
//
// Question ID: 1611
// Difficult  : Hard
// Solve Date : 2023/11/30 20:32

#include <cmath>
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1611. Minimum One Bit Operations to Make Integers Zero|:
//
// Given an integer |n|, you must transform it into |0| using the following
// operations any number of times:
//
//  • Change the rightmost ( |0ᵗʰ|) bit in the binary representation of |n|.
//
//  • Change the |iᵗʰ| bit in the binary representation of |n| if the |(i-1)ᵗʰ|
//  bit is set to |1| and the |(i-2)ᵗʰ| through |0ᵗʰ| bits are set to |0|.
// Return the minimum number of operations to transform |n| into |0|.
//
//

LEETCODE_BEGIN_RESOLVING(1611, MinimumOneBitOperationsToMakeIntegersZero,
                         Solution);

class Solution {
public:
  int minimumOneBitOperations(int n) {
    if (n == 0) {
      return 0;
    }

    int k  = floor(log2(n));
    int op = (1 << (k + 1)) - 1;
    return op - minimumOneBitOperations(n ^ (1 << k));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |0 <= n <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3
// Output: 2
//
// The binary representation of 3 is "11".
// "11" -> "01" with the 2ⁿᵈ operation since the 0ᵗʰ bit is 1.
// "01" -> "00" with the 1ˢᵗ operation.

LEETCODE_SOLUTION_UNITTEST(1611, MinimumOneBitOperationsToMakeIntegersZero,
                           example_1) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  expect   = 2;
  int  actual   = solution->minimumOneBitOperations(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 6
// Output: 4
//
// The binary representation of 6 is "110".
// "110" -> "010" with the 2ⁿᵈ operation since the 1ˢᵗ bit is 1 and 0ᵗʰ through
// 0ᵗʰ bits are 0. "010" -> "011" with the 1ˢᵗ operation. "011" -> "001" with
// the 2ⁿᵈ operation since the 0ᵗʰ bit is 1. "001" -> "000" with the 1ˢᵗ
// operation.

LEETCODE_SOLUTION_UNITTEST(1611, MinimumOneBitOperationsToMakeIntegersZero,
                           example_2) {
  auto solution = MakeSolution();
  int  n        = 6;
  int  expect   = 4;
  int  actual   = solution->minimumOneBitOperations(n);
  LCD_EXPECT_EQ(expect, actual);
}
