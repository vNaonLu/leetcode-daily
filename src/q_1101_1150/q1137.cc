// Copyright 2023 Naon Lu
//
// This file describes the solution of
// N-th Tribonacci Number
//
// https://leetcode.com/problems/n-th-tribonacci-number/
//
// Question ID: 1137
// Difficult  : Easy
// Solve Date : 2021/09/24 15:23

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1137. N-th Tribonacci Number|:
//
// The Tribonacci sequence Tₙ is defined as follows: 
//
// T₀ = 0, T₁ = 1, T₂ = 1, and Tₙ₊₃ = Tₙ + Tₙ₊₁ + Tₙ₊₂ for n >= 0.
//
// Given |n|, return the value of Tₙ.
//
//  
//

LEETCODE_BEGIN_RESOLVING(1137, NThTribonacciNumber, Solution);

class Solution {
public:
  int tribonacci(int n) {
    vector<int> res(n + 1, 1);
    res[0] = 0;
    for (int i = 3; i <= n; ++i)
      res[i] = res[i - 1] + res[i - 2] + res[i - 3];
    return res.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= n <= 37|
// * The answer is guaranteed to fit within a 32-bit integer, ie. |answer <=
// 2^31 - 1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4
// Output: 4
//
// T_3 = 0 + 1 + 1 = 2
// T_4 = 1 + 1 + 2 = 4

LEETCODE_SOLUTION_UNITTEST(1137, NThTribonacciNumber, example_1) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  expect   = 4;
  int  actual   = solution->tribonacci(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 25
// Output: 1389537
//

LEETCODE_SOLUTION_UNITTEST(1137, NThTribonacciNumber, example_2) {
  auto solution = MakeSolution();
  int  n        = 25;
  int  expect   = 1389537;
  int  actual   = solution->tribonacci(n);
  LCD_EXPECT_EQ(expect, actual);
}
