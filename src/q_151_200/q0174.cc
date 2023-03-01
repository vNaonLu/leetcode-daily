// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Dungeon Game
//
// https://leetcode.com/problems/dungeon-game/
//
// Question ID: 174
// Difficult  : Hard
// Solve Date : 2021/10/02 13:20

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |174. Dungeon Game|:
//
// The demons had captured the princess and imprisoned her in the bottom-right
// corner of a |dungeon|. The |dungeon| consists of |m x n| rooms laid out in a
// 2D grid. Our valiant knight was initially positioned in the top-left room and
// must fight his way through |dungeon| to rescue the princess. The knight has
// an initial health point represented by a positive integer. If at any point
// his health point drops to |0| or below, he dies immediately. Some of the
// rooms are guarded by demons (represented by negative integers), so the knight
// loses health upon entering these rooms; other rooms are either empty
// (represented as 0) or contain magic orbs that increase the knight's health
// (represented by positive integers). To reach the princess as quickly as
// possible, the knight decides to move only rightward or downward in each step.
// Return the knight's minimum initial health so that he can rescue the
// princess. Note that any room can contain threats or power-ups, even the first
// room the knight enters and the bottom-right room where the princess is
// imprisoned.  
//

LEETCODE_BEGIN_RESOLVING(174, DungeonGame, Solution);

class Solution {
public:
  int calculateMinimumHP(vector<vector<int>> &dungeon) {
    int                 m = dungeon.size();
    int                 n = dungeon[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[m - 1][n - 1] =
        dungeon[m - 1][n - 1] > 0 ? 1 : 1 - dungeon[m - 1][n - 1];
    for (int i = m - 2; i >= 0; --i)
      dp[i][n - 1] = max(dp[i + 1][n - 1] - dungeon[i][n - 1], 1);
    for (int j = n - 2; j >= 0; --j)
      dp[m - 1][j] = max(dp[m - 1][j + 1] - dungeon[m - 1][j], 1);
    for (int i = m - 2; i >= 0; --i)
      for (int j = n - 2; j >= 0; --j)
        dp[i][j] = max(min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j], 1);
    return dp.front().front();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == dungeon.length|
// * |n == dungeon[i].length|
// * |1 <= m, n <= 200|
// * |-1000 <= dungeon[i][j] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
// Output: 7
//
// The initial health of the knight must be at least 7 if he follows the optimal
// path: RIGHT-> RIGHT -> DOWN -> DOWN.

LEETCODE_SOLUTION_UNITTEST(174, DungeonGame, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> dungeon  = {
      {-2,  -3,  3},
      {-5, -10,  1},
      {10,  30, -5}
  };
  int expect = 7;
  int actual = solution->calculateMinimumHP(dungeon);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: dungeon = [[0]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(174, DungeonGame, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> dungeon  = {{0}};
  int                 expect   = 1;
  int                 actual   = solution->calculateMinimumHP(dungeon);
  LCD_EXPECT_EQ(expect, actual);
}
