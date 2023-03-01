// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Word Break II
//
// https://leetcode.com/problems/word-break-ii/
//
// Question ID: 140
// Difficult  : Hard
// Solve Date : 2022/05/16 17:56

#include <array>
#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |140. Word Break II|:
//
// Given a string |s| and a dictionary of strings |wordDict|, add spaces in |s|
// to construct a sentence where each word is a valid dictionary word. Return
// all such possible sentences in any order. Note that the same word in the
// dictionary may be reused multiple times in the segmentation.
//

LEETCODE_BEGIN_RESOLVING(140, WordBreakII, Solution);

class Solution {
private:
  struct trie {
    array<unique_ptr<trie>, 26> next;
    bool                        end = false;
  };
  unique_ptr<trie> root;

  void build_trie(const string &word) {
    auto p = root.get();

    for (auto &c : word) {
      auto &node = p->next[c - 'a'];
      if (node == nullptr) {
        node = make_unique<trie>();
      }
      p = node.get();
    }

    p->end = true;
  }

  void build_trie(const vector<string> &dict) {
    root = make_unique<trie>();
    for (auto &s : dict) {
      build_trie(s);
    }
  }

  string append(const string &s, string &&next) {
    return (s.empty() ? "" : (s + " ")) + std::move(next);
  }

  template <typename iterator>
  void helper(iterator beg, iterator end, string cr, trie *ct,
              vector<string> &res) {
    auto it = beg;
    auto p  = ct;
    while (it != end) {
      p = p->next[*(it++) - 'a'].get();
      if (p == nullptr) {
        break;
      } else {
        if (p->end) {
          helper(it, end, append(cr, string(beg, it)), root.get(), res);
        }
      }
    }

    if (nullptr != p && p->end) {
      res.emplace_back(append(cr, string(beg, it)));
    }
  }

public:
  vector<string> wordBreak(string s, vector<string> &wordDict) {
    vector<string> res;
    build_trie(wordDict);
    helper(s.begin(), s.end(), "", root.get(), res);

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 20|
// * |1 <= wordDict.length <= 1000|
// * |1 <= wordDict[i].length <= 10|
// * |s| and |wordDict[i]| consist of only lowercase English letters.
// * All the strings of |wordDict| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
// Output: ["cats and dog","cat sand dog"]
//

LEETCODE_SOLUTION_UNITTEST(140, WordBreakII, example_1) {
  auto           solution = MakeSolution();
  string         s        = "catsanddog";
  vector<string> wordDict = {"cat", "cats", "and", "sand", "dog"};
  vector<string> expect   = {"cats and dog", "cat sand dog"};
  vector<string> actual   = solution->wordBreak(s, wordDict);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "pineapplepenapple", wordDict =
//  ["apple","pen","applepen","pine","pineapple"]
// Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
//
// Note that you are allowed to reuse a dictionary word.

LEETCODE_SOLUTION_UNITTEST(140, WordBreakII, example_2) {
  auto           solution = MakeSolution();
  string         s        = "pineapplepenapple";
  vector<string> wordDict = {"apple", "pen", "applepen", "pine", "pineapple"};
  vector<string> expect   = {"pine apple pen apple", "pineapple pen apple",
                             "pine applepen apple"};
  vector<string> actual   = solution->wordBreak(s, wordDict);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(140, WordBreakII, example_3) {
  auto           solution = MakeSolution();
  string         s        = "catsandog";
  vector<string> wordDict = {"cats", "dog", "sand", "and", "cat"};
  vector<string> expect   = {};
  vector<string> actual   = solution->wordBreak(s, wordDict);
  EXPECT_ANYORDER_EQ(expect, actual);
}
