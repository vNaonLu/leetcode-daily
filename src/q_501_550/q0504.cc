// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Base 7
//
// https://leetcode.com/problems/base-7/
//
// Question ID: 504
// Difficult  : Easy
// Solve Date : 2022/02/11 18:34

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |504. Base 7|:
//
// Given an integer |num|, return a string of its base 7 representation.
//  
//

LEETCODE_BEGIN_RESOLVING(504, Base7, Solution);

class Solution {
private:
  vector<int> generatePowerOfSeven(int n) {
    vector<int> res;
    for (int i = 7; i <= n; i *= 7) {
      res.emplace_back(i);
    }
    return res;
  }

public:
  string convertToBase7(int num) {
    string res              = num < 0 ? "-" : "";
    num                     = abs(num);
    vector<int> power_seven = generatePowerOfSeven(num);
    for (auto it = power_seven.rbegin(); it != power_seven.rend(); ++it) {
      res.push_back('0' + (num / *it));
      num %= *it;
    }
    res.push_back('0' + num);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |-10⁷ <= num <= 10⁷|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 100
// Output: "202"
//

LEETCODE_SOLUTION_UNITTEST(504, Base7, example_1) {
  auto   solution = MakeSolution();
  int    num      = 100;
  string expect   = "202";
  string actual   = solution->convertToBase7(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = -7
// Output: "-10"
//

LEETCODE_SOLUTION_UNITTEST(504, Base7, example_2) {
  auto   solution = MakeSolution();
  int    num      = -7;
  string expect   = "-10";
  string actual   = solution->convertToBase7(num);
  LCD_EXPECT_EQ(expect, actual);
}
