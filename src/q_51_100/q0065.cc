// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Valid Number
//
// https://leetcode.com/problems/valid-number/
//
// Question ID: 65
// Difficult  : Hard
// Solve Date : 2022/02/18 23:49

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |65. Valid Number|:
//
// A valid number can be split up into these components (in order):
//
//  1. A decimal number or an integer.
//
//  2. (Optional) An |'e'| or |'E'|, followed by an integer.
// A decimal number can be split up into these components (in order):
//
//  1. (Optional) A sign character (either |'+'| or |'-'|).
//
//  2. One of the following formats:
//
//
//    1. One or more digits, followed by a dot |'.'|.
//
//    2. One or more digits, followed by a dot |'.'|, followed by one or more
//    digits.
//
//    3. A dot |'.'|, followed by one or more digits.
//
//
// An integer can be split up into these components (in order):
//
//  1. (Optional) A sign character (either |'+'| or |'-'|).
//
//  2. One or more digits.
// For example, all the following are valid numbers: |["2", "0089", "-0.1",
// "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93",
// "-123.456e789"]|, while the following are not valid numbers: |["abc", "1a",
// "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"]|. Given a string |s|, return
// |true| if |s| is a valid number.  
//

LEETCODE_BEGIN_RESOLVING(65, ValidNumber, Solution);

class Solution {
public:
  bool isNumber(string s) {
    int  i = 0, n = s.length();
    bool dot = false, exponent = true;
    // Decimal or Integer
    if (s[i] == '+' || s[i] == '-')
      ++i;
    while (i < n && s[i] >= '0' && s[i] <= '9')
      ++i, dot = true;
    if (i < n && s[i] == '.') {
      ++i;
      dot |= false;
      while (i < n && s[i] >= '0' && s[i] <= '9')
        ++i, dot = true;
    }
    if (!dot)
      return false;

    // Exponent with Integer
    if (i < n && (s[i] == 'e' || s[i] == 'E')) {
      ++i;
      exponent = false;
      if (s[i] == '+' || s[i] == '-')
        ++i;
      while (i < n && s[i] >= '0' && s[i] <= '9')
        ++i, exponent = true;
    }
    if (!exponent)
      return false;

    return i == n;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 20|
// * |s| consists of only English letters (both uppercase and lowercase), digits
// ( |0-9|), plus |'+'|, minus |'-'|, or dot |'.'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "0"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(65, ValidNumber, example_1) {
  auto   solution = MakeSolution();
  string s        = "0";
  bool   expect   = true;
  bool   actual   = solution->isNumber(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "e"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(65, ValidNumber, example_2) {
  auto   solution = MakeSolution();
  string s        = "e";
  bool   expect   = false;
  bool   actual   = solution->isNumber(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "."
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(65, ValidNumber, example_3) {
  auto   solution = MakeSolution();
  string s        = ".";
  bool   expect   = false;
  bool   actual   = solution->isNumber(s);
  LCD_EXPECT_EQ(expect, actual);
}
