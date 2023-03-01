// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Backspace String Compare
//
// https://leetcode.com/problems/backspace-string-compare/
//
// Question ID: 844
// Difficult  : Easy
// Solve Date : 2021/09/22 08:00

#include <iosfwd>
#include <stack>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |844. Backspace String Compare|:
//
// Given two strings |s| and |t|, return |true| if they are equal when both are
// typed into empty text editors. |'#'| means a backspace character. Note that
// after backspacing an empty text, the text will continue empty.  
//

LEETCODE_BEGIN_RESOLVING(844, BackspaceStringCompare, Solution);

class Solution {
private:
  template <typename Iterator>
  stack<char> solve(Iterator beg, Iterator end) {
    auto res = stack<char>();
    while (beg != end) {
      if (*beg == '#') {
        if (!res.empty()) {
          res.pop();
        }
      } else {
        res.emplace(*beg);
      }
      ++beg;
    }
    return res;
  }

public:
  bool backspaceCompare(string s, string t) {
    return solve(s.begin(), s.end()) == solve(t.begin(), t.end());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length, t.length <= 200|
// * |s| and |t| only contain lowercase letters and |'#'| characters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "ab#c", t = "ad#c"
// Output: true
//
// Both s and t become "ac".

LEETCODE_SOLUTION_UNITTEST(844, BackspaceStringCompare, example_1) {
  auto   solution = MakeSolution();
  string s        = "ab#c";
  string t        = "ad#c";
  bool   expect   = true;
  bool   actual   = solution->backspaceCompare(s, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "ab##", t = "c#d#"
// Output: true
//
// Both s and t become "".

LEETCODE_SOLUTION_UNITTEST(844, BackspaceStringCompare, example_2) {
  auto   solution = MakeSolution();
  string s        = "ab##";
  string t        = "c#d#";
  bool   expect   = true;
  bool   actual   = solution->backspaceCompare(s, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "a#c", t = "b"
// Output: false
//
// s becomes "c" while t becomes "b".

LEETCODE_SOLUTION_UNITTEST(844, BackspaceStringCompare, example_3) {
  auto   solution = MakeSolution();
  string s        = "a#c";
  string t        = "b";
  bool   expect   = false;
  bool   actual   = solution->backspaceCompare(s, t);
  LCD_EXPECT_EQ(expect, actual);
}
