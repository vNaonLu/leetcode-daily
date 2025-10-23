// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Check If Digits Are Equal in String After Operations I
//
// https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-i/
//
// Question ID: 3461
// Difficult  : Easy
// Solve Date : 2025/10/23 12:25

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3461. Check If Digits Are Equal in String After Operations
// I|:
//
// You are given a string |s| consisting of digits. Perform the following
// operation repeatedly until the string has exactly two digits:
//
//  • For each pair of consecutive digits in |s|, starting from the first digit,
//  calculate a new digit as the sum of the two digits modulo 10.
//
//  • Replace |s| with the sequence of newly calculated digits, maintaining the
//  order in which they are computed.
// Return |true| if the final two digits in |s| are the same; otherwise, return
// |false|.
//
//

LEETCODE_BEGIN_RESOLVING(3461, CheckIfDigitsAreEqualInStringAfterOperationsI,
                         Solution);

class Solution {
public:
  bool hasSameDigits(string s) {
    while (s.size() > 2) {
      string new_s;
      for (int i = 0; i < s.size() - 1; ++i) {
        new_s.push_back((s[i] + s[i + 1] - 2 * '0') % 10 + '0');
      }
      s = std::move(new_s);
    }

    return s[0] == s[1];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= s.length <= 100|
// * |s| consists of only digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "3902"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3461, CheckIfDigitsAreEqualInStringAfterOperationsI,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "3902";
  bool   expect   = true;
  bool   actual   = solution->hasSameDigits(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "34789"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3461, CheckIfDigitsAreEqualInStringAfterOperationsI,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "34789";
  bool   expect   = false;
  bool   actual   = solution->hasSameDigits(s);
  LCD_EXPECT_EQ(expect, actual);
}
