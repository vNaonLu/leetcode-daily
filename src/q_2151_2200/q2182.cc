// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Construct String With Repeat Limit
//
// https://leetcode.com/problems/construct-string-with-repeat-limit/
//
// Question ID: 2182
// Difficult  : Medium
// Solve Date : 2024/12/17 21:13

#include <iosfwd>
#include <queue>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2182. Construct String With Repeat Limit|:
//
// You are given a string |s| and an integer |repeatLimit|. Construct a new
// string |repeatLimitedString| using the characters of |s| such that no letter
// appears more than |repeatLimit| times in a row. You do not have to use all
// characters from |s|. Return the lexicographically largest
// |repeatLimitedString| possible. A string |a| is lexicographically larger than
// a string |b| if in the first position where |a| and |b| differ, string |a|
// has a letter that appears later in the alphabet than the corresponding letter
// in |b|. If the first |min(a.length, b.length)| characters do not differ, then
// the longer string is the lexicographically larger one.
//
//

LEETCODE_BEGIN_RESOLVING(2182, ConstructStringWithRepeatLimit, Solution);

class Solution {
public:
  string repeatLimitedString(string s, int repeatLimit) {
    using T = pair<char, int>;
    vector<int> freq(26);
    for (auto c : s) {
      ++freq[c - 'a'];
    }
    string res;
    res.reserve(s.size());
    priority_queue<T> pq;
    for (int i = 0; i < 26; ++i) {
      if (freq[i]) {
        pq.emplace('a' + i, freq[i]);
      }
    }

    while (!pq.empty()) {
      auto [c, cnt] = pq.top();
      pq.pop();

      auto r = min(repeatLimit, cnt);
      cnt -= r;
      res += string(r, c);

      if (cnt > 0) {
        if (pq.empty()) {
          break;
        }

        auto [c2, cnt2] = pq.top();
        pq.pop();

        res += c2;
        if (--cnt2 > 0) {
          pq.emplace(c2, cnt2);
        }
        pq.emplace(c, cnt);
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= repeatLimit <= s.length <= 10⁵|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "cczazcc", repeatLimit = 3
// Output: "zzcccac"
//

LEETCODE_SOLUTION_UNITTEST(2182, ConstructStringWithRepeatLimit, example_1) {
  auto   solution    = MakeSolution();
  string s           = "cczazcc";
  int    repeatLimit = 3;
  string expect      = "zzcccac";
  string actual      = solution->repeatLimitedString(s, repeatLimit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aababab", repeatLimit = 2
// Output: "bbabaa"
//

LEETCODE_SOLUTION_UNITTEST(2182, ConstructStringWithRepeatLimit, example_2) {
  auto   solution    = MakeSolution();
  string s           = "aababab";
  int    repeatLimit = 2;
  string expect      = "bbabaa";
  string actual      = solution->repeatLimitedString(s, repeatLimit);
  LCD_EXPECT_EQ(expect, actual);
}
