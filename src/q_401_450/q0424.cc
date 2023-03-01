// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Repeating Character Replacement
//
// https://leetcode.com/problems/longest-repeating-character-replacement/
//
// Question ID: 424
// Difficult  : Medium
// Solve Date : 2022/09/04 15:37

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |424. Longest Repeating Character Replacement|:
//
// You are given a string |s| and an integer |k|. You can choose any character
// of the string and change it to any other uppercase English character. You can
// perform this operation at most |k| times. Return the length of the longest
// substring containing the same letter you can get after performing the above
// operations.
//

LEETCODE_BEGIN_RESOLVING(424, LongestRepeatingCharacterReplacement, Solution);

class Solution {
public:
  int characterReplacement(string s, int k) {
    auto lo   = s.begin();
    auto hi   = s.begin();
    auto res  = (int)0;
    auto freq = (int)0;
    auto cnt  = unordered_map<char, int>();
    while (hi != s.end()) {
      freq = max(freq, ++cnt[*hi]);
      if (distance(lo, hi + 1) - freq > k) {
        --cnt[*lo++];
      }
      res = max<int>(res, distance(lo, ++hi));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists of only uppercase English letters.
// * |0 <= k <= s.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "ABAB", k = 2
// Output: 4
//
// Replace the two 'A's with two 'B's or vice versa.

LEETCODE_SOLUTION_UNITTEST(424, LongestRepeatingCharacterReplacement,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "ABAB";
  int    k        = 2;
  int    expect   = 4;
  int    actual   = solution->characterReplacement(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "AABABBA", k = 1
// Output: 4
//
// Replace the one 'A' in the middle with 'B' and form "AABBBBA".
// The substring "BBBB" has the longest repeating letters, which is 4.

LEETCODE_SOLUTION_UNITTEST(424, LongestRepeatingCharacterReplacement,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "AABABBA";
  int    k        = 1;
  int    expect   = 4;
  int    actual   = solution->characterReplacement(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
