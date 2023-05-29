// Copyright 2023 Naon Lu
//
// This file describes the solution of
// New 21 Game
//
// https://leetcode.com/problems/new-21-game/
//
// Question ID: 837
// Difficult  : Medium
// Solve Date : 2023/05/25 14:58

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |837. New 21 Game|:
//
// Alice plays the following game, loosely based on the card game "21".
// Alice starts with |0| points and draws numbers while she has less than |k|
// points. During each draw, she gains an integer number of points randomly from
// the range |[1, maxPts]|, where |maxPts| is an integer. Each draw is
// independent and the outcomes have equal probabilities. Alice stops drawing
// numbers when she gets |k| or more points. Return the probability that Alice
// has |n| or fewer points. Answers within |10⁻⁵| of the actual answer are
// considered accepted.
//
//

LEETCODE_BEGIN_RESOLVING(837, New21Game, Solution);

class Solution {
public:
  double new21Game(int n, int k, int maxPts) {
    if (k == 0 || n >= k + maxPts) {
      return 1.0;
    }
    vector<double> dp(n + 1);
    double         cur = 1.0;
    double         res = 0.0;
    dp[0]              = 1.0;
    for (int i = 1; i < n + 1; ++i) {
      dp[i] = cur / maxPts;
      if (i < k) {
        cur += dp[i];
      } else {
        res += dp[i];
      }
      if (i - maxPts >= 0) {
        cur -= dp[i - maxPts];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= k <= n <= 10⁴|
// * |1 <= maxPts <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 10, k = 1, maxPts = 10
// Output: 1.00000
//
// Alice gets a single card, then stops.

LEETCODE_SOLUTION_UNITTEST(837, New21Game, example_1) {
  auto   solution = MakeSolution();
  int    n        = 10;
  int    k        = 1;
  int    maxPts   = 10;
  double expect   = 1.00000;
  double actual   = solution->new21Game(n, k, maxPts);
  EXPECT_NEAR(expect, actual, 0.00001);
}

// [Example #2]
//  Input: n = 6, k = 1, maxPts = 10
// Output: 0.60000
//
// Alice gets a single card, then stops.
// In 6 out of 10 possibilities, she is at or below 6 points.

LEETCODE_SOLUTION_UNITTEST(837, New21Game, example_2) {
  auto   solution = MakeSolution();
  int    n        = 6;
  int    k        = 1;
  int    maxPts   = 10;
  double expect   = 0.60000;
  double actual   = solution->new21Game(n, k, maxPts);
  EXPECT_NEAR(expect, actual, 0.00001);
}

// [Example #3]
//  Input: n = 21, k = 17, maxPts = 10
// Output: 0.73278
//

LEETCODE_SOLUTION_UNITTEST(837, New21Game, example_3) {
  auto   solution = MakeSolution();
  int    n        = 21;
  int    k        = 17;
  int    maxPts   = 10;
  double expect   = 0.73278;
  double actual   = solution->new21Game(n, k, maxPts);
  EXPECT_NEAR(expect, actual, 0.00001);
}
