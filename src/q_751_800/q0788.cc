// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Rotated Digits
//
// https://leetcode.com/problems/rotated-digits/
//
// Question ID: 788
// Difficult  : Medium
// Solve Date : 2024/07/03 19:57

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |788. Rotated Digits|:
//
// An integer |x| is a good if after rotating each digit individually by 180
// degrees, we get a valid number that is different from |x|. Each digit must be
// rotated - we cannot choose to leave it alone. A number is valid if each digit
// remains a digit after rotation. For example:
//
//  • |0|, |1|, and |8| rotate to themselves,
//
//  • |2| and |5| rotate to each other (in this case they are rotated in a
//  different direction, in other words, |2| or |5| gets mirrored),
//
//  • |6| and |9| rotate to each other, and
//
//  • the rest of the numbers do not rotate to any other number and become
//  invalid.
// Given an integer |n|, return the number of good integers in the range |[1,
// n]|.
//
//

LEETCODE_BEGIN_RESOLVING(788, RotatedDigits, Solution);

class Solution {
public:
  int rotatedDigits(int n) {
    const int kR[] = {1, 1, 2, 0, 0, 2, 2, 0, 1, 2};
    int       res  = 0;
    for (int i = 1; i <= n; ++i) {
      int p = i;
      int s = 1;
      while (p) {
        s *= kR[p % 10];
        p /= 10;
      }
      if (s >= 2) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 10
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(788, RotatedDigits, example_1) {
  auto solution = MakeSolution();
  int  n        = 10;
  int  expect   = 4;
  int  actual   = solution->rotatedDigits(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(788, RotatedDigits, example_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 0;
  int  actual   = solution->rotatedDigits(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 2
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(788, RotatedDigits, example_3) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  expect   = 1;
  int  actual   = solution->rotatedDigits(n);
  LCD_EXPECT_EQ(expect, actual);
}
