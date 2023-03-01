// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Gap
//
// https://leetcode.com/problems/binary-gap/
//
// Question ID: 868
// Difficult  : Easy
// Solve Date : 2022/10/05 10:43

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |868. Binary Gap|:
//
// Given a positive integer |n|, find and return the longest distance between
// any two adjacent |1|'s in the binary representation of |n|. If there are no
// two adjacent |1|'s, return |0|. Two |1|'s are adjacent if there are only
// |0|'s separating them (possibly no |0|'s). The distance between two |1|'s is
// the absolute difference between their bit positions. For example, the two
// |1|'s in |"1001"| have a distance of 3.
//

LEETCODE_BEGIN_RESOLVING(868, BinaryGap, Solution);

class Solution {
public:
  int binaryGap(int n) {
    while (n != 0 && ((n & 1) == 0)) {
      n >>= 1;
    }
    auto gap = (int)0;
    auto res = (int)0;
    while (n != 0) {
      if (n & 1) {
        res = max(res, gap);
        gap = 0;
      }
      ++gap;
      n >>= 1;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 22
// Output: 2
//
// 22 in binary is "10110".
// The first adjacent pair of 1's is "10110" with a distance of 2.
// The second adjacent pair of 1's is "10110" with a distance of 1.
// The answer is the largest of these two distances, which is 2.
// Note that "10110" is not a valid pair since there is a 1 separating the two
// 1's underlined.

LEETCODE_SOLUTION_UNITTEST(868, BinaryGap, example_1) {
  auto solution = MakeSolution();
  int  n        = 22;
  int  expect   = 2;
  int  actual   = solution->binaryGap(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 8
// Output: 0
//
// 8 in binary is "1000".
// There are not any adjacent pairs of 1's in the binary representation of 8, so
// we return 0.

LEETCODE_SOLUTION_UNITTEST(868, BinaryGap, example_2) {
  auto solution = MakeSolution();
  int  n        = 8;
  int  expect   = 0;
  int  actual   = solution->binaryGap(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 5
// Output: 2
//
// 5 in binary is "101".

LEETCODE_SOLUTION_UNITTEST(868, BinaryGap, example_3) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  expect   = 2;
  int  actual   = solution->binaryGap(n);
  LCD_EXPECT_EQ(expect, actual);
}
