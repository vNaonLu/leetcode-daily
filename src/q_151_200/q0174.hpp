
#ifndef LEETCODE_Q174_H__
#define LEETCODE_Q174_H__
#include <iostream>
#include <vector>

namespace l174 {
using namespace std;

/**
  * This file is generated by leetcode_add.py
  *
  * 174.
  *      Dungeon Game
  *
  * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
  *
  *   The demons had captured the princess and imprisoned her in “the
  *   bottom-right corner” of a ‘dungeon’ . The ‘dungeon’ consists of ‘m x
  *   n’ rooms laid out in a 2D grid. Our valiant knight was initially
  *   positioned in “the top-left room” and must fight his way through
  *   ‘dungeon’ to rescue the princess.
  *   
  *   The knight has an initial health point represented by a positive
  *   integer. If at any point his health point drops to ‘0’ or below, he
  *   dies immediately.
  *   
  *   Some of the rooms are guarded by demons (represented by negative
  *   integers), so the knight loses health upon entering these rooms; other
  *   rooms are either empty (represented as 0) or contain magic orbs that
  *   increase the knight's health (represented by positive integers).
  *   
  *   To reach the princess as quickly as possible, the knight decides to
  *   move only “rightward” or “downward” in each step.
  *   
  *   Return “the knight's minimum initial health so that he can rescue the
  *   princess”.
  *   
  *   “Note” that any room can contain threats or power-ups, even the first
  *   room the knight enters and the bottom-right room where the princess is
  *   imprisoned.
  *
  * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
  *
  *   • ‘m = dungeon.length’
  *   • ‘n = dungeon[i].length’
  *   • ‘1 ≤ m, n ≤ 200’
  *   • ‘-1000 ≤ dungeon[i][j] ≤ 1000’
  *
*/

class Solution {
 public:
  int calculateMinimumHP(vector<vector<int>>& dungeon) {
    int m = dungeon.size();
    int n = dungeon[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));

    dp[m - 1][n - 1] = dungeon[m - 1][n - 1] > 0 ? 1 : 1 - dungeon[m - 1][n - 1];

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
}  // namespace l174

#endif