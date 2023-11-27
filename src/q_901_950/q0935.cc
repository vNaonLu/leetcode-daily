// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Knight Dialer
//
// https://leetcode.com/problems/knight-dialer/
//
// Question ID: 935
// Difficult  : Medium
// Solve Date : 2023/11/27 22:05

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |935. Knight Dialer|:
//
// The chess knight has a unique movement, it may move two squares vertically
// and one square horizontally, or two squares horizontally and one square
// vertically (with both forming the shape of an L). The possible movements of
// chess knight are shown in this diagaram: A chess knight can move as indicated
// in the chess diagram below:
// ![img](https://assets.leetcode.com/uploads/2020/08/18/chess.jpg)
// We have a chess knight and a phone pad as shown below, the knight can only
// stand on a numeric cell (i.e. blue cell).
// ![img](https://assets.leetcode.com/uploads/2020/08/18/phone.jpg)
// Given an integer |n|, return how many distinct phone numbers of length |n| we
// can dial. You are allowed to place the knight on any numeric cell initially
// and then you should perform |n - 1| jumps to dial a number of length |n|. All
// jumps should be valid knight jumps. As the answer may be very large, return
// the answer modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(935, KnightDialer, Solution);

class Solution {
public:
  int knightDialer(int n) {
    vector<vector<int>> mp = {
        {4, 6},
        {6, 8},
        {7, 9},
        {4, 8},
        {0, 3, 9},
        {},
        {0, 1, 7},
        {2, 6},
        {1, 3},
        {2, 4}
    };
    vector<vector<int>> dp(10, vector<int>(n + 1, 0));
    int                 res = 0;
    for (int i = 0; i < 10; ++i) {
      dp[i][1] = 1;
    }

    for (int step = 2; step <= n; ++step) {
      for (int i = 0; i < 10; ++i) {
        for (auto idx : mp[i]) {
          dp[i][step] = (dp[i][step] + dp[idx][step - 1]) % kMod;
        }
      }
    }
    for (int i = 0; i < 10; ++i) {
      res = (res + dp[i][n]) % kMod;
    }
    return res;
  }

private:
  constexpr static int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 5000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1
// Output: 10
//
// We need to dial a number of length 1, so placing the knight over any numeric
// cell of the 10 cells is sufficient.

LEETCODE_SOLUTION_UNITTEST(935, KnightDialer, example_1) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 10;
  int  actual   = solution->knightDialer(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2
// Output: 20
//
// All the valid number we can dial are [04, 06, 16, 18, 27, 29, 34, 38, 40, 43,
// 49, 60, 61, 67, 72, 76, 81, 83, 92, 94]

LEETCODE_SOLUTION_UNITTEST(935, KnightDialer, example_2) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  expect   = 20;
  int  actual   = solution->knightDialer(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 3131
// Output: 136006598
//
// Please take care of the mod.

LEETCODE_SOLUTION_UNITTEST(935, KnightDialer, example_3) {
  auto solution = MakeSolution();
  int  n        = 3131;
  int  expect   = 136006598;
  int  actual   = solution->knightDialer(n);
  LCD_EXPECT_EQ(expect, actual);
}
