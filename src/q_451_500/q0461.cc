// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Hamming Distance
//
// https://leetcode.com/problems/hamming-distance/
//
// Question ID: 461
// Difficult  : Easy
// Solve Date : 2021/11/19 22:39

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |461. Hamming Distance|:
//
// The [Hamming distance] between two integers is the number of positions at
// which the corresponding bits are different. Given two integers |x| and |y|,
// return the Hamming distance between them.  
//

LEETCODE_BEGIN_RESOLVING(461, HammingDistance, Solution);

class Solution {
public:
  int hammingDistance(int x, int y) { return __builtin_popcount(x ^ y); }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= x, y <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: x = 1, y = 4
// Output: 2
//
// 1 (0 0 0 1)
// 4 (0 1 0 0)
//  ↑ ↑
// The above arrows point to positions where the corresponding bits are
// different.

LEETCODE_SOLUTION_UNITTEST(461, HammingDistance, example_1) {
  auto solution = MakeSolution();
  int  x        = 1;
  int  y        = 4;
  int  expect   = 2;
  int  actual   = solution->hammingDistance(x, y);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: x = 3, y = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(461, HammingDistance, example_2) {
  auto solution = MakeSolution();
  int  x        = 3;
  int  y        = 1;
  int  expect   = 1;
  int  actual   = solution->hammingDistance(x, y);
  LCD_EXPECT_EQ(expect, actual);
}
