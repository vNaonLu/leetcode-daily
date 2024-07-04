// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Escape The Ghosts
//
// https://leetcode.com/problems/escape-the-ghosts/
//
// Question ID: 789
// Difficult  : Medium
// Solve Date : 2024/07/04 20:23

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |789. Escape The Ghosts|:
//
// You are playing a simplified PAC-MAN game on an infinite 2-D grid. You start
// at the point |[0, 0]|, and you are given a destination point |target =
// [x_{target}, y_{target}]| that you are trying to get to. There are several
// ghosts on the map with their starting positions given as a 2D array |ghosts|,
// where |ghosts[i] = [xᵢ, yᵢ]| represents the starting position of the |iᵗʰ|
// ghost. All inputs are integral coordinates. Each turn, you and all the ghosts
// may independently choose to either move 1 unit in any of the four cardinal
// directions: north, east, south, or west, or stay still. All actions happen
// simultaneously. You escape if and only if you can reach the target before any
// ghost reaches you. If you reach any square (including the target) at the same
// time as a ghost, it does not count as an escape. Return |true| if it is
// possible to escape regardless of how the ghosts move, otherwise return
// |false|.
//
//

LEETCODE_BEGIN_RESOLVING(789, EscapeTheGhosts, Solution);

class Solution {
public:
  bool escapeGhosts(vector<vector<int>> &ghosts, vector<int> &target) {
    int dist = abs(target[0]) + abs(target[1]);
    for (auto &x : ghosts) {
      int d = abs(target[0] - x[0]) + abs(target[1] - x[1]);
      if (d <= dist) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= ghosts.length <= 100|
// * |ghosts[i].length == 2|
// * |-10⁴ <= xᵢ, yᵢ <= 10⁴|
// * There can be multiple ghosts in the same location.
// * |target.length == 2|
// * |-10⁴ <= x_{target}, y_{target} <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ghosts = [[1,0],[0,3]], target = [0,1]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(789, EscapeTheGhosts, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> ghosts   = {
      {1, 0},
      {0, 3}
  };
  vector<int> target = {0, 1};
  bool        expect = true;
  bool        actual = solution->escapeGhosts(ghosts, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: ghosts = [[1,0]], target = [2,0]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(789, EscapeTheGhosts, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> ghosts   = {
      {1, 0}
  };
  vector<int> target = {2, 0};
  bool        expect = false;
  bool        actual = solution->escapeGhosts(ghosts, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: ghosts = [[2,0]], target = [1,0]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(789, EscapeTheGhosts, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> ghosts   = {
      {2, 0}
  };
  vector<int> target = {1, 0};
  bool        expect = false;
  bool        actual = solution->escapeGhosts(ghosts, target);
  LCD_EXPECT_EQ(expect, actual);
}
