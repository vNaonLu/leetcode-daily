// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Number of Ways to Paint N × 3 Grid
//
// https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/
//
// Question ID: 1411
// Difficult  : Hard
// Solve Date : 2026/01/03 15:23

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1411. Number of Ways to Paint N × 3 Grid|:
//
// You have a |grid| of size |n x 3| and you want to paint each cell of the grid
// with exactly one of the three colors: Red, Yellow, or Green while making sure
// that no two adjacent cells have the same color (i.e., no two cells that share
// vertical or horizontal sides have the same color). Given |n| the number of
// rows of the grid, return the number of ways you can paint this |grid|. As the
// answer may grow large, the answer must be computed modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(1411, NumberOfWaysToPaintN3Grid, Solution);

class Solution {
public:
  int numOfWays(int n) {
    uint64_t a = 6;
    uint64_t b = 6;
    for (int i = 2; i <= n; ++i) {
      auto na = (2 * a + 2 * b) % kMod;
      auto nb = (2 * a + 3 * b) % kMod;
      a       = na;
      b       = nb;
    }

    return (a + b) % kMod;
  }

private:
  static constexpr int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == grid.length|
// * |1 <= n <= 5000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1
// Output: 12
//

LEETCODE_SOLUTION_UNITTEST(1411, NumberOfWaysToPaintN3Grid, example_1) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 12;
  int  actual   = solution->numOfWays(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5000
// Output: 30228214
//

LEETCODE_SOLUTION_UNITTEST(1411, NumberOfWaysToPaintN3Grid, example_2) {
  auto solution = MakeSolution();
  int  n        = 5000;
  int  expect   = 30228214;
  int  actual   = solution->numOfWays(n);
  LCD_EXPECT_EQ(expect, actual);
}
