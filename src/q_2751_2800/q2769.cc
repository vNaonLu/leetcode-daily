// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Maximum Achievable Number
//
// https://leetcode.com/problems/find-the-maximum-achievable-number/
//
// Question ID: 2769
// Difficult  : Easy
// Solve Date : 2023/12/28 19:02

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2769. Find the Maximum Achievable Number|:
//
// You are given two integers, |num| and |t|.
// An integer |x| is called achievable if it can become equal to |num| after
// applying the following operation no more than |t| times:
//
//  • Increase or decrease |x| by |1|, and simultaneously increase or decrease
//  |num| by |1|.
// Return the maximum possible achievable number. It can be proven that there
// exists at least one achievable number.
//
//

LEETCODE_BEGIN_RESOLVING(2769, FindTheMaximumAchievableNumber, Solution);

class Solution {
public:
  int theMaximumAchievableX(int num, int t) { return num + (t << 1); }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= num, t <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 4, t = 1
// Output: 6
//
// The maximum achievable number is x = 6; it can become equal to num after
// performing this operation: 1- Decrease x by 1, and increase num by 1. Now, x
// = 5 and num = 5. It can be proven that there is no achievable number larger
// than 6.

LEETCODE_SOLUTION_UNITTEST(2769, FindTheMaximumAchievableNumber, example_1) {
  auto solution = MakeSolution();
  int  num      = 4;
  int  t        = 1;
  int  expect   = 6;
  int  actual   = solution->theMaximumAchievableX(num, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 3, t = 2
// Output: 7
//
// The maximum achievable number is x = 7; after performing these operations, x
// will equal num: 1- Decrease x by 1, and increase num by 1. Now, x = 6 and num
// = 4. 2- Decrease x by 1, and increase num by 1. Now, x = 5 and num = 5. It
// can be proven that there is no achievable number larger than 7.

LEETCODE_SOLUTION_UNITTEST(2769, FindTheMaximumAchievableNumber, example_2) {
  auto solution = MakeSolution();
  int  num      = 3;
  int  t        = 2;
  int  expect   = 7;
  int  actual   = solution->theMaximumAchievableX(num, t);
  LCD_EXPECT_EQ(expect, actual);
}
