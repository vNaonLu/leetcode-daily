// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longer Contiguous Segments of Ones than Zeros
//
// https://leetcode.com/problems/longer-contiguous-segments-of-ones-than-zeros/
//
// Question ID: 1869
// Difficult  : Easy
// Solve Date : 2023/04/11 22:02

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1869. Longer Contiguous Segments of Ones than Zeros|:
//
// Given a binary string |s|, return |true| if the longest contiguous segment of
// |1|'s is strictly longer than the longest contiguous segment of |0|'s in |s|,
// or return |false| otherwise.
//
//  • For example, in |s = "110100010"| the longest continuous segment of |1|s
//  has length |2|, and the longest continuous segment of |0|s has length |3|.
// Note that if there are no |0|'s, then the longest continuous segment of |0|'s
// is considered to have a length |0|. The same applies if there is no |1|'s.
//
//

LEETCODE_BEGIN_RESOLVING(1869, LongerContiguousSegmentsOfOnesThanZeros,
                         Solution);

class Solution {
public:
  bool checkZeroOnes(string s) {
    int len1     = 0;
    int len0     = 0;
    int len1_tmp = 0;
    int len0_tmp = 0;
    for (auto c : s) {
      if (c == '0') {
        ++len0_tmp;
        len1_tmp = 0;
      } else {
        len0_tmp = 0;
        ++len1_tmp;
      }
      len1 = max(len1, len1_tmp);
      len0 = max(len0, len0_tmp);
    }
    return len1 > len0;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s[i]| is either |'0'| or |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "1101"
// Output: true
//
// The longest contiguous segment of 1s has length 2: "1101"
// The longest contiguous segment of 0s has length 1: "1101"
// The segment of 1s is longer, so return true.

LEETCODE_SOLUTION_UNITTEST(1869, LongerContiguousSegmentsOfOnesThanZeros,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "1101";
  bool   expect   = true;
  bool   actual   = solution->checkZeroOnes(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "111000"
// Output: false
//
// The longest contiguous segment of 1s has length 3: "111000"
// The longest contiguous segment of 0s has length 3: "111000"
// The segment of 1s is not longer, so return false.

LEETCODE_SOLUTION_UNITTEST(1869, LongerContiguousSegmentsOfOnesThanZeros,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "111000";
  bool   expect   = false;
  bool   actual   = solution->checkZeroOnes(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "110100010"
// Output: false
//
// The longest contiguous segment of 1s has length 2: "110100010"
// The longest contiguous segment of 0s has length 3: "110100010"
// The segment of 1s is not longer, so return false.

LEETCODE_SOLUTION_UNITTEST(1869, LongerContiguousSegmentsOfOnesThanZeros,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "110100010";
  bool   expect   = false;
  bool   actual   = solution->checkZeroOnes(s);
  LCD_EXPECT_EQ(expect, actual);
}
