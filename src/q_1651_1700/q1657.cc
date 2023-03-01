// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Determine if Two Strings Are Close
//
// https://leetcode.com/problems/determine-if-two-strings-are-close/
//
// Question ID: 1657
// Difficult  : Medium
// Solve Date : 2022/12/02 18:06

#include <algorithm>
#include <iosfwd>
#include <set>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1657. Determine if Two Strings Are Close|:
//
// Two strings are considered close if you can attain one from the other using
// the following operations:
//
//  • Operation 1: Swap any two existing characters.
//
//
//    • For example, |abcde -> aecdb|
//
//
//
//  • Operation 2: Transform every occurrence of one existing character into
//  another existing character, and do the same with the other character.
//
//
//    • For example, |aacabb -> bbcbaa| (all |a|'s turn into |b|'s, and all
//    |b|'s turn into |a|'s)
//
//
// You can use the operations on either string as many times as necessary.
// Given two strings, |word1| and |word2|, return |true| if |word1| and |word2|
// are close, and |false| otherwise.
//

LEETCODE_BEGIN_RESOLVING(1657, DetermineIfTwoStringsAreClose, Solution);

class Solution {
public:
  bool closeStrings(string word1, string word2) {
    if (word1.size() != word2.size()) {
      return false;
    }
    if (set(word1.begin(), word1.end()) != set(word2.begin(), word2.end())) {
      return false;
    }

    auto n     = word1.size();
    auto freq1 = vector<int>(26, 0);
    auto freq2 = vector<int>(26, 0);
    for (int i = 0; i < n; ++i) {
      ++freq1[word1[i] - 'a'];
      ++freq2[word2[i] - 'a'];
    }
    sort(freq1.rbegin(), freq1.rend());
    sort(freq2.rbegin(), freq2.rend());
    for (int i = 0; i < 26; ++i) {
      if (freq1[i] != freq2[i]) {
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
// * |1 <= word1.length, word2.length <= 10⁵|
// * |word1| and |word2| contain only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word1 = "abc", word2 = "bca"
// Output: true
//
// You can attain word2 from word1 in 2 operations.
// Apply Operation 1: "abc" -> "acb"
// Apply Operation 1: "acb" -> "bca"

LEETCODE_SOLUTION_UNITTEST(1657, DetermineIfTwoStringsAreClose, example_1) {
  auto   solution = MakeSolution();
  string word1    = "abc";
  string word2    = "bca";
  bool   expect   = true;
  bool   actual   = solution->closeStrings(word1, word2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word1 = "a", word2 = "aa"
// Output: false
//
// It is impossible to attain word2 from word1, or vice versa, in any number of
// operations.

LEETCODE_SOLUTION_UNITTEST(1657, DetermineIfTwoStringsAreClose, example_2) {
  auto   solution = MakeSolution();
  string word1    = "a";
  string word2    = "aa";
  bool   expect   = false;
  bool   actual   = solution->closeStrings(word1, word2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: word1 = "cabbba", word2 = "abbccc"
// Output: true
//
// You can attain word2 from word1 in 3 operations.
// Apply Operation 1: "cabbba" -> "caabbb"
// |Apply Operation 2: "|caabbb" -> "baaccc"
// Apply Operation 2: "baaccc" -> "abbccc"

LEETCODE_SOLUTION_UNITTEST(1657, DetermineIfTwoStringsAreClose, example_3) {
  auto   solution = MakeSolution();
  string word1    = "cabbba";
  string word2    = "abbccc";
  bool   expect   = true;
  bool   actual   = solution->closeStrings(word1, word2);
  LCD_EXPECT_EQ(expect, actual);
}
