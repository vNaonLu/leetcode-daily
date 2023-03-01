// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Isomorphic Strings
//
// https://leetcode.com/problems/isomorphic-strings/
//
// Question ID: 205
// Difficult  : Easy
// Solve Date : 2022/08/25 18:23

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |205. Isomorphic Strings|:
//
// Given two strings |s| and |t|, determine if they are isomorphic.
// Two strings |s| and |t| are isomorphic if the characters in |s| can be
// replaced to get |t|. All occurrences of a character must be replaced with
// another character while preserving the order of characters. No two characters
// may map to the same character, but a character may map to itself.
//

LEETCODE_BEGIN_RESOLVING(205, IsomorphicStrings, Solution);

class Solution {
private:
  class Dictionary {
  private:
    int                      it;
    unordered_map<char, int> mp;

  public:
    Dictionary() : it{0} {}

    int get(char c) {
      auto find = mp.find(c);
      if (find == mp.end()) {
        return mp[c] = ++it;
      }
      return find->second;
    }
  };

public:
  bool isIsomorphic(string s, string t) {
    if (s.size() != t.size()) {
      return false;
    }
    auto dict_s = Dictionary{};
    auto dict_t = Dictionary{};
    auto sbeg   = s.begin();
    auto tbeg   = t.begin();
    while (sbeg != s.end()) {
      if (dict_s.get(*sbeg++) != dict_t.get(*tbeg++)) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 5 * 10⁴|
// * |t.length == s.length|
// * |s| and |t| consist of any valid ascii character.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "egg", t = "add"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(205, IsomorphicStrings, example_1) {
  auto   solution = MakeSolution();
  string s        = "egg";
  string t        = "add";
  bool   expect   = true;
  bool   actual   = solution->isIsomorphic(s, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "foo", t = "bar"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(205, IsomorphicStrings, example_2) {
  auto   solution = MakeSolution();
  string s        = "foo";
  string t        = "bar";
  bool   expect   = false;
  bool   actual   = solution->isIsomorphic(s, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "paper", t = "title"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(205, IsomorphicStrings, example_3) {
  auto   solution = MakeSolution();
  string s        = "paper";
  string t        = "title";
  bool   expect   = true;
  bool   actual   = solution->isIsomorphic(s, t);
  LCD_EXPECT_EQ(expect, actual);
}
