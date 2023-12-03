// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count the Number of Vowel Strings in Range
//
// https://leetcode.com/problems/count-the-number-of-vowel-strings-in-range/
//
// Question ID: 2586
// Difficult  : Easy
// Solve Date : 2023/12/03 22:49

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2586. Count the Number of Vowel Strings in Range|:
//
// You are given a 0-indexed array of string |words| and two integers |left| and
// |right|. A string is called a vowel string if it starts with a vowel
// character and ends with a vowel character where vowel characters are |'a'|,
// |'e'|, |'i'|, |'o'|, and |'u'|. Return the number of vowel strings |words[i]|
// where |i| belongs to the inclusive range |[left, right]|.
//
//

LEETCODE_BEGIN_RESOLVING(2586, CountTheNumberOfVowelStringsInRange, Solution);

class Solution {
public:
  int vowelStrings(vector<string> &words, int left, int right) {
    int res = 0;
    while (left <= right) {
      auto &s = words[left++];
      if (isVowel(s.front()) && isVowel(s.back())) {
        ++res;
      }
    }
    return res;
  }

private:
  bool isVowel(char c) {
    switch (c) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
      return true;
    default:
      return false;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 1000|
// * |1 <= words[i].length <= 10|
// * |words[i]| consists of only lowercase English letters.
// * |0 <= left <= right < words.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["are","amy","u"], left = 0, right = 2
// Output: 2
//
// - "are" is a vowel string because it starts with 'a' and ends with 'e'.
// - "amy" is not a vowel string because it does not end with a vowel.
// - "u" is a vowel string because it starts with 'u' and ends with 'u'.
// The number of vowel strings in the mentioned range is 2.

LEETCODE_SOLUTION_UNITTEST(2586, CountTheNumberOfVowelStringsInRange,
                           example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"are", "amy", "u"};
  int            left     = 0;
  int            right    = 2;
  int            expect   = 2;
  int            actual   = solution->vowelStrings(words, left, right);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["hey","aeo","mu","ooo","artro"], left = 1, right = 4
// Output: 3
//
// - "aeo" is a vowel string because it starts with 'a' and ends with 'o'.
// - "mu" is not a vowel string because it does not start with a vowel.
// - "ooo" is a vowel string because it starts with 'o' and ends with 'o'.
// - "artro" is a vowel string because it starts with 'a' and ends with 'o'.
// The number of vowel strings in the mentioned range is 3.

LEETCODE_SOLUTION_UNITTEST(2586, CountTheNumberOfVowelStringsInRange,
                           example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"hey", "aeo", "mu", "ooo", "artro"};
  int            left     = 1;
  int            right    = 4;
  int            expect   = 3;
  int            actual   = solution->vowelStrings(words, left, right);
  LCD_EXPECT_EQ(expect, actual);
}
