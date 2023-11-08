// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Determine if a Cell Is Reachable at a Given Time
//
// https://leetcode.com/problems/determine-if-a-cell-is-reachable-at-a-given-time/
//
// Question ID: 2849
// Difficult  : Medium
// Solve Date : 2023/11/08 19:16

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2849. Determine if a Cell Is Reachable at a Given Time|:
//
// You are given four integers |sx|, |sy|, |fx|, |fy|, and a non-negative
// integer |t|. In an infinite 2D grid, you start at the cell |(sx, sy)|. Each
// second, you must move to any of its adjacent cells. Return |true| if you can
// reach cell |(fx, fy)| after exactly |t| seconds, or |false| otherwise. A
// cell's adjacent cells are the 8 cells around it that share at least one
// corner with it. You can visit the same cell several times.
//
//

LEETCODE_BEGIN_RESOLVING(2849, DetermineIfACellIsReachableAtAGivenTime,
                         Solution);

class Solution {
public:
  bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
    if (sx == fx && sy == fy) {
      return (t > 1 || t == 0);
    }
    auto diffx      = abs(sx - fx);
    auto diffy      = abs(sy - fy);
    int  extra_time = abs(diffy - diffx);
    return min(diffx, diffy) <= t - extra_time;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= sx, sy, fx, fy <= 10⁹|
// * |0 <= t <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: sx = 2, sy = 4, fx = 7, fy = 7, t = 6
// Output: true
//
// Starting at cell (2, 4), we can reach cell (7, 7) in exactly 6 seconds by
// going through the cells depicted in the picture above.

LEETCODE_SOLUTION_UNITTEST(2849, DetermineIfACellIsReachableAtAGivenTime,
                           example_1) {
  auto solution = MakeSolution();
  int  sx       = 2;
  int  sy       = 4;
  int  fx       = 7;
  int  fy       = 7;
  int  t        = 6;
  bool expect   = true;
  bool actual   = solution->isReachableAtTime(sx, sy, fx, fy, t);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: sx = 3, sy = 1, fx = 7, fy = 3, t = 3
// Output: false
//
// Starting at cell (3, 1), it takes at least 4 seconds to reach cell (7, 3) by
// going through the cells depicted in the picture above. Hence, we cannot reach
// cell (7, 3) at the third second.

LEETCODE_SOLUTION_UNITTEST(2849, DetermineIfACellIsReachableAtAGivenTime,
                           example_2) {
  auto solution = MakeSolution();
  int  sx       = 3;
  int  sy       = 1;
  int  fx       = 7;
  int  fy       = 3;
  int  t        = 3;
  bool expect   = false;
  bool actual   = solution->isReachableAtTime(sx, sy, fx, fy, t);
  LCD_EXPECT_EQ(expect, actual);
}
