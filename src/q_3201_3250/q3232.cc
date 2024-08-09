// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find if Digit Game Can Be Won
//
// https://leetcode.com/problems/find-if-digit-game-can-be-won/
//
// Question ID: 3232
// Difficult  : Easy
// Solve Date : 2024/08/01 19:10

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3232. Find if Digit Game Can Be Won|:
//
// You are given an array of positive integers |nums|.
// Alice and Bob are playing a game. In the game, Alice can choose either all
// single-digit numbers or all double-digit numbers from |nums|, and the rest of
// the numbers are given to Bob. Alice wins if the sum of her numbers is
// strictly greater than the sum of Bob's numbers. Return |true| if Alice can
// win this game, otherwise, return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(3232, FindIfDigitGameCanBeWon, Solution);

class Solution {
public:
  bool canAliceWin(vector<int> &nums) {
    int sg = 0;
    int db = 0;
    for (auto x : nums) {
      if (x >= 10) {
        db += x;
      } else {
        sg += x;
      }
    }
    return sg != db;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i] <= 99|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4,10]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3232, FindIfDigitGameCanBeWon, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 10};
  bool        expect   = false;
  bool        actual   = solution->canAliceWin(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4,5,14]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3232, FindIfDigitGameCanBeWon, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5, 14};
  bool        expect   = true;
  bool        actual   = solution->canAliceWin(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [5,5,5,25]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3232, FindIfDigitGameCanBeWon, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 5, 5, 25};
  bool        expect   = true;
  bool        actual   = solution->canAliceWin(nums);
  LCD_EXPECT_EQ(expect, actual);
}
