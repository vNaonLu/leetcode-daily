// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check if Numbers Are Ascending in a Sentence
//
// https://leetcode.com/problems/check-if-numbers-are-ascending-in-a-sentence/
//
// Question ID: 2042
// Difficult  : Easy
// Solve Date : 2022/01/12 17:59

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2042. Check if Numbers Are Ascending in a Sentence|:
//
// A sentence is a list of tokens separated by a single space with no leading or
// trailing spaces. Every token is either a positive number consisting of digits
// |0-9| with no leading zeros, or a word consisting of lowercase English
// letters.
//
//  • For example, |"a puppy has 2 eyes 4 legs"| is a sentence with seven
//  tokens: |"2"| and |"4"| are numbers and the other tokens such as |"puppy"|
//  are words.
// Given a string |s| representing a sentence, you need to check if all the
// numbers in |s| are strictly increasing from left to right (i.e., other than
// the last number, each number is strictly smaller than the number on its right
// in |s|). Return |true| if so, or |false| otherwise.  
//

LEETCODE_BEGIN_RESOLVING(2042, CheckIfNumbersAreAscendingInASentence, Solution);

class Solution {
public:
  bool areNumbersAscending(string s) {
    int current_num = -1;
    int maximum     = -1;
    for (const auto &c : s) {
      if (isdigit(c)) {
        if (current_num > 0) {
          current_num *= 10;
          current_num += c - '0';
        } else {
          current_num = c - '0';
        }
      } else if (current_num > 0) {
        if (current_num <= maximum)
          return false;
        maximum     = current_num;
        current_num = -1;
      }
    }
    return current_num == -1 ? true : current_num > maximum;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= s.length <= 200|
// * |s| consists of lowercase English letters, spaces, and digits from |0| to
// |9|, inclusive.
// * The number of tokens in |s| is between |2| and |100|, inclusive.
// * The tokens in |s| are separated by a single space.
// * There are at least two numbers in |s|.
// * Each number in |s| is a positive number less than |100|, with no leading
// zeros.
// * |s| contains no leading or trailing spaces.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "1 box has 3 blue 4 red 6 green and 12 yellow marbles"
// Output: true
//
// The numbers in s are: 1, 3, 4, 6, 12.
// They are strictly increasing from left to right: 1 < 3 < 4 < 6 < 12.

LEETCODE_SOLUTION_UNITTEST(2042, CheckIfNumbersAreAscendingInASentence,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "1 box has 3 blue 4 red 6 green and 12 yellow marbles";
  bool   expect   = true;
  bool   actual   = solution->areNumbersAscending(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "hello world 5 x 5"
// Output: false
//
// The numbers in s are: 5, 5. They are not strictly increasing.

LEETCODE_SOLUTION_UNITTEST(2042, CheckIfNumbersAreAscendingInASentence,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "hello world 5 x 5";
  bool   expect   = false;
  bool   actual   = solution->areNumbersAscending(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "sunset is at 7 51 pm overnight lows will be in the low 50 and 60
//  s"
// Output: false
//
// The numbers in s are: 7, 51, 50, 60. They are not strictly increasing.

LEETCODE_SOLUTION_UNITTEST(2042, CheckIfNumbersAreAscendingInASentence,
                           example_3) {
  auto   solution = MakeSolution();
  string s =
      "sunset is at 7 51 pm overnight lows will be in the low 50 and 60 s";
  bool expect = false;
  bool actual = solution->areNumbersAscending(s);
  LCD_EXPECT_EQ(expect, actual);
}
