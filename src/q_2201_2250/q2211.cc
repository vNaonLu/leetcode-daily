// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Collisions on a Road
//
// https://leetcode.com/problems/count-collisions-on-a-road/
//
// Question ID: 2211
// Difficult  : Medium
// Solve Date : 2025/12/04 21:20

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2211. Count Collisions on a Road|:
//
// There are |n| cars on an infinitely long road. The cars are numbered from |0|
// to |n - 1| from left to right and each car is present at a unique point. You
// are given a 0-indexed string |directions| of length |n|. |directions[i]| can
// be either |'L'|, |'R'|, or |'S'| denoting whether the |iᵗʰ| car is moving
// towards the left, towards the right, or staying at its current point
// respectively. Each moving car has the same speed. The number of collisions
// can be calculated as follows:
//
//  • When two cars moving in opposite directions collide with each other, the
//  number of collisions increases by |2|.
//
//  • When a moving car collides with a stationary car, the number of collisions
//  increases by |1|.
// After a collision, the cars involved can no longer move and will stay at the
// point where they collided. Other than that, cars cannot change their state or
// direction of motion. Return the total number of collisions that will happen
// on the road.
//
//

LEETCODE_BEGIN_RESOLVING(2211, CountCollisionsOnARoad, Solution);

class Solution {
public:
  int countCollisions(string directions) {
    int n = directions.size();
    if (n == 1) {
      return 0;
    }

    int l = 0;
    int r = n - 1;
    while (directions[l] == 'L') {
      ++l;
    }
    while (directions[r] == 'R') {
      --r;
    }

    if (l >= r) {
      return 0;
    }

    int res = 0;

    while (l <= r) {
      while (directions[l] == 'R') {
        ++l;
        ++res;
      }

      if (directions[l] == 'L') {
        ++res;
      }

      ++l;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= directions.length <= 10⁵|
// * |directions[i]| is either |'L'|, |'R'|, or |'S'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: directions = "RLRSLL"
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(2211, CountCollisionsOnARoad, example_1) {
  auto   solution   = MakeSolution();
  string directions = "RLRSLL";
  int    expect     = 5;
  int    actual     = solution->countCollisions(directions);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: directions = "LLRR"
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2211, CountCollisionsOnARoad, example_2) {
  auto   solution   = MakeSolution();
  string directions = "LLRR";
  int    expect     = 0;
  int    actual     = solution->countCollisions(directions);
  LCD_EXPECT_EQ(expect, actual);
}
