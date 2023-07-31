// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Predict the Winner
//
// https://leetcode.com/problems/predict-the-winner/
//
// Question ID: 486
// Difficult  : Medium
// Solve Date : 2023/07/28 14:51

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |486. Predict the Winner|:
//
// You are given an integer array |nums|. Two players are playing a game with
// this array: player 1 and player 2. Player 1 and player 2 take turns, with
// player 1 starting first. Both players start the game with a score of |0|. At
// each turn, the player takes one of the numbers from either end of the array
// (i.e., |nums[0]| or |nums[nums.length - 1]|) which reduces the size of the
// array by |1|. The player adds the chosen number to their score. The game ends
// when there are no more elements in the array. Return |true| if Player 1 can
// win the game. If the scores of both players are equal, then player 1 is still
// the winner, and you should also return |true|. You may assume that both
// players are playing optimally.
//
//

LEETCODE_BEGIN_RESOLVING(486, PredictTheWinner, Solution);

class Solution {
public:
  bool PredictTheWinner(vector<int> &nums) {
    int                 n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return helper(&dp, nums, 0, n - 1, 0) >= 0;
  }

private:
  int helper(vector<vector<int>> *dp, vector<int> &v, int i, int j, int k) {
    if (i > j) {
      return 0;
    }
    if ((*dp)[i][j] != -1) {
      return (*dp)[i][j];
    }
    int res = 0;
    if (k & 1) {
      int f = -v[i] + helper(dp, v, i + 1, j, k + 1);
      int l = -v[j] + helper(dp, v, i, j - 1, k + 1);
      res   = min(f, l);
    } else {
      int f = v[i] + helper(dp, v, i + 1, j, k + 1);
      int l = v[j] + helper(dp, v, i, j - 1, k + 1);
      res   = max(f, l);
    }
    return (*dp)[i][j] = res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 20|
// * |0 <= nums[i] <= 10⁷|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,5,2]
// Output: false
//
// Initially, player 1 can choose between 1 and 2.
// If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If
// player 2 chooses 5, then player 1 will be left with 1 (or 2). So, final score
// of player 1 is 1 + 2 = 3, and player 2 is 5. Hence, player 1 will never be
// the winner and you need to return false.

LEETCODE_SOLUTION_UNITTEST(486, PredictTheWinner, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 5, 2};
  bool        expect   = false;
  bool        actual   = solution->PredictTheWinner(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,5,233,7]
// Output: true
//
// Player 1 first chooses 1. Then player 2 has to choose between 5 and 7. No
// matter which number player 2 choose, player 1 can choose 233. Finally, player
// 1 has more score (234) than player 2 (12), so you need to return True
// representing player1 can win.

LEETCODE_SOLUTION_UNITTEST(486, PredictTheWinner, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 5, 233, 7};
  bool        expect   = true;
  bool        actual   = solution->PredictTheWinner(nums);
  LCD_EXPECT_EQ(expect, actual);
}
