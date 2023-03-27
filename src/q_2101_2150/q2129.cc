// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Capitalize the Title
//
// https://leetcode.com/problems/capitalize-the-title/
//
// Question ID: 2129
// Difficult  : Easy
// Solve Date : 2023/03/21 21:07

#include <cctype>
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2129. Capitalize the Title|:
//
// You are given a string |title| consisting of one or more words separated by a
// single space, where each word consists of English letters. Capitalize the
// string by changing the capitalization of each word such that:
//
//  • If the length of the word is |1| or |2| letters, change all letters to
//  lowercase.
//
//  • Otherwise, change the first letter to uppercase and the remaining letters
//  to lowercase.
// Return the capitalized |title|.
//
//

LEETCODE_BEGIN_RESOLVING(2129, CapitalizeTheTitle, Solution);

class Solution {
public:
  string capitalizeTitle(string title) {
    auto beg = title.begin();
    while (beg != title.end()) {
      auto word_end = beg;
      while (word_end != title.end() && *word_end != ' ') {
        *word_end = tolower(*word_end);
        ++word_end;
      }
      if (distance(beg, word_end) > 2) {
        *beg = toupper(*beg);
      }
      beg = word_end;
      while (beg != title.end() && *beg == ' ') {
        ++beg;
      }
    }
    return title;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= title.length <= 100|
// * |title| consists of words separated by a single space without any leading
// or trailing spaces.
// * Each word consists of uppercase and lowercase English letters and is
// non-empty.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: title = "capiTalIze tHe titLe"
// Output: "Capitalize The Title"
//
// Since all the words have a length of at least 3, the first letter of each
// word is uppercase, and the remaining letters are lowercase.

LEETCODE_SOLUTION_UNITTEST(2129, CapitalizeTheTitle, example_1) {
  auto   solution = MakeSolution();
  string title    = "capiTalIze tHe titLe";
  string expect   = "Capitalize The Title";
  string actual   = solution->capitalizeTitle(title);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: title = "First leTTeR of EACH Word"
// Output: "First Letter of Each Word"
//
// The word "of" has length 2, so it is all lowercase.
// The remaining words have a length of at least 3, so the first letter of each
// remaining word is uppercase, and the remaining letters are lowercase.

LEETCODE_SOLUTION_UNITTEST(2129, CapitalizeTheTitle, example_2) {
  auto   solution = MakeSolution();
  string title    = "First leTTeR of EACH Word";
  string expect   = "First Letter of Each Word";
  string actual   = solution->capitalizeTitle(title);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: title = "i lOve leetcode"
// Output: "i Love Leetcode"
//
// The word "i" has length 1, so it is lowercase.
// The remaining words have a length of at least 3, so the first letter of each
// remaining word is uppercase, and the remaining letters are lowercase.

LEETCODE_SOLUTION_UNITTEST(2129, CapitalizeTheTitle, example_3) {
  auto   solution = MakeSolution();
  string title    = "i lOve leetcode";
  string expect   = "i Love Leetcode";
  string actual   = solution->capitalizeTitle(title);
  LCD_EXPECT_EQ(expect, actual);
}
