// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Break a Palindrome
//
// https://leetcode.com/problems/break-a-palindrome/
//
// Question ID: 1328
// Difficult  : Medium
// Solve Date : 2021/09/23 08:00

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1328. Break a Palindrome|:
//
// Given a palindromic string of lowercase English letters |palindrome|, replace
// exactly one character with any lowercase English letter so that the resulting
// string is not a palindrome and that it is the lexicographically smallest one
// possible. Return the resulting string. If there is no way to replace a
// character to make it not a palindrome, return an empty string. A string |a|
// is lexicographically smaller than a string |b| (of the same length) if in the
// first position where |a| and |b| differ, |a| has a character strictly smaller
// than the corresponding character in |b|. For example, |"abcc"| is
// lexicographically smaller than |"abcd"| because the first position they
// differ is at the fourth character, and |'c'| is smaller than |'d'|.  
//

LEETCODE_BEGIN_RESOLVING(1328, BreakAPalindrome, Solution);

class Solution {
public:
  string breakPalindrome(string palindrome) {
    if (palindrome.empty())
      return "";
    if (palindrome.size() == 1)
      return "";
    for (int i = 0; i < palindrome.size() / 2; ++i) {
      if (palindrome[i] != 'a') {
        palindrome[i] = 'a';
        break;
      }
      if (i == palindrome.size() / 2 - 1)
        palindrome[palindrome.size() - 1] = 'b';
    }
    return palindrome;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= palindrome.length <= 1000|
// * |palindrome| consists of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: palindrome = "abccba"
// Output: "aaccba"
//
// There are many ways to make "abccba" not a palindrome, such as "zbccba",
// "aaccba", and "abacba". Of all the ways, "aaccba" is the lexicographically
// smallest.

LEETCODE_SOLUTION_UNITTEST(1328, BreakAPalindrome, example_1) {
  auto   solution   = MakeSolution();
  string palindrome = "abccba";
  string expect     = "aaccba";
  string actual     = solution->breakPalindrome(palindrome);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: palindrome = "a"
// Output: ""
//
// There is no way to replace a single character to make "a" not a palindrome,
// so return an empty string.

LEETCODE_SOLUTION_UNITTEST(1328, BreakAPalindrome, example_2) {
  auto   solution   = MakeSolution();
  string palindrome = "a";
  string expect     = "";
  string actual     = solution->breakPalindrome(palindrome);
  LCD_EXPECT_EQ(expect, actual);
}
