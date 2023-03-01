// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Snakes and Ladders
//
// https://leetcode.com/problems/snakes-and-ladders/
//
// Question ID: 909
// Difficult  : Medium
// Solve Date : 2023/01/24 15:56

#include <iosfwd>
#include <numeric>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |909. Snakes and Ladders|:
//
// You are given an |n x n| integer matrix |board| where the cells are labeled
// from |1| to |n²| in a Boustrophedon style starting from the bottom left of
// the board (i.e. |board[n - 1][0]|) and alternating direction each row. You
// start on square |1| of the board. In each move, starting from square |curr|,
// do the following:
//
//  • Choose a destination square |next| with a label in the range |[curr + 1,
//  min(curr + 6, n²)]|.
//
//
//    • This choice simulates the result of a standard 6-sided die roll: i.e.,
//    there are always at most 6 destinations, regardless of the size of the
//    board.
//
//
//
//  • If |next| has a snake or ladder, you must move to the destination of that
//  snake or ladder. Otherwise, you move to |next|.
//
//  • The game ends when you reach the square |n²|.
// A board square on row |r| and column |c| has a snake or ladder if
// |board[r][c] != -1|. The destination of that snake or ladder is
// |board[r][c]|. Squares |1| and |n²| do not have a snake or ladder. Note that
// you only take a snake or ladder at most once per move. If the destination to
// a snake or ladder is the start of another snake or ladder, you do not follow
// the subsequentsnake or ladder.
//
//  • For example, suppose the board is |[[-1,4],[-1,3]]|, and on the first
//  move, your destination square is |2|. You follow the ladder to square |3|,
//  but do not follow the subsequent ladder to |4|.
// Return the least number of moves required to reach the square |n²|. If it is
// not possible to reach the square, return |-1|.
//

LEETCODE_BEGIN_RESOLVING(909, SnakesAndLadders, Solution);

class Solution {
public:
  int snakesAndLadders(vector<vector<int>> &board) {
    int                    n     = board.size();
    int                    label = 1;
    vector<pair<int, int>> cell(n * n + 1);
    vector<int>            cols(n);
    iota(cols.begin(), cols.end(), 0);
    for (int i = n - 1; i >= 0; --i) {
      for (auto c : cols) {
        cell[label++] = {i, c};
      }
      reverse(cols.begin(), cols.end());
    }
    vector<int> dp(n * n + 1, -1);
    queue<int>  q;
    dp[1] = 0;
    q.emplace(1);
    while (!q.empty()) {
      auto curr = q.front();
      q.pop();
      for (int i = curr + 1; i <= min(curr + 6, n * n); ++i) {
        auto [r, c] = cell[i];
        int dest    = board[r][c] != -1 ? board[r][c] : i;
        if (dp[dest] == -1) {
          dp[dest] = dp[curr] + 1;
          q.emplace(dest);
        }
      }
    }
    return dp.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == board.length == board[i].length|
// * |2 <= n <= 20|
// * |board[i][j]| is either |-1| or in the range |[1, n²]|.
// * The squares labeled |1| and |n²| do not have any ladders or snakes.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: board =
//  [[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,35,-1,-1,13,-1],[-1,-1,-1,-1,-1,-1],[-1,15,-1,-1,-1,-1]]
// Output: 4
//
// In the beginning, you start at square 1 (at row 5, column 0).
// You decide to move to square 2 and must take the ladder to square 15.
// You then decide to move to square 17 and must take the snake to square 13.
// You then decide to move to square 14 and must take the ladder to square 35.
// You then decide to move to square 36, ending the game.
// This is the lowest possible number of moves to reach the last square, so
// return 4.

LEETCODE_SOLUTION_UNITTEST(909, SnakesAndLadders, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> board    = {
      {-1, -1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1, -1},
      {-1, 35, -1, -1, 13, -1},
      {-1, -1, -1, -1, -1, -1},
      {-1, 15, -1, -1, -1, -1}
  };
  int expect = 4;
  int actual = solution->snakesAndLadders(board);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: board = [[-1,-1],[-1,3]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(909, SnakesAndLadders, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> board    = {
      {-1, -1},
      {-1,  3}
  };
  int expect = 1;
  int actual = solution->snakesAndLadders(board);
  LCD_EXPECT_EQ(expect, actual);
}
