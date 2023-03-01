// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Last Stone Weight II
//
// https://leetcode.com/problems/last-stone-weight-ii/
//
// Question ID: 1049
// Difficult  : Medium
// Solve Date : 2022/06/06 18:16

#include <iosfwd>
#include <limits>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1049. Last Stone Weight II|:
//
// You are given an array of integers |stones| where |stones[i]| is the weight
// of the |iᵗʰ| stone. We are playing a game with the stones. On each turn, we
// choose any two stones and smash them together. Suppose the stones have
// weights |x| and |y| with |x <= y|. The result of this smash is:
//
//  • If |x == y|, both stones are destroyed, and
//
//  • If |x != y|, the stone of weight |x| is destroyed, and the stone of weight
//  |y| has new weight |y - x|.
// At the end of the game, there is at most one stone left.
// Return the smallest possible weight of the left stone. If there are no stones
// left, return |0|.
//

LEETCODE_BEGIN_RESOLVING(1049, LastStoneWeightII, Solution);

class Solution {
public:
  int lastStoneWeightII(vector<int> &stones) {
    auto                sum = accumulate(stones.begin(), stones.end(), 0);
    vector<vector<int>> dp(stones.size() + 1, vector<int>(sum / 2 + 1, 0));

    for (int i = 0; i <= stones.size(); ++i) {
      dp[i][0] = 1;
    }

    for (int i = 1; i < dp.size(); ++i) {
      for (int j = 1; j < dp.front().size(); ++j) {
        if (j >= stones[i - 1]) {
          dp[i][j] = dp[i - 1][j] || dp[i - 1][j - stones[i - 1]];
        } else {
          dp[i][j] = dp[i - 1][j];
        }
      }
    }

    int res = numeric_limits<int>::max();
    for (int i = 0; i < dp.back().size(); ++i) {
      if (dp.back()[i]) {
        res = min<int>(res, sum - 2 * i);
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= stones.length <= 30|
// * |1 <= stones[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: stones = [2,7,4,1,8,1]
// Output: 1
//
// We can combine 2 and 4 to get 2, so the array converts to [2,7,1,8,1] then,
// we can combine 7 and 8 to get 1, so the array converts to [2,1,1,1] then,
// we can combine 2 and 1 to get 1, so the array converts to [1,1,1] then,
// we can combine 1 and 1 to get 0, so the array converts to [1], then that's
// the optimal value.

LEETCODE_SOLUTION_UNITTEST(1049, LastStoneWeightII, example_1) {
  auto        solution = MakeSolution();
  vector<int> stones   = {2, 7, 4, 1, 8, 1};
  int         expect   = 1;
  int         actual   = solution->lastStoneWeightII(stones);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: stones = [31,26,33,21,40]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(1049, LastStoneWeightII, example_2) {
  auto        solution = MakeSolution();
  vector<int> stones   = {31, 26, 33, 21, 40};
  int         expect   = 5;
  int         actual   = solution->lastStoneWeightII(stones);
  LCD_EXPECT_EQ(expect, actual);
}
