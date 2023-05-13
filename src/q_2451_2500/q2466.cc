// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Ways To Build Good Strings
//
// https://leetcode.com/problems/count-ways-to-build-good-strings/
//
// Question ID: 2466
// Difficult  : Medium
// Solve Date : 2023/05/13 16:17

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2466. Count Ways To Build Good Strings|:
//
// Given the integers |zero|, |one|, |low|, and |high|, we can construct a
// string by starting with an empty string, and then at each step perform either
// of the following:
//
//  • Append the character |'0'| |zero| times.
//
//  • Append the character |'1'| |one| times.
// This can be performed any number of times.
// A good string is a string constructed by the above process having a length
// between |low| and |high| (inclusive). Return the number of different good
// strings that can be constructed satisfying these properties. Since the answer
// can be large, return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(2466, CountWaysToBuildGoodStrings, Solution);

class Solution {
public:
  int countGoodStrings(int low, int high, int zero, int one) {
    vector<int64_t> dp(high + 1, -1);
    return solve(0, low, high, dp, zero, one);
  }

private:
  constexpr static int kMod = 1e9 + 7;
  int64_t solve(int64_t len, int64_t low, int64_t high, vector<int64_t> &dp,
                int zero, int one) {
    if (len > high) {
      return 0;
    }
    if (dp[len] == -1) {
      int64_t res = len >= low && len <= high ? 1 : 0;
      ;
      res += solve(len + zero, low, high, dp, zero, one) % kMod;
      res     = (res + solve(len + one, low, high, dp, zero, one)) % kMod;
      dp[len] = res;
    }
    return dp[len];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= low <= high <= 10⁵|
// * |1 <= zero, one <= low|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: low = 3, high = 3, zero = 1, one = 1
// Output: 8
//
// One possible valid good string is "011".
// It can be constructed as follows: "" -> "0" -> "01" -> "011".
// All binary strings from "000" to "111" are good strings in this example.

LEETCODE_SOLUTION_UNITTEST(2466, CountWaysToBuildGoodStrings, example_1) {
  auto solution = MakeSolution();
  int  low      = 3;
  int  high     = 3;
  int  zero     = 1;
  int  one      = 1;
  int  expect   = 8;
  int  actual   = solution->countGoodStrings(low, high, zero, one);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: low = 2, high = 3, zero = 1, one = 2
// Output: 5
//
// The good strings are "00", "11", "000", "110", and "011".

LEETCODE_SOLUTION_UNITTEST(2466, CountWaysToBuildGoodStrings, example_2) {
  auto solution = MakeSolution();
  int  low      = 2;
  int  high     = 3;
  int  zero     = 1;
  int  one      = 2;
  int  expect   = 5;
  int  actual   = solution->countGoodStrings(low, high, zero, one);
  LCD_EXPECT_EQ(expect, actual);
}
