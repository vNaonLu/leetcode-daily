// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Substring Without Repeating Characters
//
// https://leetcode.com/problems/longest-substring-without-repeating-characters/
//
// Question ID: 3
// Difficult  : Medium
// Solve Date : 2021/09/10 08:00

#include <array>
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3. Longest Substring Without Repeating Characters|:
//
// Given a string |s|, find the length of the longest substring without
// repeating characters.  
//

LEETCODE_BEGIN_RESOLVING(3, LongestSubstringWithoutRepeatingCharacters, Solution);

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    auto cnt = array<int, 128>();
    auto res = (int)0;
    auto beg = s.begin();
    auto it  = s.begin();
    while (it != s.end()) {
      if (++cnt[*it] > 1) {
        while (beg != it) {
          --cnt[*beg];
          if (*beg++ == *it) {
            break;
          }
        }
      }
      ++it;
      res = max<int>(res, distance(beg, it));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= s.length <= 5 * 10⁴|
// * |s| consists of English letters, digits, symbols and spaces.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abcabcbb"
// Output: 3
//
// The answer is "abc", with the length of 3.

LEETCODE_SOLUTION_UNITTEST(3, LongestSubstringWithoutRepeatingCharacters,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "abcabcbb";
  int    expect   = 3;
  int    actual   = solution->lengthOfLongestSubstring(s);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "bbbbb"
// Output: 1
//
// The answer is "b", with the length of 1.

LEETCODE_SOLUTION_UNITTEST(3, LongestSubstringWithoutRepeatingCharacters,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "bbbbb";
  int    expect   = 1;
  int    actual   = solution->lengthOfLongestSubstring(s);
  EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "pwwkew"
// Output: 3
//
// The answer is "wke", with the length of 3.
// Notice that the answer must be a substring, "pwke" is a subsequence and not a
// substring.

LEETCODE_SOLUTION_UNITTEST(3, LongestSubstringWithoutRepeatingCharacters,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "pwwkew";
  int    expect   = 3;
  int    actual   = solution->lengthOfLongestSubstring(s);
  EXPECT_EQ(expect, actual);
}
