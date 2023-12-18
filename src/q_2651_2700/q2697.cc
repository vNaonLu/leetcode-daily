// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Lexicographically Smallest Palindrome
//
// https://leetcode.com/problems/lexicographically-smallest-palindrome/
//
// Question ID: 2697
// Difficult  : Easy
// Solve Date : 2023/12/13 19:02

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2697. Lexicographically Smallest Palindrome|:
//
// You are given a string |s| consisting of lowercase English letters, and you
// are allowed to perform operations on it. In one operation, you can replace a
// character in |s| with another lowercase English letter. Your task is to make
// |s| a palindrome with the minimum number of operations possible. If there are
// multiple palindromes that can be made using the minimum number of operations,
// make the lexicographically smallest one. A string |a| is lexicographically
// smaller than a string |b| (of the same length) if in the first position where
// |a| and |b| differ, string |a| has a letter that appears earlier in the
// alphabet than the corresponding letter in |b|. Return the resulting
// palindrome string.
//
//

LEETCODE_BEGIN_RESOLVING(2697, LexicographicallySmallestPalindrome, Solution);

class Solution {
public:
  string makeSmallestPalindrome(string s) {
    int i = 0;
    int j = s.size() - 1;
    while (i < j) {
      if (s[i] < s[j]) {
        s[j--] = s[i++];
      } else {
        s[i++] = s[j--];
      }
    }
    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 1000|
// * |s| consists of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "egcfe"
// Output: "efcfe"
//
// The minimum number of operations to make "egcfe" a palindrome is 1, and the
// lexicographically smallest palindrome string we can get by modifying one
// character is "efcfe", by changing 'g'.

LEETCODE_SOLUTION_UNITTEST(2697, LexicographicallySmallestPalindrome,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "egcfe";
  string expect   = "efcfe";
  string actual   = solution->makeSmallestPalindrome(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcd"
// Output: "abba"
//
// The minimum number of operations to make "abcd" a palindrome is 2, and the
// lexicographically smallest palindrome string we can get by modifying two
// characters is "abba".

LEETCODE_SOLUTION_UNITTEST(2697, LexicographicallySmallestPalindrome,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "abcd";
  string expect   = "abba";
  string actual   = solution->makeSmallestPalindrome(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "seven"
// Output: "neven"
//
// The minimum number of operations to make "seven" a palindrome is 1, and the
// lexicographically smallest palindrome string we can get by modifying one
// character is "neven".

LEETCODE_SOLUTION_UNITTEST(2697, LexicographicallySmallestPalindrome,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "seven";
  string expect   = "neven";
  string actual   = solution->makeSmallestPalindrome(s);
  LCD_EXPECT_EQ(expect, actual);
}
