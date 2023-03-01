// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Convert a Number to Hexadecimal
//
// https://leetcode.com/problems/convert-a-number-to-hexadecimal/
//
// Question ID: 405
// Difficult  : Easy
// Solve Date : 2022/05/30 18:20

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |405. Convert a Number to Hexadecimal|:
//
// Given an integer |num|, return a string representing its hexadecimal
// representation. For negative integers, [two’s complement] method is used. All
// the letters in the answer string should be lowercase characters, and there
// should not be any leading zeros in the answer except for the zero itself.
// Note:You are not allowed to use any built-in library method to directly solve
// this problem.
//

LEETCODE_BEGIN_RESOLVING(405, ConvertANumberToHexadecimal, Solution);

class Solution {
private:
  char helper(int x) {
    if (x < 10) {
      return '0' + x;
    } else {
      return 'a' + x - 10;
    }
  }

public:
  string toHex(int num) {
    if (num == 0) {
      return "0";
    }

    uint32_t x = static_cast<uint32_t>(num);
    string   res;

    while (x != 0) {
      res += helper(x & 15);
      x >>= 4;
    }

    reverse(res.begin(), res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |-2³¹ <= num <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 26
// Output: "1a"
//

LEETCODE_SOLUTION_UNITTEST(405, ConvertANumberToHexadecimal, example_1) {
  auto   solution = MakeSolution();
  int    num      = 26;
  string expect   = "1a";
  string actual   = solution->toHex(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = -1
// Output: "ffffffff"
//

LEETCODE_SOLUTION_UNITTEST(405, ConvertANumberToHexadecimal, example_2) {
  auto   solution = MakeSolution();
  int    num      = -1;
  string expect   = "ffffffff";
  string actual   = solution->toHex(num);
  LCD_EXPECT_EQ(expect, actual);
}
