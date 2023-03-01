// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Determine if String Halves Are Alike
//
// https://leetcode.com/problems/determine-if-string-halves-are-alike/
//
// Question ID: 1704
// Difficult  : Easy
// Solve Date : 2022/12/01 20:19

#include <iosfwd>
#include <set>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1704. Determine if String Halves Are Alike|:
//
// You are given a string |s| of even length. Split this string into two halves
// of equal lengths, and let |a| be the first half and |b| be the second half.
// Two strings are alike if they have the same number of vowels ( |'a'|, |'e'|,
// |'i'|, |'o'|, |'u'|, |'A'|, |'E'|, |'I'|, |'O'|, |'U'|). Notice that |s|
// contains uppercase and lowercase letters. Return |true| if |a| and |b| are
// alike. Otherwise, return |false|.
//

LEETCODE_BEGIN_RESOLVING(1704, DetermineIfStringHalvesAreAlike, Solution);

class Solution {
private:
  inline const static set<char> kVowels = {'a', 'e', 'i', 'o', 'u',
                                           'A', 'E', 'I', 'O', 'U'};

  static bool isVowels(char x) { return kVowels.count(x); }

public:
  bool halvesAreAlike(string s) {
    auto fst_beg = s.begin();
    auto fst_end = s.begin() + s.size() / 2;
    auto sec_beg = fst_end;
    auto sec_end = s.end();
    return count_if(fst_beg, fst_end, isVowels) ==
           count_if(sec_beg, sec_end, isVowels);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= s.length <= 1000|
// * |s.length| is even.
// * |s| consists of uppercase and lowercase letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "book"
// Output: true
//
// a = "bo" and b = "ok". a has 1 vowel and b has 1 vowel. Therefore, they are
// alike.

LEETCODE_SOLUTION_UNITTEST(1704, DetermineIfStringHalvesAreAlike, example_1) {
  auto   solution = MakeSolution();
  string s        = "book";
  bool   expect   = true;
  bool   actual   = solution->halvesAreAlike(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "textbook"
// Output: false
//
// a = "text" and b = "book". a has 1 vowel whereas b has 2. Therefore, they are
// not alike. Notice that the vowel o is counted twice.

LEETCODE_SOLUTION_UNITTEST(1704, DetermineIfStringHalvesAreAlike, example_2) {
  auto   solution = MakeSolution();
  string s        = "textbook";
  bool   expect   = false;
  bool   actual   = solution->halvesAreAlike(s);
  LCD_EXPECT_EQ(expect, actual);
}
