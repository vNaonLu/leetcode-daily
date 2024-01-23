// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Odd Binary Number
//
// https://leetcode.com/problems/maximum-odd-binary-number/
//
// Question ID: 2864
// Difficult  : Easy
// Solve Date : 2024/01/21 15:02

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2864. Maximum Odd Binary Number|:
//
// You are given a binary string |s| that contains at least one |'1'|.
// You have to rearrange the bits in such a way that the resulting binary number
// is the maximum odd binary number that can be created from this combination.
// Return a string representing the maximum odd binary number that can be
// created from the given combination. Note that the resulting string can have
// leading zeros.
//
//

LEETCODE_BEGIN_RESOLVING(2864, MaximumOddBinaryNumber, Solution);

class Solution {
public:
  string maximumOddBinaryNumber(string s) {
    int one = 0;
    for (auto &c : s) {
      if (c == '1') {
        ++one;
      }

      c = '0';
    }

    s.back() = '1';
    --one;

    auto beg = s.begin();
    while (one--) {
      *beg++ = '1';
    }

    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| consists only of |'0'| and |'1'|.
// * |s| contains at least one |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "010"
// Output: "001"
//
// Because there is just one '1', it must be in the last position. So the answer
// is "001".

LEETCODE_SOLUTION_UNITTEST(2864, MaximumOddBinaryNumber, example_1) {
  auto   solution = MakeSolution();
  string s        = "010";
  string expect   = "001";
  string actual   = solution->maximumOddBinaryNumber(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "0101"
// Output: "1001"
//
// One of the '1's must be in the last position. The maximum number that can be
// made with the remaining digits is "100". So the answer is "1001".

LEETCODE_SOLUTION_UNITTEST(2864, MaximumOddBinaryNumber, example_2) {
  auto   solution = MakeSolution();
  string s        = "0101";
  string expect   = "1001";
  string actual   = solution->maximumOddBinaryNumber(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "111"
// Output: "111"
//

LEETCODE_SOLUTION_UNITTEST(2864, MaximumOddBinaryNumber, extra_testcase_1) {
  auto   solution = MakeSolution();
  string s        = "111";
  string expect   = "111";
  string actual   = solution->maximumOddBinaryNumber(s);
  LCD_EXPECT_EQ(expect, actual);
}
