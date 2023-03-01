// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Convert to Base -2
//
// https://leetcode.com/problems/convert-to-base-2/
//
// Question ID: 1017
// Difficult  : Medium
// Solve Date : 2022/02/16 18:10

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1017. Convert to Base -2|:
//
// Given an integer |n|, return a binary string representing its representation
// in base |-2|. Note that the returned string should not have leading zeros
// unless the string is |"0"|.  
//

LEETCODE_BEGIN_RESOLVING(1017, ConvertToBase2, Solution);

class Solution {
public:
  string baseNeg2(int n) {
    if (n == 0)
      return "0";
    string res;
    while (0 != n) {
      if (n % 2 == 0) {
        res = "0" + res;
        n   = n / -2;
      } else {
        res = "1" + res;
        n   = (n - 1) / -2;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= n <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2
// Output: "110"
// Explantion: (-2)² + (-2)¹ = 2
//

LEETCODE_SOLUTION_UNITTEST(1017, ConvertToBase2, example_1) {
  auto   solution = MakeSolution();
  int    n        = 2;
  string expect   = "110";
  string actual   = solution->baseNeg2(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3
// Output: "111"
// Explantion: (-2)² + (-2)¹ + (-2)⁰ = 3
//

LEETCODE_SOLUTION_UNITTEST(1017, ConvertToBase2, example_2) {
  auto   solution = MakeSolution();
  int    n        = 3;
  string expect   = "111";
  string actual   = solution->baseNeg2(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 4
// Output: "100"
// Explantion: (-2)² = 4
//

LEETCODE_SOLUTION_UNITTEST(1017, ConvertToBase2, example_3) {
  auto   solution = MakeSolution();
  int    n        = 4;
  string expect   = "100";
  string actual   = solution->baseNeg2(n);
  LCD_EXPECT_EQ(expect, actual);
}
