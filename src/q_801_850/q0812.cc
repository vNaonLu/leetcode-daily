// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Largest Triangle Area
//
// https://leetcode.com/problems/largest-triangle-area/
//
// Question ID: 812
// Difficult  : Easy
// Solve Date : 2022/11/22 18:04

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |812. Largest Triangle Area|:
//
// Given an array of points on the X-Y plane |points| where |points[i] = [xᵢ,
// yᵢ]|, return the area of the largest triangle that can be formed by any three
// different points. Answers within |10⁻⁵| of the actual answer will be
// accepted.
//

LEETCODE_BEGIN_RESOLVING(812, LargestTriangleArea, Solution);

class Solution {
public:
  double largestTriangleArea(vector<vector<int>> &points) {
    auto res = (double)0;
    for (auto &i : points)
      for (auto &j : points)
        for (auto &k : points)
          res = max(res, 0.5 * abs(i[0] * j[1] + j[0] * k[1] + k[0] * i[1] -
                                   j[0] * i[1] - k[0] * j[1] - i[0] * k[1]));
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= points.length <= 50|
// * |-50 <= xᵢ, yᵢ <= 50|
// * All the given points are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
// Output: 2.00000
//
// The five points are shown in the above figure. The red triangle is the
// largest.

LEETCODE_SOLUTION_UNITTEST(812, LargestTriangleArea, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {0, 0},
      {0, 1},
      {1, 0},
      {0, 2},
      {2, 0}
  };
  double expect = 2.00000;
  double actual = solution->largestTriangleArea(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: points = [[1,0],[0,0],[0,1]]
// Output: 0.50000
//

LEETCODE_SOLUTION_UNITTEST(812, LargestTriangleArea, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 0},
      {0, 0},
      {0, 1}
  };
  double expect = 0.50000;
  double actual = solution->largestTriangleArea(points);
  LCD_EXPECT_EQ(expect, actual);
}
