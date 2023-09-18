// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Substrings of Size Three with Distinct Characters
//
// https://leetcode.com/problems/substrings-of-size-three-with-distinct-characters/
//
// Question ID: 1876
// Difficult  : Easy
// Solve Date : 2023/09/15 22:50

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1876. Substrings of Size Three with Distinct Characters|:
//
// A string is good if there are no repeated characters.
// Given a string |s|​​​​​, return the number of good substrings of
// length three in |s|​​​​​​. Note that if there are multiple
// occurrences of the same substring, every occurrence should be counted. A
// substring is a contiguous sequence of characters in a string.
//
//

LEETCODE_BEGIN_RESOLVING(1876, SubstringsOfSizeThreeWithDistinctCharacters,
                         Solution);

class Solution {
public:
  int countGoodSubstrings(string s) {
    int res = 0;
    int n   = s.size();
    if (n < 3) {
      return 0;
    }

    for (int i = 0; i < n - 2; ++i) {
      string v = s.substr(i, 3);
      if (v[0] != v[1] && v[0] != v[2] && v[1] != v[2]) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s|​​​​​​ consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "xyzzaz"
// Output: 1
//
// There are 4 substrings of size 3: "xyz", "yzz", "zza", and "zaz".
// The only good substring of length 3 is "xyz".

LEETCODE_SOLUTION_UNITTEST(1876, SubstringsOfSizeThreeWithDistinctCharacters,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "xyzzaz";
  int    expect   = 1;
  int    actual   = solution->countGoodSubstrings(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aababcabc"
// Output: 4
//
// There are 7 substrings of size 3: "aab", "aba", "bab", "abc", "bca", "cab",
// and "abc". The good substrings are "abc", "bca", "cab", and "abc".

LEETCODE_SOLUTION_UNITTEST(1876, SubstringsOfSizeThreeWithDistinctCharacters,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "aababcabc";
  int    expect   = 4;
  int    actual   = solution->countGoodSubstrings(s);
  LCD_EXPECT_EQ(expect, actual);
}
