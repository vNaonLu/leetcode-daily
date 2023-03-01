// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Bitwise AND of Numbers Range
//
// https://leetcode.com/problems/bitwise-and-of-numbers-range/
//
// Question ID: 201
// Difficult  : Medium
// Solve Date : 2021/10/06 00:41

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |201. Bitwise AND of Numbers Range|:
//
// Given two integers |left| and |right| that represent the range |[left,
// right]|, return the bitwise AND of all numbers in this range, inclusive.  
//

LEETCODE_BEGIN_RESOLVING(201, BitwiseANDOfNumbersRange, Solution);

class Solution {
public:
  int rangeBitwiseAnd(int left, int right) {
    int cnt = 0;
    while (left != 0 && right != 0) {
      if (left == right)
        return left << cnt;
      left >>= 1;
      right >>= 1;
      ++cnt;
    }
    return 0;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= left <= right <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: left = 5, right = 7
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(201, BitwiseANDOfNumbersRange, example_1) {
  auto solution = MakeSolution();
  int  left     = 5;
  int  right    = 7;
  int  expect   = 4;
  int  actual   = solution->rangeBitwiseAnd(left, right);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: left = 0, right = 0
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(201, BitwiseANDOfNumbersRange, example_2) {
  auto solution = MakeSolution();
  int  left     = 0;
  int  right    = 0;
  int  expect   = 0;
  int  actual   = solution->rangeBitwiseAnd(left, right);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: left = 1, right = 2147483647
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(201, BitwiseANDOfNumbersRange, example_3) {
  auto solution = MakeSolution();
  int  left     = 1;
  int  right    = 2147483647;
  int  expect   = 0;
  int  actual   = solution->rangeBitwiseAnd(left, right);
  LCD_EXPECT_EQ(expect, actual);
}
