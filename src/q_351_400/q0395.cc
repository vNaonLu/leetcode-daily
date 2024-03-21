// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Longest Substring with At Least K Repeating Characters
//
// https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/
//
// Question ID: 395
// Difficult  : Medium
// Solve Date : 2024/03/21 20:27

#include <iosfwd>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |395. Longest Substring with At Least K Repeating Characters|:
//
// Given a string |s| and an integer |k|, return the length of the longest
// substring of |s| such that the frequency of each character in this substring
// is greater than or equal to |k|. if no such substring exists, return 0.
//
//

LEETCODE_BEGIN_RESOLVING(395, LongestSubstringWithAtLeastKRepeatingCharacters,
                         Solution);

class Solution {
public:
  int longestSubstring(string s, int k) {
    int                      res = 0;
    int                      n   = s.size();
    unordered_map<char, int> counter;
    for (int i = 1; i <= 26; ++i) {
      counter.clear();
      int lo = 0;
      int c  = 0;
      for (int hi = 0; hi < n; ++hi) {
        ++counter[s[hi]];

        if (counter[s[hi]] == k) {
          ++c;
        }

        while (counter.size() > i) {
          if (counter[s[lo]] == k) {
            --c;
          }
          --counter[s[lo]];
          if (counter[s[lo]] == 0) {
            counter.erase(s[lo]);
          }
          ++lo;
        }

        if (c == i) {
          res = max(res, hi - lo + 1);
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁴|
// * |s| consists of only lowercase English letters.
// * |1 <= k <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aaabb", k = 3
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(395, LongestSubstringWithAtLeastKRepeatingCharacters,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "aaabb";
  int    k        = 3;
  int    expect   = 3;
  int    actual   = solution->longestSubstring(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "ababbc", k = 2
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(395, LongestSubstringWithAtLeastKRepeatingCharacters,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "ababbc";
  int    k        = 2;
  int    expect   = 5;
  int    actual   = solution->longestSubstring(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
