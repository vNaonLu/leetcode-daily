// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Number of Steps to Make Two Strings Anagram
//
// https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram/
//
// Question ID: 1347
// Difficult  : Medium
// Solve Date : 2024/01/13 10:19

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1347. Minimum Number of Steps to Make Two Strings Anagram|:
//
// You are given two strings of the same length |s| and |t|. In one step you can
// choose any character of |t| and replace it with another character. Return the
// minimum number of steps to make |t| an anagram of |s|. An Anagram of a string
// is a string that contains the same characters with a different (or the same)
// ordering.
//
//

LEETCODE_BEGIN_RESOLVING(1347, MinimumNumberOfStepsToMakeTwoStringsAnagram,
                         Solution);

class Solution {
public:
  int minSteps(string s, string t) {
    vector<int> cs(26, 0);
    vector<int> ct(26, 0);

    for (auto x : s) {
      ++cs[x - 'a'];
    }

    for (auto x : t) {
      ++ct[x - 'a'];
    }

    int res = 0;
    for (int i = 0; i < 26; ++i) {
      res += abs(cs[i] - ct[i]);
    }
    return res / 2;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 5 * 10⁴|
// * |s.length == t.length|
// * |s| and |t| consist of lowercase English letters only.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "bab", t = "aba"
// Output: 1
//
// Replace the first 'a' in t with b, t = "bba" which is anagram of s.

LEETCODE_SOLUTION_UNITTEST(1347, MinimumNumberOfStepsToMakeTwoStringsAnagram,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "bab";
  string t        = "aba";
  int    expect   = 1;
  int    actual   = solution->minSteps(s, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "leetcode", t = "practice"
// Output: 5
//
// Replace 'p', 'r', 'a', 'i' and 'c' from t with proper characters to make t
// anagram of s.

LEETCODE_SOLUTION_UNITTEST(1347, MinimumNumberOfStepsToMakeTwoStringsAnagram,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "leetcode";
  string t        = "practice";
  int    expect   = 5;
  int    actual   = solution->minSteps(s, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "anagram", t = "mangaar"
// Output: 0
//
// "anagram" and "mangaar" are anagrams.

LEETCODE_SOLUTION_UNITTEST(1347, MinimumNumberOfStepsToMakeTwoStringsAnagram,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "anagram";
  string t        = "mangaar";
  int    expect   = 0;
  int    actual   = solution->minSteps(s, t);
  LCD_EXPECT_EQ(expect, actual);
}
