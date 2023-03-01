// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Duplicate Substring
//
// https://leetcode.com/problems/longest-duplicate-substring/
//
// Question ID: 1044
// Difficult  : Hard
// Solve Date : 2021/10/30 14:49

#include <deque>
#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1044. Longest Duplicate Substring|:
//
// Given a string |s|, consider all duplicated substrings: (contiguous)
// substrings of s that occur 2 or more times. The occurrences may overlap.
// Return any duplicated substring that has the longest possible length. If |s|
// does not have a duplicated substring, the answer is |""|.  
//

LEETCODE_BEGIN_RESOLVING(1044, LongestDuplicateSubstring, Solution);

class Solution {
public:
  string longestDupSubstring(string s) {
    int                             begin = 0, length = 0;
    int                             n = s.size();
    unordered_map<char, deque<int>> hash;
    for (int i = 0; i < n; ++i)
      hash[s[i]].emplace_back(i);
    for (int i = 0; i < n; ++i) {
      hash[s[i]].pop_front();
      for (auto it : hash[s[i]]) {
        int j = 0;
        while (i + j < n && it + j < n && s[i + j] == s[it + j])
          ++j;
        if (j > length) {
          begin  = i;
          length = j;
        }
        if (j == n - i - 1)
          return s.substr(begin, length);
      }
    }
    return length == 0 ? "" : s.substr(begin, length);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= s.length <= 3 * 10⁴|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "banana"
// Output: "ana"
//

LEETCODE_SOLUTION_UNITTEST(1044, LongestDuplicateSubstring, example_1) {
  auto   solution = MakeSolution();
  string s        = "banana";
  string expect   = "ana";
  string actual   = solution->longestDupSubstring(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcd"
// Output: ""
//

LEETCODE_SOLUTION_UNITTEST(1044, LongestDuplicateSubstring, example_2) {
  auto   solution = MakeSolution();
  string s        = "abcd";
  string expect   = "";
  string actual   = solution->longestDupSubstring(s);
  LCD_EXPECT_EQ(expect, actual);
}
