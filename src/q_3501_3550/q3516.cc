// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find Closest Person
//
// https://leetcode.com/problems/find-closest-person/
//
// Question ID: 3516
// Difficult  : Easy
// Solve Date : 2025/09/04 21:12

#include <cmath>
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3516. Find Closest Person|:
//
// You are given three integers |x|, |y|, and |z|, representing the positions of
// three people on a number line:
//
//  • |x| is the position of Person 1.
//
//  • |y| is the position of Person 2.
//
//  • |z| is the position of Person 3, who does not move.
// Both Person 1 and Person 2 move toward Person 3 at the same speed.
// Determine which person reaches Person 3 first:
//
//  • Return 1 if Person 1 arrives first.
//
//  • Return 2 if Person 2 arrives first.
//
//  • Return 0 if both arrive at the same time.
// Return the result accordingly.
//
//

LEETCODE_BEGIN_RESOLVING(3516, FindClosestPerson, Solution);

class Solution {
public:
  int findClosest(int x, int y, int z) {
    x -= z;
    x *= x;
    y -= z;
    y *= y;
    return x == y ? 0 : x > y ? 2 : 1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= x, y, z <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: x = 2, y = 7, z = 4
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3516, FindClosestPerson, example_1) {
  auto solution = MakeSolution();
  int  x        = 2;
  int  y        = 7;
  int  z        = 4;
  int  expect   = 1;
  int  actual   = solution->findClosest(x, y, z);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: x = 2, y = 5, z = 6
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3516, FindClosestPerson, example_2) {
  auto solution = MakeSolution();
  int  x        = 2;
  int  y        = 5;
  int  z        = 6;
  int  expect   = 2;
  int  actual   = solution->findClosest(x, y, z);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: x = 1, y = 5, z = 3
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3516, FindClosestPerson, example_3) {
  auto solution = MakeSolution();
  int  x        = 1;
  int  y        = 5;
  int  z        = 3;
  int  expect   = 0;
  int  actual   = solution->findClosest(x, y, z);
  LCD_EXPECT_EQ(expect, actual);
}
