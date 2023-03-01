// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Detect Capital
//
// https://leetcode.com/problems/detect-capital/
//
// Question ID: 520
// Difficult  : Easy
// Solve Date : 2021/12/03 18:37

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |520. Detect Capital|:
//
// We define the usage of capitals in a word to be right when one of the
// following cases holds:
//
//  • All letters in this word are capitals, like |"USA"|.
//
//  • All letters in this word are not capitals, like |"leetcode"|.
//
//  • Only the first letter in this word is capital, like |"Google"|.
// Given a string |word|, return |true| if the usage of capitals in it is right.
//  
//

LEETCODE_BEGIN_RESOLVING(520, DetectCapital, Solution);

class Solution {
private:
  template <typename T>
  bool uppercase(T &&c) noexcept {
    return c >= 'A' && c <= 'Z';
  }

public:
  bool detectCapitalUse(string word) {
    if (word.size() == 1)
      return true;
    if (uppercase(word.front()) && uppercase(word[1])) {
      for (int i = 2; i < word.size(); ++i)
        if (!uppercase(word[i]))
          return false;
    } else {
      for (int i = 1; i < word.size(); ++i)
        if (uppercase(word[i]))
          return false;
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= word.length <= 100|
// * |word| consists of lowercase and uppercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word = "USA"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(520, DetectCapital, example_1) {
  auto   solution = MakeSolution();
  string word     = "USA";
  bool   expect   = true;
  bool   actual   = solution->detectCapitalUse(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word = "FlaG"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(520, DetectCapital, example_2) {
  auto   solution = MakeSolution();
  string word     = "FlaG";
  bool   expect   = false;
  bool   actual   = solution->detectCapitalUse(word);
  LCD_EXPECT_EQ(expect, actual);
}
