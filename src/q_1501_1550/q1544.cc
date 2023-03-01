// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Make The String Great
//
// https://leetcode.com/problems/make-the-string-great/
//
// Question ID: 1544
// Difficult  : Easy
// Solve Date : 2022/11/08 18:21

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1544. Make The String Great|:
//
// Given a string |s| of lower and upper case English letters.
// A good string is a string which doesn't have two adjacent characters |s[i]|
// and |s[i + 1]| where:
//
//  • |0 <= i <= s.length - 2|
//
//  • |s[i]| is a lower-case letter and |s[i + 1]| is the same letter but in
//  upper-case or vice-versa.
// To make the string good, you can choose two adjacent characters that make the
// string bad and remove them. You can keep doing this until the string becomes
// good. Return the string after making it good. The answer is guaranteed to be
// unique under the given constraints. Notice that an empty string is also good.
//

LEETCODE_BEGIN_RESOLVING(1544, MakeTheStringGreat, Solution);

class Solution {
public:
  string makeGood(string s) {
    auto res = string();
    res.reserve(s.size());
    for (auto c : s) {
      if (res.empty()) {
        res.push_back(c);
      } else {
        auto prev = res.back();
        if ((c >= 'a' && c <= 'z' && prev >= 'A' && prev <= 'Z' &&
             prev - 'A' == c - 'a') ||
            (c >= 'A' && c <= 'Z' && prev >= 'a' && prev <= 'z' &&
             prev - 'a' == c - 'A')) {
          res.pop_back();
        } else {
          res.push_back(c);
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
// * |1 <= s.length <= 100|
// * |s| contains only lower and upper case English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "leEeetcode"
// Output: "leetcode"
//
// In the first step, either you choose i = 1 or i = 2, both will result
// "leEeetcode" to be reduced to "leetcode".

LEETCODE_SOLUTION_UNITTEST(1544, MakeTheStringGreat, example_1) {
  auto   solution = MakeSolution();
  string s        = "leEeetcode";
  string expect   = "leetcode";
  string actual   = solution->makeGood(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abBAcC"
// Output: ""
//
// We have many possible scenarios, and all lead to the same answer. For
// example: "abBAcC" --> "aAcC" --> "cC" --> "" "abBAcC" --> "abBA" --> "aA" -->
// ""

LEETCODE_SOLUTION_UNITTEST(1544, MakeTheStringGreat, example_2) {
  auto   solution = MakeSolution();
  string s        = "abBAcC";
  string expect   = "";
  string actual   = solution->makeGood(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "s"
// Output: "s"
//

LEETCODE_SOLUTION_UNITTEST(1544, MakeTheStringGreat, example_3) {
  auto   solution = MakeSolution();
  string s        = "s";
  string expect   = "s";
  string actual   = solution->makeGood(s);
  LCD_EXPECT_EQ(expect, actual);
}
