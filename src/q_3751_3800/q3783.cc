// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Mirror Distance of an Integer
//
// https://leetcode.com/problems/mirror-distance-of-an-integer/
//
// Question ID: 3783
// Difficult  : Easy
// Solve Date : 2026/04/18 20:06

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3783. Mirror Distance of an Integer|:
//
// You are given an integer |n|.
// Define its mirror distance as: |abs(n - reverse(n))|​​​​​​​
// where |reverse(n)| is the integer formed by reversing the digits of |n|.
// Return an integer denoting the mirror distance of |n|​​​​​​​.
// |abs(x)| denotes the absolute value of |x|.
//
//

LEETCODE_BEGIN_RESOLVING(3783, MirrorDistanceOfAnInteger, Solution);

class Solution {
public:
  int mirrorDistance(int n) {
    int x   = n;
    int rev = 0;
    while (x > 0) {
      rev = rev * 10 + (x % 10);
      x /= 10;
    }
    return abs(n - rev);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 25
// Output: 27
//

LEETCODE_SOLUTION_UNITTEST(3783, MirrorDistanceOfAnInteger, example_1) {
  auto solution = MakeSolution();
  int  n        = 25;
  int  expect   = 27;
  int  actual   = solution->mirrorDistance(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 10
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(3783, MirrorDistanceOfAnInteger, example_2) {
  auto solution = MakeSolution();
  int  n        = 10;
  int  expect   = 9;
  int  actual   = solution->mirrorDistance(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 7
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3783, MirrorDistanceOfAnInteger, example_3) {
  auto solution = MakeSolution();
  int  n        = 7;
  int  expect   = 0;
  int  actual   = solution->mirrorDistance(n);
  LCD_EXPECT_EQ(expect, actual);
}
