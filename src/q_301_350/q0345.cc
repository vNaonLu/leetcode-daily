// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reverse Vowels of a String
//
// https://leetcode.com/problems/reverse-vowels-of-a-string/
//
// Question ID: 345
// Difficult  : Easy
// Solve Date : 2022/08/22 00:40

#include <iosfwd>
#include <set>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |345. Reverse Vowels of a String|:
//
// Given a string |s|, reverse only all the vowels in the string and return it.
// The vowels are |'a'|, |'e'|, |'i'|, |'o'|, and |'u'|, and they can appear in
// both lower and upper cases, more than once.
//

LEETCODE_BEGIN_RESOLVING(345, ReverseVowelsOfAString, Solution);

class Solution {
public:
  string reverseVowels(string s) {
    auto mp = set<char>{'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    auto vowel_pos = vector<int>();
    for (int i = 0; i < s.size(); ++i) {
      if (mp.count(s[i])) {
        vowel_pos.emplace_back(i);
      }
    }

    auto l = 0;
    auto r = int(vowel_pos.size() - 1);

    while (l < r) {
      swap(s[vowel_pos[l++]], s[vowel_pos[r--]]);
    }

    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 3 * 10⁵|
// * |s| consist of printable ASCII characters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "hello"
// Output: "holle"
//

LEETCODE_SOLUTION_UNITTEST(345, ReverseVowelsOfAString, example_1) {
  auto   solution = MakeSolution();
  string s        = "hello";
  string expect   = "holle";
  string actual   = solution->reverseVowels(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "leetcode"
// Output: "leotcede"
//

LEETCODE_SOLUTION_UNITTEST(345, ReverseVowelsOfAString, example_2) {
  auto   solution = MakeSolution();
  string s        = "leetcode";
  string expect   = "leotcede";
  string actual   = solution->reverseVowels(s);
  LCD_EXPECT_EQ(expect, actual);
}
