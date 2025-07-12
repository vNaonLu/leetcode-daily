// Copyright 2025 Naon Lu
//
// This file describes the solution of
// The Earliest and Latest Rounds Where Players Compete
//
// https://leetcode.com/problems/the-earliest-and-latest-rounds-where-players-compete/
//
// Question ID: 1900
// Difficult  : Hard
// Solve Date : 2025/07/12 15:32

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1900. The Earliest and Latest Rounds Where Players Compete|:
//
// There is a tournament where |n| players are participating. The players are
// standing in a single row and are numbered from |1| to |n| based on their
// initial standing position (player |1| is the first player in the row, player
// |2| is the second player in the row, etc.). The tournament consists of
// multiple rounds (starting from round number |1|). In each round, the |iᵗʰ|
// player from the front of the row competes against the |iᵗʰ| player from the
// end of the row, and the winner advances to the next round. When the number of
// players is odd for the current round, the player in the middle automatically
// advances to the next round.
//
//  • For example, if the row consists of players |1, 2, 4, 6, 7|
//
//
//    • Player |1| competes against player |7|.
//
//    • Player |2| competes against player |6|.
//
//    • Player |4| automatically advances to the next round.
//
//
// After each round is over, the winners are lined back up in the row based on
// the original ordering assigned to them initially (ascending order). The
// players numbered |firstPlayer| and |secondPlayer| are the best in the
// tournament. They can win against any other player before they compete against
// each other. If any two other players compete against each other, either of
// them might win, and thus you may choose the outcome of this round. Given the
// integers |n|, |firstPlayer|, and |secondPlayer|, return an integer array
// containing two values, the earliest possible round number and the latest
// possible round number in which these two players will compete against each
// other, respectively.
//
//

LEETCODE_BEGIN_RESOLVING(1900, TheEarliestAndLatestRoundsWherePlayersCompete,
                         Solution);

class Solution {
public:
  pair<int, int> dfs(int n, int p1, int p2) {
    // Step 1: Base case — they meet
    if (p1 + p2 == n + 1) {
      return {1, 1};
    }

    if (p1 > p2) {
      swap(p1, p2);
    }

    if (n <= 4) {
      return {2, 2};
    }

    int m    = (n + 1) / 2;
    int minR = numeric_limits<int>::max();
    int maxR = numeric_limits<int>::min();

    if (p1 - 1 > n - p2) {
      int t = n + 1 - p1;
      p1    = n + 1 - p2;
      p2    = t;
    }

    if (p2 * 2 <= n + 1) {
      int a = p1 - 1;
      int b = p2 - p1 - 1;

      for (int i = 0; i <= a; ++i) {
        for (int j = 0; j <= b; ++j) {
          auto [r1, r2] = dfs(m, i + 1, i + j + 2);
          minR          = min(minR, r1 + 1);
          maxR          = max(maxR, r2 + 1);
        }
      }
    } else {
      int p4 = n + 1 - p2;
      int a  = p1 - 1;
      int b  = p4 - p1 - 1;
      int c  = p2 - p4 - 1;

      for (int i = 0; i <= a; ++i) {
        for (int j = 0; j <= b; ++j) {
          int offset    = i + j + 1 + (c + 1) / 2 + 1;
          auto [r1, r2] = dfs(m, i + 1, offset);
          minR          = min(minR, r1 + 1);
          maxR          = max(maxR, r2 + 1);
        }
      }
    }

    return {minR, maxR};
  }

  vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
    auto [earliest, latest] = dfs(n, firstPlayer, secondPlayer);
    return {earliest, latest};
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 28|
// * |1 <= firstPlayer < secondPlayer <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 11, firstPlayer = 2, secondPlayer = 4
// Output: [3,4]
//

LEETCODE_SOLUTION_UNITTEST(1900, TheEarliestAndLatestRoundsWherePlayersCompete,
                           example_1) {
  auto        solution     = MakeSolution();
  int         n            = 11;
  int         firstPlayer  = 2;
  int         secondPlayer = 4;
  vector<int> expect       = {3, 4};
  vector<int> actual =
      solution->earliestAndLatest(n, firstPlayer, secondPlayer);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5, firstPlayer = 1, secondPlayer = 5
// Output: [1,1]
//

LEETCODE_SOLUTION_UNITTEST(1900, TheEarliestAndLatestRoundsWherePlayersCompete,
                           example_2) {
  auto        solution     = MakeSolution();
  int         n            = 5;
  int         firstPlayer  = 1;
  int         secondPlayer = 5;
  vector<int> expect       = {1, 1};
  vector<int> actual =
      solution->earliestAndLatest(n, firstPlayer, secondPlayer);
  LCD_EXPECT_EQ(expect, actual);
}
