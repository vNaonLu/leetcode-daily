// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sum of Square Numbers
//
// https://leetcode.com/problems/sum-of-square-numbers/
//
// Question ID: 633
// Difficult  : Medium
// Solve Date : 2022/04/12 18:24

#include <cmath>
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |633. Sum of Square Numbers|:
//
// Given a non-negative integer |c|, decide whether there're two integers |a|
// and |b| such that |a² + b² = c|.  
//

LEETCODE_BEGIN_RESOLVING(633, SumOfSquareNumbers, Solution);

class Solution {
public:
  bool judgeSquareSum(int c) {
    long a = 0, b = sqrt(c);
    while (a <= b) {
      if (a * a + b * b == c)
        return true;
      else if (a * a + b * b < c)
        a++;
      else
        b--;
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= c <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: c = 5
// Output: true
//
// 1 * 1 + 2 * 2 = 5

LEETCODE_SOLUTION_UNITTEST(633, SumOfSquareNumbers, example_1) {
  auto solution = MakeSolution();
  int  c        = 5;
  bool expect   = true;
  bool actual   = solution->judgeSquareSum(c);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: c = 3
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(633, SumOfSquareNumbers, example_2) {
  auto solution = MakeSolution();
  int  c        = 3;
  bool expect   = false;
  bool actual   = solution->judgeSquareSum(c);
  LCD_EXPECT_EQ(expect, actual);
}
