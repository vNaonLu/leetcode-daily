// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove Duplicate Letters
//
// https://leetcode.com/problems/remove-duplicate-letters/
//
// Question ID: 316
// Difficult  : Medium
// Solve Date : 2022/03/18 18:14

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |316. Remove Duplicate Letters|:
//
// Given a string |s|, remove duplicate letters so that every letter appears
// once and only once. You must make sure your result is the smallest in
// lexicographical order among all possible results.  
//

LEETCODE_BEGIN_RESOLVING(316, RemoveDuplicateLetters, Solution);

class Solution {
public:
  string removeDuplicateLetters(string s) {
    vector<int> cnt(26, 0), visit(26, 0);

    string res;
    for (auto const &c : s) {
      ++cnt[c - 'a'];
    }

    for (auto const &c : s) {
      int idx = c - 'a';
      --cnt[idx];

      if (!visit[idx]) {
        while (res.size() > 0 && res.back() > c && cnt[res.back() - 'a'] > 0) {
          visit[res.back() - 'a'] = 0;
          res.pop_back();
        }

        res += c;
        visit[idx] = 1;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁴|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "bcabc"
// Output: "abc"
//

LEETCODE_SOLUTION_UNITTEST(316, RemoveDuplicateLetters, example_1) {
  auto   solution = MakeSolution();
  string s        = "bcabc";
  string expect   = "abc";
  string actual   = solution->removeDuplicateLetters(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "cbacdcbc"
// Output: "acdb"
//

LEETCODE_SOLUTION_UNITTEST(316, RemoveDuplicateLetters, example_2) {
  auto   solution = MakeSolution();
  string s        = "cbacdcbc";
  string expect   = "acdb";
  string actual   = solution->removeDuplicateLetters(s);
  LCD_EXPECT_EQ(expect, actual);
}
