// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Monotone Increasing Digits
//
// https://leetcode.com/problems/monotone-increasing-digits/
//
// Question ID: 738
// Difficult  : Medium
// Solve Date : 2024/06/12 14:30

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |738. Monotone Increasing Digits|:
//
// An integer has monotone increasing digits if and only if each pair of
// adjacent digits |x| and |y| satisfy |x <= y|. Given an integer |n|, return
// the largest number that is less than or equal to |n| with monotone increasing
// digits.
//
//

LEETCODE_BEGIN_RESOLVING(738, MonotoneIncreasingDigits, Solution);

class Solution {
public:
  int monotoneIncreasingDigits(int n) {
    while (!isMonotonic(n)) {
      n = n - (n % 10) - 1;
    }
    return n;
  }

private:
  bool isMonotonic(int n) {
    int k = 10;
    while (n > 0) {
      if (k < n % 10) {
        return false;
      } else {
        k = n % 10;
        n = n / 10;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |0 <= n <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 10
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(738, MonotoneIncreasingDigits, example_1) {
  auto solution = MakeSolution();
  int  n        = 10;
  int  expect   = 9;
  int  actual   = solution->monotoneIncreasingDigits(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1234
// Output: 1234
//

LEETCODE_SOLUTION_UNITTEST(738, MonotoneIncreasingDigits, example_2) {
  auto solution = MakeSolution();
  int  n        = 1234;
  int  expect   = 1234;
  int  actual   = solution->monotoneIncreasingDigits(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 332
// Output: 299
//

LEETCODE_SOLUTION_UNITTEST(738, MonotoneIncreasingDigits, example_3) {
  auto solution = MakeSolution();
  int  n        = 332;
  int  expect   = 299;
  int  actual   = solution->monotoneIncreasingDigits(n);
  LCD_EXPECT_EQ(expect, actual);
}
