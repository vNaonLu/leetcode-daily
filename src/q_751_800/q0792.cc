// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Matching Subsequences
//
// https://leetcode.com/problems/number-of-matching-subsequences/
//
// Question ID: 792
// Difficult  : Medium
// Solve Date : 2022/07/21 01:00

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |792. Number of Matching Subsequences|:
//
// Given a string |s| and an array of strings |words|, return the number of
// |words[i]| that is a subsequence of |s|. A subsequence of a string is a new
// string generated from the original string with some characters (can be none)
// deleted without changing the relative order of the remaining characters.
//
//  • For example, |"ace"| is a subsequence of |"abcde"|.
//

LEETCODE_BEGIN_RESOLVING(792, NumberOfMatchingSubsequences, Solution);

class Solution {
public:
  int numMatchingSubseq(string s, vector<string> &words) {
    vector<vector<int>> dict(26);
    for (size_t i = 0; i < s.size(); ++i) {
      dict[s[i] - 'a'].emplace_back(i);
    }

    int res = 0;
    for (auto &w : words) {
      int  curr_idx = -1;
      auto it       = w.begin();
      while (it != w.end()) {
        auto &d    = dict[*it - 'a'];
        auto  find = upper_bound(d.begin(), d.end(), curr_idx);
        if (find == d.end()) {
          break;
        } else {
          ++it;
          curr_idx = *find;
        }
      }

      if (it == w.end()) {
        ++res;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 5 * 10⁴|
// * |1 <= words.length <= 5000|
// * |1 <= words[i].length <= 50|
// * |s| and |words[i]| consist of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abcde", words = ["a","bb","acd","ace"]
// Output: 3
//
// There are three strings in words that are a subsequence of s: "a", "acd",
// "ace".

LEETCODE_SOLUTION_UNITTEST(792, NumberOfMatchingSubsequences, example_1) {
  auto           solution = MakeSolution();
  string         s        = "abcde";
  vector<string> words    = {"a", "bb", "acd", "ace"};
  int            expect   = 3;
  int            actual   = solution->numMatchingSubseq(s, words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(792, NumberOfMatchingSubsequences, example_2) {
  auto           solution = MakeSolution();
  string         s        = "dsahjpjauf";
  vector<string> words    = {"ahjpjau", "ja", "ahbwzgqnuk", "tnmlanowax"};
  int            expect   = 2;
  int            actual   = solution->numMatchingSubseq(s, words);
  LCD_EXPECT_EQ(expect, actual);
}
