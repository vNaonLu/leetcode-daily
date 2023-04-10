// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Greatest English Letter in Upper and Lower Case
//
// https://leetcode.com/problems/greatest-english-letter-in-upper-and-lower-case/
//
// Question ID: 2309
// Difficult  : Easy
// Solve Date : 2023/04/05 12:41

#include <cctype>
#include <iosfwd>
#include <string>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2309. Greatest English Letter in Upper and Lower Case|:
//
// Given a string of English letters |s|, return the greatest English letter
// which occurs as both a lowercase and uppercase letter in |s|. The returned
// letter should be in uppercase. If no such letter exists, return an empty
// string. An English letter |b| is greater than another letter |a| if |b|
// appears after |a| in the English alphabet.
//
//

LEETCODE_BEGIN_RESOLVING(2309, GreatestEnglishLetterInUpperAndLowerCase,
                         Solution);

class Solution {
public:
  string greatestLetter(string s) {
    char                res = '\0';
    unordered_set<char> memo;
    for (auto c : s) {
      memo.emplace(c);
      if (memo.count(tolower(c)) && memo.count(toupper(c))) {
        res = max<char>(res, toupper(c));
      }
    }
    return res == '\0' ? string() : (string() + res);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 1000|
// * |s| consists of lowercase and uppercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "lEeTcOdE"
// Output: "E"
//
// The letter 'E' is the only letter to appear in both lower and upper case.

LEETCODE_SOLUTION_UNITTEST(2309, GreatestEnglishLetterInUpperAndLowerCase,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "lEeTcOdE";
  string expect   = "E";
  string actual   = solution->greatestLetter(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "arRAzFif"
// Output: "R"
//
// The letter 'R' is the greatest letter to appear in both lower and upper case.
// Note that 'A' and 'F' also appear in both lower and upper case, but 'R' is
// greater than 'F' or 'A'.

LEETCODE_SOLUTION_UNITTEST(2309, GreatestEnglishLetterInUpperAndLowerCase,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "arRAzFif";
  string expect   = "R";
  string actual   = solution->greatestLetter(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "AbCdEfGhIjK"
// Output: ""
//
// There is no letter that appears in both lower and upper case.

LEETCODE_SOLUTION_UNITTEST(2309, GreatestEnglishLetterInUpperAndLowerCase,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "AbCdEfGhIjK";
  string expect   = "";
  string actual   = solution->greatestLetter(s);
  LCD_EXPECT_EQ(expect, actual);
}
