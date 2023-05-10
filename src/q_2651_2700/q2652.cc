// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sum Multiples
//
// https://leetcode.com/problems/sum-multiples/
//
// Question ID: 2652
// Difficult  : Easy
// Solve Date : 2023/05/10 18:46

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2652. Sum Multiples|:
//
// Given a positive integer |n|, find the sum of all integers in the range |[1,
// n]| inclusive that are divisible by |3|, |5|, or |7|. Return an integer
// denoting the sum of all numbers in the given range satisfying the constraint.
//
//

LEETCODE_BEGIN_RESOLVING(2652, SumMultiples, Solution);

class Solution {
public:
  int sumOfMultiples(int n) {
    int res = 0;
    for (int i = 1; i <= n; ++i) {
      if (i % 3 == 0 || i % 5 == 0 || i % 7 == 0) {
        res += i;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10³|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 7
// Output: 21
//
// Numbers in the range |[1, 7]| that are divisible by |3|, |5,| or |7 |are |3,
// 5, 6, 7|. The sum of these numbers is |21|.

LEETCODE_SOLUTION_UNITTEST(2652, SumMultiples, example_1) {
  auto solution = MakeSolution();
  int  n        = 7;
  int  expect   = 21;
  int  actual   = solution->sumOfMultiples(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 10
// Output: 40
//
// Numbers in the range |[1, 10] that are| divisible by |3|, |5,| or |7| are |3,
// 5, 6, 7, 9, 10|. The sum of these numbers is 40.

LEETCODE_SOLUTION_UNITTEST(2652, SumMultiples, example_2) {
  auto solution = MakeSolution();
  int  n        = 10;
  int  expect   = 40;
  int  actual   = solution->sumOfMultiples(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 9
// Output: 30
//
// Numbers in the range |[1, 9]| that are divisible by |3|, |5|, or |7| are |3,
// 5, 6, 7, 9|. The sum of these numbers is |30|.

LEETCODE_SOLUTION_UNITTEST(2652, SumMultiples, example_3) {
  auto solution = MakeSolution();
  int  n        = 9;
  int  expect   = 30;
  int  actual   = solution->sumOfMultiples(n);
  LCD_EXPECT_EQ(expect, actual);
}
