// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Amount of Time to Fill Cups
//
// https://leetcode.com/problems/minimum-amount-of-time-to-fill-cups/
//
// Question ID: 2335
// Difficult  : Easy
// Solve Date : 2023/10/23 16:24

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2335. Minimum Amount of Time to Fill Cups|:
//
// You have a water dispenser that can dispense cold, warm, and hot water. Every
// second, you can either fill up |2| cups with different types of water, or |1|
// cup of any type of water. You are given a 0-indexed integer array |amount| of
// length |3| where |amount[0]|, |amount[1]|, and |amount[2]| denote the number
// of cold, warm, and hot water cups you need to fill respectively. Return the
// minimum number of seconds needed to fill up all the cups.
//
//

LEETCODE_BEGIN_RESOLVING(2335, MinimumAmountOfTimeToFillCups, Solution);

class Solution {
public:
  int fillCups(vector<int> &amount) {
    sort(amount.begin(), amount.end(), greater<int>{});
    if (amount[0] >= amount[1] + amount[2]) {
      return amount[0];
    } else {
      return amount[0] + (amount[1] + amount[2] - amount[0] + 1) / 2;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |amount.length == 3|
// * |0 <= amount[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: amount = [1,4,2]
// Output: 4
//
// One way to fill up the cups is:
// Second 1: Fill up a cold cup and a warm cup.
// Second 2: Fill up a warm cup and a hot cup.
// Second 3: Fill up a warm cup and a hot cup.
// Second 4: Fill up a warm cup.
// It can be proven that 4 is the minimum number of seconds needed.

LEETCODE_SOLUTION_UNITTEST(2335, MinimumAmountOfTimeToFillCups, example_1) {
  auto        solution = MakeSolution();
  vector<int> amount   = {1, 4, 2};
  int         expect   = 4;
  int         actual   = solution->fillCups(amount);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: amount = [5,4,4]
// Output: 7
//
// One way to fill up the cups is:
// Second 1: Fill up a cold cup, and a hot cup.
// Second 2: Fill up a cold cup, and a warm cup.
// Second 3: Fill up a cold cup, and a warm cup.
// Second 4: Fill up a warm cup, and a hot cup.
// Second 5: Fill up a cold cup, and a hot cup.
// Second 6: Fill up a cold cup, and a warm cup.
// Second 7: Fill up a hot cup.

LEETCODE_SOLUTION_UNITTEST(2335, MinimumAmountOfTimeToFillCups, example_2) {
  auto        solution = MakeSolution();
  vector<int> amount   = {5, 4, 4};
  int         expect   = 7;
  int         actual   = solution->fillCups(amount);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: amount = [5,0,0]
// Output: 5
//
// Every second, we fill up a cold cup.

LEETCODE_SOLUTION_UNITTEST(2335, MinimumAmountOfTimeToFillCups, example_3) {
  auto        solution = MakeSolution();
  vector<int> amount   = {5, 0, 0};
  int         expect   = 5;
  int         actual   = solution->fillCups(amount);
  LCD_EXPECT_EQ(expect, actual);
}
