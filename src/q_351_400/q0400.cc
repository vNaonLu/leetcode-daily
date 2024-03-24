// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Nth Digit
//
// https://leetcode.com/problems/nth-digit/
//
// Question ID: 400
// Difficult  : Medium
// Solve Date : 2024/03/24 12:58

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |400. Nth Digit|:
//
// Given an integer |n|, return the |nᵗʰ| digit of the infinite integer sequence
// |[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...]|.
//
//

LEETCODE_BEGIN_RESOLVING(400, NthDigit, Solution);

class Solution {
public:
  int findNthDigit(int n) {
    int64_t d      = 9;
    int     first  = 1;
    int     length = 1;
    while (n > d * length) {
      n = n - d * length;
      ++length;
      first = first * 10;
      d     = d * 10;
    }
    first = first + (n - 1) / length;
    return to_string(first)[(n - 1) % length] - '0';
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(400, NthDigit, example_1) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  expect   = 3;
  int  actual   = solution->findNthDigit(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 11
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(400, NthDigit, example_2) {
  auto solution = MakeSolution();
  int  n        = 11;
  int  expect   = 0;
  int  actual   = solution->findNthDigit(n);
  LCD_EXPECT_EQ(expect, actual);
}
