// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Concatenation of Consecutive Binary Numbers
//
// https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/
//
// Question ID: 1680
// Difficult  : Medium
// Solve Date : 2022/03/10 18:17

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1680. Concatenation of Consecutive Binary Numbers|:
//
// Given an integer |n|, return the decimal value of the binary string formed by
// concatenating the binary representations of |1| to |n| in order, modulo
// |10^{9 }+ 7|.  
//

LEETCODE_BEGIN_RESOLVING(1680, ConcatenationOfConsecutiveBinaryNumbers,
                         Solution);

class Solution {
private:
  inline constexpr static int kMod = 1e9 + 7;

public:
  int concatenatedBinary(int n) {
    unsigned long long res = 0;
    for (int i = 1; i <= n; ++i) {
      int j = i, cnt = 0;
      while (j != 0) {
        j >>= 1;
        ++cnt;
      }
      res <<= cnt;
      res %= kMod;
      res += i;
      res %= kMod;
    }
    return (int)res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1
// Output: 1
//
// "1" in binary corresponds to the decimal value 1.

LEETCODE_SOLUTION_UNITTEST(1680, ConcatenationOfConsecutiveBinaryNumbers,
                           example_1) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 1;
  int  actual   = solution->concatenatedBinary(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3
// Output: 27
//
// In binary, 1, 2, and 3 corresponds to "1", "10", and "11".
// After concatenating them, we have "11011", which corresponds to the decimal
// value 27.

LEETCODE_SOLUTION_UNITTEST(1680, ConcatenationOfConsecutiveBinaryNumbers,
                           example_2) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  expect   = 27;
  int  actual   = solution->concatenatedBinary(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 12
// Output: 505379714
//
// : The concatenation results in "1101110010111011110001001101010111100".
// The decimal value of that is 118505380540.
// After modulo 10⁹ + 7, the result is 505379714.

LEETCODE_SOLUTION_UNITTEST(1680, ConcatenationOfConsecutiveBinaryNumbers,
                           example_3) {
  auto solution = MakeSolution();
  int  n        = 12;
  int  expect   = 505379714;
  int  actual   = solution->concatenatedBinary(n);
  LCD_EXPECT_EQ(expect, actual);
}
