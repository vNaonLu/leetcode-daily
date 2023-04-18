// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Vowel Substrings of a String
//
// https://leetcode.com/problems/count-vowel-substrings-of-a-string/
//
// Question ID: 2062
// Difficult  : Easy
// Solve Date : 2023/04/13 18:51

#include <iosfwd>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2062. Count Vowel Substrings of a String|:
//
// A substring is a contiguous (non-empty) sequence of characters within a
// string. A vowel substring is a substring that only consists of vowels (
// |'a'|, |'e'|, |'i'|, |'o'|, and |'u'|) and has all five vowels present in it.
// Given a string |word|, return the number of vowel substrings in |word|.
//
//

LEETCODE_BEGIN_RESOLVING(2062, CountVowelSubstringsOfAString, Solution);

class Solution {
private:
  bool isVowel(char x) {
    return x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u';
  }

  int solve(string &s, int target) {
    int                      res = 0;
    auto                     lo  = s.begin();
    auto                     hi  = lo;
    unordered_map<char, int> memo;
    while (hi != s.end()) {
      if (!isVowel(*hi)) {
        lo = ++hi;
        memo.clear();
        continue;
      }
      ++memo[*hi++];
      while (memo.size() > target) {
        if (--memo[*lo] == 0) {
          memo.erase(*lo);
        }
        ++lo;
      }
      res += distance(lo, hi);
    }
    return res;
  }

public:
  int countVowelSubstrings(string word) {
    return solve(word, 5) - solve(word, 4);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= word.length <= 100|
// * |word| consists of lowercase English letters only.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word = "aeiouu"
// Output: 2
//
// The vowel substrings of word are as follows (underlined):
// - "aeiouu"
// - "aeiouu"

LEETCODE_SOLUTION_UNITTEST(2062, CountVowelSubstringsOfAString, example_1) {
  auto   solution = MakeSolution();
  string word     = "aeiouu";
  int    expect   = 2;
  int    actual   = solution->countVowelSubstrings(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word = "unicornarihan"
// Output: 0
//
// Not all 5 vowels are present, so there are no vowel substrings.

LEETCODE_SOLUTION_UNITTEST(2062, CountVowelSubstringsOfAString, example_2) {
  auto   solution = MakeSolution();
  string word     = "unicornarihan";
  int    expect   = 0;
  int    actual   = solution->countVowelSubstrings(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: word = "cuaieuouac"
// Output: 7
//
// The vowel substrings of word are as follows (underlined):
// - "cuaieuouac"
// - "cuaieuouac"
// - "cuaieuouac"
// - "cuaieuouac"
// - "cuaieuouac"
// - "cuaieuouac"
// - "cuaieuouac"

LEETCODE_SOLUTION_UNITTEST(2062, CountVowelSubstringsOfAString, example_3) {
  auto   solution = MakeSolution();
  string word     = "cuaieuouac";
  int    expect   = 7;
  int    actual   = solution->countVowelSubstrings(word);
  LCD_EXPECT_EQ(expect, actual);
}
