// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Binary Substrings
//
// https://leetcode.com/problems/count-binary-substrings/
//
// Question ID: 696
// Difficult  : Easy
// Solve Date : 2022/11/04 18:27

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |696. Count Binary Substrings|:
//
// Given a binary string |s|, return the number of non-empty substrings that
// have the same number of |0|'s and |1|'s, and all the |0|'s and all the |1|'s
// in these substrings are grouped consecutively. Substrings that occur multiple
// times are counted the number of times they occur.
//

LEETCODE_BEGIN_RESOLVING(696, CountBinarySubstrings, Solution);

class Solution {
public:
  int countBinarySubstrings(string s) {
    auto res      = (int)0;
    auto prev_cnt = (int)0;
    auto curr_cnt = (int)1;

    for (int i = 1; i < s.size(); ++i) {
      if (s[i] == s[i - 1]) {
        ++curr_cnt;
      } else {
        res += min(curr_cnt, prev_cnt);
        prev_cnt = curr_cnt;
        curr_cnt = 1;
      }
    }

    res += min(curr_cnt, prev_cnt);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s[i]| is either |'0'| or |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "00110011"
// Output: 6
//
// There are 6 substrings that have equal number of consecutive 1's and 0's:
// "0011", "01", "1100", "10", "0011", and "01". Notice that some of these
// substrings repeat and are counted the number of times they occur. Also,
// "00110011" is not a valid substring because all the 0's (and 1's) are not
// grouped together.

LEETCODE_SOLUTION_UNITTEST(696, CountBinarySubstrings, example_1) {
  auto   solution = MakeSolution();
  string s        = "00110011";
  int    expect   = 6;
  int    actual   = solution->countBinarySubstrings(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "10101"
// Output: 4
//
// There are 4 substrings: "10", "01", "10", "01" that have equal number of
// consecutive 1's and 0's.

LEETCODE_SOLUTION_UNITTEST(696, CountBinarySubstrings, example_2) {
  auto   solution = MakeSolution();
  string s        = "10101";
  int    expect   = 4;
  int    actual   = solution->countBinarySubstrings(s);
  LCD_EXPECT_EQ(expect, actual);
}
