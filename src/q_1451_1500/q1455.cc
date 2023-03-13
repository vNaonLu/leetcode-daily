// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check If a Word Occurs As a Prefix of Any Word in a Sentence
//
// https://leetcode.com/problems/check-if-a-word-occurs-as-a-prefix-of-any-word-in-a-sentence/
//
// Question ID: 1455
// Difficult  : Easy
// Solve Date : 2022/12/05 16:10

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1455. Check If a Word Occurs As a Prefix of Any Word in a
// Sentence|:
//
// Given a |sentence| that consists of some words separated by a single space,
// and a |searchWord|, check if |searchWord| is a prefix of any word in
// |sentence|. Return the index of the word in |sentence| (1-indexed) where
// |searchWord| is a prefix of this word. If |searchWord| is a prefix of more
// than one word, return the index of the first word (minimum index). If there
// is no such word return |-1|. A prefix of a string |s| is any leading
// contiguous substring of |s|.
//

LEETCODE_BEGIN_RESOLVING(1455, CheckIfAWordOccursAsAPrefixOfAnyWordInASentence,
                         Solution);

class Solution {
private:
  vector<string_view> splitWords(string const &s) {
    auto res = vector<string_view>();
    auto beg = s.begin();

    while (beg != s.end() && *beg == ' ') {
      ++beg;
    }

    auto it = beg;
    while (beg != s.end()) {
      if (it == s.end() || *it == ' ') {
        res.emplace_back(s.data() + distance(s.begin(), beg),
                         distance(beg, it));
        while (it != s.end() && *it == ' ') {
          ++it;
        }
        beg = it;
      } else {
        ++it;
      }
    }
    return res;
  }

public:
  int isPrefixOfWord(string sentence, string searchWord) {
    auto words = splitWords(sentence);
    auto idx   = (int)1;
    for (auto &s : words) {
      if (s.substr(0, searchWord.size()) == searchWord) {
        return idx;
      }
      ++idx;
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= sentence.length <= 100|
// * |1 <= searchWord.length <= 10|
// * |sentence| consists of lowercase English letters and spaces.
// * |searchWord| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: sentence = "i love eating burger", searchWord = "burg"
// Output: 4
//
// "burg" is prefix of "burger" which is the 4th word in the sentence.

LEETCODE_SOLUTION_UNITTEST(1455,
                           CheckIfAWordOccursAsAPrefixOfAnyWordInASentence,
                           example_1) {
  auto   solution   = MakeSolution();
  string sentence   = "i love eating burger";
  string searchWord = "burg";
  int    expect     = 4;
  int    actual     = solution->isPrefixOfWord(sentence, searchWord);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: sentence = "this problem is an easy problem", searchWord = "pro"
// Output: 2
//
// "pro" is prefix of "problem" which is the 2nd and the 6th word in the
// sentence, but we return 2 as it's the minimal index.

LEETCODE_SOLUTION_UNITTEST(1455,
                           CheckIfAWordOccursAsAPrefixOfAnyWordInASentence,
                           example_2) {
  auto   solution   = MakeSolution();
  string sentence   = "this problem is an easy problem";
  string searchWord = "pro";
  int    expect     = 2;
  int    actual     = solution->isPrefixOfWord(sentence, searchWord);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: sentence = "i am tired", searchWord = "you"
// Output: -1
//
// "you" is not a prefix of any word in the sentence.

LEETCODE_SOLUTION_UNITTEST(1455,
                           CheckIfAWordOccursAsAPrefixOfAnyWordInASentence,
                           example_3) {
  auto   solution   = MakeSolution();
  string sentence   = "i am tired";
  string searchWord = "you";
  int    expect     = -1;
  int    actual     = solution->isPrefixOfWord(sentence, searchWord);
  LCD_EXPECT_EQ(expect, actual);
}
