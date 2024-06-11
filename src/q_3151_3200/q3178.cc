// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the Child Who Has the Ball After K Seconds
//
// https://leetcode.com/problems/find-the-child-who-has-the-ball-after-k-seconds/
//
// Question ID: 3178
// Difficult  : Easy
// Solve Date : 2024/06/11 20:22

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3178. Find the Child Who Has the Ball After K Seconds|:
//
// You are given two positive integers |n| and |k|. There are |n| children
// numbered from |0| to |n - 1| standing in a queue in order from left to right.
// Initially, child 0 holds a ball and the direction of passing the ball is
// towards the right direction. After each second, the child holding the ball
// passes it to the child next to them. Once the ball reaches either end of the
// line, i.e. child 0 or child |n - 1|, the direction of passing is reversed.
// Return the number of the child who receives the ball after |k| seconds.
//
//

LEETCODE_BEGIN_RESOLVING(3178, FindTheChildWhoHasTheBallAfterKSeconds,
                         Solution);

class Solution {
public:
  int numberOfChild(int n, int k) {
    --n;
    int rounds = k / n;
    int rem    = k % n;
    return rounds % 2 == 0 ? rem : (n - rem);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 50|
// * |1 <= k <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, k = 5
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3178, FindTheChildWhoHasTheBallAfterKSeconds,
                           example_1) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  k        = 5;
  int  expect   = 1;
  int  actual   = solution->numberOfChild(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5, k = 6
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3178, FindTheChildWhoHasTheBallAfterKSeconds,
                           example_2) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  k        = 6;
  int  expect   = 2;
  int  actual   = solution->numberOfChild(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 4, k = 2
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3178, FindTheChildWhoHasTheBallAfterKSeconds,
                           example_3) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  k        = 2;
  int  expect   = 2;
  int  actual   = solution->numberOfChild(n, k);
  LCD_EXPECT_EQ(expect, actual);
}
