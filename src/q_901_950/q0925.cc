// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Long Pressed Name
//
// https://leetcode.com/problems/long-pressed-name/
//
// Question ID: 925
// Difficult  : Easy
// Solve Date : 2022/11/03 23:25

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |925. Long Pressed Name|:
//
// Your friend is typing his |name| into a keyboard. Sometimes, when typing a
// character |c|, the key might get long pressed, and the character will be
// typed 1 or more times. You examine the |typed| characters of the keyboard.
// Return |True| if it is possible that it was your friends name, with some
// characters (possibly none) being long pressed.
//

LEETCODE_BEGIN_RESOLVING(925, LongPressedName, Solution);

class Solution {
public:
  bool isLongPressedName(string name, string typed) {
    if (name.size() > typed.size()) {
      return false;
    }

    auto nbeg = name.begin();
    auto tbeg = typed.begin();
    while (nbeg != name.end() || tbeg != typed.end()) {
      auto x = *nbeg++;
      if (tbeg == typed.end() || x != *tbeg) {
        return false;
      }
      ++tbeg;
      if (tbeg != typed.end() && *nbeg != *tbeg) {
        while (tbeg != typed.end() && *tbeg == x) {
          ++tbeg;
        }
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= name.length, typed.length <= 1000|
// * |name| and |typed| consist of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: name = "alex", typed = "aaleex"
// Output: true
//
// 'a' and 'e' in 'alex' were long pressed.

LEETCODE_SOLUTION_UNITTEST(925, LongPressedName, example_1) {
  auto   solution = MakeSolution();
  string name     = "alex";
  string typed    = "aaleex";
  bool   expect   = true;
  bool   actual   = solution->isLongPressedName(name, typed);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: name = "saeed", typed = "ssaaedd"
// Output: false
//
// 'e' must have been pressed twice, but it was not in the typed output.

LEETCODE_SOLUTION_UNITTEST(925, LongPressedName, example_2) {
  auto   solution = MakeSolution();
  string name     = "saeed";
  string typed    = "ssaaedd";
  bool   expect   = false;
  bool   actual   = solution->isLongPressedName(name, typed);
  LCD_EXPECT_EQ(expect, actual);
}
