// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Get Equal Substrings Within Budget
//
// https://leetcode.com/problems/get-equal-substrings-within-budget/
//
// Question ID: 1208
// Difficult  : Medium
// Solve Date : 2024/05/28 21:24

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1208. Get Equal Substrings Within Budget|:
//
// You are given two strings |s| and |t| of the same length and an integer
// |maxCost|. You want to change |s| to |t|. Changing the |iᵗʰ| character of |s|
// to |iᵗʰ| character of |t| costs ||s[i] - t[i]|| (i.e., the absolute
// difference between the ASCII values of the characters). Return the maximum
// length of a substring of |s| that can be changed to be the same as the
// corresponding substring of |t| with a cost less than or equal to |maxCost|.
// If there is no substring from |s| that can be changed to its corresponding
// substring from |t|, return |0|.
//
//

LEETCODE_BEGIN_RESOLVING(1208, GetEqualSubstringsWithinBudget, Solution);

class Solution {
public:
  int equalSubstring(string s, string t, int maxCost) {
    int n   = s.size();
    int beg = 0;
    int cur = 0;
    int res = 0;
    for (int end = 0; end < n; ++end) {
      cur += abs(s[end] - t[end]);

      while (cur > maxCost) {
        cur -= abs(s[beg] - t[beg]);
        ++beg;
      }

      res = max(res, end - beg + 1);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |t.length == s.length|
// * |0 <= maxCost <= 10⁶|
// * |s| and |t| consist of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abcd", t = "bcdf", maxCost = 3
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1208, GetEqualSubstringsWithinBudget, example_1) {
  auto   solution = MakeSolution();
  string s        = "abcd";
  string t        = "bcdf";
  int    maxCost  = 3;
  int    expect   = 3;
  int    actual   = solution->equalSubstring(s, t, maxCost);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcd", t = "cdef", maxCost = 3
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1208, GetEqualSubstringsWithinBudget, example_2) {
  auto   solution = MakeSolution();
  string s        = "abcd";
  string t        = "cdef";
  int    maxCost  = 3;
  int    expect   = 1;
  int    actual   = solution->equalSubstring(s, t, maxCost);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "abcd", t = "acde", maxCost = 0
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1208, GetEqualSubstringsWithinBudget, example_3) {
  auto   solution = MakeSolution();
  string s        = "abcd";
  string t        = "acde";
  int    maxCost  = 0;
  int    expect   = 1;
  int    actual   = solution->equalSubstring(s, t, maxCost);
  LCD_EXPECT_EQ(expect, actual);
}
