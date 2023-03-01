// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Smallest Even Multiple
//
// https://leetcode.com/problems/smallest-even-multiple/
//
// Question ID: 2413
// Difficult  : Easy
// Solve Date : 2023/02/03 13:19

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2413. Smallest Even Multiple|:
//
// Given a positive integer |n|, return the smallest positive integer that is a
// multiple of both |2| and |n|.
//

LEETCODE_BEGIN_RESOLVING(2413, SmallestEvenMultiple, Solution);

class Solution {
public:
  int smallestEvenMultiple(int n) { return (n & 1) == 0 ? n : 2 * n; }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 150|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5
// Output: 10
//
// The smallest multiple of both 5 and 2 is 10.

LEETCODE_SOLUTION_UNITTEST(2413, SmallestEvenMultiple, example_1) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  expect   = 10;
  int  actual   = solution->smallestEvenMultiple(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 6
// Output: 6
//
// The smallest multiple of both 6 and 2 is 6. Note that a number is a multiple
// of itself.

LEETCODE_SOLUTION_UNITTEST(2413, SmallestEvenMultiple, example_2) {
  auto solution = MakeSolution();
  int  n        = 6;
  int  expect   = 6;
  int  actual   = solution->smallestEvenMultiple(n);
  LCD_EXPECT_EQ(expect, actual);
}
