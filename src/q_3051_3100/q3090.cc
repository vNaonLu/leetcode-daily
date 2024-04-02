// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Length Substring With Two Occurrences
//
// https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/
//
// Question ID: 3090
// Difficult  : Easy
// Solve Date : 2024/04/01 17:48

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3090. Maximum Length Substring With Two Occurrences|:
//
// Given a string |s|, return the maximum length of a substring such that it
// contains at most two occurrences of each character.
//
//

LEETCODE_BEGIN_RESOLVING(3090, MaximumLengthSubstringWithTwoOccurrences,
                         Solution);

class Solution {
public:
  int maximumLengthSubstring(string s) {
    vector<int> freq(26, 0);
    int         res = 0;
    auto        lo  = s.begin();
    auto        hi  = lo;
    while (s.end() != hi) {
      auto cur = *hi - 'a';
      ++freq[cur];
      while (freq[cur] > 2) {
        --freq[*lo++ - 'a'];
      }

      res = max<int>(res, distance(lo, ++hi));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= s.length <= 100|
// * |s| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "bcbbbcba"
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3090, MaximumLengthSubstringWithTwoOccurrences,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "bcbbbcba";
  int    expect   = 4;
  int    actual   = solution->maximumLengthSubstring(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aaaa"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3090, MaximumLengthSubstringWithTwoOccurrences,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "aaaa";
  int    expect   = 2;
  int    actual   = solution->maximumLengthSubstring(s);
  LCD_EXPECT_EQ(expect, actual);
}
