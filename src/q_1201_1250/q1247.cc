// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Swaps to Make Strings Equal
//
// https://leetcode.com/problems/minimum-swaps-to-make-strings-equal/
//
// Question ID: 1247
// Difficult  : Medium
// Solve Date : 2024/10/24 20:38

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1247. Minimum Swaps to Make Strings Equal|:
//
// You are given two strings |s1| and |s2| of equal length consisting of letters
// |"x"| and |"y"| only. Your task is to make these two strings equal to each
// other. You can swap any two characters that belong to different strings,
// which means: swap |s1[i]| and |s2[j]|. Return the minimum number of swaps
// required to make |s1| and |s2| equal, or return |-1| if it is impossible to
// do so.
//
//

LEETCODE_BEGIN_RESOLVING(1247, MinimumSwapsToMakeStringsEqual, Solution);

class Solution {
public:
  int minimumSwap(string s1, string s2) {
    if (s1 == s2) {
      return 0;
    }
    int x = 0;
    int y = 0;
    for (int i = 0; i < s1.size(); ++i) {
      if (s1[i] == s2[i]) {
        continue;
      }

      if (s1[i] == 'x') {
        ++x;
      } else {
        ++y;
      }
    }

    if ((x + y) % 2 != 0) {
      return -1;
    }
    return (x + 1) / 2 + (y + 1) / 2;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s1.length, s2.length <= 1000|
// * |s1.length == s2.length|
// * |s1, s2| only contain |'x'| or |'y'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s1 = "xx", s2 = "yy"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1247, MinimumSwapsToMakeStringsEqual, example_1) {
  auto   solution = MakeSolution();
  string s1       = "xx";
  string s2       = "yy";
  int    expect   = 1;
  int    actual   = solution->minimumSwap(s1, s2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s1 = "xy", s2 = "yx"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1247, MinimumSwapsToMakeStringsEqual, example_2) {
  auto   solution = MakeSolution();
  string s1       = "xy";
  string s2       = "yx";
  int    expect   = 2;
  int    actual   = solution->minimumSwap(s1, s2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s1 = "xx", s2 = "xy"
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(1247, MinimumSwapsToMakeStringsEqual, example_3) {
  auto   solution = MakeSolution();
  string s1       = "xx";
  string s2       = "xy";
  int    expect   = -1;
  int    actual   = solution->minimumSwap(s1, s2);
  LCD_EXPECT_EQ(expect, actual);
}
