// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Total Distance Traveled
//
// https://leetcode.com/problems/minimum-total-distance-traveled/
//
// Question ID: 2463
// Difficult  : Hard
// Solve Date : 2024/10/31 12:27

#include <algorithm>
#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2463. Minimum Total Distance Traveled|:
//
// There are some robots and factories on the X-axis. You are given an integer
// array |robot| where |robot[i]| is the position of the |iᵗʰ| robot. You are
// also given a 2D integer array |factory| where |factory[j] = [positionⱼ,
// limitⱼ]| indicates that |positionⱼ| is the position of the |jᵗʰ| factory and
// that the |jᵗʰ| factory can repair at most |limitⱼ| robots. The positions of
// each robot are unique. The positions of each factory are also unique. Note
// that a robot can be in the same position as a factory initially. All the
// robots are initially broken; they keep moving in one direction. The direction
// could be the negative or the positive direction of the X-axis. When a robot
// reaches a factory that did not reach its limit, the factory repairs the
// robot, and it stops moving. At any moment, you can set the initial direction
// of moving for some robot. Your target is to minimize the total distance
// traveled by all the robots. Return the minimum total distance traveled by all
// the robots. The test cases are generated such that all the robots can be
// repaired. Note that
//
//  • All robots move at the same speed.
//
//  • If two robots move in the same direction, they will never collide.
//
//  • If two robots move in opposite directions and they meet at some point,
//  they do not collide. They cross each other.
//
//  • If a robot passes by a factory that reached its limits, it crosses it as
//  if it does not exist.
//
//  • If the robot moved from a position |x| to a position |y|, the distance it
//  moved is ||y - x||.
//
//

LEETCODE_BEGIN_RESOLVING(2463, MinimumTotalDistanceTraveled, Solution);

class Solution {
public:
  long long minimumTotalDistance(vector<int>         &robot,
                                 vector<vector<int>> &factory) {
    sort(robot.begin(), robot.end());
    sort(factory.begin(), factory.end());

    int                     m = robot.size();
    int                     n = factory.size();
    vector<vector<int64_t>> dp(m + 1, vector<int64_t>(n + 1));

    for (int i = 0; i < m; ++i) {
      dp[i][n] = numeric_limits<int64_t>::max();
    }

    for (int j = n - 1; j >= 0; --j) {
      int64_t                   prefix = 0;
      deque<pair<int, int64_t>> qq;
      qq.emplace_back(m, 0);

      for (int i = m - 1; i >= 0; --i) {
        prefix += abs(robot[i] - factory[j][0]);

        while (!qq.empty() && qq.front().first > i + factory[j][1]) {
          qq.pop_front();
        }

        while (!qq.empty() && qq.back().second >= dp[i][j + 1] - prefix) {
          qq.pop_back();
        }

        qq.emplace_back(i, dp[i][j + 1] - prefix);
        dp[i][j] = qq.front().second + prefix;
      }
    }

    return dp[0][0];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= robot.length, factory.length <= 100|
// * |factory[j].length == 2|
// * |-10⁹ <= robot[i], positionⱼ <= 10⁹|
// * |0 <= limitⱼ <= robot.length|
// * The input will be generated such that it is always possible to repair every
// robot.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: robot = [0,4,6], factory = [[2,2],[6,2]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2463, MinimumTotalDistanceTraveled, example_1) {
  auto                solution = MakeSolution();
  vector<int>         robot    = {0, 4, 6};
  vector<vector<int>> factory  = {
      {2, 2},
      {6, 2}
  };
  long long expect = 4;
  long long actual = solution->minimumTotalDistance(robot, factory);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: robot = [1,-1], factory = [[-2,1],[2,1]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2463, MinimumTotalDistanceTraveled, example_2) {
  auto                solution = MakeSolution();
  vector<int>         robot    = {1, -1};
  vector<vector<int>> factory  = {
      {-2, 1},
      { 2, 1}
  };
  long long expect = 2;
  long long actual = solution->minimumTotalDistance(robot, factory);
  LCD_EXPECT_EQ(expect, actual);
}
