// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Valid Word
//
// https://leetcode.com/problems/valid-word/
//
// Question ID: 3136
// Difficult  : Easy
// Solve Date : 2024/05/12 14:19

#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3136. Valid Word|:
//
// A word is considered valid if:
//
//  • It contains a minimum of 3 characters.
//
//  • It contains only digits (0-9), and English letters (uppercase and
//  lowercase).
//
//  • It includes at least one vowel.
//
//  • It includes at least one consonant.
// You are given a string |word|.
// Return |true| if |word| is valid, otherwise, return |false|.
// Notes:
//
//  • |'a'|, |'e'|, |'i'|, |'o'|, |'u'|, and their uppercases are vowels.
//
//  • A consonant is an English letter that is not a vowel.
//
//

LEETCODE_BEGIN_RESOLVING(3136, ValidWord, Solution);

class Solution {
public:
  bool isValid(string word) {
    int vowel     = 0;
    int consonant = 0;
    if (word.size() < 3) {
      return false;
    }

    for (auto c : word) {
      switch (c) {
      case 'A':
      case 'a':
      case 'e':
      case 'E':
      case 'i':
      case 'I':
      case 'o':
      case 'O':
      case 'u':
      case 'U':
        vowel++;
        break;
      default:
        if (!(c >= '0' && c <= '9')) {
          consonant++;
        }
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
              (c >= '0' && c <= '9'))) {
          return false;
        }
      };
    }
    return vowel > 0 && consonant > 0;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= word.length <= 20|
// * |word| consists of English uppercase and lowercase letters, digits, |'@'|,
// |'#'|, and |'$'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word = "234Adas"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3136, ValidWord, example_1) {
  auto   solution = MakeSolution();
  string word     = "234Adas";
  bool   expect   = true;
  bool   actual   = solution->isValid(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word = "b3"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3136, ValidWord, example_2) {
  auto   solution = MakeSolution();
  string word     = "b3";
  bool   expect   = false;
  bool   actual   = solution->isValid(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: word = "a3$e"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3136, ValidWord, example_3) {
  auto   solution = MakeSolution();
  string word     = "a3$e";
  bool   expect   = false;
  bool   actual   = solution->isValid(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "UuE6"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3136, ValidWord, extra_testcase_1) {
  auto   solution = MakeSolution();
  string word     = "UuE6";
  bool   expect   = false;
  bool   actual   = solution->isValid(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: "IMG"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3136, ValidWord, extra_testcase_2) {
  auto   solution = MakeSolution();
  string word     = "IMG";
  bool   expect   = true;
  bool   actual   = solution->isValid(word);
  LCD_EXPECT_EQ(expect, actual);
}
