// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Robot Bounded In Circle
//
// https://leetcode.com/problems/robot-bounded-in-circle/
//
// Question ID: 1041
// Difficult  : Medium
// Solve Date : 2022/01/09 14:29

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1041. Robot Bounded In Circle|:
//
// On an infinite plane, a robot initially stands at |(0, 0)| and faces north.
// Note that:
//
//  • The north direction is the positive direction of the y-axis.
//
//  • The south direction is the negative direction of the y-axis.
//
//  • The east direction is the positive direction of the x-axis.
//
//  • The west direction is the negative direction of the x-axis.
// The robot can receive one of three instructions:
//
//  • |"G"|: go straight 1 unit.
//
//  • |"L"|: turn 90 degrees to the left (i.e., anti-clockwise direction).
//
//  • |"R"|: turn 90 degrees to the right (i.e., clockwise direction).
// The robot performs the |instructions| given in order, and repeats them
// forever. Return |true| if and only if there exists a circle in the plane such
// that the robot never leaves the circle.  
//

LEETCODE_BEGIN_RESOLVING(1041, RobotBoundedInCircle, Solution);

class Solution {
private:
  bool isOrigin(int x, int y) { return x == 0 && y == 0; }

public:
  bool isRobotBounded(string instructions) {
    char current_dir = 'N';
    int  x = 0, y = 0;
    for (const auto &instruct : instructions) {
      if (instruct == 'G') {
        switch (current_dir) {
        case 'N':
          y += 1;
          break;
        case 'W':
          x += 1;
          break;
        case 'S':
          y -= 1;
          break;
        case 'E':
          x -= 1;
          break;
        default:
          break;
        }
      } else {
        switch (current_dir) {
        case 'N':
          current_dir = instruct == 'L' ? 'W' : 'E';
          break;
        case 'W':
          current_dir = instruct == 'L' ? 'S' : 'N';
          break;
        case 'S':
          current_dir = instruct == 'L' ? 'E' : 'W';
          break;
        case 'E':
          current_dir = instruct == 'L' ? 'N' : 'S';
          break;
        default:
          break;
        }
      }
    }
    return isOrigin(x, y) || current_dir != 'N';
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= instructions.length <= 100|
// * |instructions[i]| is |'G'|, |'L'| or, |'R'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: instructions = "GGLLGG"
// Output: true
//
// The robot is initially at (0, 0) facing the north direction.
// "G": move one step. Position: (0, 1). Direction: North.
// "G": move one step. Position: (0, 2). Direction: North.
// "L": turn 90 degrees anti-clockwise. Position: (0, 2). Direction: West.
// "L": turn 90 degrees anti-clockwise. Position: (0, 2). Direction: South.
// "G": move one step. Position: (0, 1). Direction: South.
// "G": move one step. Position: (0, 0). Direction: South.
// Repeating the instructions, the robot goes into the cycle: (0, 0) --> (0, 1)
// --> (0, 2) --> (0, 1) --> (0, 0). Based on that, we return true.

LEETCODE_SOLUTION_UNITTEST(1041, RobotBoundedInCircle, example_1) {
  auto   solution     = MakeSolution();
  string instructions = "GGLLGG";
  bool   expect       = true;
  bool   actual       = solution->isRobotBounded(instructions);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: instructions = "GG"
// Output: false
//
// The robot is initially at (0, 0) facing the north direction.
// "G": move one step. Position: (0, 1). Direction: North.
// "G": move one step. Position: (0, 2). Direction: North.
// Repeating the instructions, keeps advancing in the north direction and does
// not go into cycles. Based on that, we return false.

LEETCODE_SOLUTION_UNITTEST(1041, RobotBoundedInCircle, example_2) {
  auto   solution     = MakeSolution();
  string instructions = "GG";
  bool   expect       = false;
  bool   actual       = solution->isRobotBounded(instructions);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: instructions = "GL"
// Output: true
//
// The robot is initially at (0, 0) facing the north direction.
// "G": move one step. Position: (0, 1). Direction: North.
// "L": turn 90 degrees anti-clockwise. Position: (0, 1). Direction: West.
// "G": move one step. Position: (-1, 1). Direction: West.
// "L": turn 90 degrees anti-clockwise. Position: (-1, 1). Direction: South.
// "G": move one step. Position: (-1, 0). Direction: South.
// "L": turn 90 degrees anti-clockwise. Position: (-1, 0). Direction: East.
// "G": move one step. Position: (0, 0). Direction: East.
// "L": turn 90 degrees anti-clockwise. Position: (0, 0). Direction: North.
// Repeating the instructions, the robot goes into the cycle: (0, 0) --> (0, 1)
// --> (-1, 1) --> (-1, 0) --> (0, 0). Based on that, we return true.

LEETCODE_SOLUTION_UNITTEST(1041, RobotBoundedInCircle, example_3) {
  auto   solution     = MakeSolution();
  string instructions = "GL";
  bool   expect       = true;
  bool   actual       = solution->isRobotBounded(instructions);
  LCD_EXPECT_EQ(expect, actual);
}
