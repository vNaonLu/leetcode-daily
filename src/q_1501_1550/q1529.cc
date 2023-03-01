// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Suffix Flips
//
// https://leetcode.com/problems/minimum-suffix-flips/
//
// Question ID: 1529
// Difficult  : Medium
// Solve Date : 2022/02/12 00:03

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1529. Minimum Suffix Flips|:
//
// You are given a 0-indexed binary string |target| of length |n|. You have
// another binary string |s| of length |n| that is initially set to all zeros.
// You want to make |s| equal to |target|. In one operation, you can pick an
// index |i| where |0 <= i < n| and flip all bits in the inclusive range |[i, n
// - 1]|. Flip means changing |'0'| to |'1'| and |'1'| to |'0'|. Return the
// minimum number of operations needed to make |s| equal to |target|.  
//

LEETCODE_BEGIN_RESOLVING(1529, MinimumSuffixFlips, Solution);

class Solution {
public:
  int minFlips(string target) {
    int  res  = 0;
    char curr = '0';
    for (auto it = target.begin(); it != target.end(); ++it) {
      if (*it != curr) {
        curr = *it;
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == target.length|
// * |1 <= n <= 10⁵|
// * |target[i]| is either |'0'| or |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: target = "10111"
// Output: 3
//
// Initially, s = "00000".
// Choose index i = 2: "00000" -> "00111"
// Choose index i = 0: "00111" -> "11000"
// Choose index i = 1: "11000" -> "10111"
// We need at least 3 flip operations to form target.

LEETCODE_SOLUTION_UNITTEST(1529, MinimumSuffixFlips, example_1) {
  auto   solution = MakeSolution();
  string target   = "10111";
  int    expect   = 3;
  int    actual   = solution->minFlips(target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: target = "101"
// Output: 3
//
// Initially, s = "000".
// Choose index i = 0: "000" -> "111"
// Choose index i = 1: "111" -> "100"
// Choose index i = 2: "100" -> "101"
// We need at least 3 flip operations to form target.

LEETCODE_SOLUTION_UNITTEST(1529, MinimumSuffixFlips, example_2) {
  auto   solution = MakeSolution();
  string target   = "101";
  int    expect   = 3;
  int    actual   = solution->minFlips(target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: target = "00000"
// Output: 0
//
// We do not need any operations since the initial s already equals target.

LEETCODE_SOLUTION_UNITTEST(1529, MinimumSuffixFlips, example_3) {
  auto   solution = MakeSolution();
  string target   = "00000";
  int    expect   = 0;
  int    actual   = solution->minFlips(target);
  LCD_EXPECT_EQ(expect, actual);
}
