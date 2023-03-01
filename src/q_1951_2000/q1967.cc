// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Strings That Appear as Substrings in Word
//
// https://leetcode.com/problems/number-of-strings-that-appear-as-substrings-in-word/
//
// Question ID: 1967
// Difficult  : Easy
// Solve Date : 2022/07/11 18:42

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1967. Number of Strings That Appear as Substrings in Word|:
//
// Given an array of strings |patterns| and a string |word|, return the number
// of strings in |patterns| that exist as a substring in |word|. A substring is
// a contiguous sequence of characters within a string.
//

LEETCODE_BEGIN_RESOLVING(1967, NumberOfStringsThatAppearAsSubstringsInWord,
                         Solution);

class Solution {
public:
  int numOfStrings(vector<string> &patterns, string word) {
    int res = 0;
    for (auto &v : patterns) {
      if (word.find(v) != string::npos) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= patterns.length <= 100|
// * |1 <= patterns[i].length <= 100|
// * |1 <= word.length <= 100|
// * |patterns[i]| and |word| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: patterns = ["a","abc","bc","d"], word = "abc"
// Output: 3
//
// - "a" appears as a substring in "abc".
// - "abc" appears as a substring in "abc".
// - "bc" appears as a substring in "abc".
// - "d" does not appear as a substring in "abc".
// 3 of the strings in patterns appear as a substring in word.

LEETCODE_SOLUTION_UNITTEST(1967, NumberOfStringsThatAppearAsSubstringsInWord,
                           example_1) {
  auto           solution = MakeSolution();
  vector<string> patterns = {"a", "abc", "bc", "d"};
  string         word     = "abc";
  int            expect   = 3;
  int            actual   = solution->numOfStrings(patterns, word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: patterns = ["a","b","c"], word = "aaaaabbbbb"
// Output: 2
//
// - "a" appears as a substring in "aaaaabbbbb".
// - "b" appears as a substring in "aaaaabbbbb".
// - "c" does not appear as a substring in "aaaaabbbbb".
// 2 of the strings in patterns appear as a substring in word.

LEETCODE_SOLUTION_UNITTEST(1967, NumberOfStringsThatAppearAsSubstringsInWord,
                           example_2) {
  auto           solution = MakeSolution();
  vector<string> patterns = {"a", "b", "c"};
  string         word     = "aaaaabbbbb";
  int            expect   = 2;
  int            actual   = solution->numOfStrings(patterns, word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: patterns = ["a","a","a"], word = "ab"
// Output: 3
//
// Each of the patterns appears as a substring in word "ab".

LEETCODE_SOLUTION_UNITTEST(1967, NumberOfStringsThatAppearAsSubstringsInWord,
                           example_3) {
  auto           solution = MakeSolution();
  vector<string> patterns = {"a", "a", "a"};
  string         word     = "ab";
  int            expect   = 3;
  int            actual   = solution->numOfStrings(patterns, word);
  LCD_EXPECT_EQ(expect, actual);
}
