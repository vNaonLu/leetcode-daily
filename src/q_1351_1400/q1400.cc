// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Construct K Palindrome Strings
//
// https://leetcode.com/problems/construct-k-palindrome-strings/
//
// Question ID: 1400
// Difficult  : Medium
// Solve Date : 2025/01/11 13:02

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1400. Construct K Palindrome Strings|:
//
// Given a string |s| and an integer |k|, return |true| if you can use all the
// characters in |s| to construct |k| palindrome strings or |false| otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(1400, ConstructKPalindromeStrings, Solution);

class Solution {
public:
  bool canConstruct(string s, int k) {
    if (s.size() < k) {
      return false;
    }

    if (s.size() == k) {
      return true;
    }

    int res = 0;
    for (auto c : s) {
      res ^= 1 << (c - 'a');
    }
    return __builtin_popcount(res) <= k;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists of lowercase English letters.
// * |1 <= k <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "annabelle", k = 2
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1400, ConstructKPalindromeStrings, example_1) {
  auto   solution = MakeSolution();
  string s        = "annabelle";
  int    k        = 2;
  bool   expect   = true;
  bool   actual   = solution->canConstruct(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "leetcode", k = 3
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1400, ConstructKPalindromeStrings, example_2) {
  auto   solution = MakeSolution();
  string s        = "leetcode";
  int    k        = 3;
  bool   expect   = false;
  bool   actual   = solution->canConstruct(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "true", k = 4
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1400, ConstructKPalindromeStrings, example_3) {
  auto   solution = MakeSolution();
  string s        = "true";
  int    k        = 4;
  bool   expect   = true;
  bool   actual   = solution->canConstruct(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
