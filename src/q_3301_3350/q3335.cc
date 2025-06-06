// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Total Characters in String After Transformations I
//
// https://leetcode.com/problems/total-characters-in-string-after-transformations-i/
//
// Question ID: 3335
// Difficult  : Medium
// Solve Date : 2025/05/13 16:35

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3335. Total Characters in String After Transformations I|:
//
// You are given a string |s| and an integer |t|, representing the number of
// transformations to perform. In one transformation, every character in |s| is
// replaced according to the following rules:
//
//  • If the character is |'z'|, replace it with the string |"ab"|.
//
//  • Otherwise, replace it with the next character in the alphabet. For
//  example, |'a'| is replaced with |'b'|, |'b'| is replaced with |'c'|, and so
//  on.
// Return the length of the resulting string after exactly |t| transformations.
// Since the answer may be very large, return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(3335, TotalCharactersInStringAfterTransformationsI,
                         Solution);

class Solution {
public:
  int lengthAfterTransformations(string s, int t) {
    vector<int> dp(t + 26, 1);
    for (int i = 26; i < t + 26; ++i) {
      dp[i] = (dp[i - 26] + dp[i - 26 + 1]) % kMod;
    }
    int res = 0;
    for (auto c : s) {
      res = (res + dp[c - 'a' + t]) % kMod;
    }
    return res;
  }

private:
  constexpr static int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists only of lowercase English letters.
// * |1 <= t <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abcyy", t = 2
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(3335, TotalCharactersInStringAfterTransformationsI,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "abcyy";
  int    t        = 2;
  int    expect   = 7;
  int    actual   = solution->lengthAfterTransformations(s, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "azbk", t = 1
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3335, TotalCharactersInStringAfterTransformationsI,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "azbk";
  int    t        = 1;
  int    expect   = 5;
  int    actual   = solution->lengthAfterTransformations(s, t);
  LCD_EXPECT_EQ(expect, actual);
}
