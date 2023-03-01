// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find and Replace Pattern
//
// https://leetcode.com/problems/find-and-replace-pattern/
//
// Question ID: 890
// Difficult  : Medium
// Solve Date : 2022/07/29 18:21

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |890. Find and Replace Pattern|:
//
// Given a list of strings |words| and a string |pattern|, return a list of
// |words[i]| that match |pattern|. You may return the answer in any order. A
// word matches the pattern if there exists a permutation of letters |p| so that
// after replacing every letter |x| in the pattern with |p(x)|, we get the
// desired word. Recall that a permutation of letters is a bijection from
// letters to letters: every letter maps to another letter, and no two letters
// map to the same letter.
//

LEETCODE_BEGIN_RESOLVING(890, FindAndReplacePattern, Solution);

class Solution {
private:
  template <typename iterator>
  vector<int> toPermutation(iterator beg, iterator end) {
    auto dict = unordered_map<int, int>();
    auto res  = vector<int>();
    auto cnt  = 0;

    while (beg != end) {
      auto find = dict.find(*beg);
      if (find == dict.end()) {
        res.emplace_back(dict[*beg] = cnt++);
      } else {
        res.emplace_back(find->second);
      }
      ++beg;
    }

    return res;
  }

public:
  vector<string> findAndReplacePattern(vector<string> &words, string pattern) {
    auto res = vector<string>();
    auto key = toPermutation(pattern.begin(), pattern.end());

    for (auto &s : words) {
      auto curr = toPermutation(s.begin(), s.end());

      if (curr == key) {
        res.emplace_back(s);
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= pattern.length <= 20|
// * |1 <= words.length <= 50|
// * |words[i].length == pattern.length|
// * |pattern| and |words[i]| are lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
// Output: ["mee","aqq"]
//
// "mee" matches the pattern because there is a permutation {a -> m, b -> e,
// ...}. "ccc" does not match the pattern because {a -> c, b -> c, ...} is not a
// permutation, since a and b map to the same letter.

LEETCODE_SOLUTION_UNITTEST(890, FindAndReplacePattern, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"abc", "deq", "mee", "aqq", "dkd", "ccc"};
  string         pattern  = "abb";
  vector<string> expect   = {"mee", "aqq"};
  vector<string> actual   = solution->findAndReplacePattern(words, pattern);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["a","b","c"], pattern = "a"
// Output: ["a","b","c"]
//

LEETCODE_SOLUTION_UNITTEST(890, FindAndReplacePattern, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"a", "b", "c"};
  string         pattern  = "a";
  vector<string> expect   = {"a", "b", "c"};
  vector<string> actual   = solution->findAndReplacePattern(words, pattern);
  EXPECT_ANYORDER_EQ(expect, actual);
}
