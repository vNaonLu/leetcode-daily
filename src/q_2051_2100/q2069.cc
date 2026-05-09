// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Walking Robot Simulation II
//
// https://leetcode.com/problems/walking-robot-simulation-ii/
//
// Question ID: 2069
// Difficult  : Medium
// Solve Date : 2026/04/07 19:44

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2069. Walking Robot Simulation II|:
//
// A |width x height| grid is on an XY-plane with the bottom-left cell at |(0,
// 0)| and the top-right cell at |(width - 1, height - 1)|. The grid is aligned
// with the four cardinal directions ( |"North"|, |"East"|, |"South"|, and
// |"West"|). A robot is initially at cell |(0, 0)| facing direction |"East"|.
// The robot can be instructed to move for a specific number of steps. For each
// step, it does the following.
//
//  1. Attempts to move forward one cell in the direction it is facing.
//
//  2. If the cell the robot is moving to is out of bounds, the robot instead
//  turns 90 degrees counterclockwise and retries the step.
// After the robot finishes moving the number of steps required, it stops and
// awaits the next instruction. Implement the |Robot| class:
//
//  • |Robot(int width, int height)| Initializes the |width x height| grid with
//  the robot at |(0, 0)| facing |"East"|.
//
//  • |void step(int num)| Instructs the robot to move forward |num| steps.
//
//  • |int[] getPos()| Returns the current cell the robot is at, as an array of
//  length 2, |[x, y]|.
//
//  • |String getDir()| Returns the current direction of the robot, |"North"|,
//  |"East"|, |"South"|, or |"West"|.
//
//

LEETCODE_BEGIN_RESOLVING(2069, WalkingRobotSimulationII, Robot);

class Robot {
public:
  int w, h;
  int x = 0, y = 0;
  int dir = 0; // 0=East,1=North,2=West,3=South
  int per;

  Robot(int width, int height) {
    w   = width;
    h   = height;
    per = 2 * (w + h) - 4;
  }

  void step(int num) {
    if (per == 0)
      return;

    num %= per;

    // special case
    if (num == 0 && (x != 0 || y != 0))
      return;
    if (num == 0 && x == 0 && y == 0) {
      dir = 3; // South
      return;
    }

    while (num > 0) {
      if (dir == 0) { // East
        int move = min(num, w - 1 - x);
        x += move;
        num -= move;
        if (num > 0)
          dir = 1;
      } else if (dir == 1) { // North
        int move = min(num, h - 1 - y);
        y += move;
        num -= move;
        if (num > 0)
          dir = 2;
      } else if (dir == 2) { // West
        int move = min(num, x);
        x -= move;
        num -= move;
        if (num > 0)
          dir = 3;
      } else { // South
        int move = min(num, y);
        y -= move;
        num -= move;
        if (num > 0)
          dir = 0;
      }
    }
  }

  vector<int> getPos() { return {x, y}; }

  string getDir() {
    if (dir == 0)
      return "East";
    if (dir == 1)
      return "North";
    if (dir == 2)
      return "West";
    return "South";
  }
};

LEETCODE_END_RESOLVING(Robot);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= width, height <= 100|
// * |1 <= num <= 10⁵|
// * At most |10⁴| calls in total will be made to |step|, |getPos|, and
// |getDir|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["Robot", "step", "step", "getPos", "getDir", "step", "step", "step",
//  "getPos", "getDir"]
// [[6, 3], [2], [2], [], [], [2], [1], [4], [], []]
// Output: [null, null, null, [4, 0], "East", null, null, null, [1, 2], "West"]
//

LEETCODE_SOLUTION_UNITTEST(2069, WalkingRobotSimulationII, example_1) {
  int  s0_width  = 6;
  int  s0_height = 3;
  auto robot     = MakeRobot(s0_width, s0_height);
  int  s1_num    = 2;
  robot->step(s1_num);
  int s2_num = 2;
  robot->step(s2_num);
  vector<int> s3_expect = {4, 0};
  vector<int> s3_actual = robot->getPos();
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  string s4_expect = "East";
  string s4_actual = robot->getDir();
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_num = 2;
  robot->step(s5_num);
  int s6_num = 1;
  robot->step(s6_num);
  int s7_num = 4;
  robot->step(s7_num);
  vector<int> s8_expect = {1, 2};
  vector<int> s8_actual = robot->getPos();
  LCD_EXPECT_EQ(s8_expect, s8_actual);
  string s9_expect = "West";
  string s9_actual = robot->getDir();
  LCD_EXPECT_EQ(s9_expect, s9_actual);
}
