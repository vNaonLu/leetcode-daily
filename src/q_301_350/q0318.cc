// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Product of Word Lengths
//
// https://leetcode.com/problems/maximum-product-of-word-lengths/
//
// Question ID: 318
// Difficult  : Medium
// Solve Date : 2022/05/29 14:09

#include <iosfwd>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |318. Maximum Product of Word Lengths|:
//
// Given a string array |words|, return the maximum value of |length(word[i]) *
// length(word[j])| where the two words do not share common letters. If no such
// two words exist, return |0|.
//

LEETCODE_BEGIN_RESOLVING(318, MaximumProductOfWordLengths, Solution);

class Solution {
public:
  int maxProduct(vector<string> &words) {
    int                                   res = 0;
    vector<pair<int, unordered_set<int>>> memos;
    for (auto &s : words) {
      pair<int, unordered_set<int>> curr;
      auto &[length, letters] = curr;
      for (auto &c : s) {
        ++length;
        letters.insert(c);
      }

      memos.emplace_back(move(curr));
    }

    for (int i = 0; i < memos.size(); ++i) {
      auto &[lx, lex] = memos[i];
      for (int j = i + 1; j < memos.size(); ++j) {
        auto &[ly, ley] = memos[j];
        bool duplicate  = false;
        for (auto &c : lex) {
          if (ley.count(c)) {
            duplicate = true;
            break;
          }
        }

        if (!duplicate) {
          res = max(res, ly * lx);
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
// * |2 <= words.length <= 1000|
// * |1 <= words[i].length <= 1000|
// * |words[i]| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
// Output: 16
//
// The two words can be "abcw", "xtfn".

LEETCODE_SOLUTION_UNITTEST(318, MaximumProductOfWordLengths, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
  int            expect   = 16;
  int            actual   = solution->maxProduct(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["a","ab","abc","d","cd","bcd","abcd"]
// Output: 4
//
// The two words can be "ab", "cd".

LEETCODE_SOLUTION_UNITTEST(318, MaximumProductOfWordLengths, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"a", "ab", "abc", "d", "cd", "bcd", "abcd"};
  int            expect   = 4;
  int            actual   = solution->maxProduct(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: words = ["a","aa","aaa","aaaa"]
// Output: 0
//
// No such pair of words.

LEETCODE_SOLUTION_UNITTEST(318, MaximumProductOfWordLengths, example_3) {
  auto           solution = MakeSolution();
  vector<string> words    = {"a", "aa", "aaa", "aaaa"};
  int            expect   = 0;
  int            actual   = solution->maxProduct(words);
  LCD_EXPECT_EQ(expect, actual);
}
