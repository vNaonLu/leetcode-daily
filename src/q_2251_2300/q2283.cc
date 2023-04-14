// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check if Number Has Equal Digit Count and Digit Value
//
// https://leetcode.com/problems/check-if-number-has-equal-digit-count-and-digit-value/
//
// Question ID: 2283
// Difficult  : Easy
// Solve Date : 2023/04/14 14:35

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2283. Check if Number Has Equal Digit Count and Digit Value|:
//
// You are given a 0-indexed string |num| of length |n| consisting of digits.
// Return |true| if for every index |i| in the range |0 <= i < n|, the digit |i|
// occurs |num[i]| times in |num|, otherwise return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(2283, CheckIfNumberHasEqualDigitCountAndDigitValue,
                         Solution);

class Solution {
public:
  bool digitCount(string num) {
    vector<int> count(num.size(), 0);
    vector<int> value;
    for (auto c : num) {
      if (c - '0' < count.size()) {
        ++count[c - '0'];
      }
      value.emplace_back(c - '0');
    }
    return count == value;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == num.length|
// * |1 <= n <= 10|
// * |num| consists of digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = "1210"
// Output: true
//
// num[0] = '1'. The digit 0 occurs once in num.
// num[1] = '2'. The digit 1 occurs twice in num.
// num[2] = '1'. The digit 2 occurs once in num.
// num[3] = '0'. The digit 3 occurs zero times in num.
// The condition holds true for every index in "1210", so return true.

LEETCODE_SOLUTION_UNITTEST(2283, CheckIfNumberHasEqualDigitCountAndDigitValue,
                           example_1) {
  auto   solution = MakeSolution();
  string num      = "1210";
  bool   expect   = true;
  bool   actual   = solution->digitCount(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = "030"
// Output: false
//
// num[0] = '0'. The digit 0 should occur zero times, but actually occurs twice
// in num. num[1] = '3'. The digit 1 should occur three times, but actually
// occurs zero times in num. num[2] = '0'. The digit 2 occurs zero times in num.
// The indices 0 and 1 both violate the condition, so return false.

LEETCODE_SOLUTION_UNITTEST(2283, CheckIfNumberHasEqualDigitCountAndDigitValue,
                           example_2) {
  auto   solution = MakeSolution();
  string num      = "030";
  bool   expect   = false;
  bool   actual   = solution->digitCount(num);
  LCD_EXPECT_EQ(expect, actual);
}
