// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Merge Strings Alternately
//
// https://leetcode.com/problems/merge-strings-alternately/
//
// Question ID: 1768
// Difficult  : Easy
// Solve Date : 2022/04/21 09:01

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1768. Merge Strings Alternately|:
//
// You are given two strings |word1| and |word2|. Merge the strings by adding
// letters in alternating order, starting with |word1|. If a string is longer
// than the other, append the additional letters onto the end of the merged
// string.
//
// Return the merged string.
//
//  
//

LEETCODE_BEGIN_RESOLVING(1768, MergeStringsAlternately, Solution);

class Solution {
public:
  string mergeAlternately(string word1, string word2) {
    string res;
    auto   w1 = word1.begin(), w2 = word2.begin();
    while (w1 != word1.end() && w2 != word2.end()) {
      res.push_back(*(w1++));
      res.push_back(*(w2++));
    }
    while (w1 != word1.end()) {
      res.push_back(*(w1++));
    }
    while (w2 != word2.end()) {
      res.push_back(*(w2++));
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= word1.length, word2.length <= 100|
// * |word1| and |word2| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word1 = "abc", word2 = "pqr"
// Output: "apbqcr"
//
//  The merged string will be merged as so:
// word1: a b c
// word2: p q r
// merged: a p b q c r

LEETCODE_SOLUTION_UNITTEST(1768, MergeStringsAlternately, example_1) {
  auto   solution = MakeSolution();
  string word1    = "abc";
  string word2    = "pqr";
  string expect   = "apbqcr";
  string actual   = solution->mergeAlternately(word1, word2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word1 = "ab", word2 = "pqrs"
// Output: "apbqrs"
//
//  Notice that as word2 is longer, "rs" is appended to the end.
// word1: a b
// word2: p q r s
// merged: a p b q r s

LEETCODE_SOLUTION_UNITTEST(1768, MergeStringsAlternately, example_2) {
  auto   solution = MakeSolution();
  string word1    = "ab";
  string word2    = "pqrs";
  string expect   = "apbqrs";
  string actual   = solution->mergeAlternately(word1, word2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: word1 = "abcd", word2 = "pq"
// Output: "apbqcd"
//
//  Notice that as word1 is longer, "cd" is appended to the end.
// word1: a b c d
// word2: p q
// merged: a p b q c d

LEETCODE_SOLUTION_UNITTEST(1768, MergeStringsAlternately, example_3) {
  auto   solution = MakeSolution();
  string word1    = "abcd";
  string word2    = "pq";
  string expect   = "apbqcd";
  string actual   = solution->mergeAlternately(word1, word2);
  LCD_EXPECT_EQ(expect, actual);
}
