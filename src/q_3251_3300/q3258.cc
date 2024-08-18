// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Count Substrings That Satisfy K-Constraint I
//
// https://leetcode.com/problems/count-substrings-that-satisfy-k-constraint-i/
//
// Question ID: 3258
// Difficult  : Easy
// Solve Date : 2024/08/18 15:09

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3258. Count Substrings That Satisfy K-Constraint I|:
//
// You are given a binary string |s| and an integer |k|.
// A binary string satisfies the k-constraint if either of the following
// conditions holds:
//
//  • The number of |0|'s in the string is at most |k|.
//
//  • The number of |1|'s in the string is at most |k|.
// Return an integer denoting the number of substrings of |s| that satisfy the
// k-constraint.
//
//

LEETCODE_BEGIN_RESOLVING(3258, CountSubstringsThatSatisfyKConstraintI,
                         Solution);

class Solution {
public:
  int countKConstraintSubstrings(string s, int k) {
    int  ones  = 0;
    int  zeros = 0;
    int  res   = 0;
    auto lo    = s.begin();
    auto hi    = s.begin();
    while (hi != s.end()) {
      if (*hi == '0') {
        ++zeros;
      } else {
        ++ones;
      }

      while (zeros > k && ones > k) {
        if (*lo == '0') {
          --zeros;
        } else {
          --ones;
        }
        ++lo;
      }

      res += distance(lo, hi) + 1;
      ++hi;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 50 |
// * |1 <= k <= s.length|
// * |s[i]| is either |'0'| or |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "10101", k = 1
// Output: 12
//

LEETCODE_SOLUTION_UNITTEST(3258, CountSubstringsThatSatisfyKConstraintI,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "10101";
  int    k        = 1;
  int    expect   = 12;
  int    actual   = solution->countKConstraintSubstrings(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "1010101", k = 2
// Output: 25
//

LEETCODE_SOLUTION_UNITTEST(3258, CountSubstringsThatSatisfyKConstraintI,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "1010101";
  int    k        = 2;
  int    expect   = 25;
  int    actual   = solution->countKConstraintSubstrings(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "11111", k = 1
// Output: 15
//

LEETCODE_SOLUTION_UNITTEST(3258, CountSubstringsThatSatisfyKConstraintI,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "11111";
  int    k        = 1;
  int    expect   = 15;
  int    actual   = solution->countKConstraintSubstrings(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
