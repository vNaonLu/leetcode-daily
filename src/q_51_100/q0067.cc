// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Add Binary
//
// https://leetcode.com/problems/add-binary/
//
// Question ID: 67
// Difficult  : Easy
// Solve Date : 2022/01/10 18:14

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |67. Add Binary|:
//
// Given two binary strings |a| and |b|, return their sum as a binary string.
//  
//

LEETCODE_BEGIN_RESOLVING(67, AddBinary, Solution);

class Solution {
public:
  string addBinary(string a, string b) {
    int    i = a.length() - 1;
    int    j = b.length() - 1;
    string res;
    int    carry = 0;

    while (i >= 0 || j >= 0 || carry) {
      if (i >= 0) {
        carry += a[i] - '0';
        i--;
      }
      if (j >= 0) {
        carry += b[j] - '0';
        j--;
      }

      res += (carry % 2 + '0');
      carry = carry / 2;
    }
    reverse(res.begin(), res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= a.length, b.length <= 10⁴|
// * |a| and |b| consist only of |'0'| or |'1'| characters.
// * Each string does not contain leading zeros except for the zero itself.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: a = "11", b = "1"
// Output: "100"
//

LEETCODE_SOLUTION_UNITTEST(67, AddBinary, example_1) {
  auto   solution = MakeSolution();
  string a        = "11";
  string b        = "1";
  string expect   = "100";
  string actual   = solution->addBinary(a, b);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: a = "1010", b = "1011"
// Output: "10101"
//

LEETCODE_SOLUTION_UNITTEST(67, AddBinary, example_2) {
  auto   solution = MakeSolution();
  string a        = "1010";
  string b        = "1011";
  string expect   = "10101";
  string actual   = solution->addBinary(a, b);
  LCD_EXPECT_EQ(expect, actual);
}
