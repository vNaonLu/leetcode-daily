// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the Longest Substring Containing Vowels in Even Counts
//
// https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/
//
// Question ID: 1371
// Difficult  : Medium
// Solve Date : 2024/09/15 15:42

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1371. Find the Longest Substring Containing Vowels in Even
// Counts|:
//
// Given the string |s|, return the size of the longest substring containing
// each vowel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u' must
// appear an even number of times.
//
//

LEETCODE_BEGIN_RESOLVING(1371,
                         FindTheLongestSubstringContainingVowelsInEvenCounts,
                         Solution);

class Solution {
public:
  int findTheLongestSubstring(string s) {
    vector<int> mapy(32, -2);
    mapy[0]  = -1;
    int mask = 0;
    int res  = 0;
    for (int i = 0; i < s.size(); ++i) {
      switch (s[i]) {
      case 'a':
        mask ^= 1;
        break;
      case 'e':
        mask ^= 2;
        break;
      case 'i':
        mask ^= 4;
        break;
      case 'o':
        mask ^= 8;
        break;
      case 'u':
        mask ^= 16;
        break;
      default:
        break;
      }

      int prev = mapy[mask];
      if (prev == -2) {
        mapy[mask] = i;
      } else {
        res = max(res, i - prev);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 5 x 10^5|
// * |s| contains only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "eleetminicoworoep"
// Output: 13
//

LEETCODE_SOLUTION_UNITTEST(1371,
                           FindTheLongestSubstringContainingVowelsInEvenCounts,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "eleetminicoworoep";
  int    expect   = 13;
  int    actual   = solution->findTheLongestSubstring(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "leetcodeisgreat"
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(1371,
                           FindTheLongestSubstringContainingVowelsInEvenCounts,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "leetcodeisgreat";
  int    expect   = 5;
  int    actual   = solution->findTheLongestSubstring(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "bcbcbc"
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(1371,
                           FindTheLongestSubstringContainingVowelsInEvenCounts,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "bcbcbc";
  int    expect   = 6;
  int    actual   = solution->findTheLongestSubstring(s);
  LCD_EXPECT_EQ(expect, actual);
}
