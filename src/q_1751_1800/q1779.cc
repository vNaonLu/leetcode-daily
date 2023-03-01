// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Nearest Point That Has the Same X or Y Coordinate
//
// https://leetcode.com/problems/find-nearest-point-that-has-the-same-x-or-y-coordinate/
//
// Question ID: 1779
// Difficult  : Easy
// Solve Date : 2022/04/16 10:53

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1779. Find Nearest Point That Has the Same X or Y
// Coordinate|:
//
// You are given two integers, |x| and |y|, which represent your current
// location on a Cartesian grid: |(x, y)|. You are also given an array |points|
// where each |points[i] = [aᵢ, bᵢ]| represents that a point exists at |(aᵢ,
// bᵢ)|. A point is valid if it shares the same x-coordinate or the same
// y-coordinate as your location. Return the index (0-indexed) of the valid
// point with the smallest Manhattan distance from your current location. If
// there are multiple, return the valid point with the smallest index. If there
// are no valid points, return |-1|. The Manhattan distance between two points
// |(x₁, y₁)| and |(x₂, y₂)| is |abs(x₁ - x₂) + abs(y₁ - y₂)|.  
//

LEETCODE_BEGIN_RESOLVING(1779, FindNearestPointThatHasTheSameXOrYCoordinate,
                         Solution);

class Solution {
public:
  int nearestValidPoint(int x, int y, vector<vector<int>> &points) {
    int dist = numeric_limits<int>::max(), res = -1;

    for (int i = 0; i < points.size(); ++i) {
      auto &v              = points[i];
      int   manhattan_dist = abs(x - v[0]) + abs(y - v[1]);
      if ((v[0] == x || v[1] == y) && manhattan_dist < dist) {
        dist = manhattan_dist;
        res  = i;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= points.length <= 10⁴|
// * |points[i].length == 2|
// * |1 <= x, y, aᵢ, bᵢ <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: x = 3, y = 4, points = [[1,2],[3,1],[2,4],[2,3],[4,4]]
// Output: 2
//
// Of all the points, only [3,1], [2,4] and [4,4] are valid. Of the valid
// points, [2,4] and [4,4] have the smallest Manhattan distance from your
// current location, with a distance of 1. [2,4] has the smallest index, so
// return 2.

LEETCODE_SOLUTION_UNITTEST(1779, FindNearestPointThatHasTheSameXOrYCoordinate,
                           example_1) {
  auto                solution = MakeSolution();
  int                 x        = 3;
  int                 y        = 4;
  vector<vector<int>> points   = {
      {1, 2},
      {3, 1},
      {2, 4},
      {2, 3},
      {4, 4}
  };
  int expect = 2;
  int actual = solution->nearestValidPoint(x, y, points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: x = 3, y = 4, points = [[3,4]]
// Output: 0
//
// The answer is allowed to be on the same location as your current location.

LEETCODE_SOLUTION_UNITTEST(1779, FindNearestPointThatHasTheSameXOrYCoordinate,
                           example_2) {
  auto                solution = MakeSolution();
  int                 x        = 3;
  int                 y        = 4;
  vector<vector<int>> points   = {
      {3, 4}
  };
  int expect = 0;
  int actual = solution->nearestValidPoint(x, y, points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: x = 3, y = 4, points = [[2,3]]
// Output: -1
//
// There are no valid points.

LEETCODE_SOLUTION_UNITTEST(1779, FindNearestPointThatHasTheSameXOrYCoordinate,
                           example_3) {
  auto                solution = MakeSolution();
  int                 x        = 3;
  int                 y        = 4;
  vector<vector<int>> points   = {
      {2, 3}
  };
  int expect = -1;
  int actual = solution->nearestValidPoint(x, y, points);
  LCD_EXPECT_EQ(expect, actual);
}
