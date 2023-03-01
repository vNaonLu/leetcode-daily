// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Fraction to Recurring Decimal
//
// https://leetcode.com/problems/fraction-to-recurring-decimal/
//
// Question ID: 166
// Difficult  : Medium
// Solve Date : 2022/08/22 00:04

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |166. Fraction to Recurring Decimal|:
//
// Given two integers representing the |numerator| and |denominator| of a
// fraction, return the fraction in string format. If the fractional part is
// repeating, enclose the repeating part in parentheses. If multiple answers are
// possible, return any of them. It is guaranteed that the length of the answer
// string is less than |10⁴| for all the given inputs.
//

LEETCODE_BEGIN_RESOLVING(166, FractionToRecurringDecimal, Solution);

class Solution {
public:
  string fractionToDecimal(int numerator, int denominator) {
    auto mp  = unordered_map<int64_t, int>();
    auto res = string("");
    auto num = int64_t(abs(numerator));
    auto den = int64_t(abs(denominator));

    if ((numerator < 0) ^ (denominator < 0 && numerator != 0)) {
      res.push_back('-');
    }

    res += to_string(num / den);

    if (num % den != 0) {
      res.push_back('.');
    }

    while (num % den != 0) {
      num       = (num % den);
      auto find = mp.find(num);
      if (find != mp.end()) {
        res.push_back(')');
        res.insert(find->second, "(");
        break;
      } else {
        mp[num] = res.size();
        num *= 10;
        res += to_string(num / den);
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |-2³¹ <=numerator, denominator <= 2³¹ - 1|
// * |denominator != 0|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: numerator = 1, denominator = 2
// Output: "0.5"
//

LEETCODE_SOLUTION_UNITTEST(166, FractionToRecurringDecimal, example_1) {
  auto   solution    = MakeSolution();
  int    numerator   = 1;
  int    denominator = 2;
  string expect      = "0.5";
  string actual      = solution->fractionToDecimal(numerator, denominator);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: numerator = 2, denominator = 1
// Output: "2"
//

LEETCODE_SOLUTION_UNITTEST(166, FractionToRecurringDecimal, example_2) {
  auto   solution    = MakeSolution();
  int    numerator   = 2;
  int    denominator = 1;
  string expect      = "2";
  string actual      = solution->fractionToDecimal(numerator, denominator);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: numerator = 4, denominator = 333
// Output: "0.(012)"
//

LEETCODE_SOLUTION_UNITTEST(166, FractionToRecurringDecimal, example_3) {
  auto   solution    = MakeSolution();
  int    numerator   = 4;
  int    denominator = 333;
  string expect      = "0.(012)";
  string actual      = solution->fractionToDecimal(numerator, denominator);
  LCD_EXPECT_EQ(expect, actual);
}
