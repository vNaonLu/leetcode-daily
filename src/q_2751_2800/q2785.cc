// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sort Vowels in a String
//
// https://leetcode.com/problems/sort-vowels-in-a-string/
//
// Question ID: 2785
// Difficult  : Medium
// Solve Date : 2023/11/13 19:01

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2785. Sort Vowels in a String|:
//
// Given a 0-indexed string |s|, permute |s| to get a new string |t| such that:
//
//  • All consonants remain in their original places. More formally, if there is
//  an index |i| with |0 <= i < s.length| such that |s[i]| is a consonant, then
//  |t[i] = s[i]|.
//
//  • The vowels must be sorted in the nondecreasing order of their ASCII
//  values. More formally, for pairs of indices |i|, |j| with |0 <= i < j <
//  s.length| such that |s[i]| and |s[j]| are vowels, then |t[i]| must not have
//  a higher ASCII value than |t[j]|.
// Return the resulting string.
// The vowels are |'a'|, |'e'|, |'i'|, |'o'|, and |'u'|, and they can appear in
// lowercase or uppercase. Consonants comprise all letters that are not vowels.
//
//

LEETCODE_BEGIN_RESOLVING(2785, SortVowelsInAString, Solution);

class Solution {
public:
  string sortVowels(string s) {
    vector<string::iterator> v;
    vector<char>             vv;
    for (auto it = s.begin(); it != s.end(); ++it) {
      if (isVowel(*it)) {
        v.emplace_back(it);
        vv.emplace_back(*it);
      }
    }
    sort(vv.begin(), vv.end());
    for (int i = 0; i < v.size(); ++i) {
      (*v[i]) = vv[i];
    }
    return s;
  }

private:
  bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists only of letters of the English alphabet in uppercase and
// lowercase.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "lEetcOde"
// Output: "lEOtcede"
//
// 'E', 'O', and 'e' are the vowels in s; 'l', 't', 'c', and 'd' are all
// consonants. The vowels are sorted according to their ASCII values, and the
// consonants remain in the same places.

LEETCODE_SOLUTION_UNITTEST(2785, SortVowelsInAString, example_1) {
  auto   solution = MakeSolution();
  string s        = "lEetcOde";
  string expect   = "lEOtcede";
  string actual   = solution->sortVowels(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "lYmpH"
// Output: "lYmpH"
//
// There are no vowels in s (all characters in s are consonants), so we return
// "lYmpH".

LEETCODE_SOLUTION_UNITTEST(2785, SortVowelsInAString, example_2) {
  auto   solution = MakeSolution();
  string s        = "lYmpH";
  string expect   = "lYmpH";
  string actual   = solution->sortVowels(s);
  LCD_EXPECT_EQ(expect, actual);
}
