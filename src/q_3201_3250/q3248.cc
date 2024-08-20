// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Snake in Matrix
//
// https://leetcode.com/problems/snake-in-matrix/
//
// Question ID: 3248
// Difficult  : Easy
// Solve Date : 2024/08/13 21:22

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3248. Snake in Matrix|:
//
// There is a snake in an |n x n| matrix |grid| and can move in four possible
// directions. Each cell in the |grid| is identified by the position:
// |grid[i][j] = (i * n) + j|. The snake starts at cell 0 and follows a sequence
// of commands. You are given an integer |n| representing the size of the |grid|
// and an array of strings |commands| where each |command[i]| is either |"UP"|,
// |"RIGHT"|, |"DOWN"|, and |"LEFT"|. It's guaranteed that the snake will remain
// within the |grid| boundaries throughout its movement. Return the position of
// the final cell where the snake ends up after executing |commands|.
//
//

LEETCODE_BEGIN_RESOLVING(3248, SnakeInMatrix, Solution);

class Solution {
public:
  int finalPositionOfSnake(int n, vector<string> &commands) {
    int res = 0;
    for (auto &s : commands) {
      if (s == "UP") {
        res -= n;
      } else if (s == "DOWN") {
        res += n;
      } else if (s == "LEFT") {
        res -= 1;
      } else if (s == "RIGHT") {
        res += 1;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10|
// * |1 <= commands.length <= 100|
// * |commands| consists only of |"UP"|, |"RIGHT"|, |"DOWN"|, and |"LEFT"|.
// * The input is generated such the snake will not move outside of the
// boundaries.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2, commands = ["RIGHT","DOWN"]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3248, SnakeInMatrix, example_1) {
  auto           solution = MakeSolution();
  int            n        = 2;
  vector<string> commands = {"RIGHT", "DOWN"};
  int            expect   = 3;
  int            actual   = solution->finalPositionOfSnake(n, commands);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, commands = ["DOWN","RIGHT","UP"]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3248, SnakeInMatrix, example_2) {
  auto           solution = MakeSolution();
  int            n        = 3;
  vector<string> commands = {"DOWN", "RIGHT", "UP"};
  int            expect   = 1;
  int            actual   = solution->finalPositionOfSnake(n, commands);
  LCD_EXPECT_EQ(expect, actual);
}
