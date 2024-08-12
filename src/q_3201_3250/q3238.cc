// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the Number of Winning Players
//
// https://leetcode.com/problems/find-the-number-of-winning-players/
//
// Question ID: 3238
// Difficult  : Easy
// Solve Date : 2024/08/12 21:36

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3238. Find the Number of Winning Players|:
//
// You are given an integer |n| representing the number of players in a game and
// a 2D array |pick| where |pick[i] = [xᵢ, yᵢ]| represents that the player |xᵢ|
// picked a ball of color |yᵢ|. Player |i| wins the game if they pick strictly
// more than |i| balls of the same color. In other words,
//
//  • Player 0 wins if they pick any ball.
//
//  • Player 1 wins if they pick at least two balls of the same color.
//
//  • ...
//
//  • Player |i| wins if they pick at least |i + 1| balls of the same color.
// Return the number of players who win the game.
// Note that multiple players can win the game.
//
//

LEETCODE_BEGIN_RESOLVING(3238, FindTheNumberOfWinningPlayers, Solution);

class Solution {
public:
  int winningPlayerCount(int n, vector<vector<int>> &pick) {
    unordered_map<int, unordered_map<int, int>> picked;
    for (int i = 0; i < n; ++i) {
      picked[i] = {};
    }
    for (auto &v : pick) {
      ++picked[v[0]][v[1]];
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
      for (auto &m : picked[i]) {
        if (m.second >= i + 1) {
          ++res;
          break;
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10|
// * |1 <= pick.length <= 100|
// * |pick[i].length == 2|
// * |0 <= xᵢ <= n - 1 |
// * |0 <= yᵢ <= 10|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, pick = [[0,0],[1,0],[1,0],[2,1],[2,1],[2,0]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3238, FindTheNumberOfWinningPlayers, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> pick     = {
      {0, 0},
      {1, 0},
      {1, 0},
      {2, 1},
      {2, 1},
      {2, 0}
  };
  int expect = 2;
  int actual = solution->winningPlayerCount(n, pick);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5, pick = [[1,1],[1,2],[1,3],[1,4]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3238, FindTheNumberOfWinningPlayers, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> pick     = {
      {1, 1},
      {1, 2},
      {1, 3},
      {1, 4}
  };
  int expect = 0;
  int actual = solution->winningPlayerCount(n, pick);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 5, pick = [[1,1],[2,4],[2,4],[2,4]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3238, FindTheNumberOfWinningPlayers, example_3) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> pick     = {
      {1, 1},
      {2, 4},
      {2, 4},
      {2, 4}
  };
  int expect = 1;
  int actual = solution->winningPlayerCount(n, pick);
  LCD_EXPECT_EQ(expect, actual);
}
