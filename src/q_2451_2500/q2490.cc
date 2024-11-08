// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Circular Sentence
//
// https://leetcode.com/problems/circular-sentence/
//
// Question ID: 2490
// Difficult  : Easy
// Solve Date : 2023/03/06 14:54

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2490. Circular Sentence|:
//
// A sentence is a list of words that are separated by a single space with no
// leading or trailing spaces.
//
//  • For example, |"Hello World"|, |"HELLO"|, |"hello world hello world"| are
//  all sentences.
// Words consist of only uppercase and lowercase English letters. Uppercase and
// lowercase English letters are considered different. A sentence is circular
// if:
//
//  • The last character of a word is equal to the first character of the next
//  word.
//
//  • The last character of the last word is equal to the first character of the
//  first word.
// For example, |"leetcode exercises sound delightful"|, |"eetcode"|, |"leetcode
// eats soul" |are all circular sentences. However, |"Leetcode is cool"|,
// |"happy Leetcode"|, |"Leetcode"| and |"I like Leetcode"| are not circular
// sentences. Given a string |sentence|, return |true| if it is circular.
// Otherwise, return |false|.
//

LEETCODE_BEGIN_RESOLVING(2490, CircularSentence, Solution);

class Solution {
public:
  bool isCircularSentence(string sentence) {
    auto beg   = sentence.begin();
    auto first = beg;
    auto prev  = beg;
    while (++beg != sentence.end()) {
      if (*beg != ' ') {
        prev = beg;
        continue;
      }
      while (beg != sentence.end() && *beg == ' ') {
        ++beg;
      }
      if (beg != sentence.end() && *prev != *beg) {
        return false;
      }
    }
    return *prev == *first;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= sentence.length <= 500|
// * |sentence| consist of only lowercase and uppercase English letters and
// spaces.
// * The words in |sentence| are separated by a single space.
// * There are no leading or trailing spaces.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: sentence = "leetcode exercises sound delightful"
// Output: true
//
// The words in sentence are ["leetcode", "exercises", "sound", "delightful"].
// - leetcode'slast character is equal to exercises's first character.
// - exercises'slast character is equal to sound's first character.
// - sound'slast character is equal to delightful's first character.
// - delightful'slast character is equal to leetcode's first character.
// The sentence is circular.

LEETCODE_SOLUTION_UNITTEST(2490, CircularSentence, example_1) {
  auto   solution = MakeSolution();
  string sentence = "leetcode exercises sound delightful";
  bool   expect   = true;
  bool   actual   = solution->isCircularSentence(sentence);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: sentence = "eetcode"
// Output: true
//
// The words in sentence are ["eetcode"].
// - eetcode'slast character is equal to eetcode's first character.
// The sentence is circular.

LEETCODE_SOLUTION_UNITTEST(2490, CircularSentence, example_2) {
  auto   solution = MakeSolution();
  string sentence = "eetcode";
  bool   expect   = true;
  bool   actual   = solution->isCircularSentence(sentence);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: sentence = "Leetcode is cool"
// Output: false
//
// The words in sentence are ["Leetcode", "is", "cool"].
// - Leetcode'slast character is not equal to is's first character.
// The sentence is not circular.

LEETCODE_SOLUTION_UNITTEST(2490, CircularSentence, example_3) {
  auto   solution = MakeSolution();
  string sentence = "Leetcode is cool";
  bool   expect   = false;
  bool   actual   = solution->isCircularSentence(sentence);
  LCD_EXPECT_EQ(expect, actual);
}
