// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Check if Strings Can be Made Equal With Operations I
//
// https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-i/
//
// Question ID: 2839
// Difficult  : Easy
// Solve Date : 2024/01/15 18:50

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2839. Check if Strings Can be Made Equal With Operations I|:
//
// You are given two strings |s1| and |s2|, both of length |4|, consisting of
// lowercase English letters. You can apply the following operation on any of
// the two strings any number of times:
//
//  • Choose any two indices |i| and |j| such that |j - i = 2|, then swap the
//  two characters at those indices in the string.
// Return |true| if you can make the strings |s1| and |s2| equal, and |false|
// otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(2839, CheckIfStringsCanBeMadeEqualWithOperationsI,
                         Solution);

class Solution {
public:
  bool canBeEqual(string s1, string s2) {
    if (s1 == s2) {
      return true;
    }

    if (s1[0] != s2[0]) {
      swap(s1[0], s1[2]);
    }

    if (s1 == s2) {
      return true;
    }

    if (s1[1] != s2[1]) {
      swap(s1[1], s1[3]);
    }
    return s1 == s2;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |s1.length == s2.length == 4|
// * |s1| and |s2| consist only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s1 = "abcd", s2 = "cdab"
// Output: true
//
// We can do the following operations on s1:
// - Choose the indices i = 0, j = 2. The resulting string is s1 = "cbad".
// - Choose the indices i = 1, j = 3. The resulting string is s1 = "cdab" = s2.

LEETCODE_SOLUTION_UNITTEST(2839, CheckIfStringsCanBeMadeEqualWithOperationsI,
                           example_1) {
  auto   solution = MakeSolution();
  string s1       = "abcd";
  string s2       = "cdab";
  bool   expect   = true;
  bool   actual   = solution->canBeEqual(s1, s2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s1 = "abcd", s2 = "dacb"
// Output: false
//
// It is not possible to make the two strings equal.

LEETCODE_SOLUTION_UNITTEST(2839, CheckIfStringsCanBeMadeEqualWithOperationsI,
                           example_2) {
  auto   solution = MakeSolution();
  string s1       = "abcd";
  string s2       = "dacb";
  bool   expect   = false;
  bool   actual   = solution->canBeEqual(s1, s2);
  LCD_EXPECT_EQ(expect, actual);
}
