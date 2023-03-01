// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Short Encoding of Words
//
// https://leetcode.com/problems/short-encoding-of-words/
//
// Question ID: 820
// Difficult  : Medium
// Solve Date : 2022/06/20 18:11

#include <array>
#include <iosfwd>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |820. Short Encoding of Words|:
//
// A valid encoding of an array of |words| is any reference string |s| and array
// of indices |indices| such that:
//
//  • |words.length == indices.length|
//
//  • The reference string |s| ends with the |'#'| character.
//
//  • For each index |indices[i]|, the substring of |s| starting from
//  |indices[i]| and up to (but not including) the next |'#'| character is equal
//  to |words[i]|.
// Given an array of |words|, return the length of the shortest reference string
// |s| possible of any valid encoding of |words|.
//

LEETCODE_BEGIN_RESOLVING(820, ShortEncodingOfWords, Solution);

class Solution {
private:
  struct Trie {
    array<unique_ptr<Trie>, 26> children;
    int                         count;

    Trie() : count{0} {}
    Trie *next(char c) {
      auto &res = children[c - 'a'];
      if (res == nullptr) {
        res = make_unique<Trie>();
        count++;
      }

      return res.get();
    }
  };

public:
  int minimumLengthEncoding(vector<string> &words) {
    auto                       trie = make_unique<Trie>();
    unordered_map<Trie *, int> nodes;
    for (int i = 0; i < words.size(); ++i) {
      auto &s = words[i];
      auto  p = trie.get();
      for (int j = s.size() - 1; j >= 0; --j) {
        p = p->next(s[j]);
      }
      nodes.emplace(p, i);
    }

    int res = 0;
    for (auto &[trie, idx] : nodes) {
      if (trie->count == 0) {
        res += words[idx].size() + 1;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 2000|
// * |1 <= words[i].length <= 7|
// * |words[i]| consists of only lowercase letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["time", "me", "bell"]
// Output: 10
//
// A valid encoding would be s = |"time#bell#" and indices = [0, 2, 5|].
// words[0] = "time", the substring of s starting from indices[0] = 0 to the
// next '#' is underlined in "time#bell#" words[1] = "me", the substring of s
// starting from indices[1] = 2 to the next '#' is underlined in "time#bell#"
// words[2] = "bell", the substring of s starting from indices[2] = 5 to the
// next '#' is underlined in "time#bell#"

LEETCODE_SOLUTION_UNITTEST(820, ShortEncodingOfWords, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"time", "me", "bell"};
  int            expect   = 10;
  int            actual   = solution->minimumLengthEncoding(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["t"]
// Output: 2
//
// A valid encoding would be s = "t#" and indices = [0].

LEETCODE_SOLUTION_UNITTEST(820, ShortEncodingOfWords, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"t"};
  int            expect   = 2;
  int            actual   = solution->minimumLengthEncoding(words);
  LCD_EXPECT_EQ(expect, actual);
}
