// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Masking Personal Information
//
// https://leetcode.com/problems/masking-personal-information/
//
// Question ID: 831
// Difficult  : Medium
// Solve Date : 2024/08/21 21:27

#include <cctype>
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |831. Masking Personal Information|:
//
// You are given a personal information string |s|, representing either an email
// address or a phone number. Return the masked personal information using the
// below rules. Email address: An email address is:
//
//  • A name consisting of uppercase and lowercase English letters, followed by
//
//  • The |'@'| symbol, followed by
//
//  • The domain consisting of uppercase and lowercase English letters with a
//  dot |'.'| somewhere in the middle (not the first or last character).
// To mask an email:
//
//  • The uppercase letters in the name and domain must be converted to
//  lowercase letters.
//
//  • The middle letters of the name (i.e., all but the first and last letters)
//  must be replaced by 5 asterisks |"*****"|.
// Phone number:
// A phone number is formatted as follows:
//
//  • The phone number contains 10-13 digits.
//
//  • The last 10 digits make up the local number.
//
//  • The remaining 0-3 digits, in the beginning, make up the country code.
//
//  • Separation characters from the set |{'+', '-', '(', ')', ' '}| separate
//  the above digits in some way.
// To mask a phone number:
//
//  • Remove all separation characters.
//
//  • The masked phone number should have the form:
//
//
//    • |"***-***-XXXX"| if the country code has 0 digits.
//
//    • |"+*-***-***-XXXX"| if the country code has 1 digit.
//
//    • |"+**-***-***-XXXX"| if the country code has 2 digits.
//
//    • |"+***-***-***-XXXX"| if the country code has 3 digits.
//
//
//
//  • |"XXXX"| is the last 4 digits of the local number.
//
//

LEETCODE_BEGIN_RESOLVING(831, MaskingPersonalInformation, Solution);

class Solution {
public:
  string maskPII(string s) {
    for (auto &c : s) {
      c = tolower(c);
    }
    if (auto p = s.find('@'); p == string::npos) {
      return maskAsPhone(s);
    } else {
      return maskAsEmail(s, p);
    }
  }

private:
  string maskAsEmail(string const &s, size_t at_pos) {
    return s[0] + string(5, '*') + s.substr(at_pos - 1);
  }

  string maskAsPhone(string const &s) {
    string num;
    for (auto c : s) {
      if (isdigit(c)) {
        num += c;
      }
    }

    switch (num.size() - 10) {
    case 0:
      return string("***-***-") + num.substr(num.size() - 4);
    case 1:
      return string("+*-***-***-") + num.substr(num.size() - 4);
    case 2:
      return string("+**-***-***-") + num.substr(num.size() - 4);
    case 3:
      return string("+***-***-***-") + num.substr(num.size() - 4);
    default:
      return "";
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |s| is either a valid email or a phone number.
// * If |s| is an email:
// *| 8 <= s.length <= 40 |
// * |s| consists of uppercase and lowercase English letters and exactly one
// |'@'| symbol and |'.'| symbol.
// * If |s| is a phone number:
// * | 10 <= s.length <= 20 |
// * |s| consists of digits, spaces, and the symbols |'('|, |')'|, |'-'|,
// and |'+'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "LeetCode@LeetCode.com"
// Output: "l*****e@leetcode.com"
//

LEETCODE_SOLUTION_UNITTEST(831, MaskingPersonalInformation, example_1) {
  auto   solution = MakeSolution();
  string s        = "LeetCode@LeetCode.com";
  string expect   = "l*****e@leetcode.com";
  string actual   = solution->maskPII(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "AB@qq.com"
// Output: "a*****b@qq.com"
//

LEETCODE_SOLUTION_UNITTEST(831, MaskingPersonalInformation, example_2) {
  auto   solution = MakeSolution();
  string s        = "AB@qq.com";
  string expect   = "a*****b@qq.com";
  string actual   = solution->maskPII(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "1(234)567-890"
// Output: "***-***-7890"
//

LEETCODE_SOLUTION_UNITTEST(831, MaskingPersonalInformation, example_3) {
  auto   solution = MakeSolution();
  string s        = "1(234)567-890";
  string expect   = "***-***-7890";
  string actual   = solution->maskPII(s);
  LCD_EXPECT_EQ(expect, actual);
}
