// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Longest Subsequence Repeated k Times
//
// https://leetcode.com/problems/longest-subsequence-repeated-k-times/
//
// Question ID: 2014
// Difficult  : Hard
// Solve Date : 2025/06/27 21:26

#include <iosfwd>
#include <queue>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2014. Longest Subsequence Repeated k Times|:
//
// You are given a string |s| of length |n|, and an integer |k|. You are tasked
// to find the longest subsequence repeated |k| times in string |s|. A
// subsequence is a string that can be derived from another string by deleting
// some or no characters without changing the order of the remaining characters.
// A subsequence |seq| is repeated |k| times in the string |s| if |seq * k| is a
// subsequence of |s|, where |seq * k| represents a string constructed by
// concatenating |seq| |k| times.
//
//  • For example, |"bba"| is repeated |2| times in the string |"bababcba"|,
//  because the string |"bbabba"|, constructed by concatenating |"bba"| |2|
//  times, is a subsequence of the string |"bababcba"|.
// Return the longest subsequence repeated |k| times in string |s|. If multiple
// such subsequences are found, return the lexicographically largest one. If
// there is no such subsequence, return an empty string.
//
//

LEETCODE_BEGIN_RESOLVING(2014, LongestSubsequenceRepeatedKTimes, Solution);

class Solution {
public:
  string longestSubsequenceRepeatedK(string s, int k) {
    string        result = "";
    queue<string> q;
    q.push("");
    while (!q.empty()) {
      string curr = q.front();
      q.pop();
      for (char ch = 'a'; ch <= 'z'; ++ch) {
        string next = curr + ch;
        if (isK(next, s, k)) {
          result = next;
          q.push(next);
        }
      }
    }
    return result;
  }

  bool isK(string sub, string t, int k) {
    int count = 0, i = 0;
    for (char ch : t) {
      if (ch == sub[i]) {
        if (++i == sub.size()) {
          i = 0;
          if (++count == k)
            return true;
        }
      }
    }
    return false;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == s.length|
// * |2 <= n, k <= 2000|
// * |2 <= n < k * 8|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "letsleetcode", k = 2
// Output: "let"
//

LEETCODE_SOLUTION_UNITTEST(2014, LongestSubsequenceRepeatedKTimes, example_1) {
  auto   solution = MakeSolution();
  string s        = "letsleetcode";
  int    k        = 2;
  string expect   = "let";
  string actual   = solution->longestSubsequenceRepeatedK(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "bb", k = 2
// Output: "b"
//

LEETCODE_SOLUTION_UNITTEST(2014, LongestSubsequenceRepeatedKTimes, example_2) {
  auto   solution = MakeSolution();
  string s        = "bb";
  int    k        = 2;
  string expect   = "b";
  string actual   = solution->longestSubsequenceRepeatedK(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "ab", k = 2
// Output: ""
//

LEETCODE_SOLUTION_UNITTEST(2014, LongestSubsequenceRepeatedKTimes, example_3) {
  auto   solution = MakeSolution();
  string s        = "ab";
  int    k        = 2;
  string expect   = "";
  string actual   = solution->longestSubsequenceRepeatedK(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
