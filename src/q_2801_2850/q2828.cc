// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Check if a String Is an Acronym of Words
//
// https://leetcode.com/problems/check-if-a-string-is-an-acronym-of-words/
//
// Question ID: 2828
// Difficult  : Easy
// Solve Date : 2024/01/12 21:58

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2828. Check if a String Is an Acronym of Words|:
//
// Given an array of strings |words| and a string |s|, determine if |s| is an
// acronym of words. The string |s| is considered an acronym of |words| if it
// can be formed by concatenating the first character of each string in |words|
// in order. For example, |"ab"| can be formed from |["apple", "banana"]|, but
// it can't be formed from |["bear", "aardvark"]|. Return |true| if |s| is an
// acronym of |words|, and |false| otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(2828, CheckIfAStringIsAnAcronymOfWords, Solution);

class Solution {
public:
  bool isAcronym(vector<string> &words, string s) {
    auto wb = words.begin();
    auto sb = s.begin();
    while (wb != words.end() && sb != s.end()) {
      if (wb++->front() != *sb++) {
        return false;
      }
    }
    return words.end() == wb && s.end() == sb;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 100|
// * |1 <= words[i].length <= 10|
// * |1 <= s.length <= 100|
// * |words[i]| and |s| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["alice","bob","charlie"], s = "abc"
// Output: true
//
// The first character in the words "alice", "bob", and "charlie" are 'a', 'b',
// and 'c', respectively. Hence, s = "abc" is the acronym.

LEETCODE_SOLUTION_UNITTEST(2828, CheckIfAStringIsAnAcronymOfWords, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"alice", "bob", "charlie"};
  string         s        = "abc";
  bool           expect   = true;
  bool           actual   = solution->isAcronym(words, s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["an","apple"], s = "a"
// Output: false
//
// The first character in the words "an" and "apple" are 'a' and 'a',
// respectively. The acronym formed by concatenating these characters is "aa".
// Hence, s = "a" is not the acronym.

LEETCODE_SOLUTION_UNITTEST(2828, CheckIfAStringIsAnAcronymOfWords, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"an", "apple"};
  string         s        = "a";
  bool           expect   = false;
  bool           actual   = solution->isAcronym(words, s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: words = ["never","gonna","give","up","on","you"], s = "ngguoy"
// Output: true
//
// By concatenating the first character of the words in the array, we get the
// string "ngguoy". Hence, s = "ngguoy" is the acronym.

LEETCODE_SOLUTION_UNITTEST(2828, CheckIfAStringIsAnAcronymOfWords, example_3) {
  auto           solution = MakeSolution();
  vector<string> words    = {"never", "gonna", "give", "up", "on", "you"};
  string         s        = "ngguoy";
  bool           expect   = true;
  bool           actual   = solution->isAcronym(words, s);
  LCD_EXPECT_EQ(expect, actual);
}
