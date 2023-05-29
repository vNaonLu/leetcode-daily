// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Stone Game III
//
// https://leetcode.com/problems/stone-game-iii/
//
// Question ID: 1406
// Difficult  : Hard
// Solve Date : 2023/05/27 15:27

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1406. Stone Game III|:
//
// Alice and Bob continue their games with piles of stones. There are several
// stones arranged in a row, and each stone has an associated value which is an
// integer given in the array |stoneValue|. Alice and Bob take turns, with Alice
// starting first. On each player's turn, that player can take |1|, |2|, or |3|
// stones from the first remaining stones in the row. The score of each player
// is the sum of the values of the stones taken. The score of each player is |0|
// initially. The objective of the game is to end with the highest score, and
// the winner is the player with the highest score and there could be a tie. The
// game continues until all the stones have been taken. Assume Alice and Bob
// play optimally. Return |"Alice"| if Alice will win, |"Bob"| if Bob will win,
// or |"Tie"| if they will end the game with the same score.
//
//

LEETCODE_BEGIN_RESOLVING(1406, StoneGameIII, Solution);

class Solution {
public:
  string stoneGameIII(vector<int> &stoneValue) {
    int             n = stoneValue.size();
    vector<int64_t> pref(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
      pref[i] = pref[i - 1] + stoneValue[i - 1];
    }
    vector<vector<int>> dp(n + 1, vector<int>(2, -1));
    int                 alice = solve(pref, stoneValue, true, 0, dp);
    int                 bob   = pref.back() - alice;
    return alice > bob ? "Alice" : (bob > alice ? "Bob" : "Tie");
  }

private:
  int get(vector<int64_t> &pref, int l, int r) { return pref[r + 1] - pref[l]; }
  int solve(vector<int64_t> &pref, vector<int> &piles, bool alice, int idx,
            vector<vector<int>> &dp) {
    if (idx >= piles.size()) {
      return 0;
    }
    if (dp[idx][alice] != -1) {
      return dp[idx][alice];
    }
    if (alice) {
      int res = -1e9;
      for (int i = 1; i <= 3; ++i) {
        if (idx + i - 1 < piles.size()) {
          res = max(res, get(pref, idx, idx + i - 1) +
                             solve(pref, piles, false, idx + i, dp));
        }
      }
      return dp[idx][alice] = res;
    } else {
      int res = 1e9;
      for (int i = 1; i <= 3; ++i) {
        if (idx + i - 1 < piles.size()) {
          res = min(res, solve(pref, piles, true, idx + i, dp));
        }
      }
      return dp[idx][alice] = res;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= stoneValue.length <= 5 * 10⁴|
// * |-1000 <= stoneValue[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: values = [1,2,3,7]
// Output: "Bob"
//
// Alice will always lose. Her best move will be to take three piles and the
// score become 6. Now the score of Bob is 7 and Bob wins.

LEETCODE_SOLUTION_UNITTEST(1406, StoneGameIII, example_1) {
  auto        solution   = MakeSolution();
  vector<int> stoneValue = {1, 2, 3, 7};
  string      expected   = "Bob";
  string      actual     = solution->stoneGameIII(stoneValue);
  LCD_EXPECT_EQ(expected, actual);
}

// [Example #2]
//  Input: values = [1,2,3,-9]
// Output: "Alice"
//
// Alice must choose all the three piles at the first move to win and leave Bob
// with negative score. If Alice chooses one pile her score will be 1 and the
// next move Bob's score becomes 5. In the next move, Alice will take the pile
// with value = -9 and lose. If Alice chooses two piles her score will be 3 and
// the next move Bob's score becomes 3. In the next move, Alice will take the
// pile with value = -9 and also lose. Remember that both play optimally so here
// Alice will choose the scenario that makes her win.

LEETCODE_SOLUTION_UNITTEST(1406, StoneGameIII, example_2) {
  auto        solution   = MakeSolution();
  vector<int> stoneValue = {1, 2, 3, -9};
  string      expected   = "Alice";
  string      actual     = solution->stoneGameIII(stoneValue);
  LCD_EXPECT_EQ(expected, actual);
}

// [Example #3]
//  Input: values = [1,2,3,6]
// Output: "Tie"
//
// Alice cannot win this game. She can end the game in a draw if she decided to
// choose all the first three piles, otherwise she will lose.

LEETCODE_SOLUTION_UNITTEST(1406, StoneGameIII, example_3) {
  auto        solution   = MakeSolution();
  vector<int> stoneValue = {1, 2, 3, 6};
  string      expected   = "Tie";
  string      actual     = solution->stoneGameIII(stoneValue);
  LCD_EXPECT_EQ(expected, actual);
}
