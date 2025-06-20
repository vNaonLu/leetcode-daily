// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Manhattan Distance After K Changes
//
// https://leetcode.com/problems/maximum-manhattan-distance-after-k-changes/
//
// Question ID: 3443
// Difficult  : Medium
// Solve Date : 2025/06/20 20:14

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3443. Maximum Manhattan Distance After K Changes|:
//
// You are given a string |s| consisting of the characters |'N'|, |'S'|, |'E'|,
// and |'W'|, where |s[i]| indicates movements in an infinite grid:
//
//  • |'N'| : Move north by 1 unit.
//
//  • |'S'| : Move south by 1 unit.
//
//  • |'E'| : Move east by 1 unit.
//
//  • |'W'| : Move west by 1 unit.
// Initially, you are at the origin |(0, 0)|. You can change at most |k|
// characters to any of the four directions. Find the maximum Manhattan distance
// from the origin that can be achieved at any time while performing the
// movements in order. The Manhattan Distance between two cells |(xᵢ, yᵢ)| and
// |(xⱼ, yⱼ)| is ||xᵢ - xⱼ| + |yᵢ - yⱼ||.
//
//

LEETCODE_BEGIN_RESOLVING(3443, MaximumManhattanDistanceAfterKChanges, Solution);

class Solution {
public:
  int maxDistance(string s, int k) {
    int res   = 0;
    int north = 0, south = 0, east = 0, west = 0;

    for (int i = 0; i < s.size(); i++) {
      char c = s[i];
      if (c == 'N')
        north++;
      else if (c == 'S')
        south++;
      else if (c == 'E')
        east++;
      else if (c == 'W')
        west++;

      int x   = abs(north - south);
      int y   = abs(east - west);
      int MD  = x + y;
      int dis = MD + min(2 * k, i + 1 - MD);
      res     = max(res, dis);
    }

    return res;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |0 <= k <= s.length|
// * |s| consists of only |'N'|, |'S'|, |'E'|, and |'W'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "NWSE", k = 1
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3443, MaximumManhattanDistanceAfterKChanges,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "NWSE";
  int    k        = 1;
  int    expect   = 3;
  int    actual   = solution->maxDistance(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "NSWWEW", k = 3
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(3443, MaximumManhattanDistanceAfterKChanges,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "NSWWEW";
  int    k        = 3;
  int    expect   = 6;
  int    actual   = solution->maxDistance(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
