// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Word Subsets
//
// https://leetcode.com/problems/word-subsets/
//
// Question ID: 916
// Difficult  : Medium
// Solve Date : 2022/07/30 16:44

#include <array>
#include <iosfwd>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |916. Word Subsets|:
//
// You are given two string arrays |words1| and |words2|.
// A string |b| is a subset of string |a| if every letter in |b| occurs in |a|
// including multiplicity.
//
//  • For example, |"wrr"| is a subset of |"warrior"| but is not a subset of
//  |"world"|.
// A string |a| from |words1| is universal if for every string |b| in |words2|,
// |b| is a subset of |a|. Return an array of all the universal strings in
// |words1|. You may return the answer in any order.
//

LEETCODE_BEGIN_RESOLVING(916, WordSubsets, Solution);

class Solution {
private:
  template <typename iterator>
  auto toLetters(iterator beg, iterator end) {
    auto res = array<int, 26>();
    while (beg != end) {
      ++res[*beg++ - 'a'];
    }

    return res;
  }

public:
  vector<string> wordSubsets(vector<string> &words1, vector<string> &words2) {
    auto res                = vector<string>();
    auto reduced_word2_dict = unordered_map<int, int>();

    for (auto &w : words2) {
      auto w_cnt = unordered_map<char, int>();
      auto beg   = w.begin();
      while (beg != w.end()) {
        auto  curr   = ++w_cnt[*beg];
        auto &global = reduced_word2_dict[*beg++];
        global       = max(global, curr);
      }
    }

    for (auto &s : words1) {
      auto letters = toLetters(s.begin(), s.end());
      auto dict    = reduced_word2_dict.begin();
      while (dict != reduced_word2_dict.end()) {
        auto curr = letters[dict->first - 'a'];
        if (curr < dict->second) {
          break;
        }
        ++dict;
      }

      if (dict == reduced_word2_dict.end()) {
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
// * |1 <= words1.length, words2.length <= 10⁴|
// * |1 <= words1[i].length, words2[i].length <= 10|
// * |words1[i]| and |words2[i]| consist only of lowercase English letters.
// * All the strings of |words1| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 =
//  ["e","o"]
// Output: ["facebook","google","leetcode"]
//

LEETCODE_SOLUTION_UNITTEST(916, WordSubsets, example_1) {
  auto           solution = MakeSolution();
  vector<string> words1 = {"amazon", "apple", "facebook", "google", "leetcode"};
  vector<string> words2 = {"e", "o"};
  vector<string> expect = {"facebook", "google", "leetcode"};
  vector<string> actual = solution->wordSubsets(words1, words2);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 =
//  ["l","e"]
// Output: ["apple","google","leetcode"]
//

LEETCODE_SOLUTION_UNITTEST(916, WordSubsets, example_2) {
  auto           solution = MakeSolution();
  vector<string> words1 = {"amazon", "apple", "facebook", "google", "leetcode"};
  vector<string> words2 = {"l", "e"};
  vector<string> expect = {"apple", "google", "leetcode"};
  vector<string> actual = solution->wordSubsets(words1, words2);
  EXPECT_ANYORDER_EQ(expect, actual);
}
