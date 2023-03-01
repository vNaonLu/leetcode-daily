// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check if Binary String Has at Most One Segment of Ones
//
// https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/
//
// Question ID: 1784
// Difficult  : Easy
// Solve Date : 2022/12/14 17:37

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1784. Check if Binary String Has at Most One Segment of
// Ones|:
//
// Given a binary string |s| ​​​​​without leading zeros, return
// |true|​​​ if |s| contains at most one contiguous segment of ones.
// Otherwise, return |false|.
//

LEETCODE_BEGIN_RESOLVING(1784, CheckIfBinaryStringHasAtMostOneSegmentOfOnes,
                         Solution);

class Solution {
public:
  bool checkOnesSegment(string s) {
    auto cnt = (int)0;
    auto beg = s.begin();
    while (beg != s.end()) {
      if (*beg == '1') {
        if (beg == s.begin() || *(beg - 1) == '0') {
          ++cnt;
        }
      }
      if (cnt > 1) {
        return false;
      }
      ++beg;
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s[i]|​​​​ is either |'0'| or |'1'|.
// * |s[0]| is |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "1001"
// Output: false
//
// The ones do not form a contiguous segment.

LEETCODE_SOLUTION_UNITTEST(1784, CheckIfBinaryStringHasAtMostOneSegmentOfOnes,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "1001";
  bool   expect   = false;
  bool   actual   = solution->checkOnesSegment(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "110"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1784, CheckIfBinaryStringHasAtMostOneSegmentOfOnes,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "110";
  bool   expect   = true;
  bool   actual   = solution->checkOnesSegment(s);
  LCD_EXPECT_EQ(expect, actual);
}
