// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Maximum Walls Destroyed by Robots
//
// https://leetcode.com/problems/maximum-walls-destroyed-by-robots/
//
// Question ID: 3661
// Difficult  : Hard
// Solve Date : 2026/04/03 12:12

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3661. Maximum Walls Destroyed by Robots|:
//
//
// There is an endless straight line populated with some robots and walls. You
// are given integer arrays |robots|, |distance|, and |walls|:
//
//  • |robots[i]| is the position of the |iᵗʰ| robot.
//
//  • |distance[i]| is the maximum distance the |iᵗʰ| robot's bullet can travel.
//
//  • |walls[j]| is the position of the |jᵗʰ| wall.
// Every robot has one bullet that can either fire to the left or the right at
// most |distance[i]| meters. A bullet destroys every wall in its path that lies
// within its range. Robots are fixed obstacles: if a bullet hits another robot
// before reaching a wall, it immediately stops at that robot and cannot
// continue. Return the maximum number of unique walls that can be destroyed by
// the robots. Notes:
//
//  • A wall and a robot may share the same position; the wall can be destroyed
//  by the robot at that position.
//
//  • Robots are not destroyed by bullets.
//
//

LEETCODE_BEGIN_RESOLVING(3661, MaximumWallsDestroyedByRobots, Solution);

class Solution {
public:
  int maxWalls(vector<int> &robots, vector<int> &d, vector<int> &walls) {
    int n = robots.size();

    vector<array<int, 2>> x(n);
    for (int i = 0; i < n; i++) {
      x[i] = {robots[i], d[i]};
    }

    sort(x.begin(), x.end());
    sort(walls.begin(), walls.end());

    x.push_back({(int)1e9, 0});

    auto query = [&](int l, int r) -> int {
      if (l > r)
        return 0;
      auto it1 = upper_bound(walls.begin(), walls.end(), r);
      auto it2 = lower_bound(walls.begin(), walls.end(), l);
      return it1 - it2;
    };

    vector<array<int, 2>> dp(n);

    dp[0][0] = query(x[0][0] - x[0][1], x[0][0]);

    if (n > 1) {
      dp[0][1] = query(x[0][0], min(x[1][0] - 1, x[0][0] + x[0][1]));
    } else {
      dp[0][1] = query(x[0][0], x[0][0] + x[0][1]);
    }

    for (int i = 1; i < n; i++) {

      dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]) +
                 query(x[i][0], min(x[i + 1][0] - 1, x[i][0] + x[i][1]));

      dp[i][0] = dp[i - 1][0] +
                 query(max(x[i][0] - x[i][1], x[i - 1][0] + 1), x[i][0]);

      int leftStart = max(x[i][0] - x[i][1], x[i - 1][0] + 1);
      int leftEnd   = x[i][0];

      int overlapStart = leftStart;
      int overlapEnd   = min(x[i - 1][0] + x[i - 1][1], x[i][0] - 1);

      int res = dp[i - 1][1] + query(leftStart, leftEnd) -
                query(overlapStart, overlapEnd);

      dp[i][0] = max(dp[i][0], res);
    }

    return max(dp[n - 1][0], dp[n - 1][1]);
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= robots.length == distance.length <= 10⁵|
// * |1 <= walls.length <= 10⁵|
// * |1 <= robots[i], walls[j] <= 10⁹|
// * |1 <= distance[i] <= 10⁵|
// * All values in |robots| are unique
// * All values in |walls| are unique
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: robots = [4], distance = [3], walls = [1,10]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3661, MaximumWallsDestroyedByRobots, example_1) {
  auto        solution = MakeSolution();
  vector<int> robots   = {4};
  vector<int> distance = {3};
  vector<int> walls    = {1, 10};
  int         expect   = 1;
  int         actual   = solution->maxWalls(robots, distance, walls);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: robots = [10,2], distance = [5,1], walls = [5,2,7]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3661, MaximumWallsDestroyedByRobots, example_2) {
  auto        solution = MakeSolution();
  vector<int> robots   = {10, 2};
  vector<int> distance = {5, 1};
  vector<int> walls    = {5, 2, 7};
  int         expect   = 3;
  int         actual   = solution->maxWalls(robots, distance, walls);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: robots = [1,2], distance = [100,1], walls = [10]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3661, MaximumWallsDestroyedByRobots, example_3) {
  auto        solution = MakeSolution();
  vector<int> robots   = {1, 2};
  vector<int> distance = {100, 1};
  vector<int> walls    = {10};
  int         expect   = 0;
  int         actual   = solution->maxWalls(robots, distance, walls);
  LCD_EXPECT_EQ(expect, actual);
}
