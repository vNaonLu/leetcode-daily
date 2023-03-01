// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Domino and Tromino Tiling
//
// https://leetcode.com/problems/domino-and-tromino-tiling/
//
// Question ID: 790
// Difficult  : Medium
// Solve Date : 2021/12/10 17:59

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |790. Domino and Tromino Tiling|:
//
// You have two types of tiles: a |2 x 1| domino shape and a tromino shape. You
// may rotate these shapes.
// ![img](https://assets.leetcode.com/uploads/2021/07/15/lc-domino.jpg)
// Given an integer n, return the number of ways to tile an |2 x n| board. Since
// the answer may be very large, return it modulo |10⁹ + 7|. In a tiling, every
// square must be covered by a tile. Two tilings are different if and only if
// there are two 4-directionally adjacent cells on the board such that exactly
// one of the tilings has both squares occupied by a tile.  
//

LEETCODE_BEGIN_RESOLVING(790, DominoAndTrominoTiling, Solution);

class Solution {
public:
  int numTilings(int n) {
    uint32_t         _module = (1 << 9) + 7;
    vector<uint32_t> dp(1001, 0);
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 5;
    for (int i = 4; i <= n; ++i)
      dp[i] = (2 * dp[i - 1] + dp[i - 3]) % 1000000007;
    return dp[n];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3
// Output: 5
//
// The five different ways are show above.

LEETCODE_SOLUTION_UNITTEST(790, DominoAndTrominoTiling, example_1) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  expect   = 5;
  int  actual   = solution->numTilings(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(790, DominoAndTrominoTiling, example_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 1;
  int  actual   = solution->numTilings(n);
  LCD_EXPECT_EQ(expect, actual);
}
