// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Robot Collisions
//
// https://leetcode.com/problems/robot-collisions/
//
// Question ID: 2751
// Difficult  : Hard
// Solve Date : 2024/07/13 13:31

#include <algorithm>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2751. Robot Collisions|:
//
// There are |n| 1-indexed robots, each having a position on a line, health, and
// movement direction. You are given 0-indexed integer arrays |positions|,
// |healths|, and a string |directions| ( |directions[i]| is either 'L' for left
// or 'R' for right). All integers in |positions| are unique. All robots start
// moving on the line simultaneously at the same speed in their given
// directions. If two robots ever share the same position while moving, they
// will collide. If two robots collide, the robot with lower health is removed
// from the line, and the health of the other robot decreases by one. The
// surviving robot continues in the same direction it was going. If both robots
// have the same health, they are both removed from the line. Your task is to
// determine the health of the robots that survive the collisions, in the same
// order that the robots were given, i.e. final heath of robot 1 (if survived),
// final health of robot 2 (if survived), and so on. If there are no survivors,
// return an empty array. Return an array containing the health of the remaining
// robots (in the order they were given in the input), after no further
// collisions can occur. Note: The positions may be unsorted.
//
//
//

LEETCODE_BEGIN_RESOLVING(2751, RobotCollisions, Solution);

class Solution {
public:
  vector<int> survivedRobotsHealths(vector<int> &positions,
                                    vector<int> &healths, string directions) {
    int                    n = positions.size();
    vector<pair<int, int>> robot(n);
    for (int i = 0; i < n; ++i) {
      robot[i] = {positions[i], i};
    }
    sort(robot.begin(), robot.end(), greater<>());

    vector<int> stk;
    for (auto &[pos, i] : robot) {
      if (directions[i] == 'L') {
        stk.emplace_back(i);
      } else {
        while (!stk.empty() && healths[i] > 0) {
          int j = stk.back();
          int x = healths[j] - healths[i];
          if (x > 0) {
            --healths[j];
            healths[i] = 0;
          } else if (x < 0) {
            --healths[i];
            healths[j] = 0;
            stk.pop_back();
          } else {
            healths[i] = 0;
            healths[j] = 0;
            stk.pop_back();
          }
        }
      }
    }

    vector<int> res;
    for (auto x : healths) {
      if (x > 0) {
        res.emplace_back(x);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= positions.length == healths.length == directions.length == n <= 10⁵|
// * |1 <= positions[i], healths[i] <= 10⁹|
// * |directions[i] == 'L'| or |directions[i] == 'R'|
// * All values in |positions| are distinct
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: positions = [5,4,3,2,1], healths = [2,17,9,15,10], directions =
//  "RRRRR"
// Output: [2,17,9,15,10]
//

LEETCODE_SOLUTION_UNITTEST(2751, RobotCollisions, example_1) {
  auto        solution   = MakeSolution();
  vector<int> positions  = {5, 4, 3, 2, 1};
  vector<int> healths    = {2, 17, 9, 15, 10};
  string      directions = "RRRRR";
  vector<int> expect     = {2, 17, 9, 15, 10};
  vector<int> actual =
      solution->survivedRobotsHealths(positions, healths, directions);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: positions = [3,5,2,6], healths = [10,10,15,12], directions = "RLRL"
// Output: [14]
//

LEETCODE_SOLUTION_UNITTEST(2751, RobotCollisions, example_2) {
  auto        solution   = MakeSolution();
  vector<int> positions  = {3, 5, 2, 6};
  vector<int> healths    = {10, 10, 15, 12};
  string      directions = "RLRL";
  vector<int> expect     = {14};
  vector<int> actual =
      solution->survivedRobotsHealths(positions, healths, directions);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: positions = [1,2,5,6], healths = [10,10,11,11], directions = "RLRL"
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(2751, RobotCollisions, example_3) {
  auto        solution   = MakeSolution();
  vector<int> positions  = {1, 2, 5, 6};
  vector<int> healths    = {10, 10, 11, 11};
  string      directions = "RLRL";
  vector<int> expect     = {};
  vector<int> actual =
      solution->survivedRobotsHealths(positions, healths, directions);
  LCD_EXPECT_EQ(expect, actual);
}
