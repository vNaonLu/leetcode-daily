// Copyright 2023 Naon Lu
//
// This file describes the solution of
// XOR Operation in an Array
//
// https://leetcode.com/problems/xor-operation-in-an-array/
//
// Question ID: 1486
// Difficult  : Easy
// Solve Date : 2022/12/06 18:51

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1486. XOR Operation in an Array|:
//
// You are given an integer |n| and an integer |start|.
// Define an array |nums| where |nums[i] = start + 2 * i| (0-indexed) and |n ==
// nums.length|. Return the bitwise XOR of all elements of |nums|.
//

LEETCODE_BEGIN_RESOLVING(1486, XOROperationInAnArray, Solution);

class Solution {
public:
  int xorOperation(int n, int start) {
    auto res = 0;
    while (n--) {
      res ^= start;
      start += 2;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 1000|
// * |0 <= start <= 1000|
// * |n == nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, start = 0
// Output: 8
//
// Array nums is equal to [0, 2, 4, 6, 8] where (0 ^ 2 ^ 4 ^ 6 ^ 8) = 8.
// Where "^" corresponds to bitwise XOR operator.

LEETCODE_SOLUTION_UNITTEST(1486, XOROperationInAnArray, example_1) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  start    = 0;
  int  expect   = 8;
  int  actual   = solution->xorOperation(n, start);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, start = 3
// Output: 8
//
// Array nums is equal to [3, 5, 7, 9] where (3 ^ 5 ^ 7 ^ 9) = 8.

LEETCODE_SOLUTION_UNITTEST(1486, XOROperationInAnArray, example_2) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  start    = 3;
  int  expect   = 8;
  int  actual   = solution->xorOperation(n, start);
  LCD_EXPECT_EQ(expect, actual);
}
