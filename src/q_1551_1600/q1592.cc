// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Rearrange Spaces Between Words
//
// https://leetcode.com/problems/rearrange-spaces-between-words/
//
// Question ID: 1592
// Difficult  : Easy
// Solve Date : 2023/08/31 05:45

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1592. Rearrange Spaces Between Words|:
//
// You are given a string |text| of words that are placed among some number of
// spaces. Each word consists of one or more lowercase English letters and are
// separated by at least one space. It's guaranteed that |text| contains at
// least one word. Rearrange the spaces so that there is an equal number of
// spaces between every pair of adjacent words and that number is maximized. If
// you cannot redistribute all the spaces equally, place the extra spaces at the
// end, meaning the returned string should be the same length as |text|. Return
// the string after rearranging the spaces.
//
//

LEETCODE_BEGIN_RESOLVING(1592, RearrangeSpacesBetweenWords, Solution);

class Solution {
public:
  string reorderSpaces(string text) {
    string         res;
    vector<string> words;
    auto           beg   = toNonSpace(text.begin(), text.end());
    auto           lo    = beg;
    int            space = distance(text.begin(), beg);
    while (beg != text.end()) {
      beg = toSpace(beg, text.end());
      if (beg != lo) {
        words.emplace_back(lo, beg);
      }
      lo = toNonSpace(beg, text.end());
      space += distance(beg, lo);
      beg = lo;
    }
    space = words.size() <= 1 ? 0 : (space / (words.size() - 1));
    res   = std::move(words.front());
    for (int i = 1; i < words.size(); ++i) {
      res.resize(res.size() + space, ' ');
      res += words[i];
    }
    res.resize(text.size(), ' ');
    return res;
  }

private:
  template <typename It>
  It toNonSpace(It beg, It end) {
    while (beg != end) {
      if (*beg != ' ') {
        return beg;
      }
      ++beg;
    }
    return beg;
  }
  template <typename It>
  It toSpace(It beg, It end) {
    while (beg != end) {
      if (*beg == ' ') {
        return beg;
      }
      ++beg;
    }
    return beg;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= text.length <= 100|
// * |text| consists of lowercase English letters and |' '|.
// * |text| contains at least one word.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: text = " this is a sentence "
// Output: "this is a sentence"
//
// There are a total of 9 spaces and 4 words. We can evenly divide the 9 spaces
// between the words: 9 / (4-1) = 3 spaces.

LEETCODE_SOLUTION_UNITTEST(1592, RearrangeSpacesBetweenWords, example_1) {
  auto   solution = MakeSolution();
  string text     = "  this   is  a sentence ";
  string expect   = "this   is   a   sentence";
  string actual   = solution->reorderSpaces(text);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: text = " practice makes perfect"
// Output: "practice makes perfect "
//
// There are a total of 7 spaces and 3 words. 7 / (3-1) = 3 spaces plus 1 extra
// space. We place this extra space at the end of the string.

LEETCODE_SOLUTION_UNITTEST(1592, RearrangeSpacesBetweenWords, example_2) {
  auto   solution = MakeSolution();
  string text     = " practice   makes   perfect";
  string expect   = "practice   makes   perfect ";
  string actual   = solution->reorderSpaces(text);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "a"
// Output: "a"
//

LEETCODE_SOLUTION_UNITTEST(1592, RearrangeSpacesBetweenWords,
                           extra_testcase_1) {
  auto   solution = MakeSolution();
  string text     = "a";
  string expect   = "a";
  string actual   = solution->reorderSpaces(text);
  LCD_EXPECT_EQ(expect, actual);
}
