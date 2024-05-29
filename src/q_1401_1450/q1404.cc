// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Number of Steps to Reduce a Number in Binary Representation to One
//
// https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/
//
// Question ID: 1404
// Difficult  : Medium
// Solve Date : 2024/05/29 20:51

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1404. Number of Steps to Reduce a Number in Binary
// Representation to One|:
//
// Given the binary representation of an integer as a string |s|, return the
// number of steps to reduce it to |1| under the following rules:
//
//  •
// 	If the current number is even, you have to divide it by |2|.
//
//
//  •
// 	If the current number is odd, you have to add |1| to it.
//
// It is guaranteed that you can always reach one for all test cases.
//
//

LEETCODE_BEGIN_RESOLVING(
    1404, NumberOfStepsToReduceANumberInBinaryRepresentationToOne, Solution);

class Solution {
public:
  int numSteps(string s) {
    int i     = s.size() - 1;
    int carry = 0;
    int res   = 0;
    while (i > 0) {
      if (s[i] - '0' + carry == 0) {
        carry = 0;
        ++res;
      } else if (s[i] - '0' + carry == 2) {
        carry = 1;
        ++res;
      } else {
        carry = 1;
        res += 2;
      }
      --i;
    }

    if (carry == 1) {
      ++res;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 500|
// * |s| consists of characters '0' or '1'
// * |s[0] == '1'|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "1101"
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(
    1404, NumberOfStepsToReduceANumberInBinaryRepresentationToOne, example_1) {
  auto   solution = MakeSolution();
  string s        = "1101";
  int    expect   = 6;
  int    actual   = solution->numSteps(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "10"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(
    1404, NumberOfStepsToReduceANumberInBinaryRepresentationToOne, example_2) {
  auto   solution = MakeSolution();
  string s        = "10";
  int    expect   = 1;
  int    actual   = solution->numSteps(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "1"
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(
    1404, NumberOfStepsToReduceANumberInBinaryRepresentationToOne, example_3) {
  auto   solution = MakeSolution();
  string s        = "1";
  int    expect   = 0;
  int    actual   = solution->numSteps(s);
  LCD_EXPECT_EQ(expect, actual);
}
