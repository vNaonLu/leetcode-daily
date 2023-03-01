// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Time Visiting All Points
//
// https://leetcode.com/problems/minimum-time-visiting-all-points/
//
// Question ID: 1266
// Difficult  : Easy
// Solve Date : 2022/08/08 18:22

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1266. Minimum Time Visiting All Points|:
//
// On a 2D plane, there are |n| points with integer coordinates |points[i] =
// [xᵢ, yᵢ]|. Return the minimum time in seconds to visit all the points in the
// order given by |points|. You can move according to these rules:
//
//  • In |1| second, you can either:
//
//
//    • move vertically by oneunit,
//
//    • move horizontally by one unit, or
//
//    • move diagonally |sqrt(2)| units (in other words, move one unit
//    vertically then one unit horizontally in |1| second).
//
//
//
//  • You have to visit the points in the same order as they appear in the
//  array.
//
//  • You are allowed to pass through points that appear later in the order, but
//  these do not count as visits.
//

LEETCODE_BEGIN_RESOLVING(1266, MinimumTimeVisitingAllPoints, Solution);

class Solution {
public:
  int minTimeToVisitAllPoints(vector<vector<int>> &points) {
    auto res = 0;

    for (auto it = points.begin() + 1; it != points.end(); ++it) {
      res +=
          max(abs((*(it - 1))[0] - (*it)[0]), abs((*(it - 1))[1] - (*it)[1]));
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |points.length == n|
// * |1 <= n<= 100|
// * |points[i].length == 2|
// * |-1000<= points[i][0], points[i][1]<= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: points = [[1,1],[3,4],[-1,0]]
// Output: 7
//
// One optimal path is [1,1] -> [2,2] -> [3,3] -> [3,4] -> [2,3] -> [1,2] ->
// [0,1] -> [-1,0] Time from [1,1] to [3,4] = 3 seconds Time from [3,4] to
// [-1,0] = 4 seconds Total time = 7 seconds

LEETCODE_SOLUTION_UNITTEST(1266, MinimumTimeVisitingAllPoints, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      { 1, 1},
      { 3, 4},
      {-1, 0}
  };
  int expect = 7;
  int actual = solution->minTimeToVisitAllPoints(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: points = [[3,2],[-2,2]]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(1266, MinimumTimeVisitingAllPoints, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      { 3, 2},
      {-2, 2}
  };
  int expect = 5;
  int actual = solution->minTimeToVisitAllPoints(points);
  LCD_EXPECT_EQ(expect, actual);
}
