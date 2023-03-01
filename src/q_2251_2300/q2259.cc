// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove Digit From Number to Maximize Result
//
// https://leetcode.com/problems/remove-digit-from-number-to-maximize-result/
//
// Question ID: 2259
// Difficult  : Easy
// Solve Date : 2023/02/24 15:26

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2259. Remove Digit From Number to Maximize Result|:
//
// You are given a string |number| representing a positive integer and a
// character |digit|. Return the resulting string after removing exactly one
// occurrence of |digit| from |number| such that the value of the resulting
// string in decimal form is maximized. The test cases are generated such that
// |digit| occurs at least once in |number|.
//

LEETCODE_BEGIN_RESOLVING(2259, RemoveDigitFromNumberToMaximizeResult, Solution);

class Solution {
public:
  string removeDigit(string number, char digit) {
    auto beg   = number.begin();
    auto slice = beg;
    while (beg != number.end()) {
      if (*beg == digit) {
        slice = beg;
        if (beg + 1 == number.end() || digit < *(beg + 1)) {
          break;
        }
      }
      ++beg;
    }
    number.erase(slice);
    return number;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= number.length <= 100|
// * |number| consists of digits from |'1'| to |'9'|.
// * |digit| is a digit from |'1'| to |'9'|.
// * |digit| occurs at least once in |number|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: number = "123", digit = "3"
// Output: "12"
//
// There is only one '3' in "123". After removing '3', the result is "12".

LEETCODE_SOLUTION_UNITTEST(2259, RemoveDigitFromNumberToMaximizeResult,
                           example_1) {
  auto   solution = MakeSolution();
  string number   = "123";
  char   digit    = '3';
  string expect   = "12";
  string actual   = solution->removeDigit(number, digit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: number = "1231", digit = "1"
// Output: "231"
//
// We can remove the first '1' to get "231" or remove the second '1' to get
// "123". Since 231 > 123, we return "231".

LEETCODE_SOLUTION_UNITTEST(2259, RemoveDigitFromNumberToMaximizeResult,
                           example_2) {
  auto   solution = MakeSolution();
  string number   = "1231";
  char   digit    = '1';
  string expect   = "231";
  string actual   = solution->removeDigit(number, digit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: number = "551", digit = "5"
// Output: "51"
//
// We can remove either the first or second '5' from "551".
// Both result in the string "51".

LEETCODE_SOLUTION_UNITTEST(2259, RemoveDigitFromNumberToMaximizeResult,
                           example_3) {
  auto   solution = MakeSolution();
  string number   = "551";
  char   digit    = '5';
  string expect   = "51";
  string actual   = solution->removeDigit(number, digit);
  LCD_EXPECT_EQ(expect, actual);
}
