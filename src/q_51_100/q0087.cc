// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Scramble String
//
// https://leetcode.com/problems/scramble-string/
//
// Question ID: 87
// Difficult  : Hard
// Solve Date : 2022/09/29 17:22

#include <iosfwd>
#include <set>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |87. Scramble String|:
//
// We can scramble a string s to get a string t using the following algorithm:
//
//  1. If the length of the string is 1, stop.
//
//  2. If the length of the string is > 1, do the following:
//
//
//    • Split the string into two non-empty substrings at a random index, i.e.,
//    if the string is |s|, divide it to |x| and |y| where |s = x + y|.
//
//    • Randomlydecide to swap the two substrings or to keep them in the same
//    order. i.e., after this step, |s| may become |s = x + y| or |s = y + x|.
//
//    • Apply step 1 recursively on each of the two substrings |x| and |y|.
//
//
// Given two strings |s1| and |s2| of the same length, return |true| if |s2| is
// a scrambled string of |s1|, otherwise, return |false|.
//

LEETCODE_BEGIN_RESOLVING(87, ScrambleString, Solution);

class Solution {
public:
  bool isScramble(string s1, string s2) {
    auto n = s1.size();
    vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(n, vector<bool>(n, false)));

    for (auto i = 0; i < n; ++i) {
      for (auto j = 0; j < n; ++j) {
        dp[i][j][0] = s1[i] == s2[j];
      }
    }

    for (auto length = 2; length <= n; ++length) {
      for (auto i = 0; i <= n - length; ++i) {
        for (auto j = 0; j <= n - length; ++j) {
          for (auto len1 = 1; len1 < length; ++len1) {
            auto len2 = length - len1;
            dp[i][j][length - 1] =
                dp[i][j][length - 1] ||
                (dp[i][j][len1 - 1] && dp[i + len1][j + len1][len2 - 1]);
            dp[i][j][length - 1] =
                dp[i][j][length - 1] ||
                (dp[i + len1][j][len2 - 1] && dp[i][j + len2][len1 - 1]);
          }
        }
      }
    }

    return dp[0][0][n - 1];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |s1.length == s2.length|
// * |1 <= s1.length <= 30|
// * |s1| and |s2| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s1 = "great", s2 = "rgeat"
// Output: true
//
// One possible scenario applied on s1 is:
// "great" --> "gr/eat" // divide at random index.
// "gr/eat" --> "gr/eat" // random decision is not to swap the two substrings
// and keep them in order. "gr/eat" --> "g/r / e/at" // apply the same algorithm
// recursively on both substrings. divide at random index each of them. "g/r /
// e/at" --> "r/g / e/at" // random decision was to swap the first substring and
// to keep the second substring in the same order. "r/g / e/at" --> "r/g / e/
// a/t" // again apply the algorithm recursively, divide "at" to "a/t". "r/g /
// e/ a/t" --> "r/g / e/ a/t" // random decision is to keep both substrings in
// the same order. The algorithm stops now, and the result string is "rgeat"
// which is s2. As one possible scenario led s1 to be scrambled to s2, we return
// true.

LEETCODE_SOLUTION_UNITTEST(87, ScrambleString, example_1) {
  auto   solution = MakeSolution();
  string s1       = "great";
  string s2       = "rgeat";
  bool   expect   = true;
  bool   actual   = solution->isScramble(s1, s2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s1 = "abcde", s2 = "caebd"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(87, ScrambleString, example_2) {
  auto   solution = MakeSolution();
  string s1       = "abcde";
  string s2       = "caebd";
  bool   expect   = false;
  bool   actual   = solution->isScramble(s1, s2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s1 = "a", s2 = "a"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(87, ScrambleString, example_3) {
  auto   solution = MakeSolution();
  string s1       = "a";
  string s2       = "a";
  bool   expect   = true;
  bool   actual   = solution->isScramble(s1, s2);
  LCD_EXPECT_EQ(expect, actual);
}
