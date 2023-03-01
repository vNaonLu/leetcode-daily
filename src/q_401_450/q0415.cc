// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Add Strings
//
// https://leetcode.com/problems/add-strings/
//
// Question ID: 415
// Difficult  : Easy
// Solve Date : 2021/09/24 16:00

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |415. Add Strings|:
//
// Given two non-negative integers, |num1| and |num2| represented as string,
// return the sum of |num1| and |num2| as a string. You must solve the problem
// without using any built-in library for handling large integers (such as
// |BigInteger|). You must also not convert the inputs to integers directly.  
//

LEETCODE_BEGIN_RESOLVING(415, AddStrings, Solution);

class Solution {
public:
  string addStrings(string num1, string num2) {
    string res;
    res.reserve(max(num1.size(), num2.size()) + 1);
    int i = num1.size() - 1, j = num2.size() - 1;
    int carry = 0;
    while (i >= 0 || j >= 0 || carry) {
      int cur =
          (i >= 0 ? num1[i] - '0' : 0) + (j >= 0 ? num2[j] - '0' : 0) + carry;
      carry = cur / 10;
      cur %= 10;
      res.push_back(cur + '0');
      i--, j--;
    }
    reverse(res.begin(), res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= num1.length, num2.length <= 10⁴|
// * |num1| and |num2| consist of only digits.
// * |num1| and |num2| don't have any leading zeros except for the zero itself.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num1 = "11", num2 = "123"
// Output: "134"
//

LEETCODE_SOLUTION_UNITTEST(415, AddStrings, example_1) {
  auto   solution = MakeSolution();
  string num1     = "11";
  string num2     = "123";
  string expect   = "134";
  string actual   = solution->addStrings(num1, num2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num1 = "456", num2 = "77"
// Output: "533"
//

LEETCODE_SOLUTION_UNITTEST(415, AddStrings, example_2) {
  auto   solution = MakeSolution();
  string num1     = "456";
  string num2     = "77";
  string expect   = "533";
  string actual   = solution->addStrings(num1, num2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: num1 = "0", num2 = "0"
// Output: "0"
//

LEETCODE_SOLUTION_UNITTEST(415, AddStrings, example_3) {
  auto   solution = MakeSolution();
  string num1     = "0";
  string num2     = "0";
  string expect   = "0";
  string actual   = solution->addStrings(num1, num2);
  LCD_EXPECT_EQ(expect, actual);
}
