// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Binary Subsequence Less Than or Equal to K
//
// https://leetcode.com/problems/longest-binary-subsequence-less-than-or-equal-to-k/
//
// Question ID: 2311
// Difficult  : Medium
// Solve Date : 2022/08/03 18:50

#include <cmath>
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2311. Longest Binary Subsequence Less Than or Equal to K|:
//
// You are given a binary string |s| and a positive integer |k|.
// Return the length of the longest subsequence of |s| that makes up a binary
// number less than or equal to |k|. Note:
//
//  • The subsequence can contain leading zeroes.
//
//  • The empty string is considered to be equal to |0|.
//
//  • A subsequence is a string that can be derived from another string by
//  deleting some or no characters without changing the order of the remaining
//  characters.
//

LEETCODE_BEGIN_RESOLVING(2311, LongestBinarySubsequenceLessThanOrEqualToK,
                         Solution);

class Solution {
public:
  int longestSubsequence(string s, int k) {
    auto res   = 0;
    auto curr  = 0;
    auto digit = 0;
    auto it    = s.rbegin();

    while (it != s.rend()) {
      if (*it++ == '0') {
        ++res;
      } else {
        if (curr + pow(2, digit) <= k) {
          curr += pow(2, digit);
          ++res;
        }
      }
      ++digit;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 1000|
// * |s[i]| is either |'0'| or |'1'|.
// * |1 <= k <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "1001010", k = 5
// Output: 5
//
// The longest subsequence of s that makes up a binary number less than or equal
// to 5 is "00010", as this number is equal to 2 in decimal. Note that "00100"
// and "00101" are also possible, which are equal to 4 and 5 in decimal,
// respectively. The length of this subsequence is 5, so 5 is returned.

LEETCODE_SOLUTION_UNITTEST(2311, LongestBinarySubsequenceLessThanOrEqualToK,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "1001010";
  int    k        = 5;
  int    expect   = 5;
  int    actual   = solution->longestSubsequence(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "00101001", k = 1
// Output: 6
//
// "000001" is the longest subsequence of s that makes up a binary number less
// than or equal to 1, as this number is equal to 1 in decimal. The length of
// this subsequence is 6, so 6 is returned.

LEETCODE_SOLUTION_UNITTEST(2311, LongestBinarySubsequenceLessThanOrEqualToK,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "00101001";
  int    k        = 1;
  int    expect   = 6;
  int    actual   = solution->longestSubsequence(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
