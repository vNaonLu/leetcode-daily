// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check Whether Two Strings are Almost Equivalent
//
// https://leetcode.com/problems/check-whether-two-strings-are-almost-equivalent/
//
// Question ID: 2068
// Difficult  : Easy
// Solve Date : 2023/03/20 18:57

#include <iosfwd>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2068. Check Whether Two Strings are Almost Equivalent|:
//
// Two strings |word1| and |word2| are considered almost equivalent if the
// differences between the frequencies of each letter from |'a'| to |'z'|
// between |word1| and |word2| is at most |3|. Given two strings |word1| and
// |word2|, each of length |n|, return |true| if |word1| and |word2| are almost
// equivalent, or |false| otherwise. The frequency of a letter |x| is the number
// of times it occurs in the string.
//
//

LEETCODE_BEGIN_RESOLVING(2068, CheckWhetherTwoStringsAreAlmostEquivalent,
                         Solution);

class Solution {
public:
  bool checkAlmostEquivalent(string word1, string word2) {
    unordered_map<char, int> freq;
    for (auto c : word1) {
      ++freq[c];
    }
    for (auto c : word2) {
      --freq[c];
    }
    for (auto &[x, cnt] : freq) {
      if (abs(cnt) > 3) {
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
// * |n == word1.length == word2.length|
// * |1 <= n <= 100|
// * |word1| and |word2| consist only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word1 = "aaaa", word2 = "bccb"
// Output: false
//
// There are 4 'a's in "aaaa" but 0 'a's in "bccb".
// The difference is 4, which is more than the allowed 3.

LEETCODE_SOLUTION_UNITTEST(2068, CheckWhetherTwoStringsAreAlmostEquivalent,
                           example_1) {
  auto   solution = MakeSolution();
  string word1    = "aaaa";
  string word2    = "bccb";
  bool   expect   = false;
  bool   actual   = solution->checkAlmostEquivalent(word1, word2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word1 = "abcdeef", word2 = "abaaacc"
// Output: true
//
// The differences between the frequencies of each letter in word1 and word2 are
// at most 3:
// - 'a' appears 1 time in word1 and 4 times in word2. The difference is 3.
// - 'b' appears 1 time in word1 and 1 time in word2. The difference is 0.
// - 'c' appears 1 time in word1 and 2 times in word2. The difference is 1.
// - 'd' appears 1 time in word1 and 0 times in word2. The difference is 1.
// - 'e' appears 2 times in word1 and 0 times in word2. The difference is 2.
// - 'f' appears 1 time in word1 and 0 times in word2. The difference is 1.

LEETCODE_SOLUTION_UNITTEST(2068, CheckWhetherTwoStringsAreAlmostEquivalent,
                           example_2) {
  auto   solution = MakeSolution();
  string word1    = "abcdeef";
  string word2    = "abaaacc";
  bool   expect   = true;
  bool   actual   = solution->checkAlmostEquivalent(word1, word2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: word1 = "cccddabba", word2 = "babababab"
// Output: true
//
// The differences between the frequencies of each letter in word1 and word2 are
// at most 3:
// - 'a' appears 2 times in word1 and 4 times in word2. The difference is 2.
// - 'b' appears 2 times in word1 and 5 times in word2. The difference is 3.
// - 'c' appears 3 times in word1 and 0 times in word2. The difference is 3.
// - 'd' appears 2 times in word1 and 0 times in word2. The difference is 2.

LEETCODE_SOLUTION_UNITTEST(2068, CheckWhetherTwoStringsAreAlmostEquivalent,
                           example_3) {
  auto   solution = MakeSolution();
  string word1    = "cccddabba";
  string word2    = "babababab";
  bool   expect   = true;
  bool   actual   = solution->checkAlmostEquivalent(word1, word2);
  LCD_EXPECT_EQ(expect, actual);
}
