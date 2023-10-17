// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Ways to Stay in the Same Place After Some Steps
//
// https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/
//
// Question ID: 1269
// Difficult  : Hard
// Solve Date : 2023/10/15 14:30

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1269. Number of Ways to Stay in the Same Place After Some
// Steps|:
//
// You have a pointer at index |0| in an array of size |arrLen|. At each step,
// you can move 1 position to the left, 1 position to the right in the array, or
// stay in the same place (The pointer should not be placed outside the array at
// any time). Given two integers |steps| and |arrLen|, return the number of ways
// such that your pointer is still at index |0| after exactly |steps| steps.
// Since the answer may be too large, return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(1269, NumberOfWaysToStayInTheSamePlaceAfterSomeSteps,
                         Solution);

class Solution {
public:
  int numWays(int steps, int arrLen) {
    int                 max_col = min(steps, arrLen - 1);
    vector<vector<int>> dp(2, vector<int>(max_col + 1));
    dp[0][0] = 1;
    for (int i = 1; i <= steps; ++i) {
      for (int j = 0; j <= max_col; ++j) {
        dp[i % 2][j] = dp[(i - 1) % 2][j];
        if (j - 1 >= 0) {
          dp[i % 2][j] = (dp[i % 2][j] + dp[(i - 1) % 2][j - 1]) % kMod;
        }
        if (j + 1 <= max_col) {
          dp[i % 2][j] = (dp[i % 2][j] + dp[(i - 1) % 2][j + 1]) % kMod;
        }
      }
    }
    return dp[steps % 2][0];
  }

private:
  constexpr static int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= steps <= 500|
// * |1 <= arrLen <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: steps = 3, arrLen = 2
// Output: 4
//
// There are 4 differents ways to stay at index 0 after 3 steps.
// Right, Left, Stay
// Stay, Right, Left
// Right, Stay, Left
// Stay, Stay, Stay

LEETCODE_SOLUTION_UNITTEST(1269, NumberOfWaysToStayInTheSamePlaceAfterSomeSteps,
                           example_1) {
  auto solution = MakeSolution();
  int  steps    = 3;
  int  arrLen   = 2;
  int  expect   = 4;
  int  actual   = solution->numWays(steps, arrLen);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: steps = 2, arrLen = 4
// Output: 2
//
// There are 2 differents ways to stay at index 0 after 2 steps
// Right, Left
// Stay, Stay

LEETCODE_SOLUTION_UNITTEST(1269, NumberOfWaysToStayInTheSamePlaceAfterSomeSteps,
                           example_2) {
  auto solution = MakeSolution();
  int  steps    = 2;
  int  arrLen   = 4;
  int  expect   = 2;
  int  actual   = solution->numWays(steps, arrLen);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: steps = 4, arrLen = 2
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(1269, NumberOfWaysToStayInTheSamePlaceAfterSomeSteps,
                           example_3) {
  auto solution = MakeSolution();
  int  steps    = 4;
  int  arrLen   = 2;
  int  expect   = 8;
  int  actual   = solution->numWays(steps, arrLen);
  LCD_EXPECT_EQ(expect, actual);
}
