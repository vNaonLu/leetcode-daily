// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Longest Word in Dictionary
//
// https://leetcode.com/problems/longest-word-in-dictionary/
//
// Question ID: 720
// Difficult  : Medium
// Solve Date : 2024/06/01 15:01

#include <iosfwd>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |720. Longest Word in Dictionary|:
//
// Given an array of strings |words| representing an English Dictionary, return
// the longest word in |words| that can be built one character at a time by
// other words in |words|. If there is more than one possible answer, return the
// longest word with the smallest lexicographical order. If there is no answer,
// return the empty string. Note that the word should be built from left to
// right with each additional character being added to the end of a previous
// word.
//
//

LEETCODE_BEGIN_RESOLVING(720, LongestWordInDictionary, Solution);

class Solution {
public:
  string longestWord(vector<string> &words) {
    sort(words.begin(), words.end());
    unordered_set<string> built;
    string                res;
    for (auto &s : words) {
      if (s.size() == 1 || built.count(s.substr(0, s.size() - 1))) {
        if (s.size() > res.size()) {
          res = s;
        }
        built.insert(s);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 1000|
// * |1 <= words[i].length <= 30|
// * |words[i]| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["w","wo","wor","worl","world"]
// Output: "world"
//

LEETCODE_SOLUTION_UNITTEST(720, LongestWordInDictionary, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"w", "wo", "wor", "worl", "world"};
  string         expect   = "world";
  string         actual   = solution->longestWord(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["a","banana","app","appl","ap","apply","apple"]
// Output: "apple"
//

LEETCODE_SOLUTION_UNITTEST(720, LongestWordInDictionary, example_2) {
  auto           solution = MakeSolution();
  vector<string> words = {"a", "banana", "app", "appl", "ap", "apply", "apple"};
  string         expect = "apple";
  string         actual = solution->longestWord(words);
  LCD_EXPECT_EQ(expect, actual);
}
