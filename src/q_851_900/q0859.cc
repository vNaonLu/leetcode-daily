// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Buddy Strings
//
// https://leetcode.com/problems/buddy-strings/
//
// Question ID: 859
// Difficult  : Easy
// Solve Date : 2022/11/21 20:19

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |859. Buddy Strings|:
//
// Given two strings |s| and |goal|, return |true| if you can swap two letters
// in |s| so the result is equal to |goal|, otherwise, return |false|. Swapping
// letters is defined as taking two indices |i| and |j| (0-indexed) such that |i
// != j| and swapping the characters at |s[i]| and |s[j]|.
//
//  • For example, swapping at indices |0| and |2| in |"abcd"| results in
//  |"cbad"|.
//

LEETCODE_BEGIN_RESOLVING(859, BuddyStrings, Solution);

class Solution {
public:
  bool buddyStrings(string s, string goal) {
    if (s.size() != goal.size()) {
      return false;
    }
    auto cnt1 = vector<int>(26, 0);
    auto cnt2 = vector<int>(26, 0);
    auto diff = (int)0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] != goal[i]) {
        ++diff;
      }
      ++cnt1[s[i] - 'a'];
      ++cnt2[goal[i] - 'a'];
    }

    auto all_unique = true;
    for (int i = 0; i < cnt1.size(); ++i) {
      if (cnt1[i] != cnt2[i]) {
        return false;
      }
      if (cnt1[i] > 1) {
        all_unique = false;
      }
    }

    return diff == 2 || (diff == 0 && !all_unique);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length, goal.length <= 2 * 10⁴|
// * |s| and |goal| consist of lowercase letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "ab", goal = "ba"
// Output: true
//
// You can swap s[0] = 'a' and s[1] = 'b' to get "ba", which is equal to goal.

LEETCODE_SOLUTION_UNITTEST(859, BuddyStrings, example_1) {
  auto   solution = MakeSolution();
  string s        = "ab";
  string goal     = "ba";
  bool   expect   = true;
  bool   actual   = solution->buddyStrings(s, goal);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "ab", goal = "ab"
// Output: false
//
// The only letters you can swap are s[0] = 'a' and s[1] = 'b', which results in
// "ba" != goal.

LEETCODE_SOLUTION_UNITTEST(859, BuddyStrings, example_2) {
  auto   solution = MakeSolution();
  string s        = "ab";
  string goal     = "ab";
  bool   expect   = false;
  bool   actual   = solution->buddyStrings(s, goal);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "aa", goal = "aa"
// Output: true
//
// You can swap s[0] = 'a' and s[1] = 'a' to get "aa", which is equal to goal.

LEETCODE_SOLUTION_UNITTEST(859, BuddyStrings, example_3) {
  auto   solution = MakeSolution();
  string s        = "aa";
  string goal     = "aa";
  bool   expect   = true;
  bool   actual   = solution->buddyStrings(s, goal);
  LCD_EXPECT_EQ(expect, actual);
}
