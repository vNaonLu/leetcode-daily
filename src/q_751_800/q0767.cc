// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reorganize String
//
// https://leetcode.com/problems/reorganize-string/
//
// Question ID: 767
// Difficult  : Medium
// Solve Date : 2022/02/10 19:04

#include <iosfwd>
#include <queue>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |767. Reorganize String|:
//
// Given a string |s|, rearrange the characters of |s| so that any two adjacent
// characters are not the same. Return any possible rearrangement of |s| or
// return |""| if not possible.  
//

LEETCODE_BEGIN_RESOLVING(767, ReorganizeString, Solution);

class Solution {
public:
  string reorganizeString(string s) {
    vector<int> cnt(26, 0);
    auto        comp = [](const pair<int, int> &x, const pair<int, int> &y) {
      return x.second < y.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> q(
        comp);
    for (const auto &c : s)
      ++cnt[c - 'a'];
    for (int i = 0; i < cnt.size(); ++i) {
      if (cnt[i] != 0) {
        q.emplace(i, cnt[i]);
      }
    }
    string res;
    while (!q.empty()) {
      auto [c, cnt] = q.top();
      q.pop();
      if (c != res.back() - 'a') {
        res.push_back(c + 'a');
        if (--cnt != 0)
          q.emplace(c, cnt);
      } else {
        if (q.empty())
          return "";
        auto [next, next_cnt] = q.top();
        q.pop();
        res.push_back(next + 'a');
        if (--next_cnt != 0)
          q.emplace(next, next_cnt);
        q.emplace(c, cnt);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 500|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aab"
// Output: "aba"
//

LEETCODE_SOLUTION_UNITTEST(767, ReorganizeString, example_1) {
  auto   solution = MakeSolution();
  string s        = "aab";
  string expect   = "aba";
  string actual   = solution->reorganizeString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aaab"
// Output: ""
//

LEETCODE_SOLUTION_UNITTEST(767, ReorganizeString, example_2) {
  auto   solution = MakeSolution();
  string s        = "aaab";
  string expect   = "";
  string actual   = solution->reorganizeString(s);
  LCD_EXPECT_EQ(expect, actual);
}
