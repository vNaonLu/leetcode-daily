// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Number of Arrows to Burst Balloons
//
// https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
//
// Question ID: 452
// Difficult  : Medium
// Solve Date : 2022/01/13 18:10

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |452. Minimum Number of Arrows to Burst Balloons|:
//
// There are some spherical balloons taped onto a flat wall that represents the
// XY-plane. The balloons are represented as a 2D integer array |points| where
// |points[i] = [xₛₜₐᵣₜ, xₑₙᵈ]| denotes a balloon whose horizontal diameter
// stretches between |xₛₜₐᵣₜ| and |xₑₙᵈ|. You do not know the exact
// y-coordinates of the balloons. Arrows can be shot up directly vertically (in
// the positive y-direction) from different points along the x-axis. A balloon
// with |xₛₜₐᵣₜ| and |xₑₙᵈ| is burst by an arrow shot at |x| if |xₛₜₐᵣₜ <= x <=
// xₑₙᵈ|. There is no limit to the number of arrows that can be shot. A shot
// arrow keeps traveling up infinitely, bursting any balloons in its path. Given
// the array |points|, return the minimum number of arrows that must be shot to
// burst all balloons.  
//

LEETCODE_BEGIN_RESOLVING(452, MinimumNumberOfArrowsToBurstBalloons, Solution);

class Solution {
private:
  using diameter_t = pair<int, int>;

public:
  int findMinArrowShots(vector<vector<int>> &points) {
    if (points.empty())
      return 0;
    priority_queue<diameter_t> pq;
    vector<int>                dp(points.size(), 0);

    for (const auto &v : points) {
      pq.emplace(v[0], v[1]);
    }

    dp.front() = 1;
    int  i     = 1;
    auto range = pq.top();
    pq.pop();
    while (!pq.empty()) {
      auto cur = pq.top();
      pq.pop();
      if (cur.second < range.first) {
        dp[i] = dp[i - 1] + 1;
        range = cur;
      } else {
        dp[i]        = dp[i - 1];
        range.first  = min(range.first, cur.second);
        range.second = max(range.first, cur.second);
      }
      ++i;
    }
    return dp.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= points.length <= 10⁵|
// * |points[i].length == 2|
// * |-2³¹ <= xₛₜₐᵣₜ < xₑₙᵈ <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: points = [[10,16],[2,8],[1,6],[7,12]]
// Output: 2
//
// The balloons can be burst by 2 arrows:
// - Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
// - Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].

LEETCODE_SOLUTION_UNITTEST(452, MinimumNumberOfArrowsToBurstBalloons,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {10, 16},
      { 2,  8},
      { 1,  6},
      { 7, 12}
  };
  int expect = 2;
  int actual = solution->findMinArrowShots(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: points = [[1,2],[3,4],[5,6],[7,8]]
// Output: 4
//
// One arrow needs to be shot for each balloon for a total of 4 arrows.

LEETCODE_SOLUTION_UNITTEST(452, MinimumNumberOfArrowsToBurstBalloons,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 2},
      {3, 4},
      {5, 6},
      {7, 8}
  };
  int expect = 4;
  int actual = solution->findMinArrowShots(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: points = [[1,2],[2,3],[3,4],[4,5]]
// Output: 2
//
// The balloons can be burst by 2 arrows:
// - Shoot an arrow at x = 2, bursting the balloons [1,2] and [2,3].
// - Shoot an arrow at x = 4, bursting the balloons [3,4] and [4,5].

LEETCODE_SOLUTION_UNITTEST(452, MinimumNumberOfArrowsToBurstBalloons,
                           example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 2},
      {2, 3},
      {3, 4},
      {4, 5}
  };
  int expect = 2;
  int actual = solution->findMinArrowShots(points);
  LCD_EXPECT_EQ(expect, actual);
}
