// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Climbing Stairs
//
// https://leetcode.com/problems/climbing-stairs/
//
// Question ID: 70
// Difficult  : Easy
// Solve Date : 2021/09/16 08:00

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |70. Climbing Stairs|:
//
// You are climbing a staircase. It takes |n| steps to reach the top.
// Each time you can either climb |1| or |2| steps. In how many distinct ways
// can you climb to the top?  
//

LEETCODE_BEGIN_RESOLVING(70, ClimbingStairs, Solution);

class Solution {
public:
  int climbStairs(int n) {
    int first = 0, second = 1, res;
    for (int i = 0; i < n; ++i) {
      res    = first + second;
      first  = second;
      second = res;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 45|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2
// Output: 2
//
// There are two ways to climb to the top.
// 1. 1 step + 1 step
// 2. 2 steps

LEETCODE_SOLUTION_UNITTEST(70, ClimbingStairs, example_1) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  expect   = 2;
  int  actual   = solution->climbStairs(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3
// Output: 3
//
// There are three ways to climb to the top.
// 1. 1 step + 1 step + 1 step
// 2. 1 step + 2 steps
// 3. 2 steps + 1 step

LEETCODE_SOLUTION_UNITTEST(70, ClimbingStairs, example_2) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  expect   = 3;
  int  actual   = solution->climbStairs(n);
  LCD_EXPECT_EQ(expect, actual);
}
