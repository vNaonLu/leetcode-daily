// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Word Pattern
//
// https://leetcode.com/problems/word-pattern/
//
// Question ID: 290
// Difficult  : Easy
// Solve Date : 2021/09/25 16:34

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |290. Word Pattern|:
//
// Given a |pattern| and a string |s|, find if |s| follows the same pattern.
// Here follow means a full match, such that there is a bijection between a
// letter in |pattern| and a non-empty word in |s|.  
//

LEETCODE_BEGIN_RESOLVING(290, WordPattern, Solution);

class Solution {
public:
  bool wordPattern(string pattern, string s) {
    vector<string> words;
    for (int i = 0, l = 0; i < s.size(); ++i) {
      if (s[i] == ' ') {
        string word = s.substr(l, i - l);
        if (!word.empty())
          words.push_back(word);
        l = i + 1;
      } else if (i == s.size() - 1) {
        string word = s.substr(l, i - l + 1);
        if (!word.empty())
          words.push_back(word);
      }
    }
    if (pattern.size() != words.size())
      return false;
    unordered_map<char, string> p2w;
    unordered_map<string, char> w2p;
    for (int i = 0; i < pattern.size(); ++i) {
      if ((p2w.count(pattern[i]) && p2w[pattern[i]] == words[i] &&
           w2p.count(words[i]) && w2p[words[i]] == pattern[i]) ||
          (!p2w.count(pattern[i]) && !w2p.count(words[i]))) {
        p2w[pattern[i]] = words[i];
        w2p[words[i]]   = pattern[i];
      } else {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= pattern.length <= 300|
// * |pattern| contains only lower-case English letters.
// * |1 <= s.length <= 3000|
// * |s| contains only lowercase English letters and spaces |' '|.
// * |s| does not contain any leading or trailing spaces.
// * All the words in |s| are separated by a single space.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: pattern = "abba", s = "dog cat cat dog"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(290, WordPattern, example_1) {
  auto   solution = MakeSolution();
  string pattern  = "abba";
  string s        = "dog cat cat dog";
  bool   expect   = true;
  bool   actual   = solution->wordPattern(pattern, s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: pattern = "abba", s = "dog cat cat fish"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(290, WordPattern, example_2) {
  auto   solution = MakeSolution();
  string pattern  = "abba";
  string s        = "dog cat cat fish";
  bool   expect   = false;
  bool   actual   = solution->wordPattern(pattern, s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: pattern = "aaaa", s = "dog cat cat dog"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(290, WordPattern, example_3) {
  auto   solution = MakeSolution();
  string pattern  = "aaaa";
  string s        = "dog cat cat dog";
  bool   expect   = false;
  bool   actual   = solution->wordPattern(pattern, s);
  LCD_EXPECT_EQ(expect, actual);
}
