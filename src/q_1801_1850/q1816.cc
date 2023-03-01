// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Truncate Sentence
//
// https://leetcode.com/problems/truncate-sentence/
//
// Question ID: 1816
// Difficult  : Easy
// Solve Date : 2022/12/15 10:20

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1816. Truncate Sentence|:
//
// A sentence is a list of words that are separated by a single space with no
// leading or trailing spaces. Each of the words consists of only uppercase and
// lowercase English letters (no punctuation).
//
//  • For example, |"Hello World"|, |"HELLO"|, and |"hello world hello world"|
//  are all sentences.
// You are given a sentence |s|​​​​​​ and an integer
// |k|​​​​​​. You want to truncate |s|​​​​​​ such that
// it contains only the first |k|​​​​​​ words. Return
// |s|​​​​​​ after truncating it.
//

LEETCODE_BEGIN_RESOLVING(1816, TruncateSentence, Solution);

class Solution {
public:
  string truncateSentence(string s, int k) {
    auto beg  = s.begin();
    auto iter = s.begin();
    auto res  = string("");
    while (beg != s.end()) {
      if (*iter == ' ' || iter == s.end()) {
        res += string(beg, iter);
        beg = iter;
        --k;
      }

      if (k == 0) {
        break;
      }
      ++iter;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 500|
// * |k| is in the range |[1, the number of words in s]|.
// * |s| consist of only lowercase and uppercase English letters and spaces.
// * The words in |s| are separated by a single space.
// * There are no leading or trailing spaces.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "Hello how are you Contestant", k = 4
// Output: "Hello how are you"
//
// The words in s are ["Hello", "how" "are", "you", "Contestant"].
// The first 4 words are ["Hello", "how", "are", "you"].
// Hence, you should return "Hello how are you".

LEETCODE_SOLUTION_UNITTEST(1816, TruncateSentence, example_1) {
  auto   solution = MakeSolution();
  string s        = "Hello how are you Contestant";
  int    k        = 4;
  string expect   = "Hello how are you";
  string actual   = solution->truncateSentence(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "What is the solution to this problem", k = 4
// Output: "What is the solution"
//
// The words in s are ["What", "is" "the", "solution", "to", "this", "problem"].
// The first 4 words are ["What", "is", "the", "solution"].
// Hence, you should return "What is the solution".

LEETCODE_SOLUTION_UNITTEST(1816, TruncateSentence, example_2) {
  auto   solution = MakeSolution();
  string s        = "What is the solution to this problem";
  int    k        = 4;
  string expect   = "What is the solution";
  string actual   = solution->truncateSentence(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "chopper is not a tanuki", k = 5
// Output: "chopper is not a tanuki"
//

LEETCODE_SOLUTION_UNITTEST(1816, TruncateSentence, example_3) {
  auto   solution = MakeSolution();
  string s        = "chopper is not a tanuki";
  int    k        = 5;
  string expect   = "chopper is not a tanuki";
  string actual   = solution->truncateSentence(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
