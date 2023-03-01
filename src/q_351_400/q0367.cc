// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Valid Perfect Square
//
// https://leetcode.com/problems/valid-perfect-square/
//
// Question ID: 367
// Difficult  : Easy
// Solve Date : 2022/04/06 18:53

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |367. Valid Perfect Square|:
//
// Given a positive integer num, return |true| if |num| is a perfect square or
// |false| otherwise. A perfect square is an integer that is the square of an
// integer. In other words, it is the product of some integer with itself. You
// must not use any built-in library function, such as |sqrt|.  
//

LEETCODE_BEGIN_RESOLVING(367, ValidPerfectSquare, Solution);

class Solution {
public:
  bool isPerfectSquare(int num) {
    unsigned long long l = 1, r = num;
    while (l <= r) {
      unsigned long long m = l + (r - l) / 2;
      if (m * m == num) {
        return true;
      } else if (m * m < num) {
        l = m + 1;
      } else {
        r = m - 1;
      }
    }

    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= num <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 16
// Output: true
//
// We return true because 4 * 4 = 16 and 4 is an integer.

LEETCODE_SOLUTION_UNITTEST(367, ValidPerfectSquare, example_1) {
  auto solution = MakeSolution();
  int  num      = 16;
  bool expect   = true;
  bool actual   = solution->isPerfectSquare(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 14
// Output: false
//
// We return false because 3.742 * 3.742 = 14 and 3.742 is not an integer.

LEETCODE_SOLUTION_UNITTEST(367, ValidPerfectSquare, example_2) {
  auto solution = MakeSolution();
  int  num      = 14;
  bool expect   = false;
  bool actual   = solution->isPerfectSquare(num);
  LCD_EXPECT_EQ(expect, actual);
}
