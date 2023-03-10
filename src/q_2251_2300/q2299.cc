// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Strong Password Checker II
//
// https://leetcode.com/problems/strong-password-checker-ii/
//
// Question ID: 2299
// Difficult  : Easy
// Solve Date : 2023/03/11 00:55

#include <iosfwd>
#include <string>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2299. Strong Password Checker II|:
//
// A password is said to be strong if it satisfies all the following criteria:
//
//  • It has at least |8| characters.
//
//  • It contains at least one lowercase letter.
//
//  • It contains at least one uppercase letter.
//
//  • It contains at least one digit.
//
//  • It contains at least one special character. The special characters are the
//  characters in the following string: |"!@#$%^&*()-+"|.
//
//  • It does not contain |2| of the same character in adjacent positions (i.e.,
//  |"aab"| violates this condition, but |"aba"| does not).
// Given a string |password|, return |true| if it is a strong password.
// Otherwise, return |false|.
//

LEETCODE_BEGIN_RESOLVING(2299, StrongPasswordCheckerII, Solution);

class Solution {
private:
  inline const static unordered_set<char> kSpecialChar = {
      '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+'};

public:
  bool strongPasswordCheckerII(string password) {
    if (password.size() < 8) {
      return false;
    }
    bool has_upper   = false;
    bool has_lower   = false;
    bool has_digit   = false;
    bool has_special = false;
    for (int i = 0; i < password.size(); ++i) {
      auto curr = password[i];
      if ('A' <= curr && curr <= 'Z') {
        has_upper = true;
      } else if ('a' <= curr && curr <= 'z') {
        has_lower = true;
      } else if ('0' <= curr && curr <= '9') {
        has_digit = true;
      } else if (kSpecialChar.count(curr)) {
        has_special = true;
      }
      if (i > 0 && password[i - 1] == curr) {
        return false;
      }
    }
    return has_upper && has_lower && has_digit && has_special;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= password.length <= 100|
// * |password| consists of letters, digits, and special characters:
// |"!@#$%^&*()-+"|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: password = "IloveLe3tcode!"
// Output: true
//
// The password meets all the requirements. Therefore, we return true.

LEETCODE_SOLUTION_UNITTEST(2299, StrongPasswordCheckerII, example_1) {
  auto   solution = MakeSolution();
  string password = "IloveLe3tcode!";
  bool   expect   = true;
  bool   actual   = solution->strongPasswordCheckerII(password);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: password = "Me+You--IsMyDream"
// Output: false
//
// The password does not contain a digit and also contains 2 of the same
// character in adjacent positions. Therefore, we return false.

LEETCODE_SOLUTION_UNITTEST(2299, StrongPasswordCheckerII, example_2) {
  auto   solution = MakeSolution();
  string password = "Me+You--IsMyDream";
  bool   expect   = false;
  bool   actual   = solution->strongPasswordCheckerII(password);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: password = "1aB!"
// Output: false
//
// The password does not meet the length requirement. Therefore, we return
// false.

LEETCODE_SOLUTION_UNITTEST(2299, StrongPasswordCheckerII, example_3) {
  auto   solution = MakeSolution();
  string password = "1aB!";
  bool   expect   = false;
  bool   actual   = solution->strongPasswordCheckerII(password);
  LCD_EXPECT_EQ(expect, actual);
}
