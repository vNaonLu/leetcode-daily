// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Palindrome
//
// https://leetcode.com/problems/longest-palindrome/
//
// Question ID: 409
// Difficult  : Easy
// Solve Date : 2021/09/24 16:11

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |409. Longest Palindrome|:
//
// Given a string |s| which consists of lowercase or uppercase letters, return
// the length of the longest palindrome that can be built with those letters.
// Letters are case sensitive, for example,  |"Aa"| is not considered a
// palindrome here.  
//

LEETCODE_BEGIN_RESOLVING(409, LongestPalindrome, Solution);

class Solution {
public:
  int longestPalindrome(string s) {
    unordered_map<char, int> cnt;
    for (const auto &c : s)
      ++cnt[c];
    int res    = 0;
    int single = 0;
    for (auto it = cnt.begin(); it != cnt.end(); ++it) {
      if (it->second % 2) {
        single = 1;
        res += it->second / 2 * 2;
      } else {
        res += it->second;
      }
    }
    return res + single;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 2000|
// * |s| consists of lowercase and/or uppercase English letters only.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abccccdd"
// Output: 7
//
// One longest palindrome that can be built is "dccaccd", whose length is 7.

LEETCODE_SOLUTION_UNITTEST(409, LongestPalindrome, example_1) {
  auto   solution = MakeSolution();
  string s        = "abccccdd";
  int    expect   = 7;
  int    actual   = solution->longestPalindrome(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "a"
// Output: 1
//
// The longest palindrome that can be built is "a", whose length is 1.

LEETCODE_SOLUTION_UNITTEST(409, LongestPalindrome, example_2) {
  auto   solution = MakeSolution();
  string s        = "a";
  int    expect   = 1;
  int    actual   = solution->longestPalindrome(s);
  LCD_EXPECT_EQ(expect, actual);
}
