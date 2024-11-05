// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Number of Changes to Make Binary String Beautiful
//
// https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/
//
// Question ID: 2914
// Difficult  : Medium
// Solve Date : 2024/11/05 21:04

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2914. Minimum Number of Changes to Make Binary String
// Beautiful|:
//
// You are given a 0-indexed binary string |s| having an even length.
// A string is beautiful if it's possible to partition it into one or more
// substrings such that:
//
//  • Each substring has an even length.
//
//  • Each substring contains only |1|'s or only |0|'s.
// You can change any character in |s| to |0| or |1|.
// Return the minimum number of changes required to make the string |s|
// beautiful.
//
//

LEETCODE_BEGIN_RESOLVING(2914,
                         MinimumNumberOfChangesToMakeBinaryStringBeautiful,
                         Solution);

class Solution {
public:
  int minChanges(string s) {
    int n   = s.size();
    int res = 0;
    for (int i = 0; i < n; i += 2) {
      res += (s[i] != s[i + 1]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= s.length <= 10⁵|
// * |s| has an even length.
// * |s[i]| is either |'0'| or |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "1001"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2914,
                           MinimumNumberOfChangesToMakeBinaryStringBeautiful,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "1001";
  int    expect   = 2;
  int    actual   = solution->minChanges(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "10"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2914,
                           MinimumNumberOfChangesToMakeBinaryStringBeautiful,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "10";
  int    expect   = 1;
  int    actual   = solution->minChanges(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "0000"
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2914,
                           MinimumNumberOfChangesToMakeBinaryStringBeautiful,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "0000";
  int    expect   = 0;
  int    actual   = solution->minChanges(s);
  LCD_EXPECT_EQ(expect, actual);
}
