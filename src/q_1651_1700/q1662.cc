// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check If Two String Arrays are Equivalent
//
// https://leetcode.com/problems/check-if-two-string-arrays-are-equivalent/
//
// Question ID: 1662
// Difficult  : Easy
// Solve Date : 2022/10/25 10:52

#include <array>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1662. Check If Two String Arrays are Equivalent|:
//
// Given two string arrays |word1| and |word2|, return |true| if the two arrays
// represent the same string, and |false| otherwise. A string is represented by
// an array if the array elements concatenated in order forms the string.
//

LEETCODE_BEGIN_RESOLVING(1662, CheckIfTwoStringArraysAreEquivalent, Solution);

class Solution {
public:
  bool arrayStringsAreEqual(vector<string> &word1, vector<string> &word2) {
    auto s1 = string("");
    auto s2 = string("");
    for (auto &s : word1) {
      s1 += move(s);
    }
    for (auto &s : word2) {
      s2 += move(s);
    }
    return s1 == s2;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= word1.length, word2.length <= 10³|
// * |1 <= word1[i].length, word2[i].length <= 10³|
// * |1 <= sum(word1[i].length), sum(word2[i].length) <= 10³|
// * |word1[i]| and |word2[i]| consist of lowercase letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word1 = ["ab", "c"], word2 = ["a", "bc"]
// Output: true
//
// word1 represents string "ab" + "c" -> "abc"
// word2 represents string "a" + "bc" -> "abc"
// The strings are the same, so return true.

LEETCODE_SOLUTION_UNITTEST(1662, CheckIfTwoStringArraysAreEquivalent,
                           example_1) {
  auto           solution = MakeSolution();
  vector<string> word1    = {"ab", "c"};
  vector<string> word2    = {"a", "bc"};
  bool           expect   = true;
  bool           actual   = solution->arrayStringsAreEqual(word1, word2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word1 = ["a", "cb"], word2 = ["ab", "c"]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1662, CheckIfTwoStringArraysAreEquivalent,
                           example_2) {
  auto           solution = MakeSolution();
  vector<string> word1    = {"a", "cb"};
  vector<string> word2    = {"ab", "c"};
  bool           expect   = false;
  bool           actual   = solution->arrayStringsAreEqual(word1, word2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: word1 = ["abc", "d", "defg"], word2 = ["abcddefg"]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1662, CheckIfTwoStringArraysAreEquivalent,
                           example_3) {
  auto           solution = MakeSolution();
  vector<string> word1    = {"abc", "d", "defg"};
  vector<string> word2    = {"abcddefg"};
  bool           expect   = true;
  bool           actual   = solution->arrayStringsAreEqual(word1, word2);
  LCD_EXPECT_EQ(expect, actual);
}
