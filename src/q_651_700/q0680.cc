// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Valid Palindrome II
//
// https://leetcode.com/problems/valid-palindrome-ii/
//
// Question ID: 680
// Difficult  : Easy
// Solve Date : 2022/04/02 16:10

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |680. Valid Palindrome II|:
//
// Given a string |s|, return |true| if the |s| can be palindrome after deleting
// at most one character from it.  
//

LEETCODE_BEGIN_RESOLVING(680, ValidPalindromeII, Solution);

class Solution {
private:
  bool is_palindrome(string &s, int l, int r) {
    while (l < r) {
      if (s[l++] != s[r--]) {
        return false;
      }
    }

    return true;
  }

public:
  bool validPalindrome(string s) {
    int l = 0, r = s.size() - 1;

    while (l < r) {
      if (s[l] != s[r]) {
        return is_palindrome(s, l, r - 1) || is_palindrome(s, l + 1, r);
      }
      ++l;
      --r;
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aba"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(680, ValidPalindromeII, example_1) {
  auto   solution = MakeSolution();
  string s        = "aba";
  bool   expect   = true;
  bool   actual   = solution->validPalindrome(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abca"
// Output: true
//
// You could delete the character 'c'.

LEETCODE_SOLUTION_UNITTEST(680, ValidPalindromeII, example_2) {
  auto   solution = MakeSolution();
  string s        = "abca";
  bool   expect   = true;
  bool   actual   = solution->validPalindrome(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "abc"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(680, ValidPalindromeII, example_3) {
  auto   solution = MakeSolution();
  string s        = "abc";
  bool   expect   = false;
  bool   actual   = solution->validPalindrome(s);
  LCD_EXPECT_EQ(expect, actual);
}
