// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Stone Game II
//
// https://leetcode.com/problems/stone-game-ii/
//
// Question ID: 1140
// Difficult  : Medium
// Solve Date : 2023/05/26 16:57

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1140. Stone Game II|:
//
// Alice and Bob continue their games with piles of stones.  There are a number
// of piles arranged in a row, and each pile has a positive integer number of
// stones |piles[i]|.  The objective of the game is to end with the most stones.
// Alice and Bob take turns, with Alice starting first.  Initially, |M = 1|.
// On each player's turn, that player can take all the stones in the first |X|
// remaining piles, where |1 <= X <= 2M|.  Then, we set |M = max(M, X)|. The
// game continues until all the stones have been taken. Assuming Alice and Bob
// play optimally, return the maximum number of stones Alice can get.
//
//

LEETCODE_BEGIN_RESOLVING(1140, StoneGameII, Solution);

class Solution {
public:
  int stoneGameII(vector<int> &piles) {
    vector<vector<int>> dp(101, vector<int>(201, -1));
    int                 sum  = accumulate(piles.begin(), piles.end(), 0);
    int                 diff = solve(dp, piles, 0, 1);
    return (sum + diff) / 2;
  }

private:
  int solve(vector<vector<int>> &dp, vector<int> &piles, int i, int m) {
    if (i >= piles.size()) {
      return 0;
    }
    if (dp[i][m] != -1) {
      return dp[i][m];
    }
    int res = numeric_limits<int>::min();
    int tot = 0;
    for (int j = 0; j < 2 * m; ++j) {
      if (i + j < piles.size()) {
        tot += piles[i + j];
      }
      res = max(res, tot - solve(dp, piles, i + j + 1, max(1 + j, m)));
    }
    return dp[i][m] = res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= piles.length <= 100|
// * |1 <= piles[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: piles = [2,7,9,4,4]
// Output: 10
//
// If Alice takes one pile at the beginning, Bob takes two piles, then Alice
// takes 2 piles again. Alice can get 2 + 4 + 4 = 10 piles in total. If Alice
// takes two piles at the beginning, then Bob can take all three piles left. In
// this case, Alice get 2 + 7 = 9 piles in total. So we return 10 since it's
// larger.

LEETCODE_SOLUTION_UNITTEST(1140, StoneGameII, example_1) {
  auto        solution = MakeSolution();
  vector<int> piles    = {2, 7, 9, 4, 4};
  int         expect   = 10;
  int         actual   = solution->stoneGameII(piles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: piles = [1,2,3,4,5,100]
// Output: 104
//

LEETCODE_SOLUTION_UNITTEST(1140, StoneGameII, example_2) {
  auto        solution = MakeSolution();
  vector<int> piles    = {1, 2, 3, 4, 5, 100};
  int         expect   = 104;
  int         actual   = solution->stoneGameII(piles);
  LCD_EXPECT_EQ(expect, actual);
}
