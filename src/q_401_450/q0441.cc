// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Arranging Coins
//
// https://leetcode.com/problems/arranging-coins/
//
// Question ID: 441
// Difficult  : Easy
// Solve Date : 2021/11/05 18:21

#include <cmath>
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |441. Arranging Coins|:
//
// You have |n| coins and you want to build a staircase with these coins. The
// staircase consists of |k| rows where the |iᵗʰ| row has exactly |i| coins. The
// last row of the staircase may be incomplete. Given the integer |n|, return
// the number of complete rows of the staircase you will build.  
//

LEETCODE_BEGIN_RESOLVING(441, ArrangingCoins, Solution);

class Solution {
public:
  int arrangeCoins(int n) { return (int)(sqrt(2 * (long long)n + 0.25) - 0.5); }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5
// Output: 2
//
// Because the 3ʳᵈ row is incomplete, we return 2.

LEETCODE_SOLUTION_UNITTEST(441, ArrangingCoins, example_1) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  expect   = 2;
  int  actual   = solution->arrangeCoins(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 8
// Output: 3
//
// Because the 4ᵗʰ row is incomplete, we return 3.

LEETCODE_SOLUTION_UNITTEST(441, ArrangingCoins, example_2) {
  auto solution = MakeSolution();
  int  n        = 8;
  int  expect   = 3;
  int  actual   = solution->arrangeCoins(n);
  LCD_EXPECT_EQ(expect, actual);
}
