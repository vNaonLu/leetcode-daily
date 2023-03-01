// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check if All Characters Have Equal Number of Occurrences
//
// https://leetcode.com/problems/check-if-all-characters-have-equal-number-of-occurrences/
//
// Question ID: 1941
// Difficult  : Easy
// Solve Date : 2023/01/02 14:54

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1941. Check if All Characters Have Equal Number of
// Occurrences|:
//
// Given a string |s|, return |true| if |s| is a good string, or |false|
// otherwise. A string |s| is good if all the characters that appear in |s| have
// the same number of occurrences (i.e., the same frequency).
//

LEETCODE_BEGIN_RESOLVING(1941, CheckIfAllCharactersHaveEqualNumberOfOccurrences,
                         Solution);

class Solution {
public:
  bool areOccurrencesEqual(string s) {
    unordered_map<char, int> freq;
    for (auto c : s) {
      ++freq[c];
    }
    auto cnt = freq.begin()->second;
    for (auto &[x, c] : freq) {
      if (cnt != c) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 1000|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abacbc"
// Output: true
//
// The characters that appear in s are 'a', 'b', and 'c'. All characters occur 2
// times in s.

LEETCODE_SOLUTION_UNITTEST(1941,
                           CheckIfAllCharactersHaveEqualNumberOfOccurrences,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "abacbc";
  bool   expect   = true;
  bool   actual   = solution->areOccurrencesEqual(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aaabb"
// Output: false
//
// The characters that appear in s are 'a' and 'b'.
// 'a' occurs 3 times while 'b' occurs 2 times, which is not the same number of
// times.

LEETCODE_SOLUTION_UNITTEST(1941,
                           CheckIfAllCharactersHaveEqualNumberOfOccurrences,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "aaabb";
  bool   expect   = false;
  bool   actual   = solution->areOccurrencesEqual(s);
  LCD_EXPECT_EQ(expect, actual);
}
