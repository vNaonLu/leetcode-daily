// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Valid Palindrome
//
// https://leetcode.com/problems/valid-palindrome/
//
// Question ID: 125
// Difficult  : Easy
// Solve Date : 2023/02/19 22:53

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |125. Valid Palindrome|:
//
// A phrase is a palindrome if, after converting all uppercase letters into
// lowercase letters and removing all non-alphanumeric characters, it reads the
// same forward and backward. Alphanumeric characters include letters and
// numbers. Given a string |s|, return |true| if it is a palindrome, or |false|
// otherwise.
//

LEETCODE_BEGIN_RESOLVING(125, ValidPalindrome, Solution);

class Solution {
public:
  bool isPalindrome(string s) {
    int lo = 0;
    int hi = s.size() - 1;
    while (lo < hi) {
      while (lo < s.size() && !(isalpha(s[lo]) || isdigit(s[lo]))) {
        ++lo;
      }
      while (hi >= 0 && !(isalpha(s[hi]) || isdigit(s[hi]))) {
        --hi;
      }
      if (lo < s.size() && hi >= 0) {
        if (tolower(s[lo]) != tolower(s[hi])) {
          return false;
        }
      }
      ++lo;
      --hi;
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 2 * 10⁵|
// * |s| consists only of printable ASCII characters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "A man, a plan, a canal: Panama"
// Output: true
//
// "amanaplanacanalpanama" is a palindrome.

LEETCODE_SOLUTION_UNITTEST(125, ValidPalindrome, example_1) {
  auto   solution = MakeSolution();
  string s        = "A man, a plan, a canal: Panama";
  bool   expect   = true;
  bool   actual   = solution->isPalindrome(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "race a car"
// Output: false
//
// "raceacar" is not a palindrome.

LEETCODE_SOLUTION_UNITTEST(125, ValidPalindrome, example_2) {
  auto   solution = MakeSolution();
  string s        = "race a car";
  bool   expect   = false;
  bool   actual   = solution->isPalindrome(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = " "
// Output: true
//
// s is an empty string "" after removing non-alphanumeric characters.
// Since an empty string reads the same forward and backward, it is a
// palindrome.

LEETCODE_SOLUTION_UNITTEST(125, ValidPalindrome, example_3) {
  auto   solution = MakeSolution();
  string s        = " ";
  bool   expect   = true;
  bool   actual   = solution->isPalindrome(s);
  LCD_EXPECT_EQ(expect, actual);
}
