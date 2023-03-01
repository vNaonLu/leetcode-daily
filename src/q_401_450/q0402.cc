// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove K Digits
//
// https://leetcode.com/problems/remove-k-digits/
//
// Question ID: 402
// Difficult  : Medium
// Solve Date : 2022/02/18 18:25

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |402. Remove K Digits|:
//
// Given string num representing a non-negative integer |num|, and an integer
// |k|, return the smallest possible integer after removing |k| digits from
// |num|.  
//

LEETCODE_BEGIN_RESOLVING(402, RemoveKDigits, Solution);

class Solution {
public:
  string removeKdigits(string num, int k) {
    if (k == 0)
      return num;
    else if (num.empty() == true)
      return "0";
    string res = "";
    for (const auto &c : num) {
      while (k > 0 && res.empty() == false && res.back() > c) {
        res.pop_back();
        --k;
      }
      if (res.empty() == false || c != '0') {
        res.push_back(c);
      }
    }
    while (res.empty() == false && k > 0) {
      res.pop_back();
      --k;
    }
    return res.empty() ? "0" : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= k <= num.length <= 10⁵|
// * |num| consists of only digits.
// * |num| does not have any leading zeros except for the zero itself.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = "1432219", k = 3
// Output: "1219"
//
// Remove the three digits 4, 3, and 2 to form the new number 1219 which is the
// smallest.

LEETCODE_SOLUTION_UNITTEST(402, RemoveKDigits, example_1) {
  auto   solution = MakeSolution();
  string num      = "1432219";
  int    k        = 3;
  string expect   = "1219";
  string actual   = solution->removeKdigits(num, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = "10200", k = 1
// Output: "200"
//
// Remove the leading 1 and the number is 200. Note that the output must not
// contain leading zeroes.

LEETCODE_SOLUTION_UNITTEST(402, RemoveKDigits, example_2) {
  auto   solution = MakeSolution();
  string num      = "10200";
  int    k        = 1;
  string expect   = "200";
  string actual   = solution->removeKdigits(num, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: num = "10", k = 2
// Output: "0"
//
// Remove all the digits from the number and it is left with nothing which is 0.

LEETCODE_SOLUTION_UNITTEST(402, RemoveKDigits, example_3) {
  auto   solution = MakeSolution();
  string num      = "10";
  int    k        = 2;
  string expect   = "0";
  string actual   = solution->removeKdigits(num, k);
  LCD_EXPECT_EQ(expect, actual);
}
