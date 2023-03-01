// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find All Anagrams in a String
//
// https://leetcode.com/problems/find-all-anagrams-in-a-string/
//
// Question ID: 438
// Difficult  : Medium
// Solve Date : 2021/09/23 08:00

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |438. Find All Anagrams in a String|:
//
// Given two strings |s| and |p|, return an array of all the start indices of
// |p|'s anagrams in |s|. You may return the answer in any order. An Anagram is
// a word or phrase formed by rearranging the letters of a different word or
// phrase, typically using all the original letters exactly once.  
//

LEETCODE_BEGIN_RESOLVING(438, FindAllAnagramsInAString, Solution);

class Solution {
public:
  vector<int> findAnagrams(string s, string p) {
    auto res = vector<int>();
    auto cnt = vector<int>(26, 0);
    auto n   = (int)s.size();
    auto m   = (int)p.size();
    if (m <= n) {
      for (auto c : p) {
        ++cnt[c - 'a'];
      }

      auto lo = 0;
      auto hi = 0;
      auto tg = m;
      while (hi < m) {
        if (cnt[s[hi++] - 'a']-- > 0) {
          --tg;
        }
      }
      if (tg == 0) {
        res.emplace_back(lo);
      }

      while (hi < n) {
        if (cnt[s[lo++] - 'a']++ >= 0) {
          ++tg;
        }
        if (cnt[s[hi++] - 'a']-- > 0) {
          --tg;
        }
        if (tg == 0) {
          res.emplace_back(lo);
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
// * |1 <= s.length, p.length <= 3 * 10⁴|
// * |s| and |p| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "cbaebabacd", p = "abc"
// Output: [0,6]
//
// The substring with start index = 0 is "cba", which is an anagram of "abc".
// The substring with start index = 6 is "bac", which is an anagram of "abc".

LEETCODE_SOLUTION_UNITTEST(438, FindAllAnagramsInAString, example_1) {
  auto        solution = MakeSolution();
  string      s        = "cbaebabacd";
  string      p        = "abc";
  vector<int> expect   = {0, 6};
  vector<int> actual   = solution->findAnagrams(s, p);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abab", p = "ab"
// Output: [0,1,2]
//
// The substring with start index = 0 is "ab", which is an anagram of "ab".
// The substring with start index = 1 is "ba", which is an anagram of "ab".
// The substring with start index = 2 is "ab", which is an anagram of "ab".

LEETCODE_SOLUTION_UNITTEST(438, FindAllAnagramsInAString, example_2) {
  auto        solution = MakeSolution();
  string      s        = "abab";
  string      p        = "ab";
  vector<int> expect   = {0, 1, 2};
  vector<int> actual   = solution->findAnagrams(s, p);
  EXPECT_ANYORDER_EQ(expect, actual);
}
