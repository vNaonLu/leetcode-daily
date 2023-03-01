// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Valid Words for Each Puzzle
//
// https://leetcode.com/problems/number-of-valid-words-for-each-puzzle/
//
// Question ID: 1178
// Difficult  : Hard
// Solve Date : 2021/11/09 18:10

#include <algorithm>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1178. Number of Valid Words for Each Puzzle|:
//
// With respect to a given |puzzle| string, a |word| is valid if both the
// following conditions are satisfied:
//
//  • |word| contains the first letter of |puzzle|.
//
//  • For each letter in |word|, that letter is in |puzzle|.
//
//
//    • For example, if the puzzle is |"abcdefg"|, then valid words are
//    |"faced"|, |"cabbage"|, and |"baggage"|, while
//
//    • invalid words are |"beefed"| (does not include |'a'|) and |"based"|
//    (includes |'s'| which is not in the puzzle).
//
//
// Return an array |answer|, where |answer[i]| is the number of words in the
// given word list |words| that is valid with respect to the puzzle
// |puzzles[i]|.  
//

LEETCODE_BEGIN_RESOLVING(1178, NumberOfValidWordsForEachPuzzle, Solution);

class Solution {
private:
  constexpr static size_t kCharacterSize = 26;
  vector<vector<int>>     trie;
  vector<int>             count;
  int                     dfs_search(const string &p, int node, bool hasFirst) {
    int res = hasFirst ? count[node] : 0;
    for (const auto &c : p) {
      int i = c - 'a';
      if (trie[node][i]) {
        res += dfs_search(p, trie[node][i], hasFirst || c == p[0]);
      }
    }
    return res;
  }

public:
  vector<int> findNumOfValidWords(vector<string> &words,
                                  vector<string> &puzzles) {
    vector<int> res;
    trie  = {vector<int>(kCharacterSize)};
    count = {0};
    for (string s : words) {
      sort(s.begin(), s.end());
      s.erase(unique(s.begin(), s.end()), s.end());
      if (s.size() <= 7) {
        int node = 0;
        for (const auto &c : s) {
          int i = c - 'a';
          if (trie[node][i] == 0) {
            trie[node][i] = trie.size();
            trie.emplace_back(kCharacterSize);
            count.emplace_back(0);
          }
          node = trie[node][i];
        }
        ++count[node];
      }
    }
    for (const auto &p : puzzles)
      res.emplace_back(dfs_search(p, 0, false));
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 10⁵|
// * |4 <= words[i].length <= 50|
// * |1 <= puzzles.length <= 10⁴|
// * |puzzles[i].length == 7|
// * |words[i]| and |puzzles[i]| consist of lowercase English letters.
// * Each |puzzles[i] |does not contain repeated characters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["aaaa","asas","able","ability","actt","actor","access"],
//  puzzles = ["aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"]
// Output: [1,1,3,2,4,0]
//
// 1 valid word for "aboveyz" : "aaaa"
// 1 valid word for "abrodyz" : "aaaa"
// 3 valid words for "abslute" : "aaaa", "asas", "able"
// 2 valid words for "absoryz" : "aaaa", "asas"
// 4 valid words for "actresz" : "aaaa", "asas", "actt", "access"
// There are no valid words for "gaswxyz" cause none of the words in the list
// contains letter 'g'.

LEETCODE_SOLUTION_UNITTEST(1178, NumberOfValidWordsForEachPuzzle, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"aaaa", "asas",  "able",  "ability",
                             "actt", "actor", "access"};
  vector<string> puzzles  = {"aboveyz", "abrodyz", "abslute",
                             "absoryz", "actresz", "gaswxyz"};
  vector<int>    expect   = {1, 1, 3, 2, 4, 0};
  vector<int>    actual   = solution->findNumOfValidWords(words, puzzles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["apple","pleas","please"], puzzles =
//  ["aelwxyz","aelpxyz","aelpsxy","saelpxy","xaelpsy"]
// Output: [0,1,3,2,0]
//

LEETCODE_SOLUTION_UNITTEST(1178, NumberOfValidWordsForEachPuzzle, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"apple", "pleas", "please"};
  vector<string> puzzles  = {"aelwxyz", "aelpxyz", "aelpsxy", "saelpxy",
                             "xaelpsy"};
  vector<int>    expect   = {0, 1, 3, 2, 0};
  vector<int>    actual   = solution->findNumOfValidWords(words, puzzles);
  LCD_EXPECT_EQ(expect, actual);
}
