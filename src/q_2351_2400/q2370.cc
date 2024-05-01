// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Longest Ideal Subsequence
//
// https://leetcode.com/problems/longest-ideal-subsequence/
//
// Question ID: 2370
// Difficult  : Medium
// Solve Date : 2024/04/25 19:42

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2370. Longest Ideal Subsequence|:
//
// You are given a string |s| consisting of lowercase letters and an integer
// |k|. We call a string |t| ideal if the following conditions are satisfied:
//
//  • |t| is a subsequence of the string |s|.
//
//  • The absolute difference in the alphabet order of every two adjacent
//  letters in |t| is less than or equal to |k|.
// Return the length of the longest ideal string.
// A subsequence is a string that can be derived from another string by deleting
// some or no characters without changing the order of the remaining characters.
// Note that the alphabet order is not cyclic. For example, the absolute
// difference in the alphabet order of |'a'| and |'z'| is |25|, not |1|.
//
//

LEETCODE_BEGIN_RESOLVING(2370, LongestIdealSubsequence, Solution);

class Solution {
public:
  int longestIdealString(string s, int k) {
    vector<int> seq(26);
    for (auto c : s) {
      int i  = c - 'a';
      int j0 = max(0, i - k);
      int j1 = min(i + k, 25);
      for (int j = j0; j <= j1; ++j) {
        seq[i] = max(seq[i], seq[j]);
      }
      ++seq[i];
    }
    return *max_element(seq.begin(), seq.end());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |0 <= k <= 25|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "acfgbd", k = 2
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2370, LongestIdealSubsequence, example_1) {
  auto   solution = MakeSolution();
  string s        = "acfgbd";
  int    k        = 2;
  int    expect   = 4;
  int    actual   = solution->longestIdealString(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcd", k = 3
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2370, LongestIdealSubsequence, example_2) {
  auto   solution = MakeSolution();
  string s        = "abcd";
  int    k        = 3;
  int    expect   = 4;
  int    actual   = solution->longestIdealString(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
