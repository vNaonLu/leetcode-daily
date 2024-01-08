// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Faulty Keyboard
//
// https://leetcode.com/problems/faulty-keyboard/
//
// Question ID: 2810
// Difficult  : Easy
// Solve Date : 2024/01/08 20:44

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2810. Faulty Keyboard|:
//
// Your laptop keyboard is faulty, and whenever you type a character |'i'| on
// it, it reverses the string that you have written. Typing other characters
// works as expected. You are given a 0-indexed string |s|, and you type each
// character of |s| using your faulty keyboard. Return the final string that
// will be present on your laptop screen.
//
//

LEETCODE_BEGIN_RESOLVING(2810, FaultyKeyboard, Solution);

class Solution {
public:
  string finalString(string s) {
    string res;
    for (auto c : s) {
      if (c != 'i') {
        res.push_back(c);
      } else {
        reverse(res.begin(), res.end());
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| consists of lowercase English letters.
// * |s[0] != 'i'|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "string"
// Output: "rtsng"
//
// After typing first character, the text on the screen is "s".
// After the second character, the text is "st".
// After the third character, the text is "str".
// Since the fourth character is an 'i', the text gets reversed and becomes
// "rts". After the fifth character, the text is "rtsn". After the sixth
// character, the text is "rtsng". Therefore, we return "rtsng".

LEETCODE_SOLUTION_UNITTEST(2810, FaultyKeyboard, example_1) {
  auto   solution = MakeSolution();
  string s        = "string";
  string expect   = "rtsng";
  string actual   = solution->finalString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "poiinter"
// Output: "ponter"
//
// After the first character, the text on the screen is "p".
// After the second character, the text is "po".
// Since the third character you type is an 'i', the text gets reversed and
// becomes "op". Since the fourth character you type is an 'i', the text gets
// reversed and becomes "po". After the fifth character, the text is "pon".
// After the sixth character, the text is "pont".
// After the seventh character, the text is "ponte".
// After the eighth character, the text is "ponter".
// Therefore, we return "ponter".

LEETCODE_SOLUTION_UNITTEST(2810, FaultyKeyboard, example_2) {
  auto   solution = MakeSolution();
  string s        = "poiinter";
  string expect   = "ponter";
  string actual   = solution->finalString(s);
  LCD_EXPECT_EQ(expect, actual);
}
