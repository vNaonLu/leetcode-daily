// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Second Largest Digit in a String
//
// https://leetcode.com/problems/second-largest-digit-in-a-string/
//
// Question ID: 1796
// Difficult  : Easy
// Solve Date : 2023/03/19 14:49

#include <cctype>
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1796. Second Largest Digit in a String|:
//
// Given an alphanumeric string |s|, return the second largest numerical digit
// that appears in |s|, or |-1| if it does not exist. An alphanumeric string is
// a string consisting of lowercase English letters and digits.
//
//

LEETCODE_BEGIN_RESOLVING(1796, SecondLargestDigitInAString, Solution);

class Solution {
public:
  int secondHighest(string s) {
    int res      = -1;
    int greatest = -1;
    for (auto c : s) {
      if (isdigit(c)) {
        int n = c - '0';
        if (n > greatest) {
          res      = greatest;
          greatest = n;
        } else if (greatest != n) {
          res = max(res, n);
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 500|
// * |s| consists of only lowercase English letters and/or digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "dfa12321afd"
// Output: 2
//
// The digits that appear in s are [1, 2, 3]. The second largest digit is 2.

LEETCODE_SOLUTION_UNITTEST(1796, SecondLargestDigitInAString, example_1) {
  auto   solution = MakeSolution();
  string s        = "dfa12321afd";
  int    expect   = 2;
  int    actual   = solution->secondHighest(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abc1111"
// Output: -1
//
// The digits that appear in s are [1]. There is no second largest digit.

LEETCODE_SOLUTION_UNITTEST(1796, SecondLargestDigitInAString, example_2) {
  auto   solution = MakeSolution();
  string s        = "abc1111";
  int    expect   = -1;
  int    actual   = solution->secondHighest(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "sjhtz8344"
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(1796, SecondLargestDigitInAString,
                           extra_testcase_1) {
  auto   solution = MakeSolution();
  string s        = "sjhtz8344";
  int    expect   = 4;
  int    actual   = solution->secondHighest(s);
  LCD_EXPECT_EQ(expect, actual);
}
