// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Number of Homogenous Substrings
//
// https://leetcode.com/problems/count-number-of-homogenous-substrings/
//
// Question ID: 1759
// Difficult  : Medium
// Solve Date : 2023/11/09 20:31

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1759. Count Number of Homogenous Substrings|:
//
// Given a string |s|, return the number of homogenous substrings of |s|. Since
// the answer may be too large, return it modulo |10⁹ + 7|.
//
// A string is homogenous if all the characters of the string are the same.
//
// A substring is a contiguous sequence of characters within a string.
//
//
//

LEETCODE_BEGIN_RESOLVING(1759, CountNumberOfHomogenousSubstrings, Solution);

class Solution {
public:
  int countHomogenous(string s) {
    int  res = 0;
    auto b   = s.begin();
    auto it  = b + 1;
    while (b != s.end()) {
      if (it == s.end() || *it != *b) {
        res = (res + (1 + distance(b, it)) * distance(b, it) / 2) % kMod;
        b   = it;
      }
      ++it;
    }
    return res;
  }

private:
  static constexpr int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists of lowercase letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abbcccaa"
// Output: 13
//
// The homogenous substrings are listed as below:
// "a" appears 3 times.
// "aa" appears 1 time.
// "b" appears 2 times.
// "bb" appears 1 time.
// "c" appears 3 times.
// "cc" appears 2 times.
// "ccc" appears 1 time.
// 3 + 1 + 2 + 1 + 3 + 2 + 1 = 13.

LEETCODE_SOLUTION_UNITTEST(1759, CountNumberOfHomogenousSubstrings, example_1) {
  auto   solution = MakeSolution();
  string s        = "abbcccaa";
  int    expect   = 13;
  int    actual   = solution->countHomogenous(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "xy"
// Output: 2
//
// The homogenous substrings are "x" and "y".

LEETCODE_SOLUTION_UNITTEST(1759, CountNumberOfHomogenousSubstrings, example_2) {
  auto   solution = MakeSolution();
  string s        = "xy";
  int    expect   = 2;
  int    actual   = solution->countHomogenous(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "zzzzz"
// Output: 15
//

LEETCODE_SOLUTION_UNITTEST(1759, CountNumberOfHomogenousSubstrings, example_3) {
  auto   solution = MakeSolution();
  string s        = "zzzzz";
  int    expect   = 15;
  int    actual   = solution->countHomogenous(s);
  LCD_EXPECT_EQ(expect, actual);
}
