// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Concatenated Words
//
// https://leetcode.com/problems/concatenated-words/
//
// Question ID: 472
// Difficult  : Hard
// Solve Date : 2023/01/27 14:33

#include <iosfwd>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |472. Concatenated Words|:
//
// Given an array of strings |words| (without duplicates), return all the
// concatenated words in the given list of |words|. A concatenated word is
// defined as a string that is comprised entirely of at least two shorter words
// (not necesssarily distinct)in the given array.
//

LEETCODE_BEGIN_RESOLVING(472, ConcatenatedWords, Solution);

class Solution {
public:
  vector<string> findAllConcatenatedWordsInADict(vector<string> &words) {
    unordered_set<string> words_set;
    vector<string>        res;
    for (auto &s : words) {
      words_set.emplace(s);
    }
    for (auto &s : words) {
      int         n = s.size();
      vector<int> dp(n + 1, 0);
      dp.front() = 1;
      for (int i = 0; i < n; ++i) {
        if (dp[i]) {
          for (int j = i + 1; j <= n; ++j) {
            if (j - i < n && words_set.count(s.substr(i, j - i))) {
              dp[j] = 1;
            }
          }
          if (dp[n]) {
            res.emplace_back(s);
            break;
          }
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 10⁴|
// * |1 <= words[i].length <= 30|
// * |words[i]| consists of only lowercase English letters.
// * All the strings of |words| are unique.
// * |1 <= sum(words[i].length) <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words =
//  ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
// Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
//
// "catsdogcats" can be concatenated by "cats", "dog" and "cats";
// "dogcatsdog" can be concatenated by "dog", "cats" and "dog";
// "ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".

LEETCODE_SOLUTION_UNITTEST(472, ConcatenatedWords, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"cat", "cats",        "catsdogcats",
                             "dog", "dogcatsdog",  "hippopotamuses",
                             "rat", "ratcatdogcat"};
  vector<string> expect   = {"catsdogcats", "dogcatsdog", "ratcatdogcat"};
  vector<string> actual   = solution->findAllConcatenatedWordsInADict(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["cat","dog","catdog"]
// Output: ["catdog"]
//

LEETCODE_SOLUTION_UNITTEST(472, ConcatenatedWords, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"cat", "dog", "catdog"};
  vector<string> expect   = {"catdog"};
  vector<string> actual   = solution->findAllConcatenatedWordsInADict(words);
  LCD_EXPECT_EQ(expect, actual);
}
