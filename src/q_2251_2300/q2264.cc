// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Largest 3-Same-Digit Number in String
//
// https://leetcode.com/problems/largest-3-same-digit-number-in-string/
//
// Question ID: 2264
// Difficult  : Easy
// Solve Date : 2023/02/21 01:17

#include <iosfwd>
#include <map>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2264. Largest 3-Same-Digit Number in String|:
//
// You are given a string |num| representing a large integer. An integer is good
// if it meets the following conditions:
//
//  • It is a substring of |num| with length |3|.
//
//  • It consists of only one unique digit.
// Return the maximum good integer as a string or an empty string |""| if no
// such integer exists. Note:
//
//  • A substring is a contiguous sequence of characters within a string.
//
//  • There may be leading zeroes in |num| or a good integer.
//

LEETCODE_BEGIN_RESOLVING(2264, Largest3SameDigitNumberInString, Solution);

class Solution {
public:
  string largestGoodInteger(string num) {
    char           res = -1;
    map<char, int> freq;
    auto           lo = num.begin();
    auto           hi = lo;
    while (distance(lo, hi) < 3) {
      ++freq[*hi++];
    }
    if (freq.size() == 1) {
      res = freq.begin()->first;
    }
    while (hi != num.end()) {
      ++freq[*hi++];
      auto iter = freq.find(*lo++);
      if (--iter->second == 0) {
        freq.erase(iter);
      }
      if (freq.size() == 1) {
        res = max(res, freq.begin()->first);
      }
    }
    return res == -1 ? "" : string(3, res);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= num.length <= 1000|
// * |num| only consists of digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = "6777133339"
// Output: "777"
//
// There are two distinct good integers: "777" and "333".
// "777" is the largest, so we return "777".

LEETCODE_SOLUTION_UNITTEST(2264, Largest3SameDigitNumberInString, example_1) {
  auto   solution = MakeSolution();
  string num      = "6777133339";
  string expect   = "777";
  string actual   = solution->largestGoodInteger(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = "2300019"
// Output: "000"
//
// "000" is the only good integer.

LEETCODE_SOLUTION_UNITTEST(2264, Largest3SameDigitNumberInString, example_2) {
  auto   solution = MakeSolution();
  string num      = "2300019";
  string expect   = "000";
  string actual   = solution->largestGoodInteger(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: num = "42352338"
// Output: ""
//
// No substring of length 3 consists of only one unique digit. Therefore, there
// are no good integers.

LEETCODE_SOLUTION_UNITTEST(2264, Largest3SameDigitNumberInString, example_3) {
  auto   solution = MakeSolution();
  string num      = "42352338";
  string expect   = "";
  string actual   = solution->largestGoodInteger(num);
  LCD_EXPECT_EQ(expect, actual);
}
