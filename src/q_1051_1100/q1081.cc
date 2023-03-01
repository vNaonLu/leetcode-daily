// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Smallest Subsequence of Distinct Characters
//
// https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/
//
// Question ID: 1081
// Difficult  : Medium
// Solve Date : 2022/02/02 12:37

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1081. Smallest Subsequence of Distinct Characters|:
//
// Given a string |s|, return the lexicographically smallest subsequence of |s|
// that contains all the distinct characters of |s| exactly once.  
//

LEETCODE_BEGIN_RESOLVING(1081, SmallestSubsequenceOfDistinctCharacters,
                         Solution);

class Solution {
public:
  string smallestSubsequence(string s) {
    vector<int> cnt(26, 0), visited(26, 0), stk;
    for (const auto &c : s)
      ++cnt[c - 'a'];
    for (int i = 0; i < s.size(); ++i) {
      int idx = s[i] - 'a';
      --cnt[idx];
      if (visited[idx])
        continue;
      while (!stk.empty() && stk.back() > s[i] && cnt[stk.back() - 'a'] > 0) {
        visited[stk.back() - 'a'] = false;
        stk.pop_back();
      }
      stk.push_back(s[i]);
      visited[idx] = true;
    }
    return string(stk.begin(), stk.end());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 1000|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "bcabc"
// Output: "abc"
//

LEETCODE_SOLUTION_UNITTEST(1081, SmallestSubsequenceOfDistinctCharacters,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "bcabc";
  string expect   = "abc";
  string actual   = solution->smallestSubsequence(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "cbacdcbc"
// Output: "acdb"
//

LEETCODE_SOLUTION_UNITTEST(1081, SmallestSubsequenceOfDistinctCharacters,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "cbacdcbc";
  string expect   = "acdb";
  string actual   = solution->smallestSubsequence(s);
  LCD_EXPECT_EQ(expect, actual);
}
