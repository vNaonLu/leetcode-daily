// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Can I Win
//
// https://leetcode.com/problems/can-i-win/
//
// Question ID: 464
// Difficult  : Medium
// Solve Date : 2024/04/06 14:35

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |464. Can I Win|:
//
// In the "100 game" two players take turns adding, to a running total, any
// integer from |1| to |10|. The player who first causes the running total to
// reach or exceed 100 wins. What if we change the game so that players cannot
// re-use integers? For example, two players might take turns drawing from a
// common pool of numbers from 1 to 15 without replacement until they reach a
// total >= 100. Given two integers |maxChoosableInteger| and |desiredTotal|,
// return |true| if the first player to move can force a win, otherwise, return
// |false|. Assume both players play optimally.
//
//

LEETCODE_BEGIN_RESOLVING(464, CanIWin, Solution);

class Solution {
public:
  bool canIWin(int maxChoosableInteger, int desiredTotal) {
    if ((maxChoosableInteger * (maxChoosableInteger + 1) / 2 < desiredTotal)) {
      return false;
    }
    vector<vector<int>> dp(2, vector<int>(1 << maxChoosableInteger, -1));
    return dfs(&dp, maxChoosableInteger, desiredTotal, 0, 0, 0);
  }

private:
  bool dfs(vector<vector<int>> *dp, int m, int t, int mask, int player,
           int score) {
    if ((*dp)[player][mask] != -1) {
      return (*dp)[player][mask];
    }
    for (int i = 0; i < m; ++i) {
      int c = 1 << i;
      if ((mask & c) == 0) {
        if (score + 1 + i >= t ||
            !dfs(dp, m, t, mask | c, player ^ 1, score + i + 1)) {
          return (*dp)[player][mask] = 1;
        }
      }
    }
    return (*dp)[player][mask] = 0;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= maxChoosableInteger <= 20|
// * |0 <= desiredTotal <= 300|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: maxChoosableInteger = 10, desiredTotal = 11
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(464, CanIWin, example_1) {
  auto solution            = MakeSolution();
  int  maxChoosableInteger = 10;
  int  desiredTotal        = 11;
  bool expect              = false;
  bool actual = solution->canIWin(maxChoosableInteger, desiredTotal);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: maxChoosableInteger = 10, desiredTotal = 0
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(464, CanIWin, example_2) {
  auto solution            = MakeSolution();
  int  maxChoosableInteger = 10;
  int  desiredTotal        = 0;
  bool expect              = true;
  bool actual = solution->canIWin(maxChoosableInteger, desiredTotal);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: maxChoosableInteger = 10, desiredTotal = 1
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(464, CanIWin, example_3) {
  auto solution            = MakeSolution();
  int  maxChoosableInteger = 10;
  int  desiredTotal        = 1;
  bool expect              = true;
  bool actual = solution->canIWin(maxChoosableInteger, desiredTotal);
  LCD_EXPECT_EQ(expect, actual);
}
