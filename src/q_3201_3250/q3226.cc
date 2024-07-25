// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Number of Bit Changes to Make Two Integers Equal
//
// https://leetcode.com/problems/number-of-bit-changes-to-make-two-integers-equal/
//
// Question ID: 3226
// Difficult  : Easy
// Solve Date : 2024/07/25 16:02

#include <bitset>
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3226. Number of Bit Changes to Make Two Integers Equal|:
//
// You are given two positive integers |n| and |k|.
// You can choose any bit in the binary representation of |n| that is equal to 1
// and change it to 0. Return the number of changes needed to make |n| equal to
// |k|. If it is impossible, return -1.
//
//

LEETCODE_BEGIN_RESOLVING(3226, NumberOfBitChangesToMakeTwoIntegersEqual,
                         Solution);

class Solution {
public:
  int minChanges(int n, int k) {
    return ((n & k) < k) ? -1 : bitset<20>(n ^ k).count();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n, k <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 13, k = 4
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3226, NumberOfBitChangesToMakeTwoIntegersEqual,
                           example_1) {
  auto solution = MakeSolution();
  int  n        = 13;
  int  k        = 4;
  int  expect   = 2;
  int  actual   = solution->minChanges(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 21, k = 21
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3226, NumberOfBitChangesToMakeTwoIntegersEqual,
                           example_2) {
  auto solution = MakeSolution();
  int  n        = 21;
  int  k        = 21;
  int  expect   = 0;
  int  actual   = solution->minChanges(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 14, k = 13
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(3226, NumberOfBitChangesToMakeTwoIntegersEqual,
                           example_3) {
  auto solution = MakeSolution();
  int  n        = 14;
  int  k        = 13;
  int  expect   = -1;
  int  actual   = solution->minChanges(n, k);
  LCD_EXPECT_EQ(expect, actual);
}
