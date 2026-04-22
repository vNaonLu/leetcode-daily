// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Words Within Two Edits of Dictionary
//
// https://leetcode.com/problems/words-within-two-edits-of-dictionary/
//
// Question ID: 2452
// Difficult  : Medium
// Solve Date : 2026/04/22 20:05

#include <iosfwd>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2452. Words Within Two Edits of Dictionary|:
//
// You are given two string arrays, |queries| and |dictionary|. All words in
// each array comprise of lowercase English letters and have the same length. In
// one edit you can take a word from |queries|, and change any letter in it to
// any other letter. Find all words from |queries| that, after a maximum of two
// edits, equal some word from |dictionary|. Return a list of all words from
// |queries|, that match with some word from |dictionary| after a maximum of two
// edits. Return the words in the same order they appear in |queries|.
//
//

LEETCODE_BEGIN_RESOLVING(2452, WordsWithinTwoEditsOfDictionary, Solution);

class Solution {
public:
  vector<string> twoEditWords(vector<string> &queries,
                              vector<string> &dictionary) {
    ans.clear();
    for (auto &s1 : queries) {
      for (auto &s2 : dictionary) {
        if (numOfDiff(s1, s2) < 3) {
          ans.emplace_back(s1);
          break;
        }
      }
    }
    return ans;
  }

private:
  int numOfDiff(string const &s1, string const &s2) {
    if (s1.size() != s2.size()) {
      return 3;
    }
    int diff = 0;
    for (int i = 0; i < s1.size() && diff < 3; ++i) {
      if (s1[i] != s2[i]) {
        ++diff;
      }
    }
    return diff;
  }
  vector<string> ans;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= queries.length, dictionary.length <= 100|
// * |n == queries[i].length == dictionary[j].length|
// * |1 <= n <= 100|
// * All |queries[i]| and |dictionary[j]| are composed of lowercase English
// letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: queries = ["word","note","ants","wood"], dictionary =
//  ["wood","joke","moat"]
// Output: ["word","note","wood"]
//

LEETCODE_SOLUTION_UNITTEST(2452, WordsWithinTwoEditsOfDictionary, example_1) {
  auto           solution   = MakeSolution();
  vector<string> queries    = {"word", "note", "ants", "wood"};
  vector<string> dictionary = {"wood", "joke", "moat"};
  vector<string> expect     = {"word", "note", "wood"};
  vector<string> actual     = solution->twoEditWords(queries, dictionary);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: queries = ["yes"], dictionary = ["not"]
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(2452, WordsWithinTwoEditsOfDictionary, example_2) {
  auto           solution   = MakeSolution();
  vector<string> queries    = {"yes"};
  vector<string> dictionary = {"not"};
  vector<string> expect     = {};
  vector<string> actual     = solution->twoEditWords(queries, dictionary);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: ["t","i","m","i","p","s"]
// ["w","j","b","p","u","b","u","i","h","m"]
// Output: ["t","i","m","i","p","s"]
//

LEETCODE_SOLUTION_UNITTEST(2452, WordsWithinTwoEditsOfDictionary,
                           extra_testcase_1) {
  auto           solution   = MakeSolution();
  vector<string> queries    = {"t", "i", "m", "i", "p", "s"};
  vector<string> dictionary = {"w", "j", "b", "p", "u",
                               "b", "u", "i", "h", "m"};
  vector<string> expect     = {"t", "i", "m", "i", "p", "s"};
  vector<string> actual     = solution->twoEditWords(queries, dictionary);
  LCD_EXPECT_EQ(expect, actual);
}
