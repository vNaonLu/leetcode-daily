// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Vowel Spellchecker
//
// https://leetcode.com/problems/vowel-spellchecker/
//
// Question ID: 966
// Difficult  : Medium
// Solve Date : 2025/09/14 09:10

#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |966. Vowel Spellchecker|:
//
// Given a |wordlist|, we want to implement a spellchecker that converts a query
// word into a correct word. For a given |query| word, the spell checker handles
// two categories of spelling mistakes:
//
//  • Capitalization: If the query matches a word in the wordlist
//  (case-insensitive), then the query word is returned with the same case as
//  the case in the wordlist.
//
//
//    • Example: |wordlist = ["yellow"]|, |query = "YellOw"|: |correct =
//    "yellow"|
//
//    • Example: |wordlist = ["Yellow"]|, |query = "yellow"|: |correct =
//    "Yellow"|
//
//    • Example: |wordlist = ["yellow"]|, |query = "yellow"|: |correct =
//    "yellow"|
//
//
//
//  • Vowel Errors: If after replacing the vowels |('a', 'e', 'i', 'o', 'u')| of
//  the query word with any vowel individually, it matches a word in the
//  wordlist (case-insensitive), then the query word is returned with the same
//  case as the match in the wordlist.
//
//
//    • Example: |wordlist = ["YellOw"]|, |query = "yollow"|: |correct =
//    "YellOw"|
//
//    • Example: |wordlist = ["YellOw"]|, |query = "yeellow"|: |correct = ""|
//    (no match)
//
//    • Example: |wordlist = ["YellOw"]|, |query = "yllw"|: |correct = ""| (no
//    match)
//
//
// In addition, the spell checker operates under the following precedence rules:
//
//  • When the query exactly matches a word in the wordlist (case-sensitive),
//  you should return the same word back.
//
//  • When the query matches a word up to capitlization, you should return the
//  first such match in the wordlist.
//
//  • When the query matches a word up to vowel errors, you should return the
//  first such match in the wordlist.
//
//  • If the query has no matches in the wordlist, you should return the empty
//  string.
// Given some |queries|, return a list of words |answer|, where |answer[i]| is
// the correct word for |query = queries[i]|.
//
//

LEETCODE_BEGIN_RESOLVING(966, VowelSpellchecker, Solution);

class Solution {
public:
  vector<string> spellchecker(vector<string> &W, vector<string> &Q) {
    set<string>                   orig(W.begin(), W.end());
    unordered_map<string, string> lower, mask;
    for (int i = W.size() - 1; ~i; i--) {
      string word = W[i], wlow = lcase(word);
      lower[wlow] = word, mask[vmask(wlow)] = word;
    }
    for (string &query : Q) {
      string qlow = lcase(query), qmask = vmask(qlow);
      if (orig.count(query))
        continue;
      else if (lower.count(qlow))
        query = lower[qlow];
      else if (mask.count(qmask))
        query = mask[qmask];
      else
        query = "";
    }
    return Q;
  }
  static string vmask(string str) {
    for (char &c : str)
      if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        c = '*';
    return str;
  }
  static string lcase(string str) {
    for (char &c : str)
      c = tolower(c);
    return str;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= wordlist.length, queries.length <= 5000|
// * |1 <= wordlist[i].length, queries[i].length <= 7|
// * |wordlist[i]| and |queries[i]| consist only of only English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: wordlist = ["KiTe","kite","hare","Hare"], queries =
//  ["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
// Output: ["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]
//

LEETCODE_SOLUTION_UNITTEST(966, VowelSpellchecker, example_1) {
  auto           solution = MakeSolution();
  vector<string> wordlist = {"KiTe", "kite", "hare", "Hare"};
  vector<string> queries  = {"kite", "Kite", "KiTe", "Hare", "HARE",
                             "Hear", "hear", "keti", "keet", "keto"};
  vector<string> expect   = {"kite", "KiTe", "KiTe", "Hare", "hare",
                             "",     "",     "KiTe", "",     "KiTe"};
  vector<string> actual   = solution->spellchecker(wordlist, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: wordlist = ["yellow"], queries = ["YellOw"]
// Output: ["yellow"]
//

LEETCODE_SOLUTION_UNITTEST(966, VowelSpellchecker, example_2) {
  auto           solution = MakeSolution();
  vector<string> wordlist = {"yellow"};
  vector<string> queries  = {"YellOw"};
  vector<string> expect   = {"yellow"};
  vector<string> actual   = solution->spellchecker(wordlist, queries);
  LCD_EXPECT_EQ(expect, actual);
}
