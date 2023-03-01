// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Thousand Separator
//
// https://leetcode.com/problems/thousand-separator/
//
// Question ID: 1556
// Difficult  : Easy
// Solve Date : 2022/12/08 18:32

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1556. Thousand Separator|:
//
// Given an integer |n|, add a dot (".") as the thousands separator and return
// it in string format.
//

LEETCODE_BEGIN_RESOLVING(1556, ThousandSeparator, Solution);

class Solution {
public:
  string thousandSeparator(int n) {
    auto res   = string("");
    auto digit = (int)0;
    do {
      if (digit && (digit % 3) == 0) {
        res.push_back('.');
      }
      res.push_back('0' + (n % 10));
      n /= 10;
      ++digit;
    } while (n != 0);

    reverse(res.begin(), res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= n <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 987
// Output: "987"
//

LEETCODE_SOLUTION_UNITTEST(1556, ThousandSeparator, example_1) {
  auto   solution = MakeSolution();
  int    n        = 987;
  string expect   = "987";
  string actual   = solution->thousandSeparator(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1234
// Output: "1.234"
//

LEETCODE_SOLUTION_UNITTEST(1556, ThousandSeparator, example_2) {
  auto   solution = MakeSolution();
  int    n        = 1234;
  string expect   = "1.234";
  string actual   = solution->thousandSeparator(n);
  LCD_EXPECT_EQ(expect, actual);
}
