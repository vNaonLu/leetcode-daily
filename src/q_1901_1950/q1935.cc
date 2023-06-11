// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Number of Words You Can Type
//
// https://leetcode.com/problems/maximum-number-of-words-you-can-type/
//
// Question ID: 1935
// Difficult  : Easy
// Solve Date : 2023/06/11 13:57

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1935. Maximum Number of Words You Can Type|:
//
// There is a malfunctioning keyboard where some letter keys do not work. All
// other keys on the keyboard work properly. Given a string |text| of words
// separated by a single space (no leading or trailing spaces) and a string
// |brokenLetters| of all distinct letter keys that are broken, return the
// number of words in |text| you can fully type using this keyboard.
//
//

LEETCODE_BEGIN_RESOLVING(1935, MaximumNumberOfWordsYouCanType, Solution);

class Solution {
public:
  int canBeTypedWords(string text, string brokenLetters) {
    vector<bool> broke(26, false);
    int          res = 0;
    for (auto c : brokenLetters) {
      broke[c - 'a'] = true;
    }
    auto beg = text.begin();
    auto end = text.end();
    while (beg != end) {
      forwardNextWord(&beg, end);
      while (beg != end && *beg != ' ') {
        if (broke[*beg - 'a']) {
          break;
        }
        ++beg;
      }
      if (beg == end || *beg == ' ') {
        ++res;
      }
      forwardToGap(&beg, end);
    }
    return res;
  }

private:
  template <typename It>
  void forwardNextWord(It *beg, It end) {
    while (*beg != end && **beg == ' ') {
      ++*beg;
    }
  }
  template <typename It>
  void forwardToGap(It *beg, It end) {
    while (*beg != end && **beg != ' ') {
      ++*beg;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= text.length <= 10⁴|
// * |0 <= brokenLetters.length <= 26|
// * |text| consists of words separated by a single space without any leading or
// trailing spaces.
// * Each word only consists of lowercase English letters.
// * |brokenLetters| consists of distinct lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: text = "hello world", brokenLetters = "ad"
// Output: 1
//
// We cannot type "world" because the 'd' key is broken.

LEETCODE_SOLUTION_UNITTEST(1935, MaximumNumberOfWordsYouCanType, example_1) {
  auto   solution      = MakeSolution();
  string text          = "hello world";
  string brokenLetters = "ad";
  int    expect        = 1;
  int    actual        = solution->canBeTypedWords(text, brokenLetters);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: text = "leet code", brokenLetters = "lt"
// Output: 1
//
// We cannot type "leet" because the 'l' and 't' keys are broken.

LEETCODE_SOLUTION_UNITTEST(1935, MaximumNumberOfWordsYouCanType, example_2) {
  auto   solution      = MakeSolution();
  string text          = "leet code";
  string brokenLetters = "lt";
  int    expect        = 1;
  int    actual        = solution->canBeTypedWords(text, brokenLetters);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: text = "leet code", brokenLetters = "e"
// Output: 0
//
// We cannot type either word because the 'e' key is broken.

LEETCODE_SOLUTION_UNITTEST(1935, MaximumNumberOfWordsYouCanType, example_3) {
  auto   solution      = MakeSolution();
  string text          = "leet code";
  string brokenLetters = "e";
  int    expect        = 0;
  int    actual        = solution->canBeTypedWords(text, brokenLetters);
  LCD_EXPECT_EQ(expect, actual);
}
