// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Largest Odd Number in String
//
// https://leetcode.com/problems/largest-odd-number-in-string/
//
// Question ID: 1903
// Difficult  : Easy
// Solve Date : 2022/02/23 19:13

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1903. Largest Odd Number in String|:
//
// You are given a string |num|, representing a large integer. Return the
// largest-valued odd integer (as a string) that is a non-empty substring of
// |num|, or an empty string |""| if no odd integer exists. A substring is a
// contiguous sequence of characters within a string.  
//

LEETCODE_BEGIN_RESOLVING(1903, LargestOddNumberInString, Solution);

class Solution {
public:
  string largestOddNumber(string num) {
    while (!num.empty() && !((num.back() - '0') & 1)) {
      num.pop_back();
    }
    return num;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= num.length <= 10⁵|
// * |num| only consists of digits and does not contain any leading zeros.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = "52"
// Output: "5"
//
// The only non-empty substrings are "5", "2", and "52". "5" is the only odd
// number.

LEETCODE_SOLUTION_UNITTEST(1903, LargestOddNumberInString, example_1) {
  auto   solution = MakeSolution();
  string num      = "52";
  string expect   = "5";
  string actual   = solution->largestOddNumber(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = "4206"
// Output: ""
//
// There are no odd numbers in "4206".

LEETCODE_SOLUTION_UNITTEST(1903, LargestOddNumberInString, example_2) {
  auto   solution = MakeSolution();
  string num      = "4206";
  string expect   = "";
  string actual   = solution->largestOddNumber(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: num = "35427"
// Output: "35427"
//
// "35427" is already an odd number.

LEETCODE_SOLUTION_UNITTEST(1903, LargestOddNumberInString, example_3) {
  auto   solution = MakeSolution();
  string num      = "35427";
  string expect   = "35427";
  string actual   = solution->largestOddNumber(num);
  LCD_EXPECT_EQ(expect, actual);
}
