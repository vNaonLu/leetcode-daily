// Copyright 2023 Naon Lu
//
// This file describes the solution of
// To Lower Case
//
// https://leetcode.com/problems/to-lower-case/
//
// Question ID: 709
// Difficult  : Easy
// Solve Date : 2022/04/22 08:49

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |709. To Lower Case|:
//
// Given a string |s|, return the string after replacing every uppercase letter
// with the same lowercase letter.  
//

LEETCODE_BEGIN_RESOLVING(709, ToLowerCase, Solution);

class Solution {
public:
  string toLowerCase(string s) {
    string res = s;
    for (auto &c : res) {
      if (c >= 'A' && c <= 'Z') {
        c = 'a' + c - 'A';
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| consists of printable ASCII characters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "Hello"
// Output: "hello"
//

LEETCODE_SOLUTION_UNITTEST(709, ToLowerCase, example_1) {
  auto   solution = MakeSolution();
  string s        = "Hello";
  string expect   = "hello";
  string actual   = solution->toLowerCase(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "here"
// Output: "here"
//

LEETCODE_SOLUTION_UNITTEST(709, ToLowerCase, example_2) {
  auto   solution = MakeSolution();
  string s        = "here";
  string expect   = "here";
  string actual   = solution->toLowerCase(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "LOVELY"
// Output: "lovely"
//

LEETCODE_SOLUTION_UNITTEST(709, ToLowerCase, example_3) {
  auto   solution = MakeSolution();
  string s        = "LOVELY";
  string expect   = "lovely";
  string actual   = solution->toLowerCase(s);
  LCD_EXPECT_EQ(expect, actual);
}
