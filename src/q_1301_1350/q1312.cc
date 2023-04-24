// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Insertion Steps to Make a String Palindrome
//
// https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/
//
// Question ID: 1312
// Difficult  : Hard
// Solve Date : 2023/04/22 13:51

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1312. Minimum Insertion Steps to Make a String Palindrome|:
//
// Given a string |s|. In one step you can insert any character at any index of
// the string. Return the minimum number of steps to make |s| palindrome. A
// Palindrome String is one that reads the same backward as well as forward.
//
//

LEETCODE_BEGIN_RESOLVING(1312, MinimumInsertionStepsToMakeAStringPalindrome,
                         Solution);

class Solution {
public:
  int minInsertions(string s) {
    //
    return s.size() - longestPalindrome(s);
  }

private:
  int lcs(string &s1, string &s2) {
    int         n = s1.size();
    int         m = s2.size();
    vector<int> prev(m + 1, 0);
    vector<int> curr(m + 1, 0);
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        if (s1[i - 1] == s2[j - 1]) {
          curr[j] = 1 + prev[j - 1];
        } else {
          curr[j] = max(prev[j], curr[j - 1]);
        }
      }
      prev = curr;
    }
    return prev[m];
  }
  int longestPalindrome(string &s) {
    string t(s.rbegin(), s.rend());
    return lcs(s, t);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 500|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "zzazz"
// Output: 0
//
// The string "zzazz" is already palindrome we do not need any insertions.

LEETCODE_SOLUTION_UNITTEST(1312, MinimumInsertionStepsToMakeAStringPalindrome,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "zzazz";
  int    expect   = 0;
  int    actual   = solution->minInsertions(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "mbadm"
// Output: 2
//
// String can be "mbdadbm" or "mdbabdm".

LEETCODE_SOLUTION_UNITTEST(1312, MinimumInsertionStepsToMakeAStringPalindrome,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "mbadm";
  int    expect   = 2;
  int    actual   = solution->minInsertions(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "leetcode"
// Output: 5
//
// Inserting 5 characters the string becomes "leetcodocteel".

LEETCODE_SOLUTION_UNITTEST(1312, MinimumInsertionStepsToMakeAStringPalindrome,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "leetcode";
  int    expect   = 5;
  int    actual   = solution->minInsertions(s);
  LCD_EXPECT_EQ(expect, actual);
}
