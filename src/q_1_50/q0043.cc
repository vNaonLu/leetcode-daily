// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Multiply Strings
//
// https://leetcode.com/problems/multiply-strings/
//
// Question ID: 43
// Difficult  : Medium
// Solve Date : 2021/09/26 18:28

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |43. Multiply Strings|:
//
// Given two non-negative integers |num1| and |num2| represented as strings,
// return the product of |num1| and |num2|, also represented as a string.
// Note: You must not use any built-in BigInteger library or convert the inputs
// to integer directly.  
//

LEETCODE_BEGIN_RESOLVING(43, MultiplyStrings, Solution);

class Solution {
public:
  string multiply(string num1, string num2) {
    vector<int> ans(num1.size() + num2.size(), 0);
    int         j = num2.size();
    while (--j >= 0) {
      int i = num1.size();
      while (--i >= 0) {
        int piv = i + j + 1;
        int val = (num2[j] - '0') * (num1[i] - '0');
        ans[piv] += val;
        ans[piv - 1] += ans[piv] / 10;
        ans[piv] %= 10;
      }
    }
    string res;
    for (const auto &n : ans) {
      if (!res.empty() || n != 0) {
        res.push_back(n + '0');
      }
    }
    return res.empty() ? "0" : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= num1.length, num2.length <= 200|
// * |num1| and |num2| consist of digits only.
// * Both |num1| and |num2| do not contain any leading zero, except the number
// |0| itself.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num1 = "2", num2 = "3"
// Output: "6"
//

LEETCODE_SOLUTION_UNITTEST(43, MultiplyStrings, example_1) {
  auto   solution = MakeSolution();
  string num1     = "2";
  string num2     = "3";
  string expect   = "6";
  string actual   = solution->multiply(num1, num2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num1 = "123", num2 = "456"
// Output: "56088"
//

LEETCODE_SOLUTION_UNITTEST(43, MultiplyStrings, example_2) {
  auto   solution = MakeSolution();
  string num1     = "123";
  string num2     = "456";
  string expect   = "56088";
  string actual   = solution->multiply(num1, num2);
  LCD_EXPECT_EQ(expect, actual);
}
