// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Widest Vertical Area Between Two Points Containing No Points
//
// https://leetcode.com/problems/widest-vertical-area-between-two-points-containing-no-points/
//
// Question ID: 1637
// Difficult  : Medium
// Solve Date : 2023/12/21 18:54

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1637. Widest Vertical Area Between Two Points Containing No
// Points|:
//
// Given |n| |points| on a 2D plane where |points[i] = [xᵢ, yᵢ]|, Return the
// widest vertical area between two points such that no points are inside the
// area. A vertical area is an area of fixed-width extending infinitely along
// the y-axis (i.e., infinite height). The widest vertical area is the one with
// the maximum width. Note that points on the edge of a vertical area are not
// considered included in the area.
//
//

LEETCODE_BEGIN_RESOLVING(1637,
                         WidestVerticalAreaBetweenTwoPointsContainingNoPoints,
                         Solution);

class Solution {
public:
  int maxWidthOfVerticalArea(vector<vector<int>> &points) {
    sort(points.begin(), points.end());

    int res = 0;
    for (int i = 1; i < points.size(); ++i) {
      res = max(res, points[i][0] - points[i - 1][0]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == points.length|
// * |2 <= n <= 10⁵|
// * |points[i].length == 2|
// * |0 <= xᵢ, yᵢ <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: points = [[8,7],[9,9],[7,4],[9,7]]
// Output: 1
//
// Both the red and the blue area are optimal.

LEETCODE_SOLUTION_UNITTEST(1637,
                           WidestVerticalAreaBetweenTwoPointsContainingNoPoints,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {8, 7},
      {9, 9},
      {7, 4},
      {9, 7}
  };
  int expect = 1;
  int actual = solution->maxWidthOfVerticalArea(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: points = [[3,1],[9,0],[1,0],[1,4],[5,3],[8,8]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1637,
                           WidestVerticalAreaBetweenTwoPointsContainingNoPoints,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {3, 1},
      {9, 0},
      {1, 0},
      {1, 4},
      {5, 3},
      {8, 8}
  };
  int expect = 3;
  int actual = solution->maxWidthOfVerticalArea(points);
  LCD_EXPECT_EQ(expect, actual);
}
