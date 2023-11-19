// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Distinct Numbers on Board
//
// https://leetcode.com/problems/count-distinct-numbers-on-board/
//
// Question ID: 2549
// Difficult  : Easy
// Solve Date : 2023/11/19 14:18

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2549. Count Distinct Numbers on Board|:
//
// You are given a positive integer |n|, that is initially placed on a board.
// Every day, for |10⁹| days, you perform the following procedure:
//
//  • For each number |x| present on the board, find all numbers |1 <= i <= n|
//  such that |x % i == 1|.
//
//  • Then, place those numbers on the board.
// Return the number of distinct integers present on the board after |10⁹| days
// have elapsed. Note:
//
//  • Once a number is placed on the board, it will remain on it until the end.
//
//  • |%| stands for the modulo operation. For example, |14 % 3| is |2|.
//
//

LEETCODE_BEGIN_RESOLVING(2549, CountDistinctNumbersOnBoard, Solution);

class Solution {
public:
  int distinctIntegers(int n) { return n == 1 ? 1 : n - 1; }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5
// Output: 4
//
// Initially, 5 is present on the board.
// The next day, 2 and 4 will be added since 5 % 2 == 1 and 5 % 4 == 1.
// After that day, 3 will be added to the board because 4 % 3 == 1.
// At the end of a billion days, the distinct numbers on the board will be 2, 3,
// 4, and 5.

LEETCODE_SOLUTION_UNITTEST(2549, CountDistinctNumbersOnBoard, example_1) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  expect   = 4;
  int  actual   = solution->distinctIntegers(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3
// Output: 2
//
// Since 3 % 2 == 1, 2 will be added to the board.
// After a billion days, the only two distinct numbers on the board are 2 and 3.

LEETCODE_SOLUTION_UNITTEST(2549, CountDistinctNumbersOnBoard, example_2) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  expect   = 2;
  int  actual   = solution->distinctIntegers(n);
  LCD_EXPECT_EQ(expect, actual);
}
