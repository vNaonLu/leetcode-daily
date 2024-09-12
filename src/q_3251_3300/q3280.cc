// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Convert Date to Binary
//
// https://leetcode.com/problems/convert-date-to-binary/
//
// Question ID: 3280
// Difficult  : Easy
// Solve Date : 2024/09/08 18:15

#include <bitset>
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3280. Convert Date to Binary|:
//
// You are given a string |date| representing a Gregorian calendar date in the
// |yyyy-mm-dd| format. |date| can be written in its binary representation
// obtained by converting year, month, and day to their binary representations
// without any leading zeroes and writing them down in |year-month-day| format.
// Return the binary representation of |date|.
//
//

LEETCODE_BEGIN_RESOLVING(3280, ConvertDateToBinary, Solution);

class Solution {
public:
  string convertDateToBinary(string date) {
    auto   beg = date.begin();
    auto   it  = beg;
    string res;
    while (beg != date.end()) {
      ++it;
      if (it == date.end() || *it == '-') {
        res += toBinary(beg, it) + '-';
        beg = it == date.end() ? it : (it + 1);
      }
    }
    res.pop_back();
    return res;
  }

private:
  string toBinary(auto beg, auto end) {
    int n = 0;
    while (beg != end) {
      n = n * 10 + *beg++ - '0';
    }
    auto res = bitset<32>(n).to_string();
    auto it  = res.begin();
    while (it != res.end()) {
      if (*it != '0') {
        break;
      }
      ++it;
    }
    res = string(it, res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |date.length == 10|
// * |date[4] == date[7] == '-'|, and all other |date[i]|'s are digits.
// * The input is generated such that |date| represents a valid Gregorian
// calendar date between Jan 1ˢᵗ, 1900 and Dec 31ˢᵗ, 2100 (both inclusive).
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: date = "2080-02-29"
// Output: "100000100000-10-11101"
//

LEETCODE_SOLUTION_UNITTEST(3280, ConvertDateToBinary, example_1) {
  auto   solution = MakeSolution();
  string date     = "2080-02-29";
  string expect   = "100000100000-10-11101";
  string actual   = solution->convertDateToBinary(date);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: date = "1900-01-01"
// Output: "11101101100-1-1"
//

LEETCODE_SOLUTION_UNITTEST(3280, ConvertDateToBinary, example_2) {
  auto   solution = MakeSolution();
  string date     = "1900-01-01";
  string expect   = "11101101100-1-1";
  string actual   = solution->convertDateToBinary(date);
  LCD_EXPECT_EQ(expect, actual);
}
