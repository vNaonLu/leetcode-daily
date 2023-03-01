// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Odd Numbers in an Interval Range
//
// https://leetcode.com/problems/count-odd-numbers-in-an-interval-range/
//
// Question ID: 1523
// Difficult  : Easy
// Solve Date : 2022/04/14 18:37

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1523. Count Odd Numbers in an Interval Range|:
//
// Given two non-negative integers |low| and |high|. Return the count of odd
// numbers between |low| and |high| (inclusive).
//
//  
//

LEETCODE_BEGIN_RESOLVING(1523, CountOddNumbersInAnIntervalRange, Solution);

class Solution {
public:
  int countOdds(int low, int high) {
    return (high - low) / 2 + (high & 1 || low & 1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= low <= high <= 10^9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: low = 3, high = 7
// Output: 3
// Explanation: The odd numbers between 3 and 7 are [3,5,7].
//

LEETCODE_SOLUTION_UNITTEST(1523, CountOddNumbersInAnIntervalRange, example_1) {
  auto solution = MakeSolution();
  int  low      = 3;
  int  high     = 7;
  int  expect   = 3;
  int  actual   = solution->countOdds(low, high);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: low = 8, high = 10
// Output: 1
// Explanation: The odd numbers between 8 and 10 are [9].
//

LEETCODE_SOLUTION_UNITTEST(1523, CountOddNumbersInAnIntervalRange, example_2) {
  auto solution = MakeSolution();
  int  low      = 8;
  int  high     = 10;
  int  expect   = 1;
  int  actual   = solution->countOdds(low, high);
  LCD_EXPECT_EQ(expect, actual);
}
