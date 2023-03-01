// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Uncommon Words from Two Sentences
//
// https://leetcode.com/problems/uncommon-words-from-two-sentences/
//
// Question ID: 884
// Difficult  : Easy
// Solve Date : 2021/11/06 20:16

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |884. Uncommon Words from Two Sentences|:
//
// A sentence is a string of single-space separated words where each word
// consists only of lowercase letters. A word is uncommon if it appears exactly
// once in one of the sentences, and does not appear in the other sentence.
// Given two sentences |s1| and |s2|, return a list of all the uncommon words.
// You may return the answer in any order.  
//

LEETCODE_BEGIN_RESOLVING(884, UncommonWordsFromTwoSentences, Solution);

class Solution {
private:
  void get_word(unordered_map<string, int> &cnt, const string &s) {
    string word = "";
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == ' ') {
        ++cnt[word];
        word = "";
      } else {
        word += s[i];
      }
    }
    ++cnt[word];
  }

public:
  vector<string> uncommonFromSentences(string s1, string s2) {
    vector<string>             res;
    unordered_map<string, int> cnt;
    get_word(cnt, s1);
    get_word(cnt, s2);
    res.reserve(cnt.size());
    for (auto it = cnt.begin(); it != cnt.end(); ++it) {
      if (it->second == 1)
        res.emplace_back(it->first);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s1.length, s2.length <= 200|
// * |s1| and |s2| consist of lowercase English letters and spaces.
// * |s1| and |s2| do not have leading or trailing spaces.
// * All the words in |s1| and |s2| are separated by a single space.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s1 = "this apple is sweet", s2 = "this apple is sour"
// Output: ["sweet","sour"]
//

LEETCODE_SOLUTION_UNITTEST(884, UncommonWordsFromTwoSentences, example_1) {
  auto           solution = MakeSolution();
  string         s1       = "this apple is sweet";
  string         s2       = "this apple is sour";
  vector<string> expect   = {"sweet", "sour"};
  vector<string> actual   = solution->uncommonFromSentences(s1, s2);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: s1 = "apple apple", s2 = "banana"
// Output: ["banana"]
//

LEETCODE_SOLUTION_UNITTEST(884, UncommonWordsFromTwoSentences, example_2) {
  auto           solution = MakeSolution();
  string         s1       = "apple apple";
  string         s2       = "banana";
  vector<string> expect   = {"banana"};
  vector<string> actual   = solution->uncommonFromSentences(s1, s2);
  EXPECT_ANYORDER_EQ(expect, actual);
}
