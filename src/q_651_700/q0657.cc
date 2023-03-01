// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Robot Return to Origin
//
// https://leetcode.com/problems/robot-return-to-origin/
//
// Question ID: 657
// Difficult  : Easy
// Solve Date : 2022/11/24 10:40

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |657. Robot Return to Origin|:
//
// There is a robot starting at the position |(0, 0)|, the origin, on a 2D
// plane. Given a sequence of its moves, judge if this robot ends up at |(0, 0)|
// after it completes its moves. You are given a string |moves| that represents
// the move sequence of the robot where |moves[i]| represents its |iᵗʰ| move.
// Valid moves are |'R'| (right), |'L'| (left), |'U'| (up), and |'D'| (down).
// Return |true| if the robot returns to the origin after it finishes all of its
// moves, or |false| otherwise. Note: The way that the robot is "facing" is
// irrelevant. |'R'| will always make the robot move to the right once, |'L'|
// will always make it move left, etc. Also, assume that the magnitude of the
// robot's movement is the same for each move.
//

LEETCODE_BEGIN_RESOLVING(657, RobotReturnToOrigin, Solution);

class Solution {
public:
  bool judgeCircle(string moves) {
    auto forward = vector<int>(4, 0);
    for (auto c : moves) {
      switch (c) {
      case 'U':
        ++forward[0];
        break;
      case 'D':
        ++forward[1];
        break;
      case 'L':
        ++forward[2];
        break;
      case 'R':
        ++forward[3];
        break;
      default:
        break;
      }
    }
    return forward[0] == forward[1] && forward[2] == forward[3];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= moves.length <= 2 * 10⁴|
// * |moves| only contains the characters |'U'|, |'D'|, |'L'| and |'R'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: moves = "UD"
// Output: true
//
// : The robot moves up once, and then down once. All moves have the same
// magnitude, so it ended up at the origin where it started. Therefore, we
// return true.

LEETCODE_SOLUTION_UNITTEST(657, RobotReturnToOrigin, example_1) {
  auto   solution = MakeSolution();
  string moves    = "UD";
  bool   expect   = true;
  bool   actual   = solution->judgeCircle(moves);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: moves = "LL"
// Output: false
//
// : The robot moves left twice. It ends up two "moves" to the left of the
// origin. We return false because it is not at the origin at the end of its
// moves.

LEETCODE_SOLUTION_UNITTEST(657, RobotReturnToOrigin, example_2) {
  auto   solution = MakeSolution();
  string moves    = "LL";
  bool   expect   = false;
  bool   actual   = solution->judgeCircle(moves);
  LCD_EXPECT_EQ(expect, actual);
}
