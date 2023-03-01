// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reverse Prefix of Word
//
// https://leetcode.com/problems/reverse-prefix-of-word/
//
// Question ID: 2000
// Difficult  : Easy
// Solve Date : 2022/12/10 13:30

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2000. Reverse Prefix of Word|:
//
// Given a 0-indexed string |word| and a character |ch|, reverse the segment of
// |word| that starts at index |0| and ends at the index of the first occurrence
// of |ch| (inclusive). If the character |ch| does not exist in |word|, do
// nothing.
//
//  • For example, if |word = "abcdefd"| and |ch = "d"|, then you should reverse
//  the segment that starts at |0| and ends at |3| (inclusive). The resulting
//  string will be |"dcbaefd"|.
// Return the resulting string.
//

LEETCODE_BEGIN_RESOLVING(2000, ReversePrefixOfWord, Solution);

class Solution {
public:
  string reversePrefix(string word, char ch) {
    auto beg = word.begin();
    while (beg != word.end()) {
      if (*beg == ch) {
        reverse(word.begin(), beg + 1);
        break;
      }
      ++beg;
    }
    return word;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= word.length <= 250|
// * |word| consists of lowercase English letters.
// * |ch| is a lowercase English letter.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word = "abcdefd", ch = "d"
// Output: "dcbaefd"
//
// The first occurrence of "d" is at index 3.
// Reverse the part of word from 0 to 3 (inclusive), the resulting string is
// "dcbaefd".

LEETCODE_SOLUTION_UNITTEST(2000, ReversePrefixOfWord, example_1) {
  auto   solution = MakeSolution();
  string word     = "abcdefd";
  char   ch       = 'd';
  string expect   = "dcbaefd";
  string actual   = solution->reversePrefix(word, ch);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word = "xyxzxe", ch = "z"
// Output: "zxyxxe"
//
// The first and only occurrence of "z" is at index 3.
// Reverse the part of word from 0 to 3 (inclusive), the resulting string is
// "zxyxxe".

LEETCODE_SOLUTION_UNITTEST(2000, ReversePrefixOfWord, example_2) {
  auto   solution = MakeSolution();
  string word     = "xyxzxe";
  char   ch       = 'z';
  string expect   = "zxyxxe";
  string actual   = solution->reversePrefix(word, ch);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: word = "abcd", ch = "z"
// Output: "abcd"
//
// "z" does not exist in word.
// You should not do any reverse operation, the resulting string is "abcd".

LEETCODE_SOLUTION_UNITTEST(2000, ReversePrefixOfWord, example_3) {
  auto   solution = MakeSolution();
  string word     = "abcd";
  char   ch       = 'z';
  string expect   = "abcd";
  string actual   = solution->reversePrefix(word, ch);
  LCD_EXPECT_EQ(expect, actual);
}
