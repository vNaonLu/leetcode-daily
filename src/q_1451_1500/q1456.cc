// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Number of Vowels in a Substring of Given Length
//
// https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/
//
// Question ID: 1456
// Difficult  : Medium
// Solve Date : 2023/05/05 15:31

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1456. Maximum Number of Vowels in a Substring of Given
// Length|:
//
// Given a string |s| and an integer |k|, return the maximum number of vowel
// letters in any substring of |s| with length |k|. Vowel letters in English are
// |'a'|, |'e'|, |'i'|, |'o'|, and |'u'|.
//
//

LEETCODE_BEGIN_RESOLVING(1456, MaximumNumberOfVowelsInASubstringOfGivenLength,
                         Solution);

class Solution {
public:
  int maxVowels(string s, int k) {
    int  res  = 0;
    int  cur  = 0;
    auto beg  = s.begin();
    auto iter = beg;
    while (distance(beg, iter) < k && iter != s.end()) {
      if (isVowel(*iter++)) {
        ++cur;
      }
    }
    res = cur;
    while (iter != s.end()) {
      cout << *beg << "->" << *iter << endl;
      if (isVowel(*beg++)) {
        --cur;
      }
      if (isVowel(*iter++)) {
        ++cur;
      }
      res = max(res, cur);
    }
    return res;
  }

private:
  bool isVowel(char x) {
    return x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u';
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists of lowercase English letters.
// * |1 <= k <= s.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abciiidef", k = 3
// Output: 3
//
// The substring "iii" contains 3 vowel letters.

LEETCODE_SOLUTION_UNITTEST(1456, MaximumNumberOfVowelsInASubstringOfGivenLength,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "abciiidef";
  int    k        = 3;
  int    expect   = 3;
  int    actual   = solution->maxVowels(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aeiou", k = 2
// Output: 2
//
// Any substring of length 2 contains 2 vowels.

LEETCODE_SOLUTION_UNITTEST(1456, MaximumNumberOfVowelsInASubstringOfGivenLength,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "aeiou";
  int    k        = 2;
  int    expect   = 2;
  int    actual   = solution->maxVowels(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "leetcode", k = 3
// Output: 2
//
// "lee", "eet" and "ode" contain 2 vowels.

LEETCODE_SOLUTION_UNITTEST(1456, MaximumNumberOfVowelsInASubstringOfGivenLength,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "leetcode";
  int    k        = 3;
  int    expect   = 2;
  int    actual   = solution->maxVowels(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "weallloveyou"
// 7
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(1456, MaximumNumberOfVowelsInASubstringOfGivenLength,
                           extra_testcase_1) {
  auto   solution = MakeSolution();
  string s        = "weallloveyou";
  int    k        = 7;
  int    expect   = 4;
  int    actual   = solution->maxVowels(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
