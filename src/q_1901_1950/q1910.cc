// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Remove All Occurrences of a Substring
//
// https://leetcode.com/problems/remove-all-occurrences-of-a-substring/
//
// Question ID: 1910
// Difficult  : Medium
// Solve Date : 2025/02/11 15:14

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1910. Remove All Occurrences of a Substring|:
//
// Given two strings |s| and |part|, perform the following operation on |s|
// until all occurrences of the substring |part| are removed:
//
//  • Find the leftmost occurrence of the substring |part| and remove it from
//  |s|.
// Return |s| after removing all occurrences of |part|.
// A substring is a contiguous sequence of characters in a string.
//
//

LEETCODE_BEGIN_RESOLVING(1910, RemoveAllOccurrencesOfASubstring, Solution);

class Solution {
public:
  string removeOccurrences(string s, string part) {
    for (auto p = s.find(part); p != string::npos; p = s.find(part)) {
      s = s.substr(0, p) + s.substr(p + part.size());
    }
    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 1000|
// * |1 <= part.length <= 1000|
// * |s|​​​​​​ and |part| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "daabcbaabcbc", part = "abc"
// Output: "dab"
//

LEETCODE_SOLUTION_UNITTEST(1910, RemoveAllOccurrencesOfASubstring, example_1) {
  auto   solution = MakeSolution();
  string s        = "daabcbaabcbc";
  string part     = "abc";
  string expect   = "dab";
  string actual   = solution->removeOccurrences(s, part);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "axxxxyyyyb", part = "xy"
// Output: "ab"
//

LEETCODE_SOLUTION_UNITTEST(1910, RemoveAllOccurrencesOfASubstring, example_2) {
  auto   solution = MakeSolution();
  string s        = "axxxxyyyyb";
  string part     = "xy";
  string expect   = "ab";
  string actual   = solution->removeOccurrences(s, part);
  LCD_EXPECT_EQ(expect, actual);
}
