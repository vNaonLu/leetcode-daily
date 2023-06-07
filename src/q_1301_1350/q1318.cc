// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Flips to Make a OR b Equal to c
//
// https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/
//
// Question ID: 1318
// Difficult  : Medium
// Solve Date : 2023/06/07 18:43

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1318. Minimum Flips to Make a OR b Equal to c|:
//
// Given 3 positives numbers |a|, |b| and |c|. Return the minimum flips required
// in some bits of |a| and |b| to make ( |a| OR |b| == |c| ). (bitwise OR
// operation). Flip operation consists of change any single bit 1 to 0 or change
// the bit 0 to 1 in their binary representation.
//
//
//

LEETCODE_BEGIN_RESOLVING(1318, MinimumFlipsToMakeAORBEqualToC, Solution);

class Solution {
public:
  int minFlips(int a, int b, int c) {
    int res = 0;
    while (a > 0 || b > 0 || c > 0) {
      if ((c & 1) != ((a & 1) | (b & 1))) {
        if (c & 1) {
          ++res;
        } else {
          res += (a & 1) + (b & 1);
        }
      }
      a >>= 1;
      b >>= 1;
      c >>= 1;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= a <= 10^9|
// * |1 <= b <= 10^9|
// * |1 <= c <= 10^9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: a = 2, b = 6, c = 5
// Output: 3
//
// After flips a = 1 , b = 4 , c = 5 such that ( |a| OR |b| == |c|)

LEETCODE_SOLUTION_UNITTEST(1318, MinimumFlipsToMakeAORBEqualToC, example_1) {
  auto solution = MakeSolution();
  int  a        = 2;
  int  b        = 6;
  int  c        = 5;
  int  expect   = 3;
  int  actual   = solution->minFlips(a, b, c);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: a = 4, b = 2, c = 7
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1318, MinimumFlipsToMakeAORBEqualToC, example_2) {
  auto solution = MakeSolution();
  int  a        = 4;
  int  b        = 2;
  int  c        = 7;
  int  expect   = 1;
  int  actual   = solution->minFlips(a, b, c);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: a = 1, b = 2, c = 3
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1318, MinimumFlipsToMakeAORBEqualToC, example_3) {
  auto solution = MakeSolution();
  int  a        = 1;
  int  b        = 2;
  int  c        = 3;
  int  expect   = 0;
  int  actual   = solution->minFlips(a, b, c);
  LCD_EXPECT_EQ(expect, actual);
}
