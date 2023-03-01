// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Interleaving String
//
// https://leetcode.com/problems/interleaving-string/
//
// Question ID: 97
// Difficult  : Medium
// Solve Date : 2022/07/07 18:34

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |97. Interleaving String|:
//
// Given strings |s1|, |s2|, and |s3|, find whether |s3| is formed by an
// interleaving of |s1| and |s2|. An interleaving of two strings |s| and |t| is
// a configuration where |s| and |t| are divided into |n| and |m| substrings
// respectively, such that:
//
//  • |s = s₁ + s₂ + ... + sₙ|
//
//  • |t = t₁ + t₂ + ... + tₘ|
//
//  • ||n - m| <= 1|
//
//  • The interleaving is |s₁ + t₁ + s₂ + t₂ + s₃ + t₃ + ...| or |t₁ + s₁ + t₂ +
//  s₂ + t₃ + s₃ + ...|
// Note: |a + b| is the concatenation of strings |a| and |b|.
//

LEETCODE_BEGIN_RESOLVING(97, InterleavingString, Solution);

class Solution {
public:
  bool isInterleave(string s1, string s2, string s3) {
    if (s1.size() + s2.size() != s3.size()) {
      return false;
    }

    vector<int> dp(s2.size() + 1);
    for (int i = 0; i <= s1.size(); ++i) {
      for (int j = 0; j <= s2.size(); ++j) {
        if (i == 0 && j == 0) {
          dp[j] = true;
        } else if (i == 0) {
          dp[j] = dp[j - 1] && s2[j - 1] == s3[i + j - 1];
        } else if (j == 0) {
          dp[j] = dp[j] && s1[i - 1] == s3[i + j - 1];
        } else {
          dp[j] = (dp[j] && s1[i - 1] == s3[i + j - 1] ||
                   dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
        }
      }
    }

    return dp.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= s1.length, s2.length <= 100|
// * |0 <= s3.length <= 200|
// * |s1|, |s2|, and |s3| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
// Output: true
//
// One way to obtain s3 is:
// Split s1 into s1 = "aa" + "bc" + "c", and s2 into s2 = "dbbc" + "a".
// Interleaving the two splits, we get "aa" + "dbbc" + "bc" + "a" + "c" =
// "aadbbcbcac". Since s3 can be obtained by interleaving s1 and s2, we return
// true.

LEETCODE_SOLUTION_UNITTEST(97, InterleavingString, example_1) {
  auto   solution = MakeSolution();
  string s1       = "aabcc";
  string s2       = "dbbca";
  string s3       = "aadbbcbcac";
  bool   expect   = true;
  bool   actual   = solution->isInterleave(s1, s2, s3);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
// Output: false
//
// Notice how it is impossible to interleave s2 with any other string to obtain
// s3.

LEETCODE_SOLUTION_UNITTEST(97, InterleavingString, example_2) {
  auto   solution = MakeSolution();
  string s1       = "aabcc";
  string s2       = "dbbca";
  string s3       = "aadbbbaccc";
  bool   expect   = false;
  bool   actual   = solution->isInterleave(s1, s2, s3);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s1 = "", s2 = "", s3 = ""
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(97, InterleavingString, example_3) {
  auto   solution = MakeSolution();
  string s1       = "";
  string s2       = "";
  string s3       = "";
  bool   expect   = true;
  bool   actual   = solution->isInterleave(s1, s2, s3);
  LCD_EXPECT_EQ(expect, actual);
}
