// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Number with Alternating Bits
//
// https://leetcode.com/problems/binary-number-with-alternating-bits/
//
// Question ID: 693
// Difficult  : Easy
// Solve Date : 2021/10/06 00:46

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |693. Binary Number with Alternating Bits|:
//
// Given a positive integer, check whether it has alternating bits: namely, if
// two adjacent bits will always have different values.  
//

LEETCODE_BEGIN_RESOLVING(693, BinaryNumberWithAlternatingBits, Solution);

class Solution {
public:
  bool hasAlternatingBits(int n) {
    bool prev = n & 1;
    n >>= 1;
    while (n != 0) {
      bool current = n & 1;
      if (prev == current)
        return false;
      prev = current;
      n >>= 1;
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5
// Output: true
//
// The binary representation of 5 is: 101

LEETCODE_SOLUTION_UNITTEST(693, BinaryNumberWithAlternatingBits, example_1) {
  auto solution = MakeSolution();
  int  n        = 5;
  bool expect   = true;
  bool actual   = solution->hasAlternatingBits(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 7
// Output: false
//
// The binary representation of 7 is: 111.

LEETCODE_SOLUTION_UNITTEST(693, BinaryNumberWithAlternatingBits, example_2) {
  auto solution = MakeSolution();
  int  n        = 7;
  bool expect   = false;
  bool actual   = solution->hasAlternatingBits(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 11
// Output: false
//
// The binary representation of 11 is: 1011.

LEETCODE_SOLUTION_UNITTEST(693, BinaryNumberWithAlternatingBits, example_3) {
  auto solution = MakeSolution();
  int  n        = 11;
  bool expect   = false;
  bool actual   = solution->hasAlternatingBits(n);
  LCD_EXPECT_EQ(expect, actual);
}
