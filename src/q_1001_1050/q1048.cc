// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest String Chain
//
// https://leetcode.com/problems/longest-string-chain/
//
// Question ID: 1048
// Difficult  : Medium
// Solve Date : 2022/06/15 21:21

#include <algorithm>
#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1048. Longest String Chain|:
//
// You are given an array of |words| where each word consists of lowercase
// English letters. |word^{A}| is a predecessor of |word^{B}| if and only if we
// can insert exactly one letter anywhere in |word^{A}| without changing the
// order of the other characters to make it equal to |word^{B}|.
//
//  • For example, |"abc"| is a predecessor of |"abac"|, while |"cba"| is not a
//  predecessor of |"bcad"|.
// A word chain is a sequence of words |[word₁, word₂, ..., wordₖ]| with |k >=
// 1|, where |word₁| is a predecessor of |word₂|, |word₂| is a predecessor of
// |word₃|, and so on. A single word is trivially a word chain with |k == 1|.
// Return the length of the longest possible word chain with words chosen from
// the given list of |words|.
//

LEETCODE_BEGIN_RESOLVING(1048, LongestStringChain, Solution);

class Solution {
public:
  int longestStrChain(vector<string> &words) {
    sort(words.begin(), words.end(),
         [](auto &x, auto &y) { return x.size() < y.size(); });

    unordered_map<string, int> mp;
    int                        res = 0;

    for (auto &s : words) {
      int local = 0;
      for (int i = 0; i < s.size(); ++i) {
        auto sub = s.substr(0, i) + s.substr(i + 1, s.size() + 1);
        local    = max(local, mp[sub] + 1);
      }
      mp[s] = local;
      res   = max(res, local);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 1000|
// * |1 <= words[i].length <= 16|
// * |words[i]| only consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["a","b","ba","bca","bda","bdca"]
// Output: 4
//
// : One of the longest word chains is ["a","ba","bda","bdca"].

LEETCODE_SOLUTION_UNITTEST(1048, LongestStringChain, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"a", "b", "ba", "bca", "bda", "bdca"};
  int            expect   = 4;
  int            actual   = solution->longestStrChain(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
// Output: 5
//
// All the words can be put in a word chain ["xb", "xbc", "cxbc", "pcxbc",
// "pcxbcf"].

LEETCODE_SOLUTION_UNITTEST(1048, LongestStringChain, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"xbc", "pcxbcf", "xb", "cxbc", "pcxbc"};
  int            expect   = 5;
  int            actual   = solution->longestStrChain(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: words = ["abcd","dbqca"]
// Output: 1
//
// The trivial word chain ["abcd"] is one of the longest word chains.
// ["abcd","dbqca"] is not a valid word chain because the ordering of the
// letters is changed.

LEETCODE_SOLUTION_UNITTEST(1048, LongestStringChain, example_3) {
  auto           solution = MakeSolution();
  vector<string> words    = {"abcd", "dbqca"};
  int            expect   = 1;
  int            actual   = solution->longestStrChain(words);
  LCD_EXPECT_EQ(expect, actual);
}
