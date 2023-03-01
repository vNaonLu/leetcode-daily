// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Valid Anagram
//
// https://leetcode.com/problems/valid-anagram/
//
// Question ID: 242
// Difficult  : Easy
// Solve Date : 2021/09/10 08:00

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |242. Valid Anagram|:
//
// Given two strings |s| and |t|, return |true| if |t| is an anagram of |s|, and
// |false| otherwise. An Anagram is a word or phrase formed by rearranging the
// letters of a different word or phrase, typically using all the original
// letters exactly once.  
//

LEETCODE_BEGIN_RESOLVING(242, ValidAnagram, Solution);

class Solution {
public:
  bool isAnagram(string s, string t) {
    vector<int> cnt(26, 0);
    for (auto c : s) {
      ++cnt[c - 'a'];
    }
    for (auto c : t) {
      --cnt[c - 'a'];
    }

    for (auto c : cnt) {
      if (c != 0) {
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
// * |1 <= s.length, t.length <= 5 * 10⁴|
// * |s| and |t| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "anagram", t = "nagaram"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(242, ValidAnagram, example_1) {
  auto   solution = MakeSolution();
  string s        = "anagram";
  string t        = "nagaram";
  bool   expect   = true;
  bool   actual   = solution->isAnagram(s, t);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "rat", t = "car"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(242, ValidAnagram, example_2) {
  auto   solution = MakeSolution();
  string s        = "rat";
  string t        = "car";
  bool   expect   = false;
  bool   actual   = solution->isAnagram(s, t);
  EXPECT_EQ(expect, actual);
}
